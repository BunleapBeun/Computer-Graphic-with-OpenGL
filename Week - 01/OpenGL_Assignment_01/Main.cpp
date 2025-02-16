#include <GL/glut.h>
#include <cstdlib> // For rand()

// Window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Global variables for color and animation
float red = 1.0, green = 0.0, blue = 0.0;
float angle = 0.0;

// Draw a rectangle
void drawRectangle() {
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(-0.5, 0.5);
    glEnd();
}

// Draw a circle
void drawCircle(float radius) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159 / 180;
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();
}

// Draw a triangle
void drawTriangle() {
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.0, 0.5);
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Rotate shapes
    glRotatef(angle, 0.0, 0.0, 1.0);

    // Draw shapes with different colors
    glColor3f(red, green, blue); // Set color
    drawRectangle();

    glColor3f(1.0 - red, 1.0 - green, 1.0 - blue); // Complementary color
    drawCircle(0.3);

    glColor3f(0.0, 1.0, 0.0); // Green
    drawTriangle();

    glFlush();
    glutSwapBuffers();
}

// Mouse interaction
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Change color on left click
        red = (float)rand() / RAND_MAX;
        green = (float)rand() / RAND_MAX;
        blue = (float)rand() / RAND_MAX;
    }
    glutPostRedisplay();
}

// Timer function for animation
void update(int value) {
    angle += 2.0; // Rotate shapes
    if (angle > 360) angle -= 360;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Basic Shapes");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}