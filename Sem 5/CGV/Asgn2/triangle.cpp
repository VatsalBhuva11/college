#include <GL/glut.h>

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.5, 0.0, 0.5);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.5, 0.0, 0.0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.5, 0.0);

    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.5);
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv); // always required for all GL programs
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(600, 100);
    glutCreateWindow("Triangle Assignment");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}