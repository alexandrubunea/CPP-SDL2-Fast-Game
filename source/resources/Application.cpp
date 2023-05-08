#include <unordered_set>
#include <algorithm>
#include <thread>
#include <chrono>
#include <bitset>

#include "../headers/Application.hpp"

Application::Application(
    UINT_32 window_width,
    UINT_32 window_height,
    std::string window_name
):  WINDOW_WIDTH(window_width), 
    WINDOW_HEIGHT(window_height), 
    WINDOW_NAME(window_name) {
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) > 0) {
        Utils::print_sdl_error_message("An error occurred during SDL_Init.");
        return;
    } else Utils::print_debug_message("SDL was initialized successfully");

    // Initialize SDL_Image
    if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        Utils::print_sdl_error_message("An error occurred during IMG_Init.");
        return;
    } else Utils::print_debug_message("SDL_Image was initialized successfully.");

    // Initialize SDL_ttf
    if(TTF_Init() == -1) {
        Utils::print_ttf_error_message("An error occurred during TTF_Init.");
        return;
    } else Utils::print_debug_message("SDL_ttf was initialized successfully.");

    // Initialize SDL_CreateWindow
    window = SDL_CreateWindow(WINDOW_NAME.c_str(), 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL) {
        Utils::print_sdl_error_message("An error occured trying to create the window.");
        return;
    } else Utils::print_debug_message("Window initialized successfully.");

    // Initialize SDL_CreateRenderer
    renderer = SDL_CreateRenderer(window, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL) {
        Utils::print_sdl_error_message("An error occured trying to create the renderer.");
        return;
    } else Utils::print_debug_message("Renderer intialized sucessfully.");

    // Set the window status to running
    WINDOW_STATUS = Utils::WindowStatus::WINDOW_RUNNING;

    // Initialize the background, the walls and the bottom bar
    background_rect.x = background_rect.y = 0;
    background_rect.w = WINDOW_WIDTH;
    background_rect.h = WINDOW_HEIGHT;

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

    // Initialize the player
    __init_player__();

    // Initialize the speed factor
    speed_factor = INITIAL_GAME_SPEED;

    // Initialize the score text
    SDL_Rect score_text_rect = { 
        (INT_32) WINDOW_WIDTH / 8, 
        (INT_32) WINDOW_HEIGHT - BOTTOM_BAR_HEIGHT + 20, 
        (INT_32) WINDOW_WIDTH / 8, 
        BOTTOM_BAR_HEIGHT / 2
    };
    score_text = new GUI_Text(
        "SCORE: " + std::to_string(player.get_score()),
        "gfx/fonts/Kanit.ttf",
        30,
        { 255, 255, 255, 255 },
        score_text_rect,
        renderer
    );

    // Load the spritesheets
    __load_spritesheets__();

    // Print the debug message that the application was initialized successfully
    Utils::print_debug_message("Application initialized successfully.");

    // Start the game loop
    __loop__();
}

Application::~Application() {
    // Destroy the window and the renderer
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    IMG_Quit();

    TTF_Quit();

    if(Utils::CRASH)
        Utils::print_debug_message("Application crashed.");

    // Print the debug message that the application was destroyed successfully
    Utils::print_debug_message("Application destroyed successfully.");
}

