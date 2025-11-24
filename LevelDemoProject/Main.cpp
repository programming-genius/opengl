/* 3D OpenGL Computer Graphics Lectures by Alessandro Zoia - 2017

This software is provided 'as-is', without any express or
implied warranty.In no event will the author be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions :

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
source distribution.
*/

#include <gl/glew.h>
#include <gl/glut.h>
#include "Camera.h"
#include "Plane.h"
#include "Box.h"
#include "Sphere.h"
#include <iostream>

#define  WINDOW_WIDTH  800
#define  WINDOW_HEIGHT 480
#define  WINDOW_POS_X  100
#define  WINDOW_POS_Y  100

/***Animation variables***/
//Used by deltatime function to compute the deltaTime value
GLint previousTime = 0;
//Box1,Box0 animated
GLfloat animPawnYawAngle = 0;
//Delta time: time between two consecutive frame update
GLfloat deltaTime = 0;

/***Camera***/
Camera* camera;
/*Camera Position*/
GLdouble cameraX = 0;
GLdouble cameraY = 0.75;
GLdouble cameraZ = 0;
//Camera Orientation
GLfloat cameraRollAngle = 0; // we set fixed to zero in this demo
GLfloat cameraYawAngle = 0;
GLfloat cameraPitchAngle = 0;
//Camera Angular velocity
GLfloat cameraAngularVelocity = 6.28f; // rad/s
//Camera Speed and direction
GLdouble cameraSpeed = 10;// m/s
Vector3  cameraDir;

/***Pawns in the Scene: BOXES***/
Box* box0 = new Box();
Box* box1 = new Box();
Box* box2 = new Box();
Box* box3 = new Box();
Box* box4 = new Box();
//Pawns in the Scene: TOWERS
Box* wallTowerDown0 = new Box();
Box* wallTowerUp0 = new Box();
Box* wallTowerDown1 = new Box();
Box* wallTowerUp1 = new Box();
//Pawns in the Scene : Spheres
Sphere* sphere = new Sphere();
//Pawns in the Scene: GROUND, ROOF AND WALLS
Plane* ground = new Plane();
Plane* roof = new Plane();
Plane* wall0 = new Plane();
Plane* wall1 = new Plane();
Plane* wall2 = new Plane();
Plane* wall3 = new Plane();

/***Utils: enable local frame rendering and/or polygon visualization***/
bool polygonModeEnabled = false;
bool showAxis = false;

void animation(int t)
{
	glutPostRedisplay();
}

/*Used to compute the time elapsed between two frames (in seconds)*/
void updateDeltaTime()
{
	GLint currentTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currentTime - previousTime) / 1000.0f; // in secondi
	previousTime = currentTime;
}

//Setting Texture for all Pawns
void loadPawnTextures()
{
	TextureLoader textureLoader;

	sphere->setTexture(textureLoader, (char*) "texture\\sphereQuake0.jpg");

	box0->setTexture(textureLoader, (char*) "texture\\quakeCube0.jpg");
	box1->setTexture(textureLoader, (char*) "texture\\quakeCube1.jpg");
	box2->setTexture(textureLoader, (char*) "texture\\quakeCube2.jpg");
	box3->setTexture(textureLoader, (char*) "texture\\quakeCube2.jpg");
	box4->setTexture(textureLoader, (char*) "texture\\quakeCube2.jpg");

	wallTowerDown0->setTexture(textureLoader, (char*) "texture\\quakeTowerDown.jpg");
	wallTowerUp0->setTexture(textureLoader, (char*) "texture\\quakeTowerUp.jpg");
	wallTowerDown1->setTexture(textureLoader, (char*) "texture\\quakeTowerDown.jpg");
	wallTowerUp1->setTexture(textureLoader, (char*) "texture\\quakeTowerUp.jpg");

	ground->setTexture(textureLoader, (char*) "texture\\floorQuake.jpg");
	roof->setTexture(textureLoader, (char*) "texture\\roofQuake.jpg");

	wall0->setTexture(textureLoader, (char*) "texture\\wallQuake.jpg");
	wall1->setTexture(textureLoader, (char*) "texture\\wallQuake.jpg");
	wall2->setTexture(textureLoader, (char*) "texture\\wallQuake.jpg");
	wall3->setTexture(textureLoader, (char*) "texture\\wallQuake.jpg");
}

