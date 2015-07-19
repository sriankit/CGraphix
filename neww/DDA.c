#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

int w,h,a,b,c,d;

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);//sets the background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,w,0,h);
}
int rndP(double number){
    return (number>=0)?(int)(number+0.5):(int)(number-0.5);
}
void setPixel(int x,int y){
    glColor3f(1,1,1);   //just sets the color
    y=h-y;
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
}
void LineWithDDA(int x0,int y0,int x1,int y1){
    int dy=y1-y0;
    int dx=x1-x0;
    int steps,i;
    float xinc,yinc,x=x0,y=y0;
    if(abs((float)dx)> abs((float)dy)){
        steps = abs((float)dx);
    }
    else{
        steps=abs((float)dy);
    }
    xinc=(float)dx/(float) steps;
    yinc=(float)dy/(float) steps;
    setPixel(rndP(x),rndP(y));
    for(i=0;i<steps;i++){
        x+=xinc;
        y+=yinc;
        setPixel(rndP(x),rndP(y));
    }
    glutSwapBuffers();
}
void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
    LineWithDDA(a,b,c,d);
}
/*int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    printf("Enter the Details of the points: \n");
    printf("Windows width w: ");
    scanf("%d",&w);
    printf("Windows height h: ");
    scanf("%d",&h);

    glutInitWindowSize(w,h);
    printf("\nInitial Vertx: x1 ");
    scanf("%d",&a);
    printf(" y1: ");
    scanf("%d",&b);
    printf("\nInitial Vertx: x2 ");
    scanf("%d",&c);
    printf(" y2: ");
    scanf("%d",&d);

    glutCreateWindow("DDA line drawing ALgorithm");
    init();
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}*/

