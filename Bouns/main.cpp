#include <stdio.h>
#include <stdlib.h>
#include <GL\glut.h>
GLint window;
GLint Xsize=1000;
GLint Ysize=800;

GLfloat xt=0.0,yt=0.0,zt=0.0;  /* x,y,z translation */
GLfloat yangle=0.0,angle=0.0;   /* axis angles */
GLfloat r=1,g=0,b=0;
/* Simple  transformation routine */
GLvoid Transform(GLfloat Width, GLfloat Height)
{
    gluPerspective(45.0,Width/Height,0.1,100.0);  /* Calculate The Aspect Ratio Of The Window */
}

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
GLvoid InitGL(GLfloat Width, GLfloat Height)
{
    Transform( Width, Height ); /* Perform the transformation */
}

GLvoid DrawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	/* Clear The Screen And The Depth Buffer */
    /* Initialize our window. */
    glClearColor(0,1,0,0);
    glPushMatrix();
    glTranslatef(-1.0,0.0,-3.5);
    glRotatef(yangle,0.0,1.0,0.0);
    glTranslatef(xt,yt,zt);
    glBegin(GL_QUADS);                /* OBJECT MODULE*/
    /* top of cube*/
    //************************FRONT BODY****************************************
    glColor3f(r,g,b);
    glVertex3f( 0.2, 0.4,0.6);
    glVertex3f(0.6, 0.5,0.6);
    glVertex3f(0.6, 0.5,0.2);
    glVertex3f( 0.2,0.4,0.2);

    /* bottom of cube*/
    glVertex3f( 0.2,0.2,0.6);
    glVertex3f(0.6,0.2,0.6);
    glVertex3f(0.6,0.2,0.2);
    glVertex3f( 0.2,0.2,0.2);

    /* front of cube*/
    glVertex3f( 0.2,0.2,0.6);
    glVertex3f(0.2, 0.4,0.6);
    glVertex3f(0.2,0.4,0.2);
    glVertex3f( 0.2,0.2,0.2);

    /* back of cube.*/
    glVertex3f(0.6,0.2,0.6);
    glVertex3f(0.6,0.5,0.6);
    glVertex3f(0.6,0.5,0.2);
    glVertex3f( 0.6,0.2,0.2);

    /* left of cube*/
    glVertex3f(0.2,0.2,0.6);
    glVertex3f(0.6,0.2,0.6);
    glVertex3f(0.6,0.5,0.6);
    glVertex3f(0.2,0.4,0.6);

    /* Right of cube */
    glVertex3f(0.2,0.2,0.2);
    glVertex3f( 0.6,0.2,0.2);
    glVertex3f( 0.6,0.5,0.2);
    glVertex3f( 0.2,0.4,0.2);
//****************************************************************************
    glVertex3f(0.7,0.65,0.6);
    glVertex3f(0.7,0.65,0.2);
    glVertex3f(1.7,0.65,0.2);        //top cover
    glVertex3f(1.7,0.65,0.6);
//***************************back guard******************************
    glColor3f(r,g,b);            /* Set The Color To Blue*/
    glVertex3f( 1.8, 0.5,0.6);
    glVertex3f(1.8, 0.5,0.2);
    glVertex3f(2.1, 0.4, 0.2);
    glVertex3f(2.1,0.4,0.6);

    /* bottom of cube*/
    glVertex3f( 2.1,0.2,0.6);
    glVertex3f(2.1,0.2,0.2);
    glVertex3f(1.8,0.2,0.6);
    glVertex3f( 1.8,0.2,0.6);

    /* back of cube.*/
    glVertex3f(2.1,0.4,0.6);
    glVertex3f(2.1,0.4,0.2);
    glVertex3f(2.1,0.2,0.2);
    glVertex3f(2.1,0.2,0.6);

    /* left of cube*/
    glVertex3f(1.8,0.2,0.2);
    glVertex3f(1.8,0.5,0.2);
    glVertex3f(2.1,0.4,0.2);
    glVertex3f(2.1,0.2,0.2);

    /* Right of cube */
    glVertex3f(1.8,0.2,0.6);
    glVertex3f(1.8,0.5,0.6);
    glVertex3f(2.1,0.4,0.6);
    glVertex3f(2.1,0.2,0.6);
//******************MIDDLE BODY************************************
    glVertex3f( 0.6, 0.5,0.6);
    glVertex3f(0.6, 0.2,0.6);
    glVertex3f(1.8, 0.2, 0.6);
    glVertex3f(1.8,0.5,0.6);

    /* bottom of cube*/
    glVertex3f( 0.6,0.2,0.6);
    glVertex3f(0.6,0.2,0.2);
    glVertex3f(1.8,0.2,0.2);
    glVertex3f( 1.8,0.2,0.6);

    /* back of cube.*/
    glVertex3f(0.6,0.5,0.2);
    glVertex3f(0.6,0.2,0.2);
    glVertex3f(1.8,0.2,0.2);
    glVertex3f(1.8,0.5,0.2);
