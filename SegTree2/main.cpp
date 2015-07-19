#include<GL/glut.h>
#include<GL/glu.h>
#include<windows.h>
#include<stdio.h>
#include<stack>
#include<vector>
#include<algorithm>


using namespace std;

int oo=100;
int ww,wh;
int blkh = 20, seph = 40, sepx = 15;
int n, num;


int arr[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int tree[48];
int TL, TR;
vector<int> pts;
vector<bool> taken;

bool reBuild=true;

int wait=0;
int stx = 25, sty = 400;

GLfloat normal[] = {.3,.5,.9};
GLfloat recursing[] = {1, 1, 1};
GLfloat updateRecursing[] = {1, 0, 0};
GLfloat fontColor[] = {1, 1, 1};
GLfloat blackColor[] = {0, 0, 0};
GLfloat foundNode[] = {0, 1, 0};
GLfloat positiveColor[] = {.9, .3, .2};

bool label[48];

struct interval {
    int l,r;
};

struct greens {
    GLint x, y, sz, v;
};

int L[48], R[48];

interval intervals[20];

stack<greens> st;

int done=0;

void drawText(char *str, int x, int y) {
    glRasterPos2i(x, y);
    GLvoid *style =GLUT_BITMAP_HELVETICA_12;
    for(int i=0; str[i]; i++)
        glutBitmapCharacter(style, str[i]);
}

bool rec=true;
void displayNode(int x, int y, int v, int sz, bool show = true) {

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + sz, y);
    glVertex2f(x + sz, y-blkh);
    glVertex2f(x, y - blkh);
    glEnd();
    char s[5];
    itoa(tree[v], s, 10);
    if(show) {
        glColor3fv(fontColor);
        drawText(s, x + sz/2 - 3, y - blkh + 4);

        if(label[v]==0) {
            glColor3fv(blackColor);

            if(TL==TR) {
                R[v]=pts[TL/2 + 1];
                if(TL % 2==0) {
                    L[v]=pts[TL/2];
                } else L[v]=pts[TL/2 + 1];
                puts("leaf");
            } else {
                L[v]=L[v<<1];
                R[v]=R[v<<1|1];
            }

            //printf("%d %d %d\n",L[v],R[v],v);
            if(L[v] != -oo)itoa(L[v], s, 10);
            else strcpy(s,"-oo");
            puts(s);
            drawText(s, x, y + 4);
            if(R[v] != oo) itoa(R[v], s, 10);
            else strcpy(s,"oo");
            drawText(s, x + sz - 5, y + 4);
            label[v]=1;
        }
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
    displayNode(x, y, v, sz, false);
    glColor3fv(updateRecursing);
    if(l<=L[v] && R[v] <= r) {
        tree[v]++;
        glColor3fv(foundNode);
        displayNode(x,y,v,sz);
        glColor3fv(updateRecursing);
        st.push(greens {x,y,sz, v});

        return tree[v];
    } else if(tl == tr) {
        glColor3fv(normal);
        displayNode(x, y, v, sz);
        glColor3fv(normal);
        return 0;
    }

    int mid = tl + tr >> 1;
    int midl = L[v] + R[v] >> 1;
    int szc = (sz - sepx) / 2;
    int q1=0,q2=0;

    if(tr - tl - 1 == 0) query(v << 1 | 1, mid + 1, tr, l, r, x + szc + sepx, y - blkh - seph, szc);
    else {
        if(l <= R[v<<1]) q1=query(v << 1, tl, mid, l, r, x, y - blkh - seph, szc);
        if(r > L[v<<1|1]) q2=query(v << 1 | 1, mid + 1, tr, l, r, x + szc + sepx, y - blkh - seph, szc);
    }
    glColor3fv(normal);
    displayNode(x, y, v, sz);
    glColor3fv(normal);
    return q1+q2;

}

void getSum(int l, int r) {
    glColor3f(1.0,0,0);
    query(1, 0, n - 1, l, r, stx, sty, n * sepx * 5);
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

void build(int v, int tl, int tr, int x, int y, int sz) {
    TL = tl;
    TR = tr;
    glColor3fv(recursing);
    displayNode(x, y, v, sz, false);
    glColor3fv(normal);
    if(tl == tr) {
        tree[v] = arr[tl];
        //printf("%d %d",L[v],R[v]);
        displayNode(x, y, v, sz);
        glColor3fv(normal);
        return;
    }
    int szc = (sz - sepx) / 2;
    int mid = tl + tr >> 1;
    build(v << 1, tl, mid, x, y - blkh - seph, szc);
    build(v << 1 | 1, mid + 1, tr, x + szc + sepx, y - blkh - seph, szc);
    //L[v]=L[v<<1];
    //R[v]=R[v<<1|1];
    tree[v]=tree[v<<1] + tree[v<<1|1];
    TL=tl;
    TR=tr;
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
        } else {
            if(L[v] == R[v]) {
                if(q==L[v])
                    st.push(greens {x,y,sz,v});
                else {
                    glColor3fv(normal);
                    displayNode(x, y, v, sz);
                    return 0;
                }
            } else {
                if(q>L[v] && q < R[v]) st.push(greens {x,y,sz,v});
                else {
                    glColor3fv(normal);
                    displayNode(x, y, v, sz);
                    return 0;
                }
            }
        }

        return tree[v];
    }
    int szc = (sz - sepx) / 2;
    int mid = tl + tr >> 1;
    int ret=tree[v];

    if(tr - tl - 1 == 0) {
        ret+=cnt(v<<1, tl, mid, q, x, y - blkh - seph, szc);
        ret+=cnt(v<<1|1, mid + 1,tr,q,  x + szc + sepx, y - blkh - seph, szc);
    }

    else {
        if(q <= R[v<<1]) ret+=cnt(v<<1, tl, mid, q, x, y - blkh - seph, szc);
        else ret+=cnt(v<<1|1, mid + 1,tr,q,  x + szc + sepx, y - blkh - seph, szc);
    }
    if(tree[v]==0) {
        glColor3fv(normal);
        displayNode(x, y, v, sz);
    } else st.push(greens {x,y,sz,v});
    return ret;

}

