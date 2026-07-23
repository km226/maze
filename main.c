#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "maze.h"

int main(int argc, char* argv[]) {
    srand(time(NULL));  // 프로그램 실행 시 매번 다른 미로 생성하도록 초기화
    generate_maze();    // 미로 생성

    // 시야 배열 안보이도록 초기화
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            visible[i][j] = HIDDEN;

    // 시작 위치 시야 열기
    update_visibility();

    // SDL 초기화 실패시
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL 초기화 실패\n");
        return 1;
    }

    // 창 생성
    SDL_Window* window = SDL_CreateWindow(
        "Maze Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        N * CELL,
        N * CELL,
        SDL_WINDOW_SHOWN
    );

    // 화면 그리기 도구 renderer 생성
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED
    );

    // 이미지 라이브러리 초기화
    IMG_Init(IMG_INIT_PNG);

    // 플레이어 이미지 로드해서 playerTexture 변수에 저장
    SDL_Texture* playerTexture = IMG_LoadTexture(renderer, "image.png");

    bool isRunning = true; // 프로그램 계속 실행
    SDL_Event event;       // 입력 이벤트 변수 event 에 저장

    while (isRunning) {
        // 이벤트 처리 (키 입력, 창 닫기)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                isRunning = false;
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w: move_player('w'); break;
                    case SDLK_s: move_player('s'); break;
                    case SDLK_a: move_player('a'); break;
                    case SDLK_d: move_player('d'); break;
                }
            }
        }

        // 도착 체크
        if (px == ex && py == ey) {
            printf("도착! 게임 종료\n");
            reveal_all(); // 지금까지 가려졌던 모든 칸을 보이도록

            // 화면을 초기화하고 다시 그려서 화면 출력
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderClear(renderer); // 이걸 안하면 이전 그림이 계속 남음

            // 미로 + 플레이어 그리기
            render_maze(renderer, playerTexture);

            // 실제 화면 출력
            SDL_RenderPresent(renderer);

            // 2초동안 화면 유지
            SDL_Delay(2000);
            break;
        }

        // 위치에 따라서 계속 반복하면서 화면 갱신
        // 화면 초기화
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);

        // 미로 + 플레이어 그리기
        render_maze(renderer, playerTexture);

        // 실제 화면 출력
        SDL_RenderPresent(renderer);

        // FPS 조절(약 60FPS)
        SDL_Delay(16);
    }

    // 메모리 해제 및 종료
    SDL_DestroyTexture(playerTexture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
