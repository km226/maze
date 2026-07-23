#include <SDL2/SDL.h>
#include "maze.h"

// 화면 렌더링 함수
void render_maze(SDL_Renderer* renderer, SDL_Texture* playerTexture) {
    // 전체 미로 반복
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // 배열 좌표를 픽셀 좌표로 변환해서 화면에 그릴 위한 계산
            SDL_Rect rect = { j * CELL, i * CELL, CELL, CELL };

            // 안 보이는 영역은 검은색으로
            if (visible[i][j] == HIDDEN) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
                continue;
            }

            // 보이는 영역
            if (i == ex && j == ey)        // 도착점(초록)
                SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
            else if (maze[i][j] == WALL)   // 벽(네이비)
                SDL_SetRenderDrawColor(renderer, 30, 30, 60, 255);
            else                            // 길(회색)
                SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);

            // 칸 채우기
            SDL_RenderFillRect(renderer, &rect);

            // 테두리 밝은 회색 그리기
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            SDL_RenderDrawRect(renderer, &rect);

            // 플레이어 위치 이미지 출력
            if (i == px && j == py) {
                SDL_RenderCopy(renderer, playerTexture, NULL, &rect);
            }
        }
    }
}
