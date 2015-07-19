/*
SUBMISSION BY - Ankit Srivastava
                B.Tech 3rd Year, CSE
                11100EN014


ALGORITHM :
1. We iterate over all line segments present and divide them into 4 parts as instructed.
   The points dividing in 1/3 rd are found by section formula.
   There are two possible vertices for equilateral triangle mounted over the line segment.
   The choice is made by checking clockwise nature of point around segment by calculating cross product.

2. All the line segments are added to the queue in order until required depth is reached, upon which the current line segments are simply displayed.
*/

#include<windows.h>
#include<cmath>
#include<cstdio>
#include<GL/glut.h>
#include<queue>
using namespace std;

#define SZ(x) ((int)(x.size()))

int w=600, h=600;
int stx=333, sty=333;
int side=243;
double pi=4*atan(1.0);
double angle=pi/3;
double shiftX=0.0;
const double NINETY=pi/2;
double ANGLE;

//structure for points
struct pont {
    double x, y;
    pont(double _x, double _y) {x=_x;y=_y;}
};

//structure for line segments
struct line{
    double _x1;
    double _y1;
    double _x2;
    double _y2;
    int l;

    line(double x1, double y1, double x2, double y2, int len) {_x1=x1;_x2=x2;_y1=y1;_y2=y2;l=len;}
};

//initilaize the GL
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,w,0,h);
}

//own method for drawing a line form (x1,y1) to (x2,y2)
void drawLine(double x1, double y1, double x2, double y2) {
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f((GLfloat)x1, (GLfloat)y1);
    glVertex2f((GLfloat)x2, (GLfloat)y2);
    glEnd();
    //glFlush();
}

//computes crossProd to determine whether vector p0p1 is clockwise or counter clockwise
int crossProd(pont p0, pont p1, pont p2) {
    return (p1.x-p0.x)*(p2.y-p0.y) - (p2.x-p0.x)*(p1.y-p0.y) < 0;
}
//auxiliary method for the check
int check(double x1, double y1, double x2, double y2, double x3, double y3) {
    if(crossProd(pont(x1,y1),pont(x2,y2),pont(x3,y3))) return 1;
    else return 0;
}
//global variable queue so as to keep track of states
queue<line> q;

//breaks the line segment in required parts and pushes the line segments on the queue
void change(double x1, double y1, double x2, double y2, int l) {
    if(l==9) {
        drawLine(x1, y1, x2, y2);
        return;
    }
    double x=(x1+x2)/2;
    double y=(y1+y2)/2;
    double theta=atan2(y2-y1, x2-x1);
    if(theta<0) theta += pi;
    int indL=l/3;
    double d=(l/3)*sin(angle);
    double phi=theta-NINETY;

    double px=x+d*cos(phi);
    double py=y+d*sin(phi);
    double pxc=x-d*cos(phi);
    double pyc=y-d*sin(phi);

    double cx1=x1+indL*sin(angle)*cos(theta);
    double cy1=y1+(l/2)*sin(theta);


    double px1=(x2+2*x1)/3;
    double py1=(y2+2*y1)/3;
    double px2=(x1+2*x2)/3;
    double py2=(y1+2*y2)/3;

    if(check(px1,py1,px,py,px2,py2)==1) {
        px=pxc;
        py=pyc;
    }

    q.push(line(x1,y1,px1,py1,l/3));
    q.push(line(px1, py1, px, py,l/3));
    q.push(line(px, py, px2, py2,l/3));
    q.push(line(px2, py2, x2, y2,l/3));
}

//all the processing goes here
void go() {
    pont A=pont(stx,sty);
    pont B=pont(stx+side*cos(ANGLE),sty+side*sin(ANGLE));

    pont C=pont(stx+side*cos(angle+ANGLE),sty+side*sin(angle+ANGLE));

    q.push(line(A.x,A.y,B.x,B.y,side));
    q.push(line(B.x,B.y,C.x,C.y,side));
    q.push(line(C.x,C.y,A.x,A.y,side));

    while(SZ(q)>0){
        line p=q.front();
        q.pop();

        change(p._x1, p._y1, p._x2, p._y2, p.l);
    }
    //renders output to screen
    glutSwapBuffers();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
    go();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    scanf("%lf",&ANGLE);
    //ANGLE converted to radians
    ANGLE/=180.0;
    ANGLE*=pi;

    glutCreateWindow("test");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