void Application::__loop__() {
    // The SDL_Event that will be used to handle the events
    SDL_Event event;

    // The time in seconds between each frame
    const float delta_time = .01f;
    float current_time = Utils::hire_time_in_seconds(),
        accumulator = .0f, new_time, frame_time;

    // The game loop
    while(WINDOW_STATUS != Utils::WindowStatus::WINDOW_CLOSED) {

        // Calculate the time between each frame
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
    // Handle the events
    while(SDL_PollEvent(&e)) {

        // If the user closes the window, set the window status to closed
        if(e.type == SDL_QUIT) {
            WINDOW_STATUS = Utils::WindowStatus::WINDOW_CLOSED;
            Utils::print_debug_message("Window closed by the user.");
            Utils::set_crash(false);
            break;
        }
        
        // If the user presses a key, handle the key press
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
                case SDLK_ESCAPE: {
                    if(WINDOW_STATUS == Utils::WindowStatus::WINDOW_PAUSED)
                        WINDOW_STATUS = Utils::WindowStatus::WINDOW_RUNNING;
                    else if(WINDOW_STATUS == Utils::WindowStatus::WINDOW_RUNNING)
                        WINDOW_STATUS = Utils::WindowStatus::WINDOW_PAUSED;
                    break;
                }
            }
        }

        // If the user releases a key, handle the key release
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
    // Clear the renderer
    SDL_RenderClear(renderer);

    // Background
    SDL_RenderCopy(renderer, background, NULL, &background_rect);

    // Player
    player.render(renderer, cars_spritesheet);

    // Cars
    for(Car car : cars)
        car.render(renderer, cars_spritesheet);

    // Pickups
    for(Pickup pickup : pickups)
        pickup.render(renderer, pickups_spritesheet);

    /*
        If the speed factor is less than the initial game speed, 
        draw a blue filter over the screen
    */
    if(speed_factor < INITIAL_GAME_SPEED) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        SDL_Rect blue_filter;
        blue_filter.x = blue_filter.y = 0;
        blue_filter.w = WINDOW_WIDTH;
        blue_filter.h = WINDOW_HEIGHT;

        SDL_SetRenderDrawColor(renderer, 121, 245, 240, 80);
        SDL_RenderFillRect(renderer, &blue_filter);
    }

    // UI
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &bottom_bar);

    // Score
    score_text->update_text("SCORE: " + std::to_string(player.get_score()), renderer);
    score_text->render(renderer);

    // Present the renderer
    SDL_RenderPresent(renderer);
}

void Application::__gameplay__() {
    // If the window is paused, don't update the game
    if(WINDOW_STATUS == Utils::WindowStatus::WINDOW_PAUSED)
        return;

    /*
        Handle the player movment
    */
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

    /*
        Handle the cars movment
    */
    Utils::Vector2D position;
    for(Car &car : cars) {
        position = car.get_position();
        position.y += (BASE_SPEED * speed_factor) / 2;
        car.update_position(position);
    }

    /*
        Handle the pickups movment
    */
    for(Pickup &pickup : pickups) {
        position = pickup.get_position();
        position.y += (BASE_SPEED * speed_factor) / 2;
        pickup.update_position(position);
    }

    /*
        Increase the score based on the number of cars that reached the bottom of the screen
    */
    UINT_32 score = 
        std::count_if(cars.begin(), cars.end(), [](Car i) { return i.get_position().y >= WIN_HEIGHT; });
    player.increase_score(score);

    // Increase the speed factor every 100 points
    if(player.get_score() % 300 == 0 && player.get_score() && speed_factor < INITIAL_GAME_SPEED * 4)
        speed_factor += .05f;

    // Check if there are any cars that passed the bottom bar to remove them
    if(score)
        cars.erase(std::remove_if(cars.begin(), cars.end(),
            [](Car i) { return i.get_position().y >= WIN_HEIGHT; }), cars.end());
    
    /*
        Handle the collision and removal of the pickups
    */
    std::unordered_set<Pickup, pickup_hash, pickup_equal> collided_pickups;
    for(Pickup &pickup : pickups) {
        if(player.collide(pickup)) {
            collided_pickups.insert(pickup);

            switch(pickup.get_type()) {
                case Utils::PickupType::SCORE: {
                    player.increase_score(2);
                    break;
                }
                case Utils::PickupType::HEALTH: {
                    if(player.get_lives() < PLAYER_LIVES_CAP)
                        player.increase_lives();
                    else 
                        player.increase_score(2); // Give the player 5 points if the lives are already at the maximum
                    break;
                }
                case Utils::PickupType::CLEAR_ROAD: {
                    // Clear the road
                    cars.erase(cars.begin(), cars.end());
                    break;
                }
                case Utils::PickupType::SLOW_TIME: {
                    // Slow down the cars
                    if(speed_factor >= INITIAL_GAME_SPEED) {
                        std::thread slow_down(&Application::__slow_down_cars__, this);
                        slow_down.detach();
                    } else
                        player.increase_score(2); // Give the player 5 points if the speed is already at the minimum
                    break;
                }
            }
        }
    }
    pickups.erase(std::remove_if(pickups.begin(), pickups.end(),
        [&collided_pickups](Pickup i) { return collided_pickups.find(i) != collided_pickups.end(); }), pickups.end());
    pickups.erase(std::remove_if(pickups.begin(), pickups.end(),
        [](Pickup i) { return i.get_position().y >= WIN_HEIGHT; }), pickups.end());

    // Decrease the player lives if it collides with a car
    if(__collide_with_cars__(player)) {
        player.decrease_lives();
        if(!player.get_lives()) {
            // Game over
            // At the moment, the game will continue even if the player loses all of his lives
            player.increase_lives();
        }
    }

    // Spawn new cars and pickups
    __spawn_cars__();
    __spawn_pickups__();
}