void takeQueries() {
    int x,y;

    int ch;
    //printf("Please Choose one of the following :\n1.Insert Interval(0-15)\n2.Query a point\n");
    //scanf("%d",&ch);

    while(st.size()>0) {
        greens gr = st.top();
        glColor3fv(normal);
        displayNode(gr.x, gr.y, gr.v, gr.sz);
        st.pop();
    }

    if(done < num) {
        x=intervals[done].l;
        y=intervals[done].r;
        done++;
        //scanf("%d%d",&x,&y);
            glColor3fv(updateRecursing);
            wait = 1;
            getSum(x,y);
            glColor3fv(updateRecursing);
            wait = 0;
        system("pause");
    } else  {
        scanf("%d",&x);
            wait = 1;
            y=cnt(1, 0, n-1, x, stx, sty, n * sepx * 5);
            printf("result of stabbing query is : %d\n",y);
            wait = 0;
            system("pause");
    }


    //Sleep(500);
    glutPostRedisplay();
}

void display() {
    glColor3fv(normal);
    if(reBuild) build(1, 0, n-1, 25, 400, n * sepx * 5);
    reBuild = false;
    takeQueries();
    wait=0;

}

int main(int argc, char **argv) {
    glutInit(&argc, argv);




    scanf("%d",&num);


    pts.push_back(-oo);
    pts.push_back(oo);
    for(int i=0; i<num; i++) {
        int li,ri;
        scanf("%d%d",&li,&ri);
        intervals[i]=interval {li,ri};
        pts.push_back(li);
        pts.push_back(ri);

    }

    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    n=2*pts.size()-3;
    for(int i=0; i<pts.size(); i++) printf("%d ",pts[i]);
    taken.resize(pts.size() + 1);


    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(n * sepx * 5 + 50, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Trial");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
//    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
