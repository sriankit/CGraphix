//#include<windows.h>
#include<gl/glut.h>
//#include<utility>
//#include<vector>
#include<cstdio>
//#include<cassert>

//using namespace std;

/*#define FF first
#define pb push_back
#define SS second
#define mp make_pair*/


void init() {
    glClearColor(1.0,1.0,1.0,1.0);
    //glColor3f(0.0,0.0,0.0);
    //glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
}


int xmin,xmax,ymin,ymax;
/*pair<int,int> p0,p1;

int myDotProd(pair<int,int> v1,pair<int,int> v2) {
    return v1.FF*v2.FF+v1.SS*v2.SS;
}

pair<int,int> getVector(pair<int,int> p1,pair<int,int> p2) {
    pair<int,int>res = mp(p2.FF-p1.FF,p2.SS-p1.SS);
    return res;
}

pair<double,double> addPair(pair<int,int> p1,pair<double,double> p2) {
    return mp(p1.FF+p2.FF, p1.SS+p2.SS);
}

pair<double,double> mul(pair<int,int> v,double mul) {
    return mp(v.FF*mul,v.SS*mul);
}
*/
void display() {
    /*glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0,1.0,0.0);
    a=100,b=200,c=200,d=100;
    glBegin(GL_POLYGON);
        glVertex2f(a,b);
        glVertex2f(c,b);
        glVertex2f(c,d);
        glVertex2f(a,d);
    glEnd();
    glFlush();*/
    glClear(GL_COLOR_BUFFER_BIT);


    glColor3f(1.0,1.0,0.0);
    GLfloat a=100.0,b=123.0,c=130.0,d=154.0;
    glBegin(GL_LINES);
        glVertex2f(a,b);
        glVertex2f(c,d);
    glEnd();
    glFlush();

/*
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin,ymin);
        glVertex2f(xmin,ymax);
        glVertex2f(xmax,ymax);
        glVertex2f(xmax,ymin);
    glEnd();

    glFlush();
    /*
    glColor3f(1,0,0);
    glBegin(GL_LINES);
        glVertex2i(p0.FF,p0.SS);
        glVertex2i(p1.FF,p1.SS);
    glEnd();

    vector<pair<int,int> > normals;
    normals.pb(mp(-1,0)); //left
    normals.pb(mp(0,1));  //top
    normals.pb(mp(1,0)); //right
    normals.pb(mp(0,-1)); //down

    vector<pair<int,int> >pl;
    pl.pb(mp(xmin,ymax));
    pl.pb(mp(xmax,ymax));
    pl.pb(mp(xmax,ymin));
    pl.pb(mp(xmin,ymin));

    pair<int,int> PL(-213,-213), PE(-213,-213);
    double plt=-100,pet=100.0;

    for(int i=0;i<4;i++){
        int num=myDotProd(normals[i],getVector(p0,pl[i]));
        int den=myDotProd(normals[i],getVector(p0,p1));
        assert(den!=0);
        double fr=num/-den;
        if(fr>=0 && fr<=1) {
            if(den>0) {
                if(plt<-99 || fr<plt) plt=fr;
            } else if(den < 0) {
                if(pet>99 || fr>pet) pet=fr;
            }
        }
    }

    if(plt<-99) {
        printf("OUTSIDE");
        glFlush();
    }
    else {
        pair<double,double> st=addPair(p0,mul(getVector(p0,p1),plt));
        pair<double,double> end=addPair(p0,mul(getVector(p0,p1),pet));
        glColor3f(0,1,0);
        glBegin(GL_LINE);
            glVertex2f(st.FF,st.SS);
            glVertex2f(st.FF,st.SS);
        glEnd();
    }

    glFlush();
    */
}

int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,0);
    glutCreateWindow("cyrus beck");

    //printf("**** Welcome to illustration of line clipping flood fill algorithm: *****\n");
    printf("Window Height : 500 width : 500\n");

    //printf("Enter Coordinates of upper-left and bottom-right vertices for required rectangle\n");
    //scanf("%d%d%d%d",&a,&b,&c,&d);


    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
