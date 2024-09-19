#include <GL/freeglut.h>
#include <iostream>

int a1, b1, a2, b2;

void plotPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void Bresenham(int a1, int b1, int a2, int b2)
{
    int dx = abs(a2 - a1);
    int dy = abs(b2 - b1);
    int sx = (a1 < a2) ? 1 : -1;
    int sy = (b1 < b2) ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        plotPixel(a1, b1);
        if (a1 == a2 && b1 == b2)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            a1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            b1 += sy;
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    Bresenham(a1, b1, a2, b2);
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv)
{
    std::cout << "Enter a1, b1, a2, b2: ";
    std::cin >> a1 >> b1 >> a2 >> b2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Line Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
