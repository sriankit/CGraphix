/*
 *  window_viewport.c
 *  This program demonstrates the window-viewport transformation
 *	and the reshape callback in openGL/GLUT.
 */

#include <GL/glut.h>

/* globals for world window */
GLfloat win_left = 0.0;
GLfloat win_right = 14.0;
GLfloat win_bottom = 0.0;
GLfloat win_top = 14.0;

//#define HOUSE 1
/*
* display: display function called when main loop is entered and
* when window is marked for redisplay
*/

void display(void) {
    GLubyte fly[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x03, 0x80, 0x01, 0xC0, 0x06, 0xC0, 0x03, 0x60,
        0x04, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0C, 0x20,
        0x04, 0x18, 0x18, 0x20, 0x04, 0x0C, 0x30, 0x20,
        0x04, 0x06, 0x60, 0x20, 0x44, 0x03, 0xC0, 0x22,
        0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
        0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
        0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
        0x66, 0x01, 0x80, 0x66, 0x33, 0x01, 0x80, 0xCC,
        0x19, 0x81, 0x81, 0x98, 0x0C, 0xC1, 0x83, 0x30,
        0x07, 0xe1, 0x87, 0xe0, 0x03, 0x3f, 0xfc, 0xc0,
        0x03, 0x31, 0x8c, 0xc0, 0x03, 0x33, 0xcc, 0xc0,
        0x06, 0x64, 0x26, 0x60, 0x0c, 0xcc, 0x33, 0x30,
        0x18, 0xcc, 0x33, 0x18, 0x10, 0xc4, 0x23, 0x08,
        0x10, 0x63, 0xC6, 0x08, 0x10, 0x30, 0x0c, 0x08,
        0x10, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x08
    };
    GLubyte halftone[] = {
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
//Figure 2-11 Stippled Polygons
//66 Chapter 2: State Management and Drawing Geometric Objects
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55
    };
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    /* draw one solid, unstippled rectangle, */
    /* then two stippled rectangles */
    glRectf(25.0, 25.0, 125.0, 125.0);
    glEnable(GL_POLYGON_STIPPLE);
    glPolygonStipple(fly);
    glRectf(625.0, 25.0, 225.0, 125.0);
    glPolygonStipple(halftone);
    glRectf(225.0, 25.0, 325.0, 125.0);
    glDisable(GL_POLYGON_STIPPLE);
    glFlush();
}

void draw_house()
{

    /* clear the window */
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	/* house shape *
	glColor3f(0.0, 0.5, 0.1);
	glBegin(GL_POLYGON);
		glVertex2i(0, 0);
		glVertex2i(10, 0);
		glVertex2i(10, 10);
		glVertex2i(0, 10);
	glEnd();

	/* door *
	glColor3f(0.0, 0.1, 0.1);
	glBegin(GL_POLYGON);
		glVertex2i(4, 0);
		glVertex2i(4, 3);
		glVertex2i(6, 3);
		glVertex2i(6, 0);
	glEnd();

	/* windows */
	glColor3f(0.5, 0.2, 0.1);
	glBegin(GL_QUADS);
		glVertex2i(1, 1);
		glVertex2i(1, 9);
		glVertex2i(3, 9);
		glVertex2i(3, 1);

		glVertex2i(7, 1);
		glVertex2i(7, 9);
		glVertex2i(9, 9);
		glVertex2i(9, 1);

		glVertex2i(3, 4);
		glVertex2i(3, 6);
		glVertex2i(7, 6);
		glVertex2i(7, 4);
	glEnd();

	/* roof *
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2i(0, 10);
		glVertex2i(5, 13);
		glVertex2i(10, 10);
	glEnd();

	/* show the output */
	glFlush();
}

void my_reshape(int w, int h)
{
	/* 3 possibilities for viewports */

	/* Possibility 1: always use entire screen window as viewport */
	/* graphics will distort when non-square aspect ratio) */
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	/* Possibility 2: always use a square viewport as big as possible */
	/* graphics will remain undisorted, but large portions of screen window */
	/* may be unused */
	//if(w<=h) glViewport(0, 0, w, w);
	//else glViewport(0, 0, h, h);

	/* Possibility 3: keep same viewport throughout */
	/* Graphics will be clipped as window is made smaller */
	//glViewport(0, 0, 500, 500);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(win_left, win_right, win_bottom, win_top);

	//glMatrixMode(GL_MODELVIEW);
}

void my_keyboard(unsigned char key, int x, int y)
{
	GLfloat win_center_x, win_center_y;

	switch(key){
		/* pan up */
		case 'w':
		case 'W':
			win_bottom += 1.0;
			win_top += 1.0;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(win_left, win_right, win_bottom, win_top);
			glutPostRedisplay();
			break;
		/* pan down */
		case 's':
		case 'S':
			win_bottom -= 1.0;
			win_top -= 1.0;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(win_left, win_right, win_bottom, win_top);
			glutPostRedisplay();
			break;
		/* pan left */
		case 'a':
		case 'A':
			win_left -= 1.0;
			win_right -= 1.0;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(win_left, win_right, win_bottom, win_top);
			glutPostRedisplay();
			break;
		/* pan right */
		case 'd':
		case 'D':
			win_left += 1.0;
			win_right += 1.0;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(win_left, win_right, win_bottom, win_top);
			glutPostRedisplay();
			break;
		/* zoom in */
		case '=':
		case '+':
			win_center_x = (win_left + win_right)/2.0;
			win_center_y = (win_bottom + win_top)/2.0;
			win_left = ((win_left - win_center_x)*0.5) + win_center_x;
			win_right = ((win_right - win_center_x)*0.5) + win_center_x;
			win_bottom = ((win_bottom - win_center_y)*0.5) + win_center_y;
			win_top = ((win_top - win_center_y)*0.5) + win_center_y;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(win_left, win_right, win_bottom, win_top);
			glutPostRedisplay();
			break;
		/* zoom out */
		case '-':
			win_center_x = (win_left + win_right)/2.0;
			win_center_y = (win_bottom + win_top)/2.0;
			win_left = ((win_left - win_center_x)*2.0) + win_center_x;
			win_right = ((win_right - win_center_x)*2.0) + win_center_x;
			win_bottom = ((win_bottom - win_center_y)*2.0) + win_center_y;
			win_top = ((win_top - win_center_y)*2.0) + win_center_y;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(win_left, win_right, win_bottom, win_top);
			glutPostRedisplay();
			break;
		default:
			break;
	}
}

int main(int argc, char **argv)
{
	/* create window, set coordinate space */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Windows, Viewports, and Reshaping");

	/* register callbacks */
	glutDisplayFunc(draw_house);
	glutReshapeFunc(my_reshape);
	glutKeyboardFunc(my_keyboard);

	/* enter the main loop */
	glutMainLoop();

	return 0;
}