void Application::__spawn_cars__() {
    // If there are already MAX_CARS_ON_SCREEN cars on the screen, don't spawn any more
    if(cars.size() > MAX_CARS_ON_SCREEN) return;

    UINT_32 cars_to_spawn = MAX_CARS_ON_SCREEN - cars.size(),
        random_lane, random_y, random_texture;
    SDL_Rect texture_rect;
    bool doesnt_collide = true;
    Car new_car(0, 0, 0, 0, {0, 0, 0, 0});
    std::unordered_set<UINT_32> occupied_lanes;

    for(UINT_32 i = 0; i < cars_to_spawn; ++i) {
        // Generate a random lane and y position
        random_lane = Utils::random_number(1, NUMBER_OF_LANES(WINDOW_WIDTH));
        random_y = Utils::random_number(PLAYER_HEIGHT, PLAYER_HEIGHT * 10);
        random_texture = Utils::random_number(0, CAR_SPRITES_NUMBER - 1);
        doesnt_collide = true;

        // Set the texture rect
        texture_rect.x = car_sprites[random_texture][0];
        texture_rect.y = car_sprites[random_texture][1];
        texture_rect.w = car_sprites[random_texture][2];
        texture_rect.h = car_sprites[random_texture][3];

        // Check if the new car collides with any of the existing cars
        new_car = Car(
            WINDOW_WIDTH - WALL_THICKNESS - (PLAYER_WIDTH * random_lane) + CAR_DISTANCE / 2,
            -(float) random_y,
            PLAYER_WIDTH - CAR_DISTANCE,
            PLAYER_HEIGHT,
            texture_rect
        );

        // Check if the new car collides with any of the existing cars
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
    // If there are already MAX_PICKUPS_ON_SCREEN pickups on the screen, don't spawn any more
    if(pickups.size() > MAX_PICKUPS_ON_SCREEN) return;

    UINT_32 pickups_to_spawn = MAX_PICKUPS_ON_SCREEN - pickups.size(),
        random_x, random_y, chance;

    SDL_Rect texture_rect;
    Utils::PickupType type;

    // Check if the new pickup collides with any of the existing pickups
    std::unordered_set<std::pair<UINT_32, UINT_32>, Utils::pair_hash> occupied_positions;

    for(UINT_32 i = 0; i < pickups_to_spawn;) {
        // Generate a random x and y position
        random_x = Utils::random_number(WALL_THICKNESS, WINDOW_WIDTH - WALL_THICKNESS - PICK_UP_WIDTH);
        random_y = Utils::random_number(-100, 0);

        /*
            Check if the new pickup collides with any of the existing pickups
            The pickup is a rectangle with the width of PICK_UP_WIDTH and the height of PICK_UP_HEIGHT
            The pickup is spawned in the top left corner of the rectangle
        */
       bool occupied = false;
       for(int dx : {-PICK_UP_WIDTH, 0, PICK_UP_WIDTH})
            for(int dy : {-PICK_UP_HEIGHT, 0, PICK_UP_HEIGHT})
                if(occupied_positions.find({random_x + dx, random_y + dy}) != occupied_positions.end())
                    occupied = true;
        if(!occupied) {

            /*
                We generate a random chance for the type
                The type is used to identify the pickup
            */
            chance = Utils::random_number(0, 100);

            if (chance < 80) {
                texture_rect = {
                    (INT_32) pickup_sprites[0][0],
                    (INT_32) pickup_sprites[0][1],
                    (INT_32) pickup_sprites[0][2],
                    (INT_32) pickup_sprites[0][3]
                };
                type = Utils::PickupType::SCORE;
            }
            else if (chance < 90) {
                texture_rect = {
                    (INT_32) pickup_sprites[2][0],
                    (INT_32) pickup_sprites[2][1],
                    (INT_32) pickup_sprites[2][2],
                    (INT_32) pickup_sprites[2][3]
                };
                type = Utils::PickupType::HEALTH;
            }
            else if (chance < 95) {
                texture_rect = {
                    (INT_32) pickup_sprites[3][0],
                    (INT_32) pickup_sprites[3][1],
                    (INT_32) pickup_sprites[3][2],
                    (INT_32) pickup_sprites[3][3]
                };
                type = Utils::PickupType::SLOW_TIME;
            }
            else {
                texture_rect = {
                    (INT_32) pickup_sprites[2][0],
                    (INT_32) pickup_sprites[2][1],
                    (INT_32) pickup_sprites[2][2],
                    (INT_32) pickup_sprites[2][3]
                };
                type = Utils::PickupType::CLEAR_ROAD;
            }

            occupied_positions.insert({random_x, random_y});
            pickups.push_back(Pickup(random_x, random_y, PICK_UP_WIDTH, PICK_UP_HEIGHT, type, texture_rect));

            // Check if the new pickup collides with any of the existing cars
            if(__collide_with_cars__(pickups.back())) {

                // If it does, remove it from the pickups vector and the occupied_positions set
                pickups.pop_back();
                occupied_positions.erase({random_x, random_y});
                continue;
            }

            // If it doesn't, increment i
            ++i;
        }
    }
}

bool Application::__collide_with_cars__(GameObject &object) {
    // Check if the object collides with any of the cars
    for(Car &car : cars) {
        if(object.collide(car))
            return true;
    }
    return false;
}

void Application::__slow_down_cars__() {
    float original_speed_factor = speed_factor;

    speed_factor = 0.5;
    std::this_thread::sleep_for(std::chrono::seconds(SLOW_TIME_DURATION));

    speed_factor = original_speed_factor;
}

void Application::__load_spritesheets__() {
    /*
        Load the spritesheet for the player
    */
    SDL_Surface *cars_surface = IMG_Load("gfx/cars.png");
    
    if(cars_surface == nullptr)
        Utils::print_sdl_image_error_message("Could not load gfx/cars.png");
    else Utils::print_debug_message("Loaded gfx/cars.png");

    cars_spritesheet = SDL_CreateTextureFromSurface(renderer, cars_surface);
    SDL_FreeSurface(cars_surface);

    /*
        Load the background texture
    */
    SDL_Surface *bg = IMG_Load("gfx/background.png");
    if(bg == nullptr)
        Utils::print_sdl_image_error_message("Could not load gfx/background.png");
    else Utils::print_debug_message("Loaded gfx/background.png");

    background = SDL_CreateTextureFromSurface(renderer, bg);
    SDL_FreeSurface(bg);

    /*
        Load the spritesheet for the pickups
    */
    SDL_Surface *pickups_surface = IMG_Load("gfx/pickups.png");
    if(pickups_surface == nullptr)
        Utils::print_sdl_image_error_message("Could not load gfx/pickups.png");
    else Utils::print_debug_message("Loaded gfx/pickups.png");

    pickups_spritesheet = SDL_CreateTextureFromSurface(renderer, pickups_surface);
    SDL_FreeSurface(pickups_surface);
}

void Application::__init_player__() {
    INT_32 random_lane = Utils::random_number(1, NUMBER_OF_LANES(WINDOW_WIDTH));
    INT_32 random_sprite = Utils::random_number(0, PLAYER_SPRITES_NUMBER - 1);

    SDL_Rect player_texture_rect = {
        (INT_32) player_sprites[random_sprite][0],
        (INT_32) player_sprites[random_sprite][1],
        (INT_32) player_sprites[random_sprite][2],
        (INT_32) player_sprites[random_sprite][3]
    };

    player = Player(
        WINDOW_WIDTH - WALL_THICKNESS - (PLAYER_WIDTH * random_lane) + CAR_DISTANCE / 2,
        PLAYER_Y,
        PLAYER_WIDTH - CAR_DISTANCE,
        PLAYER_HEIGHT,
        player_texture_rect
    );
}