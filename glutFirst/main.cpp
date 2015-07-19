#include<windows.h>
#include<cstdio>
#include<cmath>
#include<GL/glut.h>
#include<iostream>
using namespace std;
int w,h,a,b,c,d,dl,bl;

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,w,0,h);
}
int roundP(double number) {
    return (number>=0)?(int)(number+0.5):(int)(number-0.5);
}
void setPixel(int x,int y) {
    glColor3f(1,1,1);
    y=h-y;
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
}
void lineDDA(int x0,int y0,int x1,int y1) {
    int dy=y1-y0;
    int dx=x1-x0;
    int steps,i;
    double xinc,yinc,x=x0,y=y0;
    if(abs((double)dx)> abs((double)dy)) {
        steps = abs((double)dx);
    } else {
        steps=abs((double)dy);
    }
    xinc=(dx+0.0)/steps;
    yinc=(dy+0.0)/steps;
    setPixel(roundP(x),roundP(y));
    for(i=0; i<steps; i++) {
        x+=xinc;
        y+=yinc;
        setPixel(roundP(x),roundP(y));
    }
    //glutSwapBuffers();
}

void drawDashed(int x1,int y1,int x2,int y2,int dashLen, int blankLen) {
    double alpha=atan2((y2-y1),(x2-x1));
    double sinal=sin(alpha);
    double cosal=cos(alpha);
    cout<<"alpha = "<<alpha;
    int x=x1;
    int y=y1;
    while(x<x2){
        printf("plotted frmm %d %d\n",x,y);
        int x3=x+min(dashLen,x2-x)*cosal;
        int y3=y+min(dashLen,x2-x)*sinal;
        lineDDA(x,y,x3,y3);
        x=x3+blankLen*cosal;
        y=y3+blankLen*sinal;

    }
    puts("out");
    glutSwapBuffers();
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
    drawDashed(a,b,c,d,dl,bl);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    printf("Enter the Details of the points: \n");
    printf("****** ENTER WINDOW DETAILS ******\n");
    printf("Windows width w: ");
    scanf("%d",&w);
    printf("Windows height h: ");
    scanf("%d",&h);

    glutInitWindowSize(w,h);
    printf("\n****** ENTER DETAILS OF FIRST POINT ******\n");
    printf("\nx1 = ");
    scanf("%d",&a);
    printf("\ny1 = ");
    scanf("%d",&b);
    printf("\n****** ENTER DETAILS OF SECOND POINT ******\n");
    printf("\nx2 = ");
    scanf("%d",&c);
    printf("\ny2 = ");
    scanf("%d",&d);

    printf("Enter length of dash:");
    scanf("%d",&dl);
    printf("Enter length of blank:");
    scanf("%d",&bl);


    glutCreateWindow("DDA line drawing Algorithm");
    init();
    glutDisplayFunc(Display);
    glutMainLoop();
    system("pause");
    return 0;
}