void placeBoxes()
{
	//Animated : Transform applied dynamically  in draw method
	box1->setSize(1, 1, 1);
	box1->setPosition(0, 0.5, -5);
	box0->setSize(1, 1, 1);
	box0->setPosition(5, 0.5, -5);

	//Fixed boxes
	box2->setSize(1, 1, 1);
	box2->setPosition(4, 0.5, 4);
	box2->setOrientation(0, 0, 0);
	box2->modelTransform(NULL);

	box3->setSize(1, 1, 1);
	box3->setPosition(0, 0, 1.5);
	box3->setOrientation(0, 0, 0);
	box3->modelTransform(box2);

	box4->setSize(1, 1, 1);
	box4->setPosition(0, 1, -0.75);
	box4->setOrientation(0, 0, 0);
	box4->modelTransform(box3);

}

void buildTowers()
{

	wallTowerDown0->setSize(1, 1, 1);
	wallTowerDown0->setPosition(-5, 0.5, 5);
	wallTowerDown0->setOrientation(0, 0, 0);
	wallTowerDown0->modelTransform(NULL);

	wallTowerUp0->setSize(1, 1, 1);
	wallTowerUp0->setPosition(0, 1, 0);
	wallTowerUp0->setOrientation(180, 0, 0);
	wallTowerUp0->modelTransform(wallTowerDown0);

	wallTowerDown1->setSize(1, 1, 1);
	wallTowerDown1->setPosition(-5, 0.5, -5);
	wallTowerDown1->setOrientation(0, 0, 0);
	wallTowerDown1->modelTransform(NULL);

	wallTowerUp1->setSize(1, 1, 1);
	wallTowerUp1->setPosition(0, 1, 0);
	wallTowerUp1->setOrientation(180, 0, 0);
	wallTowerUp1->modelTransform(wallTowerDown1);

}

void placeSpheres()
{
	sphere->setSize(0.5, 15);
	sphere->setPosition(5, 0.5, 0);
}

void buildGroundAndRoof()
{
	ground->setSize(7, 7);
	ground->setPosition(0, 0, 0);
	ground->setOrientation(0, 0, 0);
	ground->modelTransform(NULL);

	roof->setSize(7, 7);
	roof->setPosition(0, 2, 0);
	roof->setOrientation(0, 0, 0);
	roof->modelTransform(NULL);
}

void buildWalls()
{
	wall0->setSize(7, 1);
	wall0->setPosition(0, 1, -7);
	wall0->setOrientation(90, 90, 0);
	wall0->modelTransform(NULL);

	wall1->setSize(7, 1);
	wall1->setPosition(0, 1, 7);
	wall1->setOrientation(90, 90, 0);
	wall1->modelTransform(NULL);

	wall2->setSize(7, 1);
	wall2->setPosition(-7, 1, 0);
	wall2->setOrientation(90, 0, 0);
	wall2->modelTransform(NULL);

	wall3->setSize(7, 1);
	wall3->setPosition(7, 1, 0);
	wall3->setOrientation(90, 0, 0);
	wall3->modelTransform(NULL);
}
/*Initialize Pawns and Camera*/
void initScene()
{
	//Camera
	camera = new Camera();

	//Setting Texture for all Pawns
	loadPawnTextures();

	//Build ground and roof 
	buildGroundAndRoof();

	//Build walls
	buildWalls();

	//Build Towers
	buildTowers();

	//Place boxes in the scene
	placeBoxes();

	//Place spheres in the scene
	placeSpheres();

}

void reshape(GLint width, GLint height)
{
	// Determine the new aspect ratio
	GLdouble gldAspect = (GLdouble)width / (GLdouble)height;

	// Reset the projection matrix with the new aspect ratio.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, gldAspect, 0.01, 60.0);

	// Set the viewport to take up the entire window.
	glViewport(0, 0, width, height);
}

void idle() {
}

