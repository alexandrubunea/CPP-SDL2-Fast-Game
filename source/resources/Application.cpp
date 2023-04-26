#include "../headers/Application.hpp"
#include "../headers/Core.hpp"


Application::Application(
    UINT_32 window_width,
    UINT_32 window_height,
    std::string window_name
):  WINDOW_WIDTH(window_width), 
    WINDOW_HEIGHT(window_height), 
    WINDOW_NAME(window_name) {
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

    const float delta_time = .1f;
    float current_time = Utils::hire_time_in_seconds(),
        accumulator = .0f, new_time, frame_time;

    while(WINDOW_STATUS != WINDOW_CLOSED) {
        new_time = Utils::hire_time_in_seconds();
        frame_time = new_time - current_time;
        current_time = new_time;
        accumulator += frame_time;

        while(accumulator >= delta_time) {
            __controller__(event);
            
            accumulator -= delta_time;
        }
        __render__();
    }
}

void Application::__controller__(SDL_Event& e) {
    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT)
            WINDOW_STATUS = WINDOW_CLOSED;
    }
}

void Application::__render__() {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}