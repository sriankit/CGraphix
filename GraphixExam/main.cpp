#include<gl/glut.h>
#include<stdio.h>

int h,k,r;
int a,b;

void init(){
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,a,0,b);
}

void putPixel(int x,int y) {
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
}

void plot(int x,int y){
    putPixel(h+x,k+y);
    putPixel(h+y,k+x);
    putPixel(h+x,k-y);
    putPixel(h-y,k+x);
    putPixel(h-x,k+y);
    putPixel(h+y,k-x);
    putPixel(h-x,k-y);
    putPixel(h-y,k-x);
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
    midPoint(h,k,r);
    /*int x=0,y=r;
    int p=1-r;
    plot(x,y);
    for(x=0;x<=y;x++){
        if(p<0) p+=2*x+1;
        else {
            --y;
            p+=2*(x-y)+1;
        }
        plot(x,y);
        printf("%d %d\n",x,y);
    }
    glutSwapBuffers();
    */
}

int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

    glutInitWindowPosition(0,0);
    //glutInitWindowSize(500,500);
    scanf("%d%d%d",&h,&k,&r);
    init();
    glutCreateWindow("Mid-pt Circle Generation");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
