#include<windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int w,h;
int xc,yc,r,ch;
void init(){
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glPointSize(1.0);
    glLoadIdentity();
    gluOrtho2D(0,w,0,h);
}

void putPixel(int x,int y) {
    glColor3f(1.0,0.0,1.0);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
}

void plot(int x,int y){

    putPixel(xc+x,yc+y);
    putPixel(xc+y,yc+x);
    putPixel(xc+x,yc-y);
    putPixel(xc-y,yc+x);
    putPixel(xc-x,yc+y);
    putPixel(xc+y,yc-x);
    putPixel(xc-x,yc-y);
    putPixel(xc-y,yc-x);
    Sleep(14);
    glFlush();
}

void midPoint(int xc,int yc,int r) {
    int x=0;
    int y=r;
    int p=1-r;
    plot(x,y);

    while(x<=y){
        x++;
        if(p<0) p+=2*x+3;
        else {
            y--;
            p+=2*(x-y)+5;
        }
        plot(x,y);
        //Sleep(50);
        //glFlush();
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    midPoint(xc,yc,r);
}

int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100,100);

    w=500;
    h=500;

    printf("Enter coordinates of center : ");
    scanf("%d%d",&xc,&yc);

    printf("Enter radius : ");
    scanf("%d",&r);

    glutCreateWindow("Mid Point Circle generation algorithm");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
