#pragma comment(lib, "opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>

#define PI 3.1415926535f

// 원 그리기 함수
void drawCircle(float cx, float cy, float r, int num_segments, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * PI * i / num_segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// 선 그리기 함수
void drawLine(float x1, float y1, float x2, float y2) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

// 화면 출력 함수
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 얼굴 타원 (파란색)
    drawCircle(0.0f, 0.0f, 0.8f, 100, 0.0f, 0.5f, 1.0f);

    // 눈 (검정)
    drawCircle(-0.65f, 0.2f, 0.07f, 50, 0.0f, 0.0f, 0.0f);
    drawCircle(0.65f, 0.2f, 0.07f, 50, 0.0f, 0.0f, 0.0f);

    // 볼 (흰색)
    drawCircle(-0.15f, -0.2f, 0.2f, 50, 1.0f, 1.0f, 1.0f);
    drawCircle(0.15f, -0.2f, 0.2f, 50, 1.0f, 1.0f, 1.0f);

    // 코 (검정)
    drawCircle(0.0f, -0.08f, 0.12f, 50, 0.0f, 0.0f, 0.0f);

    // 수염 왼쪽 3줄
    drawLine(-0.2f, -0.15f, -0.6f, -0.10f);
    drawLine(-0.2f, -0.2f, -0.6f, -0.2f);
    drawLine(-0.2f, -0.25f, -0.6f, -0.3f);

    // 수염 오른쪽 3줄
    drawLine(0.2f, -0.15f, 0.6f, -0.10f);
    drawLine(0.2f, -0.2f, 0.6f, -0.2f);
    drawLine(0.2f, -0.25f, 0.6f, -0.3f);

    glFlush();
}

// 초기화 함수
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 배경 흰색

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // GLU 없이 좌표계 설정

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(600, 600, "OpenGL Cat Face (No GLU)", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    init();

    while (!glfwWindowShouldClose(window)) {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
