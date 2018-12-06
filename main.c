#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#define pi 3.14
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int value);
static void on_display(void);
static void on_reshape(int width, int height);

static float x;
static float y;
static float i;
static float b;
static int promena = 0;
static float phi, theta;
static float delta_phi, delta_theta;
static int timer_active;
static int timer_active2;
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
    //glColor3f(0,0,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 1000, 0, 0, 0, 0, 1, 0);
   glColor3f(0.9, 0.5, 0.5);

    glPushMatrix();
       glTranslatef(1.5, 4, 0);
       glutSolidSphere(0.2, 10, 10);
       glTranslatef(0.1, 0, 0);
       glutSolidSphere(0.16, 10, 10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-800,x,0);
        glRotatef(90, 1, 0, 0);
        glColor3f(0, 0, 1);
         gluLookAt(5 * cos(theta) * cos(phi),
              5* cos(theta) * sin(phi),
              5* sin(theta),
              0, 0, 0, 0, 1, 0);
        glRotatef(90, 0, 0, 1);
        glutWireCube(100);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(800,y,0);
        glColor3f(0, 1, 0);
         gluLookAt(5 * cos(theta) * cos(phi),
              5* cos(theta) * sin(phi),
              5* sin(theta),
              0, 0, 0, 0, 1, 0);
        glutWireCube(100);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0,0);
         gluLookAt(5 * cos(theta) * cos(phi),
              5* cos(theta) * sin(phi),
              5* sin(theta),
              0, 0, 0, 0, 1, 0);
        glutSolidSphere(20,1000,1000);
    glPopMatrix();
    /*
    //Inicijalizacija plocica
    glBegin(GL_POLYGON);
        glVertex3f(0.97,0.3,0);
        glVertex3f(0.92,0.3,0);
        glVertex3f(0.92,-0.3,0);
        glVertex3f(0.97,-0.3,0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(-0.97,0.3,0);
        glVertex3f(-0.92,0.3,0);
        glVertex3f(-0.92,-0.3,0);
        glVertex3f(-0.97,-0.3,0);
    glEnd();*/
    glutSwapBuffers();
}
static void on_timer(int value)
{
    if (value != 0)
        return;

    /* Provere i pomeranja Igraceve plocice*/
    if((x >= -400 && i < 0) || (x<= 400 && i >0))
         x+=i;

    glutPostRedisplay();
    if(timer_active)
        glutTimerFunc(50, on_timer, 0);
}
static void on_timer2(int value)
{
    if (value != 0)
        return;

    if(promena ==0)
    {
        y+=b;
        if(y>=400)
            promena = 1;
    }
    else if(promena ==1)
    {
        y-=b;
        if(y <= -400)
            promena = 0;
    }
    glutPostRedisplay();
    if(timer_active2)
        glutTimerFunc(50, on_timer2, 0);

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
            glutTimerFunc(50, on_timer, 0);
        break;
    case 'h':
            i =25;
            glutTimerFunc(50, on_timer, 0);
        break;
    case 'r': 
      if (!timer_active2) {
            timer_active2 = 1;
            b = 25;
            glutTimerFunc(50, on_timer2, 0);
        }
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
        b=0;
        i=0;
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