//*********************ENTER WINDOW**********************************
    glColor3f(0.3,0.3,0.3);
    glVertex3f( 0.77, 0.63,0.2);
    glVertex3f(0.75, 0.5,0.2);        //quad front window
    glVertex3f(1.2, 0.5, 0.2);
    glVertex3f( 1.22,0.63,0.2);

    glVertex3f(1.27,0.63,.2);
    glVertex3f(1.25,0.5,0.2);        //quad back window
    glVertex3f(1.65,0.5,0.2);
    glVertex3f(1.67,0.63,0.2);

    glColor3f(r,g,b);
    glVertex3f(0.7,0.65,0.2);
    glVertex3f(0.7,0.5,.2);       //first separation
    glVertex3f(0.75,0.5,0.2);
    glVertex3f(0.77,0.65,0.2);

    glVertex3f(1.2,0.65,0.2);
    glVertex3f(1.2,0.5,.2);       //second separation
    glVertex3f(1.25,0.5,0.2);
    glVertex3f(1.27,0.65,0.2);

    glVertex3f(1.65,0.65,0.2);
    glVertex3f(1.65,0.5,.2);     //3d separation
    glVertex3f(1.7,0.5,0.2);
    glVertex3f(1.7,0.65,0.2);

    glVertex3f( 0.75, 0.65,0.2);
    glVertex3f(0.75, 0.63,0.2);        //line strip
    glVertex3f(1.7, 0.63, 0.2);
    glVertex3f( 1.7,0.65,0.2);

    glVertex3f( 0.75, 0.65,0.6);
    glVertex3f(0.75, 0.63,0.6);        //line strip
    glVertex3f(1.7, 0.63, 0.6);
    glVertex3f( 1.7,0.65,0.6);

    glColor3f(0.3,0.3,0.3);
    glVertex3f( 0.77, 0.63,0.6);
    glVertex3f(0.75, 0.5,0.6);        //quad front window
    glVertex3f(1.2, 0.5, 0.6);
    glVertex3f( 1.22,0.63,0.6);

    glVertex3f(1.27,0.63,.6);
    glVertex3f(1.25,0.5,0.6);        //quad back window
    glVertex3f(1.65,0.5,0.6);
    glVertex3f(1.67,0.63,0.6);

    glColor3f(r,g,b);
    glVertex3f(0.7,0.65,0.6);
    glVertex3f(0.7,0.5,.6);       //first separation
    glVertex3f(0.75,0.5,0.6);
    glVertex3f(0.77,0.65,0.6);

    glVertex3f(1.2,0.65,0.6);
    glVertex3f(1.2,0.5,.6);       //second separation
    glVertex3f(1.25,0.5,0.6);
    glVertex3f(1.27,0.65,0.6);

    glVertex3f(1.65,0.65,0.6);
    glVertex3f(1.65,0.5,.6);
    glVertex3f(1.7,0.5,0.6);
    glVertex3f(1.7,0.65,0.6);
    glEnd();


//**************************************************************
    glBegin(GL_QUADS);

    /* top of cube*/
    glColor3f(0.3,0.3,0.3);
    glVertex3f( 0.6, 0.5,0.6);
    glVertex3f(0.6, 0.5,0.2);        //quad front window
    glVertex3f(0.7, 0.65, 0.2);
    glVertex3f( 0.7,0.65,0.6);

    glVertex3f(1.7,0.65,.6);
    glVertex3f(1.7,0.65,0.2);        //quad back window
    glVertex3f(1.8,0.5,0.2);
    glVertex3f(1.8,0.5,0.6);
    glEnd();
//********************WHEEL*********************************************

    glColor3f(0,0,0);//black wheel
    glPushMatrix();

    glTranslatef(0.6,0.2,0.6);
    glutSolidTorus(0.025,0.07,10,10);

    glTranslatef(0,0,-0.4);
    glutSolidTorus(0.025,0.07,10,10);

    glTranslatef(1.1,0,0);
    glutSolidTorus(0.025,0.07,10,10);

    glTranslatef(0,0,0.4);
    glutSolidTorus(0.025,0.07,10,10);

    glPopMatrix();
//*************************************************************
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
    glutPostRedisplay();
    glutSwapBuffers();
}

/*  The function called whenever a "normal" key is pressed. */
void NormalKey(GLubyte key, GLint x, GLint y)
{
    switch ( key )
    {
    case 'y':
        yangle += 1;
        glutPostRedisplay();
        break;
    case 'i':
        zt += 1;
        glutPostRedisplay();
        break;
    case 'o':
        zt -= 1;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}
void MoveCar( int Key, int x, int y )
{
    switch ( Key )
    {
    case GLUT_KEY_RIGHT:
        xt += 1;
        glutPostRedisplay();
        break;

    case GLUT_KEY_LEFT:
        xt -= 1;
        glutPostRedisplay();
        break;
    }
}
int main(int argc, char **argv)
{

    /* Initialisation and window creation */

    glutInit(&argc, argv);               /* Initialize GLUT state. */

    glutInitDisplayMode(GLUT_RGBA |      /* RGB and Alpha */GLUT_DOUBLE|     /* double buffer */GLUT_DEPTH);     /* Z buffer (depth) */

    glutInitWindowSize(Xsize,Ysize);     /* set initial window size. */
    glutCreateWindow("3d"); /* Open a window with a title. */
    /* Now register the various callback functions */
    glutDisplayFunc(DrawGLScene);        /* Function to do all our OpenGL drawing. */
    glutKeyboardFunc(NormalKey);         /*Normal key is pressed */
    glutSpecialFunc( MoveCar );
    InitGL(Xsize,Ysize);

    glutMainLoop();                      /* Start Event Processing Engine. */
    return 1;
}