/*Draw the level using Pawns and Camera defined previously*/
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);

	//Polygon mode check
	if (polygonModeEnabled) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glMatrixMode(GL_MODELVIEW);

	//First we have to place the camera
	camera->setPosition(cameraX, cameraY, cameraZ);
	camera->setOrientation(0, cameraPitchAngle, cameraYawAngle);
	camera->viewTransform();

	//Update Camera direction
	cameraDir = camera->getDirection();

	//Ground and roof
	ground->drawPawn(showAxis);
	roof->drawPawn(showAxis);

	//Walls
	wall0->drawPawn(showAxis);
	wall1->drawPawn(showAxis);
	wall2->drawPawn(showAxis);
	wall3->drawPawn(showAxis);

	//Towers
	wallTowerDown0->drawPawn(showAxis);
	wallTowerUp0->drawPawn(showAxis);
	wallTowerDown1->drawPawn(showAxis);
	wallTowerUp1->drawPawn(showAxis);

	//Animated boxes
	box0->setOrientation(0, 0, animPawnYawAngle);
	box0->modelTransform(NULL);
	box0->drawPawn(showAxis);

	box1->setOrientation(0, 0, animPawnYawAngle);
	box1->modelTransform(NULL);
	box1->drawPawn(showAxis);

	//Fixed boxes
	box2->drawPawn(showAxis);
	box3->drawPawn(showAxis);
	box4->drawPawn(showAxis);

	//Animated Spheres
	sphere->setOrientation(0, 0, animPawnYawAngle);
	sphere->modelTransform(NULL);
	sphere->drawPawn(showAxis);

	//Update Yaw Angle for boxes and spheres animation
	animPawnYawAngle += 0.5f;

	if (animPawnYawAngle == 360) animPawnYawAngle = 0;

	updateDeltaTime();
	glutSwapBuffers();
}

void initLights()
{
	/*Default lighting*/
	GLfloat light_ambient_0[4] = { 0, 0, 0, 1 };
	GLfloat light_diffuse_0[4] = { 1, 1, 1, 1 };
	GLfloat light_specular_0[4] = { 1, 1, 1, 1 };
	GLfloat light_positio_0[4] = { 1, 1, 1, 0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient_0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse_0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular_0);

	glLightfv(GL_LIGHT0, GL_POSITION, light_positio_0);

	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glClearColor(0.126f, 0.126f, 0.128f, 1.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

}

void processSpecialKeys(int key, int x, int y)
{
	//Rad to degree factor
	GLfloat convFactor = (180.f / 3.14f);
	switch (key) {
	case GLUT_KEY_LEFT:
		cameraYawAngle += (cameraAngularVelocity * deltaTime) * convFactor;
		break;
	case GLUT_KEY_RIGHT:
		cameraYawAngle -= (cameraAngularVelocity * deltaTime) * convFactor;
		break;
	case GLUT_KEY_UP:
		cameraPitchAngle += (cameraAngularVelocity * deltaTime) * convFactor;
		break;
	case GLUT_KEY_DOWN:
		cameraPitchAngle -= (cameraAngularVelocity * deltaTime) * convFactor;
		break;
	default:
		break;
	}
	if (cameraYawAngle >= 360) cameraYawAngle = cameraYawAngle - 360;
	if (cameraPitchAngle >= 360) cameraPitchAngle = cameraPitchAngle - 360;

	glutPostRedisplay();
}
void processNormalKeys(unsigned char key, int x, int y)
{
	Vector3 pos(cameraX, cameraY, cameraZ);

	switch (key) {
	case 'a':
		pos += cameraDir * cameraSpeed * deltaTime;
		cameraX = pos.x;
		cameraY = pos.y;
		cameraZ = pos.z;
		break;
	case 's':
		pos -= cameraDir * cameraSpeed * deltaTime;
		cameraX = pos.x;
		cameraY = pos.y;
		cameraZ = pos.z;
		break;
	case 'p':
		polygonModeEnabled = !polygonModeEnabled;
		break;
	case 'x':
		showAxis = !showAxis;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void timer(int value) {
	glutPostRedisplay();        // chiede un nuovo frame → chiama display()
	glutTimerFunc(16, timer, 0); // richiama il timer dopo ~16 ms (≈60 FPS)
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
	previousTime = glutGet(GLUT_ELAPSED_TIME); // inizializza

	// Avvia il timer!
	glutTimerFunc(0, timer, 0);
	updateDeltaTime();
	//glutTimerFunc((int)deltaTime, animation, 0);
	glutCreateWindow("OpenGL 3D Computer Graphics - ModelView Transformation - https://3dopenglgraphics.blogspot.it");

	glutReshapeFunc(reshape);
	glutDisplayFunc(draw);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutIdleFunc(idle);
	glutIgnoreKeyRepeat(false);

	GLenum err = glewInit();

	if (GLEW_OK != err)
	{
		std::cout << "Failed to initialize GLEW";
	}
	else
	{
		std::cout << "Using GLEW Version: " << glewGetString(GLEW_VERSION);
	}


	initLights();
	initScene();
	glutMainLoop();
	return 0;
}