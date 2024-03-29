#include<windows.h>
#include<stdio.h>
#include<GL/glut.h>
#define outcode int

double xmin=50,ymin=50,xmax=100,ymax=100;// windows boudaries
double xvmin=200,yvmin =200, xvmax=300,yvmax=300; // Viewport boudaries

const int RIGHT= 8; // bit codes for the right
const int LEFT =2;  //bit codes for the left
const int TOP=4;    // bit codes for the top
const int BOTTOM=1; //bit codes for the bottom

outcode ComputeOutCode(double x,double y); // used to compute bit codes of a point

// Cohen -Sutherland clipping algorithm clips a line from
// p0=(x0,y0)  to p1 =(x1,y1) against a rectangle with.
// diagonal from (xmin,ymin)to (xmax,ymax)

void CohenSutherlandLineClipAnddraw(double x0,double y0,double x1,double y1) {
    //OutCodes for P0 ,P! and Whatever point lines outside the clip rectangle

    outcode outcode0,outcode1,outcodeOut;
    int accept =0,done =0;
    //compute outcodes
    outcode0= ComputeOutCode(x0,y0);
    outcode1= ComputeOutCode(x1,y1);

    do {
        if(!(outcode0|outcode1)) { // logical or is 0 trivially accept and exit
            accept=1;
            done=1;
        }

        else if(outcode0 & outcode1) // logical and is 0 trivially accept and exit
            done=1;
        else {
            //failed both tests , so calculate the line segment clip;
            // from an outside point to an intersection with clip edge
            double x,y;
            // at least one endpoint is outside the clip rectangle ; pick it.
            outcodeOut= outcode0?outcode0:outcode1;
            //now find the intersection point ;
            // use formula y=y0+slope*(x-x0),x=x0+(1/slope)*(y-y0)
            if(outcodeOut & TOP) { //point is abive the clip rectangle
                x= x0+(x1-x0)*(ymax-y0)/(y1-y0);
                y=ymax;
            } else if(outcodeOut & BOTTOM) { //point is below the clip rectangle
                x= x0+(x1-x0)*(ymin-y0)/(y1-y0);
                y=ymin;
            } else if(outcodeOut & RIGHT) { //point is right the clip rectangle
                y= y0+(y1-y0)*(xmax-x0)/(x1-x0);
                x=xmax;
            } else {               //point is left the clip rectangle
                y= y0+(y1-y0)*(xmin-x0)/(x1-x0);
                x=xmin;
            }
// now we move outside point to intersection point to clip
            // and get ready for next pass.
            if(outcodeOut == outcode0) {
                x0=x;
                y0=y;
                outcode0 = ComputeOutCode(x0,y0);
            } else {
                x1=x;
                y1=y;
                outcode1 = ComputeOutCode(x1,y1);
            }
        }
    } while(!done);
    if(accept) {
        // window to viewport mapping
        double sx=(xvmax-xvmin)/(xmax-xmin);// scale parameters
        double sy=(yvmax-yvmin)/(ymax-ymin);// scale parameters
        double vx0 = xvmin+(x0-xmin)*sx;
        double vy0 = yvmin+(y0-ymin)*sy;
        double vx1 = xvmin+(x1-xmin)*sx;
        double vy1 = yvmin+(y1-ymin)*sy;
        //draw a red color viewport
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(xvmin,yvmin);
            glVertex2f(xvmax,yvmin);
            glVertex2f(xvmax,yvmax);
            glVertex2f(xvmin,yvmax);
        glEnd();
        glColor3f(0.0,0.0,1.0);
        glBegin(GL_LINES);
            glVertex2d(vx0,vy0);
            glVertex2d(vx1,vy1);
        glEnd();
    }
}
// compute the bit code for a point (x,y) using the clip rectangle
// bounded diagonally by (xmin,ymin) and (xmax,ymax)
outcode ComputeOutCode(double x,double y) {
    outcode code =0;
    if(y>ymax)   //above the clip window
        code |=TOP;
    if(y<ymin)   //below the clip window
        code |=BOTTOM;
    if(x>xmax)        //to the right the clip window
        code |=RIGHT;
    if(x<xmin)  //to the left the clip window
        code |=TOP;
    return code;
}

double x0,y0,x1,y1;

void display() {
    //double x0=120,y0=10,x1=40,y1=130;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0); // draw red color line
    glBegin(GL_LINES);
        glVertex2d(x0,y0);
        glVertex2d(x1,y1);

        glVertex2d(60,20);
        glVertex2d(80,120);
    glEnd();
    glColor3f(0.0,0.0,1.0); // draw a blue colored window
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin,ymin);
        glVertex2f(xmax,ymin);
        glVertex2f(xmax,ymax);
        glVertex2f(xmin,ymax);
    glEnd();
    CohenSutherlandLineClipAnddraw(x0,y0,x1,y1);
    CohenSutherlandLineClipAnddraw(60,20,80,120);
    glFlush();
}
void myinit() {
    glClearColor(.2,1.0,1.0,1.0);
    glColor3f(0.0,0.0,0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
}
int main(int argc, char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("cohen Sutherland line clipping algorithm");

    printf("**** Welcome to illustration of line clipping algorithm: *****\n");
    printf("Window Height : 500 width : 500\n");

    printf("Enter the end pts of line to be clipped\n");
    scanf("%lf%lf%lf%lf",&x0,&y0,&x1,&y1);

    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
    return 0;
}
