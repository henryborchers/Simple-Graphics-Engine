//
// Created by Borchers, Henry Samuel on 1/20/17.
//

//#include "gengine.h"
#include <SDL2/SDL.h>

//static uint8_t inter_counter(uint8_t counter);

//int simple_sdl() {
//
//    SDL_Window      *window = NULL;
//    SDL_Renderer    *renderer = NULL;
//    SDL_Texture     *texture = NULL;
//
//    int             ret = 0;
//    uint8_t         counter = 0;
//
//    puts("Running simple SDL");
//
//    graphics_init();
//
//    if((ret = SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN, &window, &renderer)) != 0) {
//        return ret;
//    }
//
//    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 200, 100);
//
//    if(!texture){
//        ret = 1;
//        goto end_loop;
//    }
//
//    while(1){
//        SDL_Event e;
//
//        while(SDL_PollEvent(&e)){
//            if(e.type == SDL_QUIT){
//                puts("Quit");
//                goto end_loop;
//            }
//        }
//
//        // Fill color
//        SDL_SetRenderTarget(renderer, texture);
//        SDL_SetRenderDrawColor(renderer, 0xFF, counter, counter, counter);
//        SDL_RenderClear(renderer);
//
//        // render texture
//        SDL_SetRenderTarget(renderer, NULL);
//        SDL_RenderCopy(renderer, texture, NULL, NULL);
//        SDL_RenderPresent(renderer);
//
//        SDL_Delay(10);
//
//        counter = inter_counter(counter);
//    }
//
//    end_loop:
//    SDL_DestroyTexture(texture);
//    SDL_DestroyWindow(window);
//    SDL_DestroyRenderer(renderer);
//    SDL_Quit();
//    return ret;
//}

int graphics_init() {
    int ret;

    if ((ret = SDL_Init(SDL_INIT_EVERYTHING)) != 0) {
        return ret;
    }

    return 0;
}
//
//uint8_t inter_counter(uint8_t counter) {
//    static int direction = 1;
//    if(counter + 1 == 255){
//        direction = -1;
//    }
//    if (counter - 1 == 0){
//        direction = 1;
//    }
//
//    return (uint8_t)(counter + direction);
//}