#include "Pawn.h"

Pawn::~Pawn()
{
	if (hTransform != nullptr)
		delete hTransform;
}

void Pawn::setPosition(double xPos, double yPos, double zPos)
{
	x = xPos;
	y = yPos;
	z = zPos;
}

void Pawn::setOrientation(double rollAngle, double pitchAngle, double yawAngle)
{
	roll = rollAngle * PI_180;
	pitch = pitchAngle * PI_180;
	yaw = yawAngle * PI_180;
}

void Pawn::setTexture(TextureLoader textureLoader, char* filePath)
{
	textureLoader.SetHighQualityTextures(true);
	textureLoader.LoadTextureFromDisk(filePath, &texture);
}

void Pawn::enableGLTexture2D()
{
	GLint polygonMode[2];
	glGetIntegerv(GL_POLYGON_MODE, polygonMode);

	/*We want disable texture mapping because wireframe is enabled*/
	if (polygonMode[1] != GL_LINE)
		glEnable(GL_TEXTURE_2D);

	/*Gouraud Shading*/
	glShadeModel(GL_SMOOTH);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture.TextureID);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glGenerateMipmap(GL_TEXTURE_2D);

}

void Pawn::disableGLTexture2D()
{
	glDisable(GL_TEXTURE_2D);
}

void Pawn::modelTransform(Pawn* relativeTo)
{
	GLdouble viewMatrix[16];

	/*Save the current model view matrix*/
	glGetDoublev(GL_MODELVIEW_MATRIX, viewMatrix);

	/*First column*/
	GLdouble a0 = cos(roll) * cos(yaw);
	GLdouble a1 = sin(roll) * cos(yaw);
	GLdouble a2 = -sin(yaw);
	GLdouble a3 = 0;
	/*Second column*/
	GLdouble a4 = cos(roll) * sin(yaw) * sin(pitch) - sin(roll) * cos(pitch);
	GLdouble a5 = sin(roll) * sin(yaw) * sin(pitch) + cos(roll) * cos(pitch);
	GLdouble a6 = cos(yaw) * sin(pitch);
	GLdouble a7 = 0;
	/*Third column*/
	GLdouble a8 = cos(roll) * sin(yaw) * cos(pitch) + sin(roll) * sin(pitch);
	GLdouble a9 = sin(roll) * sin(yaw) * cos(pitch) - cos(roll) * sin(pitch);
	GLdouble a10 = cos(yaw) * cos(pitch);
	GLdouble a11 = 0;
	/*Fourth column*/
	GLdouble a12 = x;
	GLdouble a13 = y;
	GLdouble a14 = z;
	GLdouble a15 = 1;

	/*Homogeneous trasformation that descibes position and orientation of the current frame
	respect to the world or respect to the last frame( if you are reasoning in moving frame)*/
	GLdouble hTransform[16] = { a0,  a1,   a2,  a3, /*First column*/
								a4,  a5,   a6,  a7, /*Second column*/
								a8,  a9,  a10,  a11, /*Third column*/
								a12, a13, a14,  a15 };/*Fourth column*/

	if (this->hTransform == nullptr) this->hTransform = new GLdouble[16];

	for (int i = 0; i < 16; i++) this->hTransform[i] = hTransform[i];

	if (relativeTo != nullptr)
	{
		/*The glLoadMatrix function replaces the current matrix with the one specified in input.
		The current matrix is the projection matrix, modelview matrix, or texture matrix,
		determined by the current matrix mode (see the use of glMatrixMode)*/
		glLoadMatrixd(relativeTo->hTransform);
		glMultMatrixd(hTransform);
		glGetDoublev(GL_MODELVIEW_MATRIX, this->hTransform);//we have to save a composite trasformation
	}

	/*We have to restore the modelview matrix*/

	/*In the draw method of the main class we need to execute the glMatrixMode(GL_MODELVIEW) instruction
	before to use a pawn*/
	glLoadMatrixd(viewMatrix);

}

void Pawn::drawPawn(bool showAxis)
{
	GLdouble viewMatrix[16];

	/*Save the current model view matrix*/
	glGetDoublev(GL_MODELVIEW_MATRIX, viewMatrix);

	glMultMatrixd(this->hTransform);

	enableGLTexture2D();

	draw();

	disableGLTexture2D();

	if (showAxis) drawAxis();

	/*We have to restore the modelview matrix*/
	glLoadMatrixd(viewMatrix);
}

void Pawn::drawAxis()
{
	glDisable(GL_LIGHTING);

	glLineWidth(3.f);
	glBegin(GL_LINES);

	// x red
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(1.f, 0.f, 0.f);

	// y green
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 1.f, 0.f);

	// z blue
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, 1.f);

	glEnd();
	glLineWidth(1.f);
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
}