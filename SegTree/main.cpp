#include<GL/glut.h>
#include<GL/glu.h>
#include<windows.h>
#include<stdio.h>
#include<stack>


using namespace std;

int ww,wh;
int blkh = 20, seph = 40, sepx = 20;
int n;

int arr[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int tree[48];
int TL, TR;

bool reBuild=true;

int wait=1;
int stx = 25, sty = 400;

GLfloat normal[] = {.3,.5,.9};
GLfloat recursing[] = {1, 1, 1};
GLfloat updateRecursing[] = {1, 0, 0};
GLfloat fontColor[] = {1, 1, 1};
GLfloat blackColor[] = {0, 0, 0};
GLfloat foundNode[] = {0, 1, 0};
GLfloat positiveColor[] = {.9, .3, .2};

bool label[48];

struct greens {
    GLint x, y, sz, v;
};

stack<greens> st;

void drawText(char *str, int x, int y) {
    glRasterPos2i(x, y);
    GLvoid *style =GLUT_BITMAP_HELVETICA_12;
    for(int i=0; str[i]; i++)
        glutBitmapCharacter(style, str[i]);
}

void displayNode(int x, int y, int v, int sz, bool show = true) {
    //puts("called displayNode");
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + sz, y);
        glVertex2f(x + sz, y-blkh);
        glVertex2f(x, y - blkh);
    glEnd();
    char s[4];
    itoa(tree[v], s, 10);
    if(show) {
        glColor3fv(fontColor);
        drawText(s, x + sz/2 - 3, y - blkh + 4);
    }
    if(label[v]==0) {
        glColor3fv(blackColor);
        itoa(TL, s, 10);
        drawText(s, x, y + 4);
        itoa(TR, s, 10);
        drawText(s, x + sz - 5, y + 4);
        label[v]=1;
    }

    if(wait) {
        Sleep(400);
    }
    glFlush();
}

int query(int v, int tl, int tr, int l, int r, int x, int y, int sz) {
    TL = tl;
    TR = tr;
    glColor3fv(updateRecursing);
    displayNode(x, y, v, sz);
    glColor3fv(updateRecursing);
    if(l<=tl && tr <= r) {
        tree[v]++;
        glColor3fv(foundNode);
        displayNode(x,y,v,sz);
        glColor3fv(updateRecursing);
        st.push(greens {x,y,sz, v});

        return tree[v];
    }
    int mid = tl + tr >> 1;
    int szc = (sz - sepx) / 2;
    int q1=0,q2=0;
    if(l <= mid) q1=query(v << 1, tl, mid, l, r, x, y - blkh - seph, szc);
    if(r > mid) q2=query(v << 1 | 1, mid + 1, tr, l, r, x + szc + sepx, y - blkh - seph, szc);
    glColor3fv(normal);
    displayNode(x, y, v, sz);
    glColor3fv(normal);
    return q1+q2;

}

void getSum(int l, int r) {
    glColor3f(1.0,0,0);
    query(1, 0, n - 1, l, r, stx, sty, n * sepx * 3);
}


void init(void) {
    glClearColor(1.0, 1.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    ww=w;
    wh=h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, w, 0.0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    reBuild=true;
    glClear(GL_COLOR_BUFFER_BIT);

}

/*void printStrokedString(GLbyte *s) {
    GLint len = strlen(s);
    glCallLists(len, GL_BYTE, s);
}*/

void build(int v, int tl, int tr, int x, int y, int sz) {
    TL = tl;
    TR = tr;
    glColor3fv(recursing);
    displayNode(x, y, v, sz, true);
    glColor3fv(normal);
    if(tl == tr) {
        tree[v] = arr[tl];
        displayNode(x, y, v, sz);
        glColor3fv(normal);
        return;
    }
    int szc = (sz - sepx) / 2;
    int mid = tl + tr >> 1;
    build(v << 1, tl, mid, x, y - blkh - seph, szc);
    build(v << 1 | 1, mid + 1, tr, x + szc + sepx, y - blkh - seph, szc);
    tree[v]=tree[v<<1] + tree[v<<1|1];
    displayNode(x, y, v, sz);
    glColor3fv(normal);
    //glutPostRedisplay();
}

int cnt(int v, int tl, int tr, int q, int x, int y, int sz) {
    glColor3fv(positiveColor);
    displayNode(x, y, v, sz);
    if(tl == tr) {
        if(tree[v]==0) {
            glColor3fv(normal);
            displayNode(x, y, v, sz);
        } else st.push(greens {x,y,sz,v});
        return tree[v];
    }
    int szc = (sz - sepx) / 2;
    int mid = tl + tr >> 1;
    int ret=tree[v];
    if(q <= mid) ret+=cnt(v<<1, tl, mid, q, x, y - blkh - seph, szc);
    else ret+=cnt(v<<1|1, mid + 1,tr,q,  x + szc + sepx, y - blkh - seph, szc);
    if(tree[v]==0) {
        glColor3fv(normal);
        displayNode(x, y, v, sz);
    } else st.push(greens {x,y,sz,v});
    return ret;

}

void takeQueries() {
    int x,y;

    int ch;
    printf("Please Choose one of the following :\n1.Insert Interval(0-15)\n2.Query a point\n");
    scanf("%d",&ch);

    while(st.size()>0) {
        greens gr = st.top();
        glColor3fv(normal);
        displayNode(gr.x, gr.y, gr.v, gr.sz);
        st.pop();
    }

    if(ch == 1) {
        scanf("%d%d",&x,&y);
        if(x<0 || x>15 || y<0 || y>15) {
            puts("Invalid input");
        } else {
            glColor3fv(updateRecursing);
            wait = 1;
            getSum(x,y);
            glColor3fv(updateRecursing);
            wait = 0;
        }
    } else if(ch == 2) {
        scanf("%d",&x);
        if(x<0 || x>15) puts("Invalid input");
        else {
            wait = 1;
            y=cnt(1, 0, n-1, x, stx, sty, n * sepx * 3);
            printf("result of stabbing query is : %d\n",y);
            wait = 0;
        }
    } else puts("Invalid Choice");


    //Sleep(500);
    glutPostRedisplay();
}

void display() {
    //printf("called display");
    //glClear(GL_COLOR_BUFFER_BIT);
    //glPushMatrix();
    glColor3fv(normal);
    //glRectf(250, 100, 30, 60);
    //wait=1;
    if(reBuild) build(1, 0, n-1, 25, 400, n * sepx * 3);
    //glFlush();
    reBuild = false;
    takeQueries();
    wait=0;
    //glColor3fv(updateRecursing);
    //wait = 1;
    //getSum(3, 14);
    //displayNode(30, 200, 5);
    //glutSwapBuffers();
}




int main(int argc, char **argv) {
    glutInit(&argc, argv);
    n = 13;

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(n * sepx * 3 + 50, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Trial");
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
//    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
