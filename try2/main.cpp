#include<gl/glut.h>
#include<stdio.h>

int a,b,c,d;

void myinit(){
    glClearColor(1.0,1.0,1.0,1.0);
    //glColor3f(0.0,0.0,0.0);
    //glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
        glVertex2f(a,b);
        glVertex2f(c,b);
        glVertex2f(c,d);
        glVertex2f(a,d);
    glEnd();
    glFlush();
}

int main(int argc,char ** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("try 2");

    //printf("**** Welcome to illustration of line clipping flood fill algorithm: *****\n");
    printf("Window Height : 500 width : 500\n");

    //printf("Enter Coordinates of upper-left and bottom-right vertices for required rectangle\n");
    scanf("%d%d%d%d",&a,&b,&c,&d);


    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
