#include <windows.h>
#include <stdio.h>

int main() {
    char letter = 'O';
    POINT mousePos;
    int isDragging = 0;
    int letterX = 10;
    int letterY = 5;

    system("cls");

    while (1) {
        // 마우스 위치 갱신
        GetCursorPos(&mousePos);

        // 콘솔 좌표 정보 가져오기
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

        // 마우스 좌표를 콘솔 문자 좌표로 변환 (픽셀 → 문자)
        int consoleX = (mousePos.x - csbi.srWindow.Left) / 10;
        int consoleY = (mousePos.y - csbi.srWindow.Top) / 29;

        // 좌클릭 감지
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            if (!isDragging) {
                // 클릭 시작 시, 드래그 시작
                isDragging = 1;
            }

            if (isDragging) {
                // 드래그 중이면 'O' 위치를 마우스 좌표로 갱신
                letterX = consoleX;
                letterY = consoleY;
            }
        }
        else {
            // 클릭이 떨어졌다면 드래그 중지
            isDragging = 0;
        }

        // 콘솔 출력
        system("cls");
        printf("알파벳 '%c'을 마우스로 드래그하세요.\n", letter);
        printf("현재 알파벳 '%c'의 위치: (%d, %d)\n", letter, letterX, letterY);

        // 'O' 출력 위치 설정
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { letterX, letterY });
        printf("%c", letter);

        // ESC 키로 종료
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            printf("\n프로그램 종료\n");
            break;
        }

        Sleep(10);  // CPU 과부하 방지
    }

    return 0;
}
