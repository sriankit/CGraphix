#include<cstdio>
#include<cmath>
#include<GL/glut.h>

using namespace std;

int width=500,height=500,a,b,c,d;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,width,0,height);
}
void putPixel(int x,int y)
{
    glColor3f(1,1,1);
    y=height-y;
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
}

void bresenham(int x0,int y0,int x1,int y1)
{
    int dy=y1-y0;
    int dx=x1-x0;

    int p = 2*dy-dx;

    int x,y,x_end;
    if(x0>x1)
    {
        x=x1;
        y=y1;
        x_end=x0;
        //dx=-dx;
        //dy=-dy;
    }
    else
    {
        x=x0;
        y=y0;
        x_end=x1;
    }

    putPixel(x,y);

    while(x<=x_end)
    {
        x++;
        if(p<0)
        {
            p=p+2*dy;
        }
        else
        {
            y++;
            p=p+2*(dy-dx);
        }
        putPixel(x,y);
    }
    glutSwapBuffers();
}
void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
    bresenham(a,b,c,d);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    printf("****Enter the Details of the points:**** \n");

    glutInitWindowSize(width,height);
    printf("\nfirst Vertex:\nx1 : ");
    scanf("%d",&a);
    printf("y1 : ");
    scanf("%d",&b);
    printf("\nsecond Vertx:\nx2 : ");
    scanf("%d",&c);
    printf("y2 : ");
    scanf("%d",&d);

    glutCreateWindow("Bresenham line drawing ALgorithm");
    init();
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}
