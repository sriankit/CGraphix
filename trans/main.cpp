/*
#include <stdio.h>
#include <math.h>
#include<GL/glut.h>

typedef float Matrix3x3 [3][3];
Matrix3x3 theMatrix;
int NEdges;
float ptsIni[20][2];
float ptsFin[20][2];
float refpt[2];
float RotAngle;
float TransDistX,TransDistY;
float ScaleX,ScaleY;
int choice,choiceRef;
void setPixel(GLfloat x,GLfloat y)
{
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
}
int roundOff(float number)
{
    return (number>=0)?(int)(number+0.5):(int)(number-0.5);
}
void LineDDA(float x0,float y0,float x1,float y1)
{
    float dY=y1-y0;
    float dX=x1-x0;
    int steps,i;
    float x_inc,y_inc,X=x0,Y=y0;
    if(abs(dX)> abs(dY))
    {
        steps = (int)abs(dX);
    }
    else
    {
        steps=(int)abs(dY);
    }
    x_inc=dX/(float) steps;
    y_inc=dY/(float) steps;
    setPixel(roundOff(X),roundOff(Y));glFlush();
    for(i=0;i<steps;i++)
    {
        X=X+x_inc;
        Y=Y+y_inc;
        setPixel(roundOff(X),roundOff(Y));glFlush();
    }
    glFlush();
}

void giveOutput(float out[20][2])
{
    int i;
    for(i=0;i<NEdges-1;i+=1)
    LineDDA(out[i][0],out[i][1],out[i+1][0],out[i+1][1]);
    LineDDA(out[NEdges-1][0],out[NEdges-1][1],out[0][0],out[0][1]);

    glFlush();
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,1,0);
    giveOutput(ptsIni);

    glColor3f(1,0,0);
    giveOutput(ptsFin);
}

void matrixSetIdentity(Matrix3x3 m)
{
    int i, j;
    for (i=0; i<3; i++)
    for (j=0; j<3; j++)
    m[i][j] = (i == j);
}

void matrixPreMultiply(Matrix3x3 a , Matrix3x3 b)
{
    int i,j;
    Matrix3x3 tmp;
    for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
    tmp[i][j] = a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j];
    for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
    theMatrix[i][j] = tmp[i][j];
}

void Translate(int tx, int ty)
{
    Matrix3x3 m;
    matrixSetIdentity(m);
    m[0][2] = tx;
    m[1][2] = ty;
    matrixPreMultiply(m, theMatrix);
}

void Scale(float sx , float sy)
{
    Matrix3x3 m;
    matrixSetIdentity(m);
    m[0][0] = sx;
    m[0][2] = (1 - sx)*refpt[0];
    m[1][1] = sy;
    m[1][2] = (1 - sy)*refpt[1];
    matrixPreMultiply(m , theMatrix);
}

void Rotate(float a)
{
    Matrix3x3 m;
    matrixSetIdentity(m);
    a = a*22/1260;
    m[0][0] = cos(a);
    m[0][1] = -sin(a) ;
    m[0][2] = refpt[0]*(1 - cos(a)) + refpt[1]*sin(a);
    m[1][0] = sin(a);
    m[1][1] = cos(a);
    m[1][2] = refpt[1]*(1 - cos(a)) - refpt[0]*sin(a);
    matrixPreMultiply(m , theMatrix);
}

void TransformPoints(void)
{
    int k;
    float tmp;

    printf("Number of vertices in polygon : ");
    scanf("%d",&NEdges);
    printf("Co-ordinate pairs -\n");
    for (k=0;k<NEdges;k++)
    scanf("%f%f",&ptsIni[k][0],&ptsIni[k][1]);

    printf("Enter your choice\n:1:Transform\n:2:Rotation\n:3:Scaling\n");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:     printf("Enter translation along X & Y\n=>");
        scanf("%f%f",&TransDistX , &TransDistY);
        for(k=0;k<NEdges;k++)
        {
            theMatrix[0][0]=ptsIni[k][0];
            theMatrix[1][0]=ptsIni[k][1];
            theMatrix[2][0]=1;
            Translate(TransDistX,TransDistY);
            ptsFin[k][0]=theMatrix[0][0];
            ptsFin[k][1]=theMatrix[1][0];
        }
        break;

        case 2:     printf("Angle of Rotation\n");
        scanf("%f",&RotAngle);
        printf("Reference point Co-ordinates:\n");
        scanf("%f%f",&refpt[0],&refpt[1]);
        for(k=0;k<NEdges;k++)
        {
            theMatrix[0][0]=ptsIni[k][0];
            theMatrix[1][0]=ptsIni[k][1];
            theMatrix[2][0]=1;
            Rotate(RotAngle);
            ptsFin[k][0]=theMatrix[0][0];
            ptsFin[k][1]=theMatrix[1][0];
        }
        break;

        case 3:
         printf("Scaling ratios along X & Y\n");
        scanf("%f%f",&ScaleX , &ScaleY);
        for(k=0;k<NEdges;k++)
        {
            theMatrix[0][0]=ptsIni[k][0];
            theMatrix[1][0]=ptsIni[k][1];
            theMatrix[2][0]=1;

            Scale(ScaleX,ScaleY);

            ptsFin[k][0]=theMatrix[0][0];
            ptsFin[k][1]=theMatrix[1][0];
        }
        break;

        default:    printf("Wrong choice!!!\n");
    }

    glutCreateWindow("2D Transformation");
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,500.0,0.0,500.0);
    glutDisplayFunc(Display);
    glutMainLoop();
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    int n,m;
    printf("Enter size of Window:\n");
    scanf("%d%d",&n,&m);
    glutInitWindowSize(500,500);
    TransformPoints();
    return 0;
}
*/
//#include<windows.h>
#include <stdio.h>
#include <math.h>
#include<GL/glut.h>
#include<stdlib.h>
typedef float Matrix3x3 [3][3];
Matrix3x3 theMatrix;
int NEdges;
float ptsIni[20][2];
float ptsFin[20][2];
float refpt[2];
float RotAngle;
float TransDistX,TransDistY;
float ScaleX,ScaleY;
int choice,choiceRef;
 int k;
    float tmp;

