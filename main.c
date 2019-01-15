#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "image.h"
#define FILENAME1 "fudteren.bmp"
static GLuint names[2];
static float matrix[16];
#define pi 3.14
static void displayText( float x, float y, int r, int g, int b, const char *string );
static void on_keyboard(unsigned char key, int a, int c);
static void initialize(void);
static void on_timer(int value);
static void on_timer2(int value);
static void on_timer3(int value);
static void on_timer4(int value);
static void on_display(void);
static void draw_score_igrac(float x,float y);
static void draw_score_racunar(float x,float y);
static void on_reshape(int width, int height);
static void on_display(void);
static float x_curr, y_curr; // koordinate loptice
//Promenljive za crtanje score-a
static float x_scoreR = 970;
static float y_scoreR = 560;
static float x_scoreI = -970;
static float y_scoreI = 560;
static int score_igrac = 0;
static int score_racunar = 0;
const static float r = 20; // poluprecnik loptice
static float x_bot;// x_bot ,y_bot su promenljive koje sluze za proracun mesta udarca kuglice na strani racunarove plocice
static float y_bot;
static float x_k =45;//x_bot,y_bot brzina loptice
static float y_k = 45;
static float x;//promenljiva po kojoj se krece igraceva plocica po y koordinati
static float y;//promenljiva po kojoj se krece racunar plocica po y koordinati
static float i;//pomeraj igraceve plocice
static float b;
static float phi, theta;//uglovi kamere
static int timer_active;// flag timer za igracevu plocicu
static int timer_active2;// flag timer za racunar plocice
static int timer_active3;// flag timer za lopticu
static int timer_active4;// flag timer za globalni timer

