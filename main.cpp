#include "GL/glut.h"
#include "iostream"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "algorithm"
using namespace std;

/*---- environment ---------*/
float View_Volume_Len = 100.0;
float Camera_Pos_X = 0.0;
float Camera_Pos_Y = 0.0;
float Camera_Pos_Z = 100.0;

/*---- color ---------*/
GLfloat COLOR_BLACK[4] = {0.0, 0.0, 0.0, 1.0};  //black
GLfloat COLOR_WHITE[4] = {1.0, 1.0, 1.0, 1.0}; //white
GLfloat COLOR_RED[4] = {1.0, 0.0, 0.0, 1.0};  //red
GLfloat COLOR_YELLOW[4] = {1.0, 1.0, 0.0, 1.0};  //yellow
GLfloat COLOR_GREEN[4] = {0.0, 1.0, 0.0, 1.0};  //green
GLfloat COLOR_BLUE[4] = {0.0, 0.0, 1.0, 1.0};  //blue
GLfloat COLOR_ORANGE[4] = {1.0, 0.528, 0.0, 1.0};  //orange

/*---- math ---------*/
float PI = 3.1415926;

/*---- letter X,Y,Z ---------*/
float X_Y_Z_LEN = 5.0;  //X Y ZÈýžö×ÖÄžµÄµÄ±ß³€

/*---- axis ---------*/
float AXIS_WIDTH = 3.0;  //the width of axis
float AXIS_LEN = 80.0;  //×ø±êÖáÕý²¿·Ö³€¶È
float n_pyramid_r = 4.0;  //Ô²×¶Ìåµ×²¿µÄÕý¶à±ßÐÎµÄ°ëŸ¶
float n_pyramid_h = 10.0;  //Ô²×¶ÌåµÄžß¶È

/*---- mouse ---------*/
bool mouseLeftDown;
float mouseX, mouseY;
float AngleX, AngleY;




float PArray[500][3];
int N;
void clean1();



/*---- environment settings ---------*/
void init(void){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    srand((int)time(0));
    clean1();
}

void reshape(int w, int h){
	int t;
	if( w<h ) t = w; else t = h;
    //int t = min(w,h);
    glViewport (0, 0,  t, t);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-View_Volume_Len, View_Volume_Len, \
            -View_Volume_Len, View_Volume_Len, \
            1.1, 2*View_Volume_Len);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(Camera_Pos_X, Camera_Pos_Y, Camera_Pos_Z, \
              0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

/*---- axis and letter X,Y,Z---------*/
void typeXYZ(){
    glPushMatrix();
        glLineWidth(3.0);
        glColor4fv(COLOR_RED);
        glBegin(GL_LINES);
            glVertex3f(-X_Y_Z_LEN, X_Y_Z_LEN, 0.0);
            glVertex3f(X_Y_Z_LEN, -X_Y_Z_LEN, 0.0);
            glVertex3f(X_Y_Z_LEN, X_Y_Z_LEN, 0.0);
            glVertex3f(-X_Y_Z_LEN, -X_Y_Z_LEN, 0.0);
        glEnd();

        glTranslatef(2*X_Y_Z_LEN+X_Y_Z_LEN/2, 0.0, 0.0);
        glColor4fv(COLOR_GREEN);
        glBegin(GL_LINES);
            glVertex3f(-X_Y_Z_LEN, X_Y_Z_LEN, 0.0);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(X_Y_Z_LEN, X_Y_Z_LEN, 0.0);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, -X_Y_Z_LEN, 0.0);
        glEnd();

        glTranslatef(2*X_Y_Z_LEN+X_Y_Z_LEN/2, 0.0, 0.0);
        glColor4fv(COLOR_BLUE);
        glBegin(GL_LINES);
            glVertex3f(-X_Y_Z_LEN, X_Y_Z_LEN, 0.0);
            glVertex3f(X_Y_Z_LEN, X_Y_Z_LEN, 0.0);
            glVertex3f(X_Y_Z_LEN, X_Y_Z_LEN, 0.0);
            glVertex3f(-X_Y_Z_LEN, -X_Y_Z_LEN, 0.0);
            glVertex3f(-X_Y_Z_LEN, -X_Y_Z_LEN, 0.0);
            glVertex3f(X_Y_Z_LEN, -X_Y_Z_LEN, 0.0);
        glEnd();
    glPopMatrix();
}

void draw_n_pyramid(int n){
    float temp1 = 2*PI/n;
	int i;

    for(i=0;i<n;++i){
        glBegin(GL_TRIANGLES);
            glVertex3f( n_pyramid_r*cos(temp1*i), n_pyramid_r*sin(temp1*i), 0.0 );
            glVertex3f( n_pyramid_r*cos(temp1*(i+1)), n_pyramid_r*sin(temp1*(i+1)), 0.0 );
            glVertex3f( 0.0, 0.0, n_pyramid_h );
        glEnd();
    }
    glBegin(GL_POLYGON);
        for(i=n-1;i>=0;--i)
            glVertex3f( n_pyramid_r*cos(temp1*i), n_pyramid_r*sin(temp1*i), 0.0 );
    glEnd();
}

