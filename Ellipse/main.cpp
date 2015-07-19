#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define ROUND(a) ((ll) (a + 0.5))

int a,b,w,h;
typedef long long ll;
void init() {
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,w,0.0,h);
}

void setPixel(GLint x,GLint y) {
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void plotEllipse(int xCenter,int yCenter,int x,int y) {
    setPixel(xCenter+x,yCenter+y);
    setPixel(xCenter-x,yCenter+y);
    setPixel(xCenter-x,yCenter-y);
    setPixel(xCenter+x,yCenter-y);
}

void EllipseMidPoint(int Rx, int Ry) {
    int xCenter=w/2,yCenter=h/2;
    ll Rx2 = Rx*Rx;
    ll Ry2 = Ry*Ry;
    ll twoRx2 = 2 * Rx2;
    ll twoRy2 = 2 * Ry2;

    int x = 0;
    int y = Ry;
    ll px = 0;
    ll py = twoRx2 * y;
    plotEllipse(xCenter, yCenter, x, y);

    /* For Region 1 */
    ll p = ROUND(Ry2 - (Rx2*Ry) + (0.25) * Rx2);
    while(px < py) {
        printf("%d %d %d %d %d\n",x,y,p,px,py);
        x++;
        px += twoRy2;
        if(p < 0) {
            p += Ry2 + px;
        } else {
            y--;
            py -= twoRx2;
            p += Ry2 + px - py;
        }
        plotEllipse(xCenter, yCenter, x, y);
    }

    /* For Region 2*/
    p = ROUND(Ry2 * (x + 0.5)*(x + 0.5) + Rx2 * (y - 1)*(y - 1) - Rx2 * Ry2);
    while(y > 0) {
        y--;
        py -= twoRx2;
        if(p > 0) {
            p += Rx2 - py;
        } else {
            x++;
            px += twoRy2;
            p += Rx2 - py + px;
        }
        plotEllipse(xCenter, yCenter, x, y);
    }
    glFlush();
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,1);
    EllipseMidPoint(a,b);
}

int main(int argc,char **argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);

    printf(" ********      Enter size of window      **********\n");
    printf("Enter width:");
    scanf("%d",&w);
    printf("Enter height");
    scanf("%d",&h);

    printf("Enter major and minor axis lengths:\n");
    scanf("%d%d",&a,&b);

    glutCreateWindow("Ellipse");
    init();
    glutDisplayFunc(Display);
    glutMainLoop();

    return 0;
}
