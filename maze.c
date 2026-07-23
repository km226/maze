#include <stdlib.h>
#include "maze.h"

// 전역 변수 정의
int maze[N][N];
int visible[N][N];

int px = 0, py = 0;         // 플레이어 현재 위치 (왼쪽 위)
int ex = N - 1, ey = N - 1; // 도착 위치 (오른쪽 아래)

// 미로 생성 함수
void generate_maze(void) {
    // 모든 칸을 벽으로 초기화
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            maze[i][j] = WALL;

    int x = 0, y = 0; // 현재 위치 (시작점)
    maze[x][y] = ROAD; // 시작점은 길로 설정

    // 시작 -> 도착까지 갈 수 있는 길 만들기
    while (x != N - 1 || y != N - 1) {
        if (x == N - 1) y++;      // 맨 아래 줄이면 오른쪽으로만 이동 가능
        else if (y == N - 1) x++; // 맨 오른쪽이면 아래로만 이동 가능
        else {                     // 그 외에는 랜덤으로 이동
            if (rand() % 2) x++;  // 50% 확률로 아래, 오른쪽으로 이동
            else y++;
        }
        maze[x][y] = ROAD; // 이동한 곳은 길로 설정
    }

    // 추가로 랜덤 길 생성
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            // 처음에 다 벽으로 만들었기 때문에 25% 확률로 벽을 제거하면서 길 생성
            if (maze[i][j] == WALL && rand() % 4 == 0)
                maze[i][j] = ROAD;
}

// 시야 업데이트
void update_visibility(void) {
    int range = 1; // 플레이어 주변 1칸까지 보이도록 설정

    // 먼저 전체를 안 보이게 초기화
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            visible[i][j] = HIDDEN;

    // 플레이어 중심으로 범위 탐색
    for (int i = px - range; i <= px + range; i++) {
        for (int j = py - range; j <= py + range; j++) {
            // 배열 범위 안인지 확인
            if (i >= 0 && i < N && j >= 0 && j < N) {
                // 원형 시야
                if ((i - px) * (i - px) + (j - py) * (j - py) <= range * range)
                    visible[i][j] = VISIBLE; // 보이는 영역
            }
        }
    }
}

// 플레이어 이동 함수
void move_player(char cmd) {
    int nx = px, ny = py; // 이동할 위치를 임시로 저장

    // 입력에 따라 이동 방향 결정
    if (cmd == 'w') nx--;      // 위
    else if (cmd == 's') nx++; // 아래
    else if (cmd == 'a') ny--; // 왼
    else if (cmd == 'd') ny++; // 오
    else return;

    // 배열 범위 체크
    if (nx < 0 || nx >= N || ny < 0 || ny >= N)
        return;

    // 벽이면 이동 금지
    if (maze[nx][ny] == WALL)
        return;

    // 이동 적용
    px = nx;
    py = ny;

    // 이동 후 시야 갱신
    update_visibility();
}

// 클리어시 전체 맵을 공개하는 함수
void reveal_all(void) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            visible[i][j] = VISIBLE; // 전부 보이게 설정
}