int main(int argc,char** argv)
{

    //Inicijalizacija prozora
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);   
    glutInitWindowSize(1300,800);

    glutCreateWindow(argv[0]);
    //Inicijalizacija ugla kamere
    phi = theta = 0;
    glClearColor(0.75, 0.75, 0.75, 0);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    initialize();
    glutDisplayFunc(on_display);
    //Inicijalizacija pocetnik koordinata loptice
    x_curr = 0;
    y_curr = 0;
    //pomeraj loptice 
    x_k =5;
    y_k =5;
    glutTimerFunc(50, on_timer4, 0);
    glEnable(GL_DEPTH_TEST);
    
    glutMainLoop();
    return 0;
}
static void on_reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 3000);
}
static void on_display(void)
{   
    GLfloat light_position[] = { 0, 0, 1600, 0 };
    GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1 };
    GLfloat light_diffuse[] = { 0.9, 0.9, 0.9, 1 };
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };
    GLfloat shininess = 30;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 1600, 0, 0, 0, 0, 1, 0); 
    glRotatef(phi,0,1,0);
    glRotatef(theta,1,0,0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //Korisnikova Plocica
    GLfloat ambient_coeffs1[] = { 0, 0, 0.2, 1 };
    GLfloat diffuse_coeffs1[] = { 0, 0, 0.6, 1 };
    GLfloat specular_coeffs1[] = {0, 0, 0.6, 1 };
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs1);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glPushMatrix();
        glTranslatef(-880,x,0);
        glColor3f(0, 0, 1);
        glScalef(0.2,2,0.2);
        glutSolidCube(100);
    glPopMatrix();
    //Racunar plocica
    GLfloat ambient_coeffs2[] = { 0, 0.2,0, 1 };
    GLfloat diffuse_coeffs2[] = {0, 0,6,0, 1 };
    GLfloat specular_coeffs2[] = {0, 0.6,0, 1 };
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs2);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glPushMatrix();
        glTranslatef(880,y,0);
        glColor3f(0, 1, 0);
        glScalef(0.2,2,0.2);
        glutSolidCube(100);
    glPopMatrix();
    //Loptica
    GLfloat ambient_coeffs3[] = { 0.8, 0, 0, 1 };
    GLfloat diffuse_coeffs3[] = { 0.8, 0, 0, 1 };
    GLfloat specular_coeffs3[] = {0.2, 0, 0, 1 };
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs3);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs3);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs3);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glPushMatrix();
        glColor3f(1,0,0);
        glTranslatef(x_curr,y_curr,0);
        glutSolidSphere(r,50,50);
    glPopMatrix();
     glColor3f(0, 0, 0);
     glBegin(GL_LINE_LOOP);
        glVertex3f(900, 580, 0);
        glVertex3f(-900, 580, 0);
        glVertex3f(-900, -580, 0);
        glVertex3f(900,-580, 0);    
    glEnd();
    draw_score_igrac(x_scoreI,y_scoreI);
    draw_score_racunar(x_scoreR,y_scoreR);
    //Cliping ravan koja pomaze prilikom postavljanja texture
    GLdouble v[4] = {1,0,0,0};
    glPushMatrix();
        glTranslatef(-900,0,0);
        glClipPlane(GL_CLIP_PLANE1,v);
        glEnable(GL_CLIP_PLANE1);
    glPopMatrix();
    
    glBindTexture(GL_TEXTURE_2D, names[1]);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);

        glTexCoord2f(0, 0);
        glVertex3f(-990, -580, 0);

        glTexCoord2f(0,1);
        glVertex3f(-990, 580, 0);

        glTexCoord2f(1, 1);
        glVertex3f(900, 580, 0);

        glTexCoord2f(1, 0);
        glVertex3f(900, -580, 0);
    glEnd();
    glDisable(GL_CLIP_PLANE1);
    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);
    displayText(-1300,300,1,0,0,"e - easy mode");
    displayText(-1300,250,1,0,0,"r - default mode");
    displayText(-1300,200,1,0,0,"h - hard mode");
       if(score_racunar == 5)
    {
        displayText(-300,700,1,0,0,"Pobednik je Racunar :(!!");
        displayText(-300,650,1,0,0,"Pritisni taster \'R\' za novu igru");
        timer_active4=1;
    }
     if(score_igrac == 5)
    {
        displayText(-300,700,1,0,0,"BRAVO BRAVO TI SI POBEDNIK!");
        displayText(-300,650,1,0,0,"Pritisni taster \'R\' za novu igru");
        timer_active4=1;
    }
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
    // timer koji vrsi pomeranje racunar plocice

    // racunanje funkcije prave kretanja loptice u svakom trenutku kako bi plocica znala kuda da se krece
    float koef = y_k/x_k;
    float n = x_curr*koef + y_curr;
    x_bot = -880;
    y_bot = x_bot*koef + n;

    if(y_bot >= -560 && y_bot <= 560)
    {
        if(y_bot > y)
            y+=b;
        else if(y_bot < y)
            y-=b;
    }
    if(y+b >= 480 || y+b<= -480)
        b*=-1;
    if(timer_active2)
        glutTimerFunc(20, on_timer2, 0);
}
static void on_timer3(int value)
{
    if (value != 0)
        return;
    // timer za kretanje loptice
    y_curr += y_k;
    // provera da li loptica udara u gornju ili donju ivicu
    if(y_curr>=560 || y_curr <=-560)
        y_k*=-1;

    x_curr-= x_k; // vrsi se pomeranje loptice
   if((y_curr>=(x-100) && y_curr<=(x+100) && x_curr == -860) || (y_curr>=(y-100) && y_curr<=(y+100) && x_curr == 860))
    {
        //provera da li loptica udara u plocice
        x_k*=-1;
    }
   else if(x_curr <= -880)
   {
        //racunanje score-a 
        score_racunar ++;
        x_curr = 0;
        y_curr = 0;
        timer_active3 = 0;
        return;
   }
   else if(x_curr >= 880)
   {
        score_igrac++;
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
    // ovaj timer sluzi kako bi u svakom momentu timera iscrtavao glutPostRedisplay 
    // da ne bi dolazilo do "seckanja"
    glutPostRedisplay();
    if(!timer_active4)
        glutTimerFunc(50, on_timer4, 0);
}

static void on_keyboard(unsigned char key, int a, int c)
{
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;

    case 'g':
            i = 25;// pomeraj "na gore"
            glutTimerFunc(10, on_timer, 0);
        break;
    case 'f':
            i =-25;// pomeraj "na dole" 
            glutTimerFunc(10, on_timer, 0);
        break;
    case 'r': 
    //pokrecemo racunar plocicu u default modu 
     b = 3;
      if (!timer_active2) {
            timer_active2 = 1;
            glutTimerFunc(20, on_timer2, 0);
        }
        break;
      case 'e': 
    //pokrecemo racunar plocicu u easy modu
      b = 1;
      if (!timer_active2) {
            timer_active2 = 1;
            glutTimerFunc(20, on_timer2, 0);
        }
        break;   
    case 'h': 
    //pokrecemo racunar plocicu u hard modu
     b = 5;
      if (!timer_active2) {
            timer_active2 = 1;
            glutTimerFunc(20, on_timer2, 0);
        }
        break; 
    case 'G':
        //pokrecemo lopticu
        if (!timer_active3) {
            glutTimerFunc(20, on_timer3, 0);
            timer_active3 = 1;
        }
        break;
      case 'R':
        //Resetuje se sve i vraca u pocetni polozaj 
        score_racunar = 0;
        score_igrac = 0;
        x=0;
        y=0;
        x_curr = 0;
        y_curr = 0;
        phi =0;
        theta =0;
        timer_active4=0;
        timer_active3=0;
        timer_active2 = 0;
        timer_active= 0;
        glutPostRedisplay();
        //if(!timer_active4)
        //glutTimerFunc(50, on_timer4, 0);

        break;
    //tasteri p,P,t,T sluze za rotiranje kamere(odnosno scene)
      case 'p':
        phi+=10;
        glutPostRedisplay();
        break;
      case 't':
        theta += 10;
        glutPostRedisplay();
        break;
      case 'T':
        theta -=10;
        glutPostRedisplay();
        break;
    case 'P':
        phi -=10;
        glutPostRedisplay();
        break;
    }
}
//u zavisnosti od score-a racunara i igraca iscrtava se potreban broj kuglica za rezultat
static void draw_score_racunar(float x,float y)
{   

    if(score_racunar >= 1)
    {
        glPushMatrix();
            glTranslatef(x,y,0);
            glutSolidSphere(25,50,50);
        glPopMatrix();
    }
    if(score_racunar >=2)
    {
        glPushMatrix();
        glTranslatef(x,y-60,0);
        glutSolidSphere(25,50,50);
    glPopMatrix();
    }  
    if(score_racunar >= 3) 
    {
        glPushMatrix();
            glTranslatef(x,y-120,0);
            glutSolidSphere(25,50,50);
        glPopMatrix();
    }
    if(score_racunar >= 4)
    {
        glPushMatrix();
            glTranslatef(x,y-180,0);
            glutSolidSphere(25,50,50);
        glPopMatrix();
    }
    if(score_racunar >= 5)
    {
        glPushMatrix();
            glTranslatef(x,y-240,0);
            glutSolidSphere(25,50,50);
        glPopMatrix();
    }
}
static void draw_score_igrac(float x,float y)
{   
    if(score_igrac >= 1)
    {
        glPushMatrix();
            glTranslatef(x,y,0);
            glutSolidSphere(25,50,50);
        glPopMatrix();
    }
    if(score_igrac >=2)
    {
        glPushMatrix();
        glTranslatef(x,y-60,0);
        glutSolidSphere(25,50,50);
    glPopMatrix();
    }  
    if(score_igrac >= 3) 
    {
        glPushMatrix();
            glTranslatef(x,y-120,0);
            glutSolidSphere(25,50,50);
        glPopMatrix();
    }
    if(score_igrac >= 4)
    {
        glPushMatrix();
            glTranslatef(x,y-180,0);
            glutSolidSphere(25,50,50);
        glPopMatrix();
    }
    if(score_igrac >= 5)
    {
        glPushMatrix();
            glTranslatef(x,y-240,0);
            glutSolidSphere(25,50,50);
        glPopMatrix();
    }
}

static void initialize(void)
{
    /* Objekat koji predstavlja teskturu ucitanu iz fajla. */
    Image * image;

    /* Postavlja se boja pozadine. */

    /* Ukljucuje se testiranje z-koordinate piksela. */
    glEnable(GL_DEPTH_TEST);

    /* Ukljucuju se teksture. */
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    /*
     * Inicijalizuje se objekat koji ce sadrzati teksture ucitane iz
     * fajla.
     */
    image = image_init(900, 580);


    /* Generisu se identifikatori tekstura. */
    glGenTextures(2, names);


    /* Kreira se druga tekstura. */
    image_read(image, FILENAME1);

    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Unistava se objekat za citanje tekstura iz fajla. */
    image_done(image);

    /* Inicijalizujemo matricu rotacije. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
}
static void displayText( float x, float y, int r, int g, int b, const char *string ) {
    int j = strlen( string );
 
    glColor3f( r, g, b );
    glRasterPos3f( x, y ,0);
    for( int i = 0; i < j; i++ ) {
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
    }
}