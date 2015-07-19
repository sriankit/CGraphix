#include<windows.h>
#include <GL/glut.h>
#include <stdio.h>

#define X_COORDINATE 0
#define Y_COORDINATE 1
#define Z_COORDINATE 2

float xBoundaryLeft, xBoundaryRight, yBoundaryUp, yBoundaryDown;
float givenLineP1[3], givenLineP2[3];
float clippedLineP1[3], clippedLineP2[3];

void myInit() {
    glClearColor(0.0,1.0,1.0,1.0);
    glColor3f(0.0,0.0,0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
}
void display () {

    glClear (GL_COLOR_BUFFER_BIT);

    /* First draw the clipping rectangle. */
    glColor3f (0.0, 0.0, 0.0);
    glBegin (GL_LINE_LOOP);
        glVertex3f (xBoundaryLeft, yBoundaryUp, 0.0);
        glVertex3f (xBoundaryRight, yBoundaryUp, 0.0);
        glVertex3f (xBoundaryRight, yBoundaryDown, 0.0);
        glVertex3f (xBoundaryLeft, yBoundaryDown, 0.0);

    glEnd();
    glFlush();
    Sleep(2000);

    /* Now draw the given line segment (in black) */
    glBegin (GL_LINES);
        glVertex3fv (givenLineP1);
        glVertex3fv (givenLineP2);
    glEnd();
    glFlush();
    Sleep(1000);

    /* Now draw the clipped line segment (in red) */
    glColor3f (1.0, 0.0, 0.0);
    glBegin (GL_LINES);
        glVertex3fv (clippedLineP1);
        glVertex3fv (clippedLineP2);
    glEnd();

    glFlush();
}

int main (int argc, char **argv) {

    int i;
    float tempPoint[3];

    printf ("Enter Left X-Boundary: ");
    scanf ("%f", &xBoundaryLeft);
    printf ("Enter Right X-Boundary: ");
    scanf ("%f", &xBoundaryRight);
    printf ("Enter Upper Y-Boundary: ");
    scanf ("%f", &yBoundaryUp);
    printf ("Enter Lower Y-Boundary: ");
    scanf ("%f", &yBoundaryDown);

    printf ("Enter (x1, y1) for the line: ");
    for (i = 0; i < 2; i++) scanf ("%f", &givenLineP1[i]);
    printf ("Enter (x2, y2) for the line: ");
    for (i = 0; i < 2; i++) scanf ("%f", &givenLineP2[i]);
    givenLineP1[2] = givenLineP2[2] = 0;

    for (i = 0; i < 3; i++)
    clippedLineP1[i] = givenLineP1[i], clippedLineP2[i] = givenLineP2[i];

    /* Check if line is horizontal. */
    if (clippedLineP1[Y_COORDINATE]-clippedLineP2[Y_COORDINATE] == 0) {
    /* If line is above yBoundaryUp or below yBoundaryDown */
    if (clippedLineP1[Y_COORDINATE] > yBoundaryUp
        || clippedLineP1[Y_COORDINATE] < yBoundaryDown)
        for (i = 0; i < 3; i++) clippedLineP1[i] = 0, clippedLineP2[i] = 0;
    else {          /* Clip line as necessary */
        if (clippedLineP1[X_COORDINATE] > clippedLineP2[X_COORDINATE]) {
        /* Let p1 be the left point (swap) */
        for (i = 0; i < 3; i++) tempPoint[i] = clippedLineP1[i];
        for (i = 0; i < 3; i++) clippedLineP1[i] = clippedLineP2[i];
        for (i = 0; i < 3; i++) clippedLineP2[i] = tempPoint[i];
        }

        /* Check if both points are either to the left of
         xBoundaryRight or right of xBoundaryLeft. */
        if ((clippedLineP1[X_COORDINATE] < xBoundaryLeft &&
         clippedLineP2[X_COORDINATE] < xBoundaryLeft) ||
        (clippedLineP1[X_COORDINATE] > xBoundaryRight &&
         clippedLineP2[X_COORDINATE] > xBoundaryRight))
        /* In which case, clippedLine will be null */
        for (i = 0; i < 3; i++)
            clippedLineP1[i] = clippedLineP2[i] = 0;
        else {  /* Check both points if they exceed their boundaries. */
        if (clippedLineP1[X_COORDINATE] < xBoundaryLeft)
            clippedLineP1[X_COORDINATE] = xBoundaryLeft;
        if (clippedLineP2[X_COORDINATE] > xBoundaryRight)
            clippedLineP2[X_COORDINATE] = xBoundaryRight;
        }
    }
    }
    /* Repeat the above for vertical lines. */
    else if (clippedLineP1[X_COORDINATE]-clippedLineP2[X_COORDINATE] == 0) {
    /* If line is left of xBoundaryLeft or right of xBoundaryRight. */
    if (clippedLineP1[X_COORDINATE] > xBoundaryRight
        || clippedLineP1[X_COORDINATE] < xBoundaryLeft)
        for (i = 0; i < 3; i++) clippedLineP1[i] = 0, clippedLineP2[i] = 0;
    else {          /* Clip line as necessary */
        if (clippedLineP1[Y_COORDINATE] < clippedLineP2[Y_COORDINATE]) {
        /* Let p1 be the upper point (swap) */
        for (i = 0; i < 3; i++) tempPoint[i] = clippedLineP1[i];
        for (i = 0; i < 3; i++) clippedLineP1[i] = clippedLineP2[i];
        for (i = 0; i < 3; i++) clippedLineP2[i] = tempPoint[i];
        }

        /* Check if both points are above yBoundaryUp
         or below yBoundaryDown. */
        if ((clippedLineP1[Y_COORDINATE] < yBoundaryDown &&
         clippedLineP2[Y_COORDINATE] < yBoundaryDown) ||
        (clippedLineP1[Y_COORDINATE] > yBoundaryUp &&
         clippedLineP2[Y_COORDINATE] > yBoundaryUp))
        /* In which case, clippedLine will be null */
        for (i = 0; i < 3; i++)
            clippedLineP1[i] = clippedLineP2[i] = 0;
        else {  /* Check both points if they exceed their boundaries. */
        if (clippedLineP1[Y_COORDINATE] > yBoundaryUp)
            clippedLineP1[Y_COORDINATE] = yBoundaryUp;
        if (clippedLineP2[Y_COORDINATE] < yBoundaryDown)
            clippedLineP2[Y_COORDINATE] = yBoundaryDown;
        }
    }
    }

    /* Line is neither vertical nor horizontal. */
    else {
    /* Calcluate the four alphas (as in text book). We actually need
       not have to perform the division. But, optimisation later. */

    float a1, a2, a3, a4;

    /* as alpha increases from 0 to 1, we move from one point to
     the other, left to right. As a convention, let P1 be the point
    that is to the left. */
    if (clippedLineP1[X_COORDINATE] > clippedLineP2[X_COORDINATE]) {
        /* Let p1 be the left point (swap) */
        for (i = 0; i < 3; i++) tempPoint[i] = clippedLineP1[i];
        for (i = 0; i < 3; i++) clippedLineP1[i] = clippedLineP2[i];
        for (i = 0; i < 3; i++) clippedLineP2[i] = tempPoint[i];
        /* Swap givenLine too. */
        for (i = 0; i < 3; i++) tempPoint[i] = givenLineP1[i];
        for (i = 0; i < 3; i++) givenLineP1[i] = givenLineP2[i];
        for (i = 0; i < 3; i++) givenLineP2[i] = tempPoint[i];
    }

    /* Parametric line equations:
       x(alpha) = (1-alpha)x1 + (alpha)x2
       y(alpha) = (1-alpha)y1 + (alpha)y2 */

    a1 = (yBoundaryDown-clippedLineP1[Y_COORDINATE]);
    a1 /= (clippedLineP2[Y_COORDINATE]-clippedLineP1[Y_COORDINATE]);
    /* alpha1 is the intersection with yBoundaryDown. */

    a2 = (xBoundaryLeft-clippedLineP1[X_COORDINATE]);
    a2 /= (clippedLineP2[X_COORDINATE]-clippedLineP1[X_COORDINATE]);
    /* alpha2 is the intersection with xBoundaryLeft. */

    a3 = (yBoundaryUp-clippedLineP1[Y_COORDINATE]);
    a3 /= (clippedLineP2[Y_COORDINATE]-clippedLineP1[Y_COORDINATE]);
    /* alpha3 is the intersection with yBoundaryUp. */

    a4 = (xBoundaryRight-clippedLineP1[X_COORDINATE]);
    a4 /= (clippedLineP2[X_COORDINATE]-clippedLineP1[X_COORDINATE]);
    /* alpha4 is the intersection with xBoundaryRight. */

    /* There are 8 permuations of a1 < a2 < a3 < a4 wherein the line
     could be inside the clipping rectangle. */

    /* These 8 permutations are demonstrated in the liang_barsky_help.jpg help
     file available at http://puttu.net/programming/cglab/liang_barsky_help.jpg */

    /* Case 1:  */
    /* Case 1 and case 3 takes care of opposite corner passing through lines.  */
    if (a1 <= a2 && a2 < a3 && a3 <= a4) {
        /* If both points are to the left of xBoundaryLeft or above
         yBoundaryUp, then the line segment is completely outside. */
        if ((clippedLineP1[X_COORDINATE] < xBoundaryLeft &&
        clippedLineP2[X_COORDINATE] < xBoundaryLeft) ||
        (clippedLineP1[Y_COORDINATE] > yBoundaryUp &&
         clippedLineP2[Y_COORDINATE] > yBoundaryUp))
        for (i = 0; i < 3; i++)
            clippedLineP1[i] = clippedLineP2[i] = 0;
        else {
        if (clippedLineP1[X_COORDINATE] < xBoundaryLeft) {
            clippedLineP1[X_COORDINATE] = xBoundaryLeft;
            clippedLineP1[Y_COORDINATE] =
            ((1-a2)*givenLineP1[Y_COORDINATE])+(a2*givenLineP2[Y_COORDINATE]);
        }
        if (clippedLineP2[Y_COORDINATE] > yBoundaryUp) {
            clippedLineP2[Y_COORDINATE] = yBoundaryUp;
            clippedLineP2[X_COORDINATE] =
            ((1-a3)*givenLineP1[X_COORDINATE])+(a3*givenLineP2[X_COORDINATE]);
        }
        }
    }
    /* Case 2: */
    else if (a3 < a2 && a2 < a1 && a1 < a4) {
        /* If both points are to the left of xBoundaryLeft or below
         yBoundaryDown, then the line segment is completely outside. */
        if ((clippedLineP1[X_COORDINATE] < xBoundaryLeft &&
        clippedLineP2[X_COORDINATE] < xBoundaryLeft) ||
        (clippedLineP1[Y_COORDINATE] < yBoundaryDown &&
         clippedLineP2[Y_COORDINATE] < yBoundaryDown))
        for (i = 0; i < 3; i++)
            clippedLineP1[i] = clippedLineP2[i] = 0;
        else {
        if (clippedLineP1[X_COORDINATE] < xBoundaryLeft) {
            clippedLineP1[X_COORDINATE] = xBoundaryLeft;
            clippedLineP1[Y_COORDINATE] =
            ((1-a2)*givenLineP1[Y_COORDINATE])+(a2*givenLineP2[Y_COORDINATE]);
        }
        if (clippedLineP2[Y_COORDINATE] < yBoundaryDown) {
            clippedLineP2[Y_COORDINATE] = yBoundaryDown;
            clippedLineP2[X_COORDINATE] =
            ((1-a1)*givenLineP1[X_COORDINATE])+(a1*givenLineP2[X_COORDINATE]);
        }
        }
    }
    /* Case 3: */
    else if (a2 <= a3 && a3 < a4 && a4 <= a1){
        /* If both points are above yBoundaryUp or right of
         xBoundaryRight, then the line segment is completely outside. */
        if ((clippedLineP1[X_COORDINATE] > xBoundaryRight &&
        clippedLineP2[X_COORDINATE] > xBoundaryRight) ||
        (clippedLineP1[Y_COORDINATE] > yBoundaryUp &&
         clippedLineP2[Y_COORDINATE] > yBoundaryUp))
        for (i = 0; i < 3; i++)
            clippedLineP1[i] = clippedLineP2[i] = 0;
        else {
        if (clippedLineP1[Y_COORDINATE] > yBoundaryUp) {
            clippedLineP1[Y_COORDINATE] = yBoundaryUp;
            clippedLineP1[X_COORDINATE] =
            ((1-a3)*givenLineP1[X_COORDINATE])+(a3*givenLineP2[X_COORDINATE]);
        }
        if (clippedLineP2[X_COORDINATE] > xBoundaryRight) {
            clippedLineP2[X_COORDINATE] = xBoundaryRight;
            clippedLineP2[Y_COORDINATE] =
            ((1-a4)*givenLineP1[Y_COORDINATE])+(a4*givenLineP2[Y_COORDINATE]);
        }
        }
    }
    /* Case 4: */
    else if (a2 < a1 && a1 < a4 && a4 < a3) {
        /* If both points are below yBoundaryDown or right of
         xBoundaryRight, then the line segment is completely outside. */
        if ((clippedLineP1[X_COORDINATE] > xBoundaryRight &&
        clippedLineP2[X_COORDINATE] > xBoundaryRight) ||
        (clippedLineP1[Y_COORDINATE] < yBoundaryDown &&
         clippedLineP2[Y_COORDINATE] < yBoundaryDown))
        for (i = 0; i < 3; i++)
            clippedLineP1[i] = clippedLineP2[i] = 0;
        else  {
        if (clippedLineP1[Y_COORDINATE] < yBoundaryDown) {
            clippedLineP1[Y_COORDINATE] = yBoundaryDown;
            clippedLineP1[X_COORDINATE] =
            ((1-a1)*givenLineP1[X_COORDINATE])+(a1*givenLineP2[X_COORDINATE]);
        }
        if (clippedLineP2[X_COORDINATE] > xBoundaryRight) {
            clippedLineP2[X_COORDINATE] = xBoundaryRight;
            clippedLineP2[Y_COORDINATE] =
            ((1-a4)*givenLineP1[Y_COORDINATE])+(a4*givenLineP2[Y_COORDINATE]);
        }
        }
    }
    /* Case 5: */
    else if (a2 < a1 && a1 < a3 && a3 < a4){
        /* If both the points are below yBoundaryDown or above
         yBoundaryUp, then the line segment is completely outside. */
        if ((clippedLineP1[Y_COORDINATE] > yBoundaryUp &&
        clippedLineP2[Y_COORDINATE] > yBoundaryUp) ||
        (clippedLineP1[Y_COORDINATE] < yBoundaryDown &&
         clippedLineP2[Y_COORDINATE] < yBoundaryDown))
        for (i = 0; i < 3; i++)
            clippedLineP1[i] = clippedLineP2[i] = 0;
        else {
        if (clippedLineP1[Y_COORDINATE] < yBoundaryDown) {
            clippedLineP1[Y_COORDINATE] = yBoundaryDown;
            clippedLineP1[X_COORDINATE] =
            ((1-a1)*givenLineP1[X_COORDINATE])+(a1*givenLineP2[X_COORDINATE]);
        }
        if (clippedLineP2[Y_COORDINATE] > yBoundaryUp) {
            clippedLineP2[Y_COORDINATE] = yBoundaryUp;
            clippedLineP2[X_COORDINATE] =
            ((1-a3)*givenLineP1[X_COORDINATE])+(a3*givenLineP2[X_COORDINATE]);
        }
        }
    }
    /* Case 6: */
    else if (a1 < a2 && a2 < a4 && a4 < a3) {
        /* If both the points are to the left of xBoundaryLeft or
         to the right of xBoundaryRight, line segment is completely outside. */
         if ((clippedLineP1[X_COORDINATE] > xBoundaryRight &&
        clippedLineP2[X_COORDINATE] > xBoundaryRight) ||
        (clippedLineP1[X_COORDINATE] < xBoundaryLeft &&
         clippedLineP2[X_COORDINATE] < xBoundaryLeft))
        for (i = 0; i < 3; i++)
            clippedLineP1[i] = clippedLineP2[i] = 0;
         else {
         if (clippedLineP1[X_COORDINATE] < xBoundaryLeft) {
             clippedLineP1[X_COORDINATE] = xBoundaryLeft;
             clippedLineP1[Y_COORDINATE] =
             ((1-a2)*givenLineP1[Y_COORDINATE])+(a2*givenLineP2[Y_COORDINATE]);
         }
         if (clippedLineP2[X_COORDINATE] > xBoundaryRight) {
             clippedLineP2[X_COORDINATE] = xBoundaryRight;
             clippedLineP2[Y_COORDINATE] =
             ((1-a4)*givenLineP1[Y_COORDINATE])+(a4*givenLineP2[Y_COORDINATE]);
         }
         }
    }
    /* Case 7: */
    else if (a3 < a2 && a2 < a4 && a4 < a1) {
        /* If both the points are to the left of xBoundaryLeft or
         to the right of xBoundaryRight, line segment is completely outside. */
         if ((clippedLineP1[X_COORDINATE] > xBoundaryRight &&
        clippedLineP2[X_COORDINATE] > xBoundaryRight) ||
        (clippedLineP1[X_COORDINATE] < xBoundaryLeft &&
         clippedLineP2[X_COORDINATE] < xBoundaryLeft))
        for (i = 0; i < 3; i++)
            clippedLineP1[i] = clippedLineP2[i] = 0;
         else {
         if (clippedLineP1[X_COORDINATE] < xBoundaryLeft) {
             clippedLineP1[X_COORDINATE] = xBoundaryLeft;
             clippedLineP1[Y_COORDINATE] =
             ((1-a2)*givenLineP1[Y_COORDINATE])+(a2*givenLineP2[Y_COORDINATE]);
         }
         if (clippedLineP2[X_COORDINATE] > xBoundaryRight) {
             clippedLineP2[X_COORDINATE] = xBoundaryRight;
             clippedLineP2[Y_COORDINATE] =
             ((1-a4)*givenLineP1[Y_COORDINATE])+(a4*givenLineP2[Y_COORDINATE]);
         }
         }
    }


       /* Case 8:  */
    else if (a2 < a3 && a3 < a1 && a1 < a4) {
        /* If both the points are below yBoundaryDown or above
         yBoundaryUp, then the line segment is completely outside. */
        if ((clippedLineP1[Y_COORDINATE] > yBoundaryUp &&
        clippedLineP2[Y_COORDINATE] > yBoundaryUp) ||
        (clippedLineP1[Y_COORDINATE] < yBoundaryDown &&
         clippedLineP2[Y_COORDINATE] < yBoundaryDown))
        for (i = 0; i < 3; i++)
            clippedLineP1[i] = clippedLineP2[i] = 0;
        else {
        if (clippedLineP1[Y_COORDINATE] > yBoundaryUp) {
            clippedLineP1[Y_COORDINATE] = yBoundaryUp;
                clippedLineP1[X_COORDINATE] =
            ((1-a3)*givenLineP1[X_COORDINATE])+(a3*givenLineP2[X_COORDINATE]);
        }
        if (clippedLineP2[Y_COORDINATE] < yBoundaryDown) {
            clippedLineP2[Y_COORDINATE] = yBoundaryDown;
            clippedLineP2[X_COORDINATE] =
            ((1-a1)*givenLineP1[X_COORDINATE])+(a1*givenLineP2[X_COORDINATE]);
        }
        }
    }
    /* Line does not pass inside: */
    else
        for (i = 0; i < 3; i++)
        clippedLineP1[i] = clippedLineP2[i] = 0;
    }

    glutInit (&argc, argv);
    glutCreateWindow ("Liang Barsky");
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (400, 400);
    glutInitWindowSize (500, 500);
    glutDisplayFunc (display);
    myInit();
    glutMainLoop();
}
