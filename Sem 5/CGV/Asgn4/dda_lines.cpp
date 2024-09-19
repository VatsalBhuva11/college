#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

int startX, startY, endX, endY;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // DDA(startX, startY, endX, endY);
}

void DDA(int x1, int y1, int x2, int y2)
{

    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = std::max(abs(dx), abs(dy));

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++)
    {
        glVertex2i(static_cast<int>(round(x)), static_cast<int>(round(y)));
        x += xInc;
        y += yInc;
    }
    glEnd();
    glFlush();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv)
{
    std::cout << "Enter the coordinates of the first point (x1 y1): ";
    std::cin >> startX >> startY;
    std::cout << "Enter the coordinates of the second point (x2 y2): ";
    std::cin >> endX >> endY;

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInit(&argc, argv);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

/*
void DDA(int x1, int y1, int x2, int y2)
{

    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = std::max(abs(dx), abs(dy));

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++)
    {
        glVertex2i(static_cast<int>(round(x)), static_cast<int>(round(y)));
        x += xInc;
        y += yInc;
    }
    glEnd();
    glFlush();
}

*/