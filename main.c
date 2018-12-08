#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define pi 3.14
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int value);
static void on_timer2(int value);
static void on_timer3(int value);
static void on_timer4(int value);
static void on_display(void);
static void on_reshape(int width, int height);
static float x_curr, y_curr; 
const static float r = 20;
static float x_k =25;
static float y_k = 25;
static float x;
static float y;
static float i;
static float b;

static float phi, theta;
static float delta_phi, delta_theta;
static int timer_active;
static int timer_active2;
static int timer_active3;
static void on_display(void);
int main(int argc,char** argv)
{

	//Inicijalizacija prozora
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);	
	glutInitWindowSize(1300,800);

	glutCreateWindow(argv[0]);
	
	  /* Incijalizuju se globalne promenljive. */
    phi = theta = 0;
    delta_phi = delta_theta = pi / 90;
    glClearColor(0.75, 0.75, 0.75, 0);
	glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
	glutDisplayFunc(on_display);
    x_curr = 0;
    y_curr = 0;

    x_k =5;
    y_k =5;
    glutTimerFunc(50, on_timer4, 0);
    glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}
static void on_reshape(int width, int height)
{
    /* Postavlja se viewport. */
    glViewport(0, 0, width, height);

    /* Postavljaju se parametri projekcije. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 1500);
}
static void on_display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /*gluLookAt(1100 * cos(theta) * cos(phi),
              1100 * cos(theta) * sin(phi),
             1100 + 220*5 * sin(theta),
             0,0,0,
              0, 1, 0);*/
    gluLookAt(0, 0, 1100, 0, 0, 0, 0, 1, 0); 
    glPushMatrix();
        glTranslatef(-880,x,0);
        glColor3f(0, 0, 1);
        glScalef(0.2,2,0.2);
        glutWireCube(100);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(880,y,0);
        glColor3f(0, 1, 0);
        glScalef(0.2,2,0.2);
        glutWireCube(100);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0,0);
        glTranslatef(x_curr,y_curr,0);
        glutSolidSphere(r,50,50);
    glPopMatrix();
    /*();
        glColor3f(0.5,0.5,0.5);
        glTranslatef(-20,0,0);
        glScalef(2.3,1.5,0);
        glutSolidCube(800);
    glPopMatrix();*/
     glColor3f(0, 0, 0);
     glBegin(GL_LINE_LOOP);
        glVertex3f(900, 580, 0);
        glVertex3f(-900, 580, 0);
        glVertex3f(-900, -580, 0);
        glVertex3f(900,-580, 0);    
    glEnd();
	glutSwapBuffers();
}
static void on_timer(int value)
{
    if (value != 0)
        return;

    /* Provere i pomeranja Igraceve plocice*/
    if((x+i >= -480 && i < 0) || (x+i<= 480 && i >0))
         x+=i;
    if(timer_active)
        glutTimerFunc(10, on_timer, 0);
}
static void on_timer2(int value)
{
    if (value != 0)
        return;
    y+=b;
    if(y+b >= 480 || y+b<= -480)
        b*=-1;
    if(timer_active2)
        glutTimerFunc(10, on_timer2, 0);
}
static void on_timer3(int value)
{
    if (value != 0)
        return;

    y_curr += y_k;
    if(y_curr>=560 || y_curr <=-560)
        y_k*=-1;

    x_curr-= x_k;
   if((y_curr>=(x-100) && y_curr<=(x+100) && x_curr == -860) || (y_curr>=(x-100) && y_curr<=(x+100) && x_curr == 860))
    {
        x_k*=-1;
    }
   else if(x_curr <= -880 || x_curr >= 880)
   {
        x_curr = 0;
        y_curr = 0;
        timer_active3 = 0;
        return;
   }
    if(timer_active3)
        glutTimerFunc(20, on_timer3, 0);
}
static void on_timer4(int value)
{
    if (value != 0)
        return;
    glutPostRedisplay();
    glutTimerFunc(50, on_timer4, 0);
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;

    case 'g':
            i = -25;
            glutTimerFunc(10, on_timer, 0);
        break;
    case 'h':
            i =25;
            glutTimerFunc(10, on_timer, 0);
        break;
    case 'r': 
      if (!timer_active2) {
            timer_active2 = 1;
            b = 5;
            glutTimerFunc(10, on_timer2, 0);
        }
        break;
    case 'G':
        /* Pokrece se animacija. */
        if (!timer_active3) {
            glutTimerFunc(20, on_timer3, 0);
            timer_active3 = 1;
        }
        break;
      case 'p':
        /* Dekrementira se ugao phi i ponovo iscrtava scena. */
        phi -= delta_phi;
        if (phi > 2 * pi) {
            phi -= 2 * pi;
        } else if (phi < 0) {
            phi += 2 * pi;
        }
        glutPostRedisplay();
        break;
      case 't':
        /*
         * Dekrementira se ugao theta i ponovo iscrtava scena. Ovaj
         * ugao se odrzava u intervalu [-89,89] stepeni.
         */
        theta -= delta_theta;
        if (theta < -(pi / 2 - pi / 180)) {
            theta = -(pi / 2 - pi / 180);
        }
        glutPostRedisplay();
        break;
      case 'R':
        /* Resetuju se uglovi phi i theta na pocetne vrednosti. */
        x=0;
        y=0;
        timer_active3=0;
        timer_active2 = 0;
        timer_active= 0;
        phi = theta = 0;
        glutPostRedisplay();
        break;
      case 'T':
        /*
         * Inkrementira se ugao theta i ponovo iscrtava scena. Ovaj
         * ugao se odrzava u intervalu [-89,89] stepeni.
         */
        theta += delta_theta;
        if (theta > pi / 2 - pi / 180) {
            theta = pi / 2 - pi / 180;
        }
        glutPostRedisplay();
        break;
    case 'P':
        /* Inkrementira se ugao phi i ponovo iscrtava scena. */
        phi += delta_phi;
        if (phi > 2 * pi) {
            phi -= 2 * pi;
        } else if (phi < 0) {
            phi += 2 * pi;
        }
        glutPostRedisplay();
        break;
    }
}