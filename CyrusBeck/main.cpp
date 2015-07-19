#include <windows.h>
#include <gl/Gl.h>
#include <gl/glut.h>
#include <stdio.h>


struct GLintPoint {
    GLint x,y;
};


struct GLfloatPoint {
    GLfloat x,y;
};


const int MAX = 100;


typedef struct {
    int num;
    GLintPoint pt[MAX];
} GLintPointArray;


class GLfloatPointArray {
public:
    int num;
    GLfloatPoint pt[MAX];
};


typedef GLfloat colorType[3];


void drawDot (GLint x, GLint y, GLfloat r, GLfloat g, GLfloat b) {
    glColor3f(r,g,b);
    glColor3f(r,g,b);
    glBegin (GL_POINTS);
    glVertex2i (x,y);
    glEnd();
}


void drawIntPolygon (GLintPointArray P, colorType c) {
    glColor3fv (c);
    glBegin(GL_LINE_LOOP);
    for (int i=0; i<P.num; i++)
        glVertex2i (P.pt[i].x,P.pt[i].y);
    glEnd();
}


void drawFloatPolygon (GLfloatPointArray P, colorType c) {
    glColor3fv (c);
    glBegin(GL_LINE_LOOP);
    for (int i=0; i < P.num; i++)
        glVertex2f (P.pt[i].x,P.pt[i].y);
    glEnd();
}


void myInit(void) {
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f (0.0f,0.0f,0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}


const int MaxN = 100;


typedef GLfloatPoint Normals[MaxN];


void buildintPolygon (GLintPointArray &P) {
    P.num = 4;
    P.pt[0].x = 50;
    P.pt[0].y = 50;
    P.pt[1].x = 150;
    P.pt[1].y = 100;
    P.pt[2].x = 100;
    P.pt[2].y = 300;
    P.pt[3].x = 10;
    P.pt[3].y = 400;
}


void buildfloatPolygon (GLfloatPointArray &P) {
    P.num = 4;
    P.pt[0].x = 50;
    P.pt[0].y = 50;
    P.pt[1].x = 50;
    P.pt[1].y = 100;
    P.pt[2].x = 100;
    P.pt[2].y = 100;
    P.pt[3].x = 100;
    P.pt[3].y = 50;
}


float DotProduct (GLfloatPoint v1, GLfloatPoint v2) {
    return v1.x*v2.x + v1.y*v2.y;
}


void CalcNormals (GLfloatPointArray p, Normals & n) {
    int i,j,k;
    GLfloatPoint v;
    for (i = 0; i < p.num; i++) {
        j = (i+1)%p.num;
        k = (i+2)%p.num;
        n[i].x = -(p.pt[j].y - p.pt[i].y)/(p.pt[j].x - p.pt[i].x);
        n[i].y = 1.0;
        v.x = p.pt[k].x - p.pt[i].x;
        v.y = p.pt[k].y - p.pt[i].y;
        if (DotProduct (n[i],v) > 0) {
            n[i].x *= -1;
            n[i].y  = -1;
        }
    }
}


void CBClip (GLfloatPoint p1, GLfloatPoint p2, Normals n, GLfloatPointArray p,
             bool & visible, GLfloatPoint & rp, GLfloatPoint & q) {
    float t1,t2,t,numer,den;
    GLfloatPoint dirV,F;
    int i;
    t1 = 0.0;
    t2 = 1.0;
    dirV.x = p2.x - p1.x;
    dirV.y = p2.y - p1.y;
    visible = true;
    i = 0;
    while ( (i < p.num) && visible) {
        F.x = p1.x - p.pt[i].x;
        F.y = p1.y - p.pt[i].y;
        numer  = DotProduct (n[i],F);
        den   =  DotProduct (n[i],dirV);
        if (den == 0.0) {
            if (numer > 0.0)
                visible = false;
        } else {
            t = -(numer/den);
            if (den < 0.0) {
                if (t <= 1.0)
                    if (t > t1)
                        t1 = t;
            } else if ( t >= 0.0) {
                if (t < t2)
                    t2 = t;
            }
        }
        i++;
    }
    if ( t1 <= t2) {
        rp.x = p1.x + t1*dirV.x;
        rp.y = p1.y + t1*dirV.y;
        q.x = p1.x + t2*dirV.x;
        q.y = p1.y + t2*dirV.y;
    } else
        visible = false;
}


void myDisplay(void) {
    GLfloatPointArray Poly;
    colorType C = {0.0f,1.0f,0.0f};
    bool visible;
    GLfloatPoint p1 = {40,20},p2 = {200,400},cp1,cp2;
    Normals Nor;


    glClear(GL_COLOR_BUFFER_BIT);
    buildfloatPolygon(Poly);
    drawFloatPolygon (Poly,C);
    glColor3f (0.0f,0.0f,0.0f);
    glBegin(GL_LINES);
    glVertex2f (40,20);
    glVertex2f (200,400);
    glEnd();
    CalcNormals (Poly,Nor);
    CBClip (p1,p2,Nor,Poly,visible,cp1,cp2);
    if (visible) {
        glColor3f (1.0f,0.0f,0.0f);
        glBegin(GL_LINES);
        glVertex2f (cp1.x,cp1.y);
        glVertex2f (cp2.x,cp2.y);
        glEnd();
    }
    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Cyrus Beck Clipping");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
}
