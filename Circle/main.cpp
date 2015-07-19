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
    glLoadIdentity();
    gluOrtho2D(0,w,0,h);
}

void putPixel(int x,int y) {
    glColor3f(1.0,1.0,1.0);
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
}

void poly(int xc,int yc,int r) {
    int x=xc-r;
    while(x <= xc+r) {
        int d=sqrt(r*r-(xc-x)*(xc-x));
        putPixel(x,yc+d);
        printf("%d %d\n",x,yc+d);
        putPixel(x,yc-d);
        printf("%d %d\n",x,yc-d);
        x++;
    }
    glutSwapBuffers();
}

void parametric(int xc,int yc,int r) {
    double pi=4*atan(1.0);
    for(double theta=0;theta<=pi/4;theta+=.01) {
        plot(r*cos(theta)+.5,r*sin(theta)+.5);
    }
    glutSwapBuffers();
}

void bresenHam(int xc,int yc,int r){
    int x=0;
    int y=r;
    int d=3-2*r;
    while(x<=y){
        plot(x,y);
        printf("%d,%d %d\nv",x,y,d);
        if(d<0) d+=4*x+6;
        else {
            d+=4*(x-y)+10;
            --y;
        }
        ++x;
    }
    glutSwapBuffers();
}

void midPoint(int xc,int yc,int r) {
    int x=0;
    int y=r;
    int p=1-r;
    plot(x,y);

    while(x<=y){
        x++;
        if(p<0) p+=2*x+1;
        else {
            y--;
            p+=2*(x-y)+1;
        }
        plot(x,y);
        printf("%d,%d %d\n",x,y,p);
    }
    glutSwapBuffers();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    switch(ch){
        case 1:
            poly(xc,yc,r);
            break;
        case 2:
            parametric(xc,yc,r);
            break;
        case 3:
            bresenHam(xc,yc,r);
            break;
        case 4:
            midPoint(xc,yc,r);
            break;
        default:
            puts("Wrong Choice");
    }

}

int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowPosition(100,100);

    w=400;
    h=400;

    printf("Enter coordinates of center : ");
    scanf("%d%d",&xc,&yc);

    printf("Enter radius : ");
    scanf("%d",&r);

    printf("Enter Algorithm Choice : 1.Polynomial\n2.Parametric\n3.BresenHam\n4.Mid-point\n");
    scanf("%d",&ch);

    glutCreateWindow("Circle generation algorithms");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
