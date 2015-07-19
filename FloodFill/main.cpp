#include<GL/glut.h>
#include<stdio.h>
#include<windows.h>

int a,b,c,d;

struct fill{
    float r,g,b;
};

struct fill fillC{0.0,0.2,1.0};
struct fill def{0.0,1.0,0.0};

void setpixel(struct fill fillcolor,int x,int y)
{
     glColor3f(fillcolor.r,fillcolor.g,fillcolor.b);
     glBegin(GL_POINTS);
     glVertex2i(x,y);
     glEnd();
     glFlush();
}

struct fill getpixcol(int x,int y)
{
    struct fill gotpixel;
    unsigned char pick_col[3];
    glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,pick_col);
    gotpixel.r =(float) pick_col[0]/255.0;
    gotpixel.g =(float) pick_col[1]/255.0;
    gotpixel.b =(float) pick_col[2]/255.0;
    return(gotpixel);
}

int mrnd=3;

void floodFill(int x, int y,struct fill fillColor,struct fill old)
{
    struct fill tmp;
    tmp=getpixcol(x,y);
    printf("r:%f g:%f b:%f\n",tmp.r,tmp.g,tmp.b);
    if(tmp.r * 1000!=old.r * 1000 || tmp.g*1000!=old.g*1000 || tmp.b*1000!=old.b*1000){
        puts("RETURN");
        return;
    }
    setpixel(fillColor,x,y);
    int dx[4]={1,0,-1};
    int dy[4]={-1,0,1};
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
        //mrnd=(mrnd*7)%8;
        //int ind = mrnd>>1;
        //mrnd=ind;
            if(i==1 && j==1) continue;
            floodFill(x+dx[i],y+dy[j],fillC,old);
        }
    }

    glFlush();
    Sleep(2);
}

void myinit() {
    glClearColor(0.0,1.0,1.0,1.0);
    glColor3f(0.0,0.0,0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);


    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
        glVertex2f(a,b);
        glVertex2f(c,b);
        glVertex2f(c,d);
        glVertex2f(a,d);
    glEnd();
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(a,b);
        glVertex2f(c,b);
        glVertex2f(c,d);
        glVertex2f(a,d);
    glEnd();
    glFlush();
    //Sleep(1000);
    int seedx=a+c>>1;
    int seedy=b+d>>1;

    floodFill(seedx,seedy,fillC,def);
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Flood Fill algorithm");

    printf("**** Welcome to illustration of line clipping flood fill algorithm: *****\n");
    printf("Window Height : 500 width : 500\n");

    printf("Enter Coordinates of upper-left and bottom-right vertices for required rectangle\n");
    scanf("%d%d%d%d",&a,&b,&c,&d);


    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
