#include<windows.h>
#include <GL/glut.h>
#include<iostream>
#include <stdlib.h>

using namespace std;

int lastFrameTime,boxX = 100;
void handleKeypress(unsigned char key, int x, int y) {
    switch(key) {
    case 27:
        exit(0);
    }
}
void initRendering() {
    glEnable(GL_DEPTH_TEST);
}

void handleResize(int w,int h) {
    glViewport(0,0,w,h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluPerspective(25.0,(double)w/(double)h,1.0,200.0);
}

float _angle=0.0;
float _cameraangle=30.0;

void display(void) {
  glColor3f(0.0,1.0,0.0);
  int sign = 1;

  if (lastFrameTime == 0) {
    /*
     * sets lastFrameTime to be the number of milliseconds since
     * Init() was called;
     */
    lastFrameTime = glutGet(GLUT_ELAPSED_TIME);
  }

  int now = glutGet(GLUT_ELAPSED_TIME);
  int elapsedMilliseconds = now - lastFrameTime;
  float elapsedTime = float(elapsedMilliseconds) / 1000.0f;
  lastFrameTime = now;

  int windowWidth = glutGet(GLUT_WINDOW_WIDTH);

  if (boxX > windowWidth) {
    boxX -= windowWidth;
  }
  boxX += (sign)*256.0f * elapsedTime;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  //creates a new matrix at the top that we can do things to?
  glTranslatef(boxX, 0.0f, 0.0f);

  /*
   * draw a "quad" (rectangle)
   */
  glBegin(GL_QUADS);
  glVertex2f(0.0f, 0.0f);
  glVertex2f(128.0f, 0.0f);
  glVertex2f(128.0f, 128.0f);
  glVertex2f(0.0f, 128.0f);
  glEnd();
  glPopMatrix();
  //pops that matrix off the stack so we can have a "clean" version to do something next time.?

  glutSwapBuffers();
}
void update(int value) {
    _angle+=2.0f;
    if(_angle>360.f) {
        _angle-=360;
    }
    glutPostRedisplay();
    glutTimerFunc(25,update,0);
}

int main(int argc,char**argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(600,600);


    glutCreateWindow("rotate");
    initRendering();
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);

    glutTimerFunc(25,update,0);
//this call the function update in every 25 millsecond
//so value of angle of rotation change and object rotates continuously
    glutMainLoop();


    return 0;
}
