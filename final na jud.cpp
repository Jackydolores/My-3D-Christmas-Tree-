


#include <iostream>
#include <glut.h>
#include "imageloader.h"
#include "primitives.h"
//#include <irrKlang.h>

//unsing namespace irrKlang;
//IsoundEngine* engine = createIrrKlangDevice();



using namespace std;

void display();
void reshape(int, int);
void update(int);
void cube();
GLuint loadTexture(Image* image);
void processNormalKeys(unsigned char, int, int);
//void renderBitmapString(
//	float x,
//	float y,
	//float z,
	//void *font,
	//char*string);






float angle = 0.0;// angle of rotation for the camera direction
float lx = 0.0f, lz = -1.0f;// actual vector representing the camera's direction
float cameraX = 0.0f, cameraZ = 5.0f;// XZ position of the camera
float _angle = -70.0f; // objects angle
long count = 0;
GLuint _textureId;




//set materials
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 60.0 };

//set world light
GLfloat lmodel_ambient[] = { 0.0, 0.2, 0.2, 1.0 };

//light positions
GLfloat xlight0 = 0.0f, ylight0 = 4.5f, zlight0 = 0.0f;
GLfloat xlight1 = 4.0, ylight1 = 0.0, zlight1 = 0.0f;
GLfloat xlight2 = -4.0, ylight2 = 0.0, zlight2 = 0.0f;


//set Light #0
GLfloat light_position[] = { xlight0, ylight0, zlight0, 1.0 };
GLfloat light[] = { 1.0, 0.0, 0.0 };

//set Light #1
GLfloat light_position1[] = { xlight1, ylight1, zlight1, 1.0 };
GLfloat light1[] = { 0.0, 0.0, 1.0 };

//set Light #2
GLfloat light_position2[] = { xlight2, ylight2, zlight2, 1.0 };
GLfloat light2[] = { 0.0, 1.0, 0.0 };


//Emissions
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_emissionRed[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat mat_emissionBlue[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat mat_emissionGreen[] = { 0.0, 1.0, 0.0, 1.0 };

//Initializes 3D rendering
void initRendering() {

	//engine->play2D("filename" , true);
	glClearColor(0.0, 0.0, 0.0, 1.0); //set background to black

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_LIGHT6);
	glEnable(GL_LIGHT7);
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glEnable(GL_AUTO_NORMAL);
	glShadeModel(GL_SMOOTH); //Enable smooth shading

	Image* image = loadBMP("green.bmp");
	_textureId = loadTexture(image);
	delete image;
}







int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	//Create the window
	//glutCreateWindow ("My 3D Christmas Tree by: Jackquilen C. Dolores");
	initRendering();

	//Create the window
	glutCreateWindow("my 3D Christmas tree");
	initRendering();

	//Set handler functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(processNormalKeys);//controls
	glutTimerFunc(1000 / 60, update, 0); //Add a timer

	glutMainLoop();
	return 0;
}

