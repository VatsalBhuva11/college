#include <GL/glut.h>
#include <math.h>

const int numBlades = 3;
float angle = 0.0f;

void rotatePoint(float &x, float &y, float angle)
{
    float rad = angle * M_PI / 180.0f; // Convert to radians
    float cosA = cos(rad);
    float sinA = sin(rad);

    float newX = x * cosA - y * sinA;
    float newY = x * sinA + y * cosA;

    x = newX;
    y = newY;
}

void drawBlade(float startAngle, float sweepAngle, float bladeAngle)
{
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    glVertex2f(0.0f, 0.0f);

    for (int i = 0; i <= 20; i++)
    {
        float theta = startAngle + (sweepAngle * i) / 20;
        float x = cos(theta) * 0.8f; // radius 0.8
        float y = sin(theta) * 0.8f;

        rotatePoint(x, y, bladeAngle);

        glVertex2f(x, y);
    }

    glEnd();
}

void drawCenterCircle(float radius)
{
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    glVertex2f(0.0f, 0.0f);

    for (int i = 0; i <= 100; i++)
    {
        float theta = 2.0f * M_PI * i / 100;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x, y);
    }

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawCenterCircle(0.2f); // Draw the central circle

    for (int i = 0; i < numBlades; i++)
    {
        float startAngle = (i * 2 * M_PI) / numBlades;
        drawBlade(startAngle, M_PI / numBlades, angle); // Apply rotation to each blade
    }

    glutSwapBuffers();
}

void update(int value)
{
    angle += 2.0f;
    if (angle > 360.0f)
    {
        angle -= 360.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Fan Animation with Matrix Rotation");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}
