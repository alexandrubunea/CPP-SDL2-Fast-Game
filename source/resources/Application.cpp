#include <vector>
#include <algorithm>
#include <unordered_set>

#include "../headers/Application.hpp"
#include "../headers/Core.hpp"
#include "../headers/Player.hpp"
#include "../headers/Car.hpp"
#include "../headers/Pickup.hpp"

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
        WINDOW_WIDTH - WALL_THICKNESS - (PLAYER_WIDTH * random_lane) + CAR_DISTANCE / 2,
        PLAYER_Y,
        PLAYER_WIDTH - CAR_DISTANCE,
        PLAYER_HEIGHT
    );

    speed_factor = 1.0f;

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
                    keyboard[KEY_LEFT] = true;
                    break;
                }
                case SDLK_d: {
                    keyboard[KEY_RIGHT] = true;
                    break;
                }
                case SDLK_w: {
                    keyboard[KEY_UP] = true;
                    break;
                }
                case SDLK_s: {
                    keyboard[KEY_DOWN] = true;
                    break;
                }
            }
        }
        if(e.type == SDL_KEYUP) {
            switch(e.key.keysym.sym) {
                case SDLK_a: {
                    keyboard[KEY_LEFT] = false;
                    break;
                }
                case SDLK_d: {
                    keyboard[KEY_RIGHT] = false;
                    break;
                }
                case SDLK_w: {
                    keyboard[KEY_UP] = false;
                    break;
                }
                case SDLK_s: {
                    keyboard[KEY_DOWN] = false;
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

    // Pickups
    for(Pickup pickup : pickups)
        pickup.render(renderer);

    SDL_RenderPresent(renderer);
}

void Application::__gameplay__() {
    if(keyboard[KEY_LEFT]) {
        Utils::Vector2D position = player.get_position();
        position.x -= MOVMENT_SPEED;
        if(position.x >= WALL_THICKNESS)
            player.update_position(position);
    }
    if(keyboard[KEY_RIGHT]) {
        Utils::Vector2D position = player.get_position();
        position.x += MOVMENT_SPEED;
        if(position.x + PLAYER_WIDTH - CAR_DISTANCE <= WINDOW_WIDTH - WALL_THICKNESS)
            player.update_position(position);
    }
    if(keyboard[KEY_UP]) {
        Utils::Vector2D position = player.get_position();
        position.y -= MOVMENT_SPEED;
        if(position.y >= 0)
            player.update_position(position);
    }
    if(keyboard[KEY_DOWN]) {
        Utils::Vector2D position = player.get_position();
        position.y += MOVMENT_SPEED;
        if(position.y + PLAYER_HEIGHT <= WINDOW_HEIGHT - BOTTOM_BAR_HEIGHT)
            player.update_position(position);
    }

    Utils::Vector2D position;
    for(Car &car : cars) {
        position = car.get_position();
        position.y += BASE_SPEED * speed_factor;
        car.update_position(position);
    }

    for(Pickup &pickup : pickups) {
        position = pickup.get_position();
        position.y += BASE_SPEED * speed_factor;
        pickup.update_position(position);
    }

    UINT_32 score = 
        std::count_if(cars.begin(), cars.end(), [](Car i) { return i.get_position().y >= WIN_HEIGHT; });
    player.increase_score(score);

    if(player.get_score() % 100 == 0 && player.get_score() && speed_factor < 2.0f)
        speed_factor += .1f;

    if(score)
        cars.erase(std::remove_if(cars.begin(), cars.end(),
            [](Car i) { return i.get_position().y >= WIN_HEIGHT; }), cars.end());
    
    std::unordered_set<Pickup, pickup_hash, pickup_equal> collided_pickups;
    for(Pickup &pickup : pickups) {
        if(player.collide(pickup)) {
            collided_pickups.insert(pickup);
        }
    }
    pickups.erase(std::remove_if(pickups.begin(), pickups.end(),
        [&collided_pickups](Pickup i) { return collided_pickups.find(i) != collided_pickups.end(); }), pickups.end());
    pickups.erase(std::remove_if(pickups.begin(), pickups.end(),
        [](Pickup i) { return i.get_position().y >= WIN_HEIGHT; }), pickups.end());

    for(Car &car : cars) {
        if(player.collide(car))
            car.change_color({255, 0, 0, 255});
        else
            car.change_color({255, 255, 255, 255});
    }

    for(Pickup &pickup : pickups) {
        if(player.collide(pickup))
            pickup.change_color({255, 0, 0, 255});
        else
            pickup.change_color({255, 255, 255, 255});
    }

    __spawn_cars__();
    __spawn_pickups__();
}

void Application::__spawn_cars__() {
    if(cars.size() > MAX_CARS_ON_SCREEN) return;

    UINT_32 cars_to_spawn = MAX_CARS_ON_SCREEN - cars.size(),
        random_lane, random_y;
    bool doesnt_collide = true;
    Car new_car(0, 0, 0, 0);
    std::unordered_set<UINT_32> occupied_lanes;

    for(UINT_32 i = 0; i < cars_to_spawn; ++i) {
        random_lane = Utils::random_number(1, NUMBER_OF_LANES(WINDOW_WIDTH));
        random_y = Utils::random_number(PLAYER_HEIGHT, PLAYER_HEIGHT * 10);
        doesnt_collide = true;

        new_car = Car(
            WINDOW_WIDTH - WALL_THICKNESS - (PLAYER_WIDTH * random_lane) + CAR_DISTANCE / 2,
            -(float) random_y,
            PLAYER_WIDTH - CAR_DISTANCE,
            PLAYER_HEIGHT
        );

        for(Car car : cars) {
            if(new_car.collide(car)) {
                doesnt_collide = false;
                break;
            }
        }

        if(occupied_lanes.find(random_lane) == occupied_lanes.end() && doesnt_collide) {
            occupied_lanes.insert(random_lane);
            cars.push_back(new_car);
        }
    }
}

void Application::__spawn_pickups__() {
    if(pickups.size() > MAX_PICKUPS_ON_SCREEN) return;

    UINT_32 pickups_to_spawn = MAX_PICKUPS_ON_SCREEN - pickups.size(),
        random_x, random_y;
    std::unordered_set<std::pair<UINT_32, UINT_32>, Utils::pair_hash> occupied_positions;

    for(UINT_32 i = 0; i < pickups_to_spawn;) {
        random_x = Utils::random_number(WALL_THICKNESS, WINDOW_WIDTH - WALL_THICKNESS - PICK_UP_WIDTH);
        random_y = Utils::random_number(-100, 0);
        if(
            occupied_positions.find({random_x, random_y}) == occupied_positions.end() &&
            occupied_positions.find({random_x + PICK_UP_WIDTH, random_y}) == occupied_positions.end() &&
            occupied_positions.find({random_x, random_y + PICK_UP_HEIGHT}) == occupied_positions.end() &&
            occupied_positions.find({random_x + PICK_UP_WIDTH, random_y + PICK_UP_HEIGHT}) == occupied_positions.end() &&
            occupied_positions.find({random_x - PICK_UP_WIDTH, random_y}) == occupied_positions.end() &&
            occupied_positions.find({random_x, random_y - PICK_UP_HEIGHT}) == occupied_positions.end() &&
            occupied_positions.find({random_x - PICK_UP_WIDTH, random_y - PICK_UP_HEIGHT}) == occupied_positions.end() &&
            occupied_positions.find({random_x + PICK_UP_WIDTH, random_y - PICK_UP_HEIGHT}) == occupied_positions.end() &&
            occupied_positions.find({random_x - PICK_UP_WIDTH, random_y + PICK_UP_HEIGHT}) == occupied_positions.end()
            ) {
            occupied_positions.insert({random_x, random_y});
            pickups.push_back(Pickup(random_x, random_y, PICK_UP_WIDTH, PICK_UP_HEIGHT));

            if(__collide_with_cars__(pickups.back())) {
                pickups.pop_back();
                occupied_positions.erase({random_x, random_y});
                continue;
            }

            ++i;
        }
    }
}

bool Application::__collide_with_cars__(GameObject &object) {
    for(Car &car : cars) {
        if(object.collide(car))
            return true;
    }
    return false;
}