//Draws the 3D scene
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();




	glTranslatef(0.0f, 0.0f, -15.0f); //move object in -z axis to seen in display




	//camera controls
	gluLookAt(cameraX, 1.0f, cameraZ,
		cameraX + lx, 1.0f, cameraZ + lz,
		0.0f, 1.0f, 0.0f);


	//setting world lighting
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); //add ambient lighting
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//set light position
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light); //add diffuse specular lighting
	glLightfv(GL_LIGHT0, GL_SPECULAR, light); //add specular lighting
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess

	//door gate
	glPushMatrix();
	glScalef(1.0f, 1.7, 1.0);
	glTranslatef(-0.0f, 1.6f, 9.0f);
	glRotatef(_angle, 0.0f,1.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-2.0f, -2.0f);
	glVertex2f(2.0f, -2.0f);
	glVertex2f(2.0f, 2.0f);
	glVertex2f(-2.0f, 2.0f);
	glEnd();
	glPopMatrix();

	//pyramid
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(0.0f, 5.0f, -7.0f);
	glRotatef(40.0, 0.0f, 0.0f, 0.0f);
	pyramid();
	glPopMatrix();


	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glScalef(2.0f, 1.0, 1.0);
	glTranslatef(0.0f, 4.0f, -7.0f);
	glRotatef(40.0, 0.0f, 0.0f, 0.0f);
	pyramid();
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glScalef(3.0f, 1.0, 1.0);
	glTranslatef(0.0f, 3.0f, -7.0f);
	glRotatef(40.0, 0.0f, 0.0f, 0.0f);
	pyramid();
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glScalef(2.0f, 1.0, 1.0);
	glTranslatef(0.0f, 0.5f, -7.0f);
	glRotatef(40.0, 0.0f, 0.0f, 0.0f);
	pyramid();
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glScalef(4.0f, 1.0, 1.0);
	glTranslatef(0.0f, 2.0f, -7.0f);
	glRotatef(40.0, 0.0f, 0.0f, 0.0f);
	pyramid();
	glPopMatrix();



	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glScalef(4.1f, 1.0, 1.0);
	glTranslatef(0.0f, 1.0f, -7.0f);
	glRotatef(40.0, 0.0f, 0.0f, 0.0f);
	pyramid();
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glScalef(4.5f, 1.0, 1.0);
	glTranslatef(0.0f, 0.6f, -7.0f);
	glRotatef(40.0, 0.0f, 0.0f, 0.0f);
	pyramid();
	glPopMatrix();
	
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glScalef(5.0f, 1.0, 1.0);
	glTranslatef(0.0f, 0.0f, -7.0f);
	glRotatef(40.0, 0.0f, 0.0f, 0.0f);
	pyramid();
	glPopMatrix();
	

	//ground balls
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(-2.5f, 0.1f, 3.0f); //location
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glColor3f(1.0f, 1.0f, 0.0f);//add color material to object
	glutWireSphere(0.9,100,100);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(2.5f, 0.1f, 3.0f); //location
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glColor3f(1.0f, 1.0f, 0.0f);//add color material to object
	glutWireSphere(0.9,100,100);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(2.5f, 0.1f, 0.3f); //location
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glutWireSphere(0.9,100,100);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(-2.5f, 0.1f, 0.3f); //location
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glutWireSphere(0.9,100,100);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(-2.5f, 0.1f, 2.0f); //location
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glutWireSphere(0.9,60,60);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(2.5f, 0.1f, 2.0f); //location
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glutWireSphere(0.9,60,60);
	glPopMatrix();
	//Christmas balls
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(0.9f, 4.1f, -6.0f); //location
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glutWireSphere(0.2,40,24);
	glPopMatrix();

glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(-0.9f, 4.1f, -6.0f); //location
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glutWireSphere(0.2,40,24);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(-1.5f, 3.1f, -6.0f); //location
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glutWireSphere(0.2,40,24);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(1.5f, 3.1f, -6.0f); //location
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glutWireSphere(0.2,40,24);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(-2.0f, 2.1f, -6.0f); //location
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glutWireSphere(0.2,40,24);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(2.0f, 2.1f, -6.0f); //location
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glutWireSphere(0.2,40,24);
	glPopMatrix();

glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(3.0f, 1.1f, -6.0f); //location
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glutWireSphere(0.2,40,24);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(-3.0f, 1.1f, -6.0f); //location
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glutWireSphere(0.2,40,24);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(3.3f, 0.1f, -6.0f); //location
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glutWireSphere(0.2,40,24);
	glPopMatrix();

glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(-3.3f, 0.1f, -6.0f); //location
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glutWireSphere(0.2,40,24);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(-3.6f, -0.7f, -6.0f); //location
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glutWireSphere(0.2,40,24);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(3.6f, -0.7f, -6.0f); //location
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glutWireSphere(0.2,40,24);
	glPopMatrix();
	//stand
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	//glScalef(1.3f, 2.0, 1.0);
	glColor3f(0.0f, 0.0f, 1.0f);//add color material to object
	glTranslatef(0.0f, -2.0f, -9.0f); //location
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glutSolidTorus(0.5, 1, 50, 48);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	//glScalef(1.3f, 2.0, 1.0);
	glColor3f(0.0f, 0.0f, 1.0f);//add color material to object
	glRotatef(270.0, 1.0f, 0.0f, 0.0f); //rotation animation
	glTranslatef(0.0f, -2.0f, -5.0f); //location
	glutSolidCone(1.0, 1.0 ,1.0, 1.0);
	glPopMatrix();


	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glScalef(0.3f, 2.0, 1.0);
	glColor3f(0.0f, 0.0f, 1.0f);//add color material to object
	glTranslatef(0.0f, 0.1f, -7.0f); //location
	glRotatef(40, 0.0f, 0.0f, 0.0f); //rotation animation
	cube();
	glPopMatrix();



	//gate
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glScalef(8.0f,4.5, 1.0);
	glColor3f(1.0f, 1.0f, 0.0f);//add color material to object
	glTranslatef(1.0f, 0.6f, 9.0f); //location
	glRotatef(40, 0.0f, 0.0f, 0.0f); //rotation animation
	cube();
	glPopMatrix();

	//gate
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glScalef(8.0f, 4.5, 1.0);
	glColor3f(1.0f, 1.0f, 0.0f);//add color material to object
	glTranslatef(-1.0f, 0.6f, 9.2f); //location
	glRotatef(40, 0.0f, 0.0f, 0.0f); //rotation animation
	cube();
	glPopMatrix();
	//top
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(0.0f, 6.0f, -7.0f);
	glRotatef(_angle, 0.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireSphere(0.6, 100, 100);
	glPopMatrix();

	
	//house
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	//glScalef(3.0f, 1.0, 1.0);
	glTranslatef(0.0f, 2.0f, -9.0f);
	glRotatef(40.0, 0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-3.0f, -4.0f, 2.0f);
	glVertex3f(3.0f, -4.0f, 2.0f);
	glVertex3f(3.0f, 1.0f, 2.0f);
	glVertex3f(0.0f, 4.0f, 2.0f);
	glVertex3f(-3.0f, 1.0f, 2.0f);
	glEnd();

	//right wall
	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex3f(3.0f, -4.0f, 2.0f);
	glVertex3f(3.0f, -4.0f, -2.0f);
	glVertex3f(3.0f, 1.0f, -2.0f);
	glVertex3f(3.0f, 1.0f, 2.0f);
	glEnd();

	//back wall
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(-3.0f, -4.0f, -2.0f);
	glVertex3f(3.0f, -4.0f, -2.0f);
	glVertex3f(3.0f, 1.0f, -2.0f);
	glVertex3f(0.0f, 4.0f, -2.0f);
	glVertex3f(-3.0f, 1.0f, -2.0f);
	glEnd();

	//left wall
	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex3f(-3.0f, -4.0f, 2.0f);
	glVertex3f(-3.0f, -4.0f, -2.0f);
	glVertex3f(-3.0f, 1.0f, -2.0f);
	glVertex3f(-3.0f, 1.0f, 2.0f);
	glEnd();

	//right roof
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(3.0f, 1.0f, 2.0f);
	glVertex3f(3.0f, 1.0f, -2.0f);
	glVertex3f(0.0f, 4.0f, -2.0f);
	glVertex3f(0.0f, 4.0f, 2.0f);
	glEnd();

	//left roof
	glColor3f(0, 1, 1);
	glBegin(GL_POLYGON);
	glVertex3f(-3.0f, 1.0f, 2.0f);
	glVertex3f(-3.0f, 1.0f, -2.0f);
	glVertex3f(0.0f, 4.0f, -2.0f);
	glVertex3f(0.0f, 4.0f, 2.0f);
	glEnd();

	//below floor
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex3f(3.0f, -4.0f, 2.0f);
	glVertex3f(3.0f, -4.0f, -2.0f);
	glVertex3f(-3.0f, -4.0f, -2.0f);
	glVertex3f(-3.0f, -4.0f, 2.0f);

	glEnd();

	glPopMatrix();
	//house
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	//glScalef(3.0f, 1.0, 1.0);
	glTranslatef(-5.0f, 2.0f, -15.0f);
	glRotatef(40.0, 0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-3.0f, -4.0f, 2.0f);
	glVertex3f(3.0f, -4.0f, 2.0f);
	glVertex3f(3.0f, 1.0f, 2.0f);
	glVertex3f(0.0f, 4.0f, 2.0f);
	glVertex3f(-3.0f, 1.0f, 2.0f);
	glEnd();

	//right wall
	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex3f(3.0f, -4.0f, 2.0f);
	glVertex3f(3.0f, -4.0f, -2.0f);
	glVertex3f(3.0f, 1.0f, -2.0f);
	glVertex3f(3.0f, 1.0f, 2.0f);
	glEnd();

	//back wall
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(-3.0f, -4.0f, -2.0f);
	glVertex3f(3.0f, -4.0f, -2.0f);
	glVertex3f(3.0f, 1.0f, -2.0f);
	glVertex3f(0.0f, 4.0f, -2.0f);
	glVertex3f(-3.0f, 1.0f, -2.0f);
	glEnd();

	//left wall
	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex3f(-3.0f, -4.0f, 2.0f);
	glVertex3f(-3.0f, -4.0f, -2.0f);
	glVertex3f(-3.0f, 1.0f, -2.0f);
	glVertex3f(-3.0f, 1.0f, 2.0f);
	glEnd();

	//right roof
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(3.0f, 1.0f, 2.0f);
	glVertex3f(3.0f, 1.0f, -2.0f);
	glVertex3f(0.0f, 4.0f, -2.0f);
	glVertex3f(0.0f, 4.0f, 2.0f);
	glEnd();

	//left roof
	glColor3f(0, 1, 1);
	glBegin(GL_POLYGON);
	glVertex3f(-3.0f, 1.0f, 2.0f);
	glVertex3f(-3.0f, 1.0f, -2.0f);
	glVertex3f(0.0f, 4.0f, -2.0f);
	glVertex3f(0.0f, 4.0f, 2.0f);
	glEnd();

	//below floor
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex3f(3.0f, -4.0f, 2.0f);
	glVertex3f(3.0f, -4.0f, -2.0f);
	glVertex3f(-3.0f, -4.0f, -2.0f);
	glVertex3f(-3.0f, -4.0f, 2.0f);

	glEnd();

	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glScalef(3.0f, 1.0, 1.0);
	glTranslatef(0.0f, 2.0f, -8.0f);
	glRotatef(40.0, 0.0f, 0.0f, 0.0f);
	pyramid();
	glPopMatrix();
	//house
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	//glScalef(3.0f, 1.0, 1.0);
	glTranslatef(5.0f, 2.0f, -18.0f);
	glRotatef(40.0, 0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-3.0f, -4.0f, 2.0f);
	glVertex3f(3.0f, -4.0f, 2.0f);
	glVertex3f(3.0f, 1.0f, 2.0f);
	glVertex3f(0.0f, 4.0f, 2.0f);
	glVertex3f(-3.0f, 1.0f, 2.0f);
	glEnd();

	//right wall
	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex3f(3.0f, -4.0f, 2.0f);
	glVertex3f(3.0f, -4.0f, -2.0f);
	glVertex3f(3.0f, 1.0f, -2.0f);
	glVertex3f(3.0f, 1.0f, 2.0f);
	glEnd();

	//back wall
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(-3.0f, -4.0f, -2.0f);
	glVertex3f(3.0f, -4.0f, -2.0f);
	glVertex3f(3.0f, 1.0f, -2.0f);
	glVertex3f(0.0f, 4.0f, -2.0f);
	glVertex3f(-3.0f, 1.0f, -2.0f);
	glEnd();

	//left wall
	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex3f(-3.0f, -4.0f, 2.0f);
	glVertex3f(-3.0f, -4.0f, -2.0f);
	glVertex3f(-3.0f, 1.0f, -2.0f);
	glVertex3f(-3.0f, 1.0f, 2.0f);
	glEnd();

	//right roof
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(3.0f, 1.0f, 2.0f);
	glVertex3f(3.0f, 1.0f, -2.0f);
	glVertex3f(0.0f, 4.0f, -2.0f);
	glVertex3f(0.0f, 4.0f, 2.0f);
	glEnd();

	//left roof
	glColor3f(0, 1, 1);
	glBegin(GL_POLYGON);
	glVertex3f(-3.0f, 1.0f, 2.0f);
	glVertex3f(-3.0f, 1.0f, -2.0f);
	glVertex3f(0.0f, 4.0f, -2.0f);
	glVertex3f(0.0f, 4.0f, 2.0f);
	glEnd();

	//below floor
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex3f(3.0f, -4.0f, 2.0f);
	glVertex3f(3.0f, -4.0f, -2.0f);
	glVertex3f(-3.0f, -4.0f, -2.0f);
	glVertex3f(-3.0f, -4.0f, 2.0f);

	glEnd();

	glPopMatrix();


	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0.0f, -1.0f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(-1000.0f, -5.0f, -1000.0f);
	glTexCoord2f(1000, 0);
	glVertex3f(-1000.0f, -5.0f, 1000.0f);
	glTexCoord2f(1000.0f, 1000.0f);
	glVertex3f(1000.0f, -5.0f, 1000.0f);
	glTexCoord2f(0.0f, 1000.f);
	glVertex3f(1000.0f, -5.0f, -1000.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	//RED LIGHT SOURCE
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);//add color material to object
	glRotatef(_angle, 1.0f, 0.0f, 0.0f); //rotation animation
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//set light position
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light); //add diffuse specular lighting
	glLightfv(GL_LIGHT0, GL_SPECULAR, light); //add specular lighting
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emissionRed);
	glTranslatef(xlight0, ylight0, zlight0); //location
	glutSolidSphere(0.1, 12, 12);
	glPopMatrix();

	//BLUE LIGHT SOURCE
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);//add color material to object
	glRotatef(_angle, 0.0f, 1.0f, 0.0f); //rotation animation
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);//set light position
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1); //add diffuse specular lighting
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1); //add specular lighting
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emissionBlue);
	glTranslatef(xlight1, ylight1, zlight1); //location
	glutSolidSphere(0.1, 12, 12);
	glPopMatrix();

	//GREEN LIGHT SOURCE
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);//add color material to object
	glRotatef(_angle, 1.0f, 1.0f, 1.0f); //rotation animation
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);//set light position
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2); //add diffuse specular lighting
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2); //add specular lighting
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emissionGreen);
	glTranslatef(xlight2, ylight2, zlight2); //location
	glutSolidSphere(0.1, 12, 12);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//WHITE
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);//add color material to object
	glRotatef(_angle, 1.0f, 0.0f, 1.0f); //rotation animation
	glLightfv(GL_LIGHT3, GL_POSITION, light_position2);//set light position
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light2); //add diffuse specular lighting
	glLightfv(GL_LIGHT3, GL_SPECULAR, light2); //add specular lighting
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emissionGreen);
	glTranslatef(xlight2, ylight2, zlight2); //location
	glutSolidSphere(0.1, 12, 12);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//yellow
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glRotatef(_angle, 0.0f, -1.0f, -1.0f); //rotation animation
	glLightfv(GL_LIGHT4, GL_POSITION, light_position2);//set light position
	glLightfv(GL_LIGHT4, GL_DIFFUSE, light2); //add diffuse specular lighting
	glLightfv(GL_LIGHT4, GL_SPECULAR, light2); //add specular lighting
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emissionGreen);
	glTranslatef(xlight2, ylight2, zlight2); //location
	glutSolidSphere(0.1, 12, 12);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//outside ball
	glPushMatrix();
	//glTranslatef(2.0f, 2.0f, 13.0f);
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glRotatef(_angle, 1.0f, 0.0f, 1.0f); //rotation animation
	glLightfv(GL_LIGHT5, GL_POSITION, light_position2);//set light position
	glLightfv(GL_LIGHT5, GL_DIFFUSE, light2); //add diffuse specular lighting
	glLightfv(GL_LIGHT5, GL_SPECULAR, light2); //add specular lighting
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emissionGreen);
	glTranslatef(xlight2, ylight2, zlight2); //location
	glutSolidSphere(0.1, 12, 12);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glRotatef(_angle, 1.0f, 0.0f, 1.0f); //rotation animation
	glLightfv(GL_LIGHT6, GL_POSITION, light_position2);//set light position
	glLightfv(GL_LIGHT6, GL_DIFFUSE, light2); //add diffuse specular lighting
	glLightfv(GL_LIGHT6, GL_SPECULAR, light2); //add specular lighting
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emissionGreen);
	glTranslatef(xlight2, ylight2, zlight2); //location
	glutSolidSphere(0.1, 12, 12);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 0.0f, 1.0f);//add color material to object
	glRotatef(_angle, 1.0f, 0.5f, 1.0f); //rotation animation
	glLightfv(GL_LIGHT7, GL_POSITION, light_position2);//set light position
	glLightfv(GL_LIGHT7, GL_DIFFUSE, light2); //add diffuse specular lighting
	glLightfv(GL_LIGHT7, GL_SPECULAR, light2); //add specular lighting
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emissionGreen);
	glTranslatef(xlight2, ylight2, zlight2); //location
	glutSolidSphere(0.1, 12, 12);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();



	glutSwapBuffers();
}


//Called when the window is resized
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void update(int value) {
	_angle += 1.5f;
	if (_angle > 360) {
		_angle -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, update, 0);
}
/*

void renderBitmapString(
	float x,
	float y,
	float z,
	void *font,
	char*string); {

char *c;
glRasterPos3f(x,y,z);
for (c=string; *c != '\0'; c++) {
	glutBitmapCharacter(font, *c);

}
}
*/
//keyboard controls
void processNormalKeys(unsigned char key, int x, int y) {
	float fraction = 1.5f;


	switch (key) {
	case 'w':
		cameraX += lx * fraction;
		cameraZ += lz * fraction;
		break;
	case 's':
		cameraX -= lx * fraction;
		cameraZ -= lz * fraction;
		break;
	case 'a':
		angle -= 0.1f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case 'd':
		angle += 0.1f;
		lx = sin(angle);
		lz = -cos(angle);
		break;

	}
}

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
		//as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}



