#include<GL/glut.h>
#include<stdio.h>
#include<windows.h>

using namespace std;

int w=500,h=500;
int x=0;
void init() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0,1.0,1.0,1.0);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    gluOrtho2D(0.0, w, 0.0, h);
}

void display() {
    glClearColor(1.0,1.0,1.0,1.0);
    glTranslatef(1.0*x,1.0,0.0);

    glPushMatrix();
    glColor3f(.2,.5,0);

    //glRotatef(20.0,0.0,0.0,0.0);
    glBegin(GL_POLYGON);
        glVertex2i(100,100);
        glVertex2i(150,100);
        glVertex2i(150,150);
        glVertex2i(120,170);
    glEnd();
    glPopMatrix();
    glFlush();
    x++;
    Sleep(100);
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cart");

    init();

    glutDisplayFunc(display);
//    glutMouseFunc(mouse);
    glutMainLoop();
}
