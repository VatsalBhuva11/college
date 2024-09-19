#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GL/glut.h"

// Function to draw a filled circle
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

// Function to draw an oval
void drawOval(float cx, float cy, float rx, float ry, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = rx * cosf(theta);
        float y = ry * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

// Function to draw a filled arc (for the smile)
void drawArc(float cx, float cy, float r, int num_segments, float start_angle, float end_angle) {
    glBegin(GL_POLYGON);
    for (int i = 0; i <= num_segments; i++) {
        float theta = start_angle - i * (end_angle - start_angle) / num_segments;
        float x = 1.6*r * cosf(theta);
        float y = 1.1*r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Face (neon green)
    glColor3f(0.0f, 1.0f, 0.0f); 
    drawCircle(0.0f, 0.0f, 0.5f, 100);

    // Left Eye (white oval with black pupil)
    glColor3f(1.0f, 1.0f, 1.0f); 
    drawOval(-0.2f, 0.2f, 0.12f, 0.08f, 100);
    glColor3f(0.0f, 0.0f, 0.0f); 
    drawCircle(-0.2f, 0.2f, 0.05f, 100);

    // Right Eye (white oval with black pupil)
    glColor3f(1.0f, 1.0f, 1.0f); 
    drawOval(0.2f, 0.2f, 0.12f, 0.08f, 100);
    glColor3f(0.0f, 0.0f, 0.0f); 
    drawCircle(0.2f, 0.2f, 0.05f, 100);

    // Smile (red semi-circle)
    glColor3f(1.0f, 0.0f, 0.0f); 
    drawArc(0.0f, -0.1f, 0.2f, 100, 0.0f, 3.1415926f); // Semi-circle arc for the smile

    glFlush();
}

void init() {
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f); // Gray background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Smiley Face");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
