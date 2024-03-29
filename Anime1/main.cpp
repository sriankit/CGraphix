#include<Gl/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

static GLfloat spin = 05.0;
int dir = 1;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);

}



void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    //glPushMatrix();
    glRotatef(spin, 0.0, 0.0, 1.0);
    glColor3f(.0, .0, 1.0);
    glRectf(-25.0, -25.0, 25.0, 25.0);
    //glPopMatrix();
    //sleep(100);
    Sleep(500);
    //glutSwapBuffers();
    //glFlush();

    glutSwapBuffers();
}

void spinDisplay(void) {
    spin = spin + dir * 8.0;
    if (spin > 360.0)
        spin = spin - 360.0;
    if(spin < 0.0)
        spin += 360.0;
    glutPostRedisplay();
}
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void mouse(int button, int state, int x, int y) {
    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) {
            dir = 1;
            glutIdleFunc(spinDisplay);
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN){
            dir = -1;
            glutIdleFunc(spinDisplay);
        }
        break;
    default:
        break;
    }
}
/*
* Request double buffer display mode.
* Register mouse input callback functions
*/
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    //OpenGL and Its Deprecation Mechanism 27
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
