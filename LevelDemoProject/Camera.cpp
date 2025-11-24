#include "Camera.h"

Camera::Camera() {
}

Camera::~Camera()
{
	if (hTransformInverse != nullptr)
		delete hTransformInverse;
}

void Camera::setPosition(GLdouble xPos, GLdouble yPos, GLdouble zPos)
{
	x = xPos;
	y = yPos;
	z = zPos;
}

void Camera::setOrientation(GLdouble rollAngle, GLdouble pitchAngle, GLdouble yawAngle)
{
	roll = rollAngle * PI_180;
	pitch = pitchAngle * PI_180;
	yaw = yawAngle * PI_180;
}

void Camera::viewTransform()
{

	/*Homegeneous trasformation that describes position and
	orientation of the camera frame respect to world frame*/

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

	/*At this point we need to realize the Inverse Homogeneous trasformation*/

	/*First we compute the last column of the Inverse homogeneous trasformation*/
	GLdouble iP[3] = { a0 * x + a1 * y + a2 * z,
					   a4 * x + a5 * y + a6 * z,
					   a8 * x + a9 * y + a10 * z };

	/*And now we can define the complete Inverse homogeneous trasformation: position and orientation of the world frame
	respect to camera frame*/
	GLdouble hTransformInverse[16] = { a0, a4, a8, 0, //First column
									   a1, a5, a9, 0, //Second column 
									   a2, a6, a10, 0,//Third column
									  -iP[0], -iP[1], -iP[2], 1 }; //Fourth column

	/*Build Homogeneous Trasformation Matrix in array form*/
	if (this->hTransformInverse == nullptr)
		this->hTransformInverse = new GLdouble[16];

	/*Initialize Homogeneous Trasformation Matrix in array form*/
	for (int i = 0; i < 16; i++)
		this->hTransformInverse[i] = hTransformInverse[i];

	/*The glLoadMatrix function replaces the current matrix with the one specified in input.
	The current matrix is the projection matrix, modelview matrix, or texture matrix,
	determined by the current matrix mode (see the use of glMatrixMode)*/

	/*In the draw method of the main class we need to execute the glMatrixMode(GL_MODELVIEW) instruction
	before to use the camera object*/
	glLoadMatrixd(hTransformInverse);

}

Vector3 Camera::getDirection() {
	//we compute the -z vector with z the versor of frame attached to the camera expressed in world frame
	Vector3 direction(-cos(roll) * sin(yaw) * cos(pitch) - sin(roll) * sin(pitch),
		-sin(roll) * sin(yaw) * cos(pitch) + cos(roll) * sin(pitch),
		-cos(yaw) * cos(pitch));
	return direction;
}
