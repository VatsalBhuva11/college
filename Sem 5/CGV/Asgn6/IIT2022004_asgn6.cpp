#include <GL/glut.h>

// Function to draw a simple cube
void drawCube() {
    glBegin(GL_LINES);
    // Front face
    glVertex3f(-1.0, -1.0,  1.0);
    glVertex3f( 1.0, -1.0,  1.0);

    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f( 1.0,  1.0,  1.0);

    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f(-1.0,  1.0,  1.0);

    glVertex3f(-1.0,  1.0,  1.0);
    glVertex3f(-1.0, -1.0,  1.0);

    // Back face
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f( 1.0, -1.0, -1.0);

    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);

    glVertex3f( 1.0,  1.0, -1.0);
    glVertex3f(-1.0,  1.0, -1.0);

    glVertex3f(-1.0,  1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);

    // Connect front face to back face
    glVertex3f(-1.0, -1.0,  1.0);
    glVertex3f(-1.0, -1.0, -1.0);

    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f( 1.0, -1.0, -1.0);

    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f( 1.0,  1.0, -1.0);

    glVertex3f(-1.0,  1.0,  1.0);
    glVertex3f(-1.0,  1.0, -1.0);
    glEnd();
}

// Display function to render the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Left viewport: Orthographic projection
    glViewport(0, 0, 400, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0); // Orthographic projection
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawCube(); // Draw the cube with orthographic projection

    // Right viewport: Perspective projection
    glViewport(400, 0, 400, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 100.0); // Perspective projection
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3.0, 3.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Position the camera for perspective view
    drawCube(); // Draw the cube with perspective projection

    glFlush();
}

// Initialization function
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glEnable(GL_DEPTH_TEST);          // Enable depth testing for proper 3D rendering
}

// Main function to set up the GLUT framework
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 500);  // Set the window size
    glutCreateWindow("Orthographic and Perspective Projections Side by Side");

    init();  // Call initialization function

    glutDisplayFunc(display);  // Set display callback
    glutMainLoop();            // Enter the event-processing loop
    return 0;
}

