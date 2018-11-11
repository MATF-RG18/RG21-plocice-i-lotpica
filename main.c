#include <GL/glut.h>
#include <stdlib.h>


static void on_display(void);
int main(int argc,char** argv)
{

	//Inicijalizacija prozora
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB);	
	glutInitWindowSize(1300,800);

	glutCreateWindow(argv[0]);
	
	
	glutDisplayFunc(on_display);
	glutMainLoop();
	return 0;
}
static void on_display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,1);
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
	glEnd();
	glutSwapBuffers();
}
