#include <stdio.h>
#include <GL/glut.h>
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
    // front face
    glVertex3f(2.0, 4.0, 0.0);
    glVertex3f(8.0, 4.0, 0.0);
    glVertex3f(8.0, 10.0, 0.0);
    glVertex3f(2.0, 10.0, 0.0);
    glEnd();
    glFlush();

    // back face
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
    glVertex3f(4.0, 6.0, 0.0);
    glVertex3f(10.0, 6.0, 0.0);
    glVertex3f(10.0, 12.0, 0.0);
    glVertex3f(4.0, 12.0, 0.0);
    glEnd();
    glFlush();

    // join front and back faces
    glBegin(GL_LINES);
    glVertex3f(2.0, 4.0, 0.0);
    glVertex3f(4.0, 6.0, 0.0);

    glVertex3f(8.0, 4.0, 0.0);
    glVertex3f(10.0, 6.0, 0.0);

    glVertex3f(8.0, 10.0, 0.0);
    glVertex3f(10.0, 12.0, 0.0);

    glVertex3f(2.0, 10.0, 0.0);
    glVertex3f(4.0, 12.0, 0.0);
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cube");

    glClearColor(0.0, 0.0, 0.0, 0.0);         // black background
    glOrtho(0.0, 20.0, 0.0, 20.0, -1.0, 1.0); // setup a 10x10x2 viewing world

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}