void xyzAxis(void){
    //x axis
    glColor4fv(COLOR_BLACK);
    glLineWidth(AXIS_WIDTH);
    glBegin(GL_LINES);
        glVertex3f(-AXIS_LEN*2/3, 0.0, 0.0);
        glVertex3f(AXIS_LEN, 0.0, 0.0);
    glEnd();
    glPushMatrix();
        glTranslatef(AXIS_LEN, 0.0, 0.0);
        glRotatef(90.0, 0.0, 1.0, 0.0);
        glLineWidth(1.0);
        glColor4fv(COLOR_RED);
        draw_n_pyramid(10);
    glPopMatrix();

    //y axis
    glColor4fv(COLOR_BLACK);
    glLineWidth(AXIS_WIDTH);
    glBegin(GL_LINES);
        glVertex3f(0.0, -AXIS_LEN*2/3, 0.0);
        glVertex3f(0.0, AXIS_LEN, 0.0);
    glEnd();
    glPushMatrix();
        glTranslatef(0.0, AXIS_LEN, 0.0);
        glRotatef(90.0, -1.0, 0.0, 0.0);
        glLineWidth(1.0);
        glColor4fv(COLOR_GREEN);
        draw_n_pyramid(10);
    glPopMatrix();

    //z axis
    glColor4fv(COLOR_BLACK);
    glLineWidth(AXIS_WIDTH);
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, -AXIS_LEN*2/3);
        glVertex3f(0.0, 0.0, AXIS_LEN);
    glEnd();
    glPushMatrix();
        glTranslatef(0.0, 0.0, AXIS_LEN);
        glLineWidth(1.0);
        glColor4fv(COLOR_BLUE);
        draw_n_pyramid(10);
    glPopMatrix();
}




/*---- Interaction with people ---------*/
void keyboard(unsigned char key,int x,int y){
    switch(key){
        case 'a':
            ++N;
            cout<<N<<endl;
            int t;
            t = rand()%2;
            if(!t)
                PArray[N][0] = (float)(rand()%((int)View_Volume_Len-20));
            else
                PArray[N][0] = -(float)(rand()%((int)View_Volume_Len-20));

            t = rand()%2;
            if(!t)
                PArray[N][1] = (float)(rand()%((int)View_Volume_Len-20));
            else
                PArray[N][1] = -(float)(rand()%((int)View_Volume_Len-20));

            t = rand()%2;
            if(!t)
                PArray[N][2] = (float)(rand()%((int)View_Volume_Len-20));
            else
                PArray[N][2] = -(float)(rand()%((int)View_Volume_Len-20));
            glutPostRedisplay();
            break;
        case 'b':
            --N;
            cout<<N<<endl;
            glutPostRedisplay();
            break;
		case 27:
			cout<<"ESC"<<endl;
			glutPostRedisplay();
			break;
		default:
			break;
    }
}

void mouse(int button, int state, int x, int y){
    mouseX = x,  mouseY = y;
    if( button==GLUT_LEFT_BUTTON ){
        if( state==GLUT_DOWN )
            mouseLeftDown = true;
        else if( state==GLUT_UP )
            mouseLeftDown = false;
    }
}

void mouseMotion(int x, int y){
    if(mouseLeftDown){
        AngleY += (x-mouseX);
        AngleX += (y-mouseY);
        mouseX = x;
        mouseY = y;
    }
    glutPostRedisplay();
}


void clean1(){
	N = 0;
	PArray[0][0] = 0, PArray[0][1] = 0, PArray[0][2] = 0;
}


double pows(double a, int x){
    if(x==0)
        return 1.0;
    double res = 1.0;
    for(int i=1;i<=x;++i)
        res *= a;
    return res;
}
double C(int n,int r){
    double res = 1.0;
    for(int i=1;i<=r;++i){
        res = res*(n+1-i)/i;
    }
    return res;
}

double Bi_n(int i, int n, double t){
    double sum=1,sumB,B_sumt,B_sumT;

    B_sumt = pows(t, i);
    B_sumT = pows(1-t, n-i);
    sumB = C(n,i) * B_sumt * B_sumT;
    return sumB;
}

void draw_bezior(){
    double t;
    double sum=1,sumB;

    glPointSize(2.0);
    for(t=0;t<=1.0;t+=0.002){
        double pt[3];
        pt[0] = pt[1] = pt[2] = 0.0;
        for(int i=0;i<=N;i++){
            double bi_n=Bi_n(i,N,t);
            pt[0] += PArray[i][0]*bi_n;
            pt[1] += PArray[i][1]*bi_n;
            pt[2] += PArray[i][2]*bi_n;
        }
        float pt2[3];
        pt2[0] = (float)pt[0], pt2[1] = (float)pt[1], pt2[2] = (float)pt[2];
        glBegin(GL_POINTS);
            glVertex3fv(pt2);
        glEnd();
        glutPostRedisplay();
    }
}

void draw1(){
	glPointSize(6.0f);
	glColor4fv(COLOR_RED);
	for(int i=0;i<=N;++i){
        glBegin(GL_POINTS);
            glVertex3fv(PArray[i]);
        glEnd();
	}
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
        for(int i=0;i<=N;++i)
            glVertex3fv(PArray[i]);
	glEnd();

	glPointSize(3.0f);
	glColor4fv(COLOR_BLACK);
    draw_bezior();
}


/*---- Main Display ---------*/
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        glTranslatef(-AXIS_LEN*4/5, -AXIS_LEN*4/5, AXIS_LEN*4/5);
        typeXYZ();
    glPopMatrix();

    glPushMatrix();
        glRotatef(AngleX, 1.0, 0.0, 0.0);
        glRotatef(AngleY, 0.0, 1.0, 0.0);
        /*----------------------------------------*/
        glPushMatrix();
            xyzAxis();
        glPopMatrix();
		glPushMatrix();
			draw1();
		glPopMatrix();

        /*----------------------------------------*/
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}







int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (700, 700);
    glutInitWindowPosition (0, 0);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
