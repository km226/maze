#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>

#define N 10       // 미로 크기 (N x N)
#define CELL 75    // 한 칸의 화면 크기(픽셀 단위)
#define WALL 1     // 벽
#define ROAD 0     // 길
#define HIDDEN 0   // 시야 안보임
#define VISIBLE 1  // 시야 보임

// 전역 상태 (main.c 에서 정의, 각 소스 파일에서는 extern 으로 참조)
extern int maze[N][N];     // 미로 배열
extern int visible[N][N];  // 시야 정보

extern int px, py; // 플레이어 현재 위치 (시작점, 왼쪽 위)
extern int ex, ey; // 도착 위치 (오른쪽 아래)

// maze.c
void generate_maze(void);
void update_visibility(void);
void move_player(char cmd);
void reveal_all(void);

// render.c
void render_maze(SDL_Renderer* renderer, SDL_Texture* playerTexture);

#endif // MAZE_H
