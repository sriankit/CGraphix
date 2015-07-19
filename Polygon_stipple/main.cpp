#include<GL/glut.h>

GLfloat win_left = 0.0;
GLfloat win_right = 540.0;
GLfloat win_bottom = 0.0;
GLfloat win_top = 140.0;

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
    //glClear(GL_COLOR_BUFFER_BIT);
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
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
    gluOrtho2D(win_left, win_right, win_bottom, win_top);
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

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(350, 150);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
//Displaying Points, Lines, and Polygons 67
    glutReshapeFunc(reshape);
    glutKeyboardFunc(my_keyboard);
    glutMainLoop();
    return 0;
}