void init()
{
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,500.0,0.0,500.0);
}

void setPixel(GLfloat x,GLfloat y)
{
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
}

int roundOff(float number)
{
    return (number>=0)?(int)(number+0.5):(int)(number-0.5);
}
void LineDDA(float x0,float y0,float x1,float y1)
{
    float dY=y1-y0;
    float dX=x1-x0;
    int steps,i;
    float x_inc,y_inc,X=x0,Y=y0;
    if(abs(dX)> abs(dY))
    {
        steps = (int)abs(dX);
    }
    else
    {
        steps=(int)abs(dY);
    }
    x_inc=dX/(float) steps;
    y_inc=dY/(float) steps;
    setPixel(roundOff(X),roundOff(Y));glFlush();
    for(i=0;i<steps;i++)
    {
        X=X+x_inc;
        Y=Y+y_inc;
        setPixel(roundOff(X),roundOff(Y));glFlush();
    }
    glFlush();
}

void giveOutput(float out[20][2])
{
    int i;
    for(i=0;i<NEdges-1;i+=1)
    LineDDA(out[i][0],out[i][1],out[i+1][0],out[i+1][1]);
    LineDDA(out[NEdges-1][0],out[NEdges-1][1],out[0][0],out[0][1]);

    glFlush();
}

void matrixSetIdentity(Matrix3x3 m)
{
    int i, j;
    for (i=0; i<3; i++)
    for (j=0; j<3; j++)
    m[i][j] = (i == j);
}

void matrixPreMultiply(Matrix3x3 a , Matrix3x3 b)
{
    int i,j;
    Matrix3x3 tmp;
    for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
    tmp[i][j] = a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j];
    for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
    theMatrix[i][j] = tmp[i][j];
}

void Translate(int tx, int ty)
{
    Matrix3x3 m;
    matrixSetIdentity(m);
    m[0][2] = tx;
    m[1][2] = ty;
    matrixPreMultiply(m, theMatrix);
}

void Scale(float sx , float sy)
{
    Matrix3x3 m;
    matrixSetIdentity(m);
    m[0][0] = sx;
    m[0][2] = (1 - sx)*refpt[0];
    m[1][1] = sy;
    m[1][2] = (1 - sy)*refpt[1];
    matrixPreMultiply(m , theMatrix);
}

void Rotate(float a)
{
    Matrix3x3 m;
    matrixSetIdentity(m);
    a = a*22/1260;
    m[0][0] = cos(a);
    m[0][1] = -sin(a) ;
    m[0][2] = refpt[0]*(1 - cos(a)) + refpt[1]*sin(a);
    m[1][0] = sin(a);
    m[1][1] = cos(a);
    m[1][2] = refpt[1]*(1 - cos(a)) - refpt[0]*sin(a);
    matrixPreMultiply(m , theMatrix);
}

void Display()
{
    printf("Choice :\n");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:     printf("Translation along X & Y\n=>");
        scanf("%f%f",&TransDistX , &TransDistY);
        for(k=0;k<NEdges;k++)
        {
            theMatrix[0][0]=ptsIni[k][0];
            theMatrix[1][0]=ptsIni[k][1];
            theMatrix[2][0]=1;

            Translate(TransDistX,TransDistY);

            ptsFin[k][0]=theMatrix[0][0];
            ptsFin[k][1]=theMatrix[1][0];
        }
        break;

        case 2:     printf("Angle of Rotation\n=>");
        scanf("%f",&RotAngle);
        printf("Reference point Co-ordinates:\n=>");
        scanf("%f%f",&refpt[0],&refpt[1]);
        for(k=0;k<NEdges;k++)
        {
            theMatrix[0][0]=ptsIni[k][0];
            theMatrix[1][0]=ptsIni[k][1];
            theMatrix[2][0]=1;

            Rotate(RotAngle);

            ptsFin[k][0]=theMatrix[0][0];
            ptsFin[k][1]=theMatrix[1][0];
        }
        break;

        case 3:     printf("Scaling ratios along X & Y\n=>");
        scanf("%f%f",&ScaleX , &ScaleY);
        for(k=0;k<NEdges;k++)
        {
            theMatrix[0][0]=ptsIni[k][0];
            theMatrix[1][0]=ptsIni[k][1];
            theMatrix[2][0]=1;

            Scale(ScaleX,ScaleY);

            ptsFin[k][0]=theMatrix[0][0];
            ptsFin[k][1]=theMatrix[1][0];
        }
        break;

        default:    printf("Wrong choice!!!\n");
    };

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,1,0);
    giveOutput(ptsIni);

    glColor3f(1,0,0);
    giveOutput(ptsFin);

    glutPostRedisplay();
}

void TransformPoints(void)
{

    printf("Number of vertices in polygon : ");
    scanf("%d",&NEdges);
    printf("Co-ordinate pairs -\n",NEdges);
    for (k=0;k<NEdges;k++)
    scanf("%f%f",&ptsIni[k][0],&ptsIni[k][1]);
    glutCreateWindow("Transformation");
    init();
    glutDisplayFunc(Display);
    glutMainLoop();
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    int n,m;
    printf("Enter size of Window:\n");
    scanf("%d%d",&n,&m);
    glutInitWindowSize(500,500);
    TransformPoints();
    return 0;
}
