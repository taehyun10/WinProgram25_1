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
        // ���콺 ��ġ ����
        GetCursorPos(&mousePos);

        // �ܼ� ��ǥ ���� ��������
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

        // ���콺 ��ǥ�� �ܼ� ���� ��ǥ�� ��ȯ (�ȼ� �� ����)
        int consoleX = (mousePos.x - csbi.srWindow.Left) / 10;
        int consoleY = (mousePos.y - csbi.srWindow.Top) / 29;

        // ��Ŭ�� ����
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            if (!isDragging) {
                // Ŭ�� ���� ��, �巡�� ����
                isDragging = 1;
            }

            if (isDragging) {
                // �巡�� ���̸� 'O' ��ġ�� ���콺 ��ǥ�� ����
                letterX = consoleX;
                letterY = consoleY;
            }
        }
        else {
            // Ŭ���� �������ٸ� �巡�� ����
            isDragging = 0;
        }

        // �ܼ� ���
        system("cls");
        printf("���ĺ� '%c'�� ���콺�� �巡���ϼ���.\n", letter);
        printf("���� ���ĺ� '%c'�� ��ġ: (%d, %d)\n", letter, letterX, letterY);

        // 'O' ��� ��ġ ����
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { letterX, letterY });
        printf("%c", letter);

        // ESC Ű�� ����
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            printf("\n���α׷� ����\n");
            break;
        }

        Sleep(10);  // CPU ������ ����
    }

    return 0;
}
