#include <vector>
#include <algorithm>
#include <unordered_set>

#include "../headers/Application.hpp"
#include "../headers/Core.hpp"
#include "../headers/Player.hpp"
#include "../headers/Car.hpp"

Application::Application(
    UINT_32 window_width,
    UINT_32 window_height,
    std::string window_name
):  WINDOW_WIDTH(window_width), 
    WINDOW_HEIGHT(window_height), 
    WINDOW_NAME(window_name),
    player(Player(0, 0, 0, 0)) {
    if(SDL_Init(SDL_INIT_VIDEO) > 0) {
        Utils::print_sdl_error_message("An error occurred during SDL_Init.");
        return;
    } else Utils::print_debug_message("SDL was initialized successfully");

    window = SDL_CreateWindow(WINDOW_NAME.c_str(), 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL) {
        Utils::print_sdl_error_message("An error occured trying to create the window.");
        return;
    } else Utils::print_debug_message("Window initialized successfully.");

    renderer = SDL_CreateRenderer(window, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL) {
        Utils::print_sdl_error_message("An error occured trying to create the renderer.");
        return;
    } else Utils::print_debug_message("Renderer intialized sucessfully.");

    WINDOW_STATUS = WINDOW_RUNNING;

    background.x = background.y = 0;
    background.w = WINDOW_WIDTH;
    background.h = WINDOW_HEIGHT;

    left_wall.x = left_wall.y = 0;
    left_wall.h = WINDOW_HEIGHT;
    left_wall.w = WALL_THICKNESS;

    right_wall.x = WINDOW_WIDTH - WALL_THICKNESS;
    right_wall.y = 0;
    right_wall.w = WALL_THICKNESS;
    right_wall.h = WINDOW_HEIGHT;

    bottom_bar.x = 0;
    bottom_bar.y = WINDOW_HEIGHT - BOTTOM_BAR_HEIGHT;
    bottom_bar.w = WINDOW_WIDTH;
    bottom_bar.h = BOTTOM_BAR_HEIGHT;

    INT_32 random_lane = Utils::random_number(1, NUMBER_OF_LANES(WINDOW_WIDTH));

    player = Player(
        WINDOW_WIDTH - WALL_THICKNESS - (PLAYER_WIDTH * random_lane),
        PLAYER_Y,
        PLAYER_WIDTH,
        PLAYER_HEIGHT
    );

    __loop__();

    SDL_Quit();
}

Application::~Application() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Application::__loop__() {
    SDL_Event event;

    const float delta_time = .01f;
    float current_time = Utils::hire_time_in_seconds(),
        accumulator = .0f, new_time, frame_time;

    while(WINDOW_STATUS != WINDOW_CLOSED) {
        new_time = Utils::hire_time_in_seconds();
        frame_time = new_time - current_time;
        current_time = new_time;
        accumulator += frame_time;

        while(accumulator >= delta_time) {
            __controller__(event);
            __gameplay__();

            accumulator -= delta_time;
        }
        __render__();
    }
}

void Application::__controller__(SDL_Event& e) {
    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT)
            WINDOW_STATUS = WINDOW_CLOSED;
        if(e.type == SDL_KEYDOWN) {
            switch(e.key.keysym.sym) {
                case SDLK_a: {
                    Utils::Vector2D position = player.get_position();
                    position.x -= PLAYER_WIDTH;
                    if(position.x >= WALL_THICKNESS)
                        player.update_position(position);

                    break;
                }
                case SDLK_d: {
                    Utils::Vector2D position = player.get_position();
                    position.x += PLAYER_WIDTH;
                    if(position.x < WINDOW_WIDTH - WALL_THICKNESS)
                        player.update_position(position);

                    break;
                }
                case SDLK_w: {
                    Utils::Vector2D position = player.get_position();
                    position.y -= ACCELERATION;
                    if(position.y >= 0)
                        player.update_position(position);

                    break;
                }
                case SDLK_s: {
                    Utils::Vector2D position = player.get_position();
                    position.y += ACCELERATION;
                    if(position.y + PLAYER_HEIGHT <= WINDOW_HEIGHT - BOTTOM_BAR_HEIGHT)
                        player.update_position(position);

                    break;
                }
            }
        }
    }
}

void Application::__render__() {
    SDL_RenderClear(renderer);

    // Background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &background);

    // UI
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &left_wall);
    SDL_RenderFillRect(renderer, &right_wall);
    SDL_RenderFillRect(renderer, &bottom_bar);

    // Player
    player.render(renderer);

    // Cars
    for(Car car : cars)
        car.render(renderer);

    SDL_RenderPresent(renderer);
}

void Application::__gameplay__() {
    Utils::Vector2D position;
    for(Car &car : cars) {
        position = car.get_position();
        position.y += BASE_SPEED;
        car.update_position(position);
    }
    
    cars.erase(std::remove_if(cars.begin(), cars.end(),
        [](Car i) { return i.get_position().y >= WIN_HEIGHT; }), cars.end());

    __spawn_cars__();
}

void Application::__spawn_cars__() {
    if(cars.size() > MINIMUM_CARS_ON_SCREEN) return;

    UINT_32 cars_to_spawn = MINIMUM_CARS_ON_SCREEN - cars.size(),
        random_lane;
    std::unordered_set<UINT_32> occupied_lanes;

    /*
        Bug:
            All the cars are spawning on the same position dispite
        of the random_lane to have a different value all the time.
    */

    for(UINT_32 i = 0; i < cars_to_spawn; ++i) {
        random_lane = Utils::random_number(1, NUMBER_OF_LANES(WINDOW_WIDTH));
        if(occupied_lanes.find(random_lane) == occupied_lanes.end()) {
            occupied_lanes.insert(random_lane);
            cars.push_back(Car(
                WINDOW_WIDTH - WALL_THICKNESS - (PLAYER_WIDTH * random_lane),
                0,
                PLAYER_WIDTH,
                PLAYER_HEIGHT
            ));
        }
    }
}