#include <GL/glut.h>
#include <stdlib.h>

static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int value);
static void on_display(void);
static void on_reshape(int width, int height);

static float x;
static float y;
static float i;
static float b;
static int promena = 0;

static int timer_active;
static int timer_active2;
static void on_display(void);
int main(int argc,char** argv)
{

	//Inicijalizacija prozora
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB);	
	glutInitWindowSize(1300,800);

	glutCreateWindow(argv[0]);
	
	
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
	glColor3f(0,0,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 1000, 0, 0, 0, 0, 1, 0);
    glPushMatrix();
        glTranslatef(-800,x,0);
        glColor3f(0, 0, 1);
        glutWireCube(100);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(800,y,0);
        glColor3f(0, 0, 1);
        glutWireCube(100);
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
    }
}