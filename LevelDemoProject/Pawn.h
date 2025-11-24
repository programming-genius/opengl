/* 3D OpenGL Computer Graphics Lectures  by Alessandro Zoia - 2017

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

#ifndef PAWN_H
#define PAWN_H
#ifndef PI_180
#define PI_180 (3.14159265359 / 180.0) 
#endif
#include <gl/glew.h>
#include <gl/glut.h>
#include <math.h>
#include "Geometry.h"
#include "TextureLoader.h"

class Pawn {

public:

	~Pawn();

	/*
	Description :  Set the origin of the object frame respect to the last frame
	Parameters : xPos,yPos,zPos are origin coordinates expressed in world frame
	*/
	void setPosition(double xPos, double yPos, double zPos);

	/*
	Description :  Set the orientation of the object frame using Euler angles respect to the last frame
	Parameters : rollAngle,pitchAngle,yawAngle are the RPY Euler angles (degree angles)
	*/
	void setOrientation(double rollAngle, double pitchAngle, double yawAngle);

	/* Apply a texture on the Pawn */
	void setTexture(TextureLoader textureLoader, char* filePath);

	/* Description : Executes the model trasformation and adds the pawn to the scene calling the draw method
	   Parameters : RelativeTo is a Pawn used as reference for this trasformation
	*/
	void modelTransform(Pawn* relativeTo);

	/* Description : Use the model matrix and performs the drawing of the
					Pawn calling the draw() method
	   Parameters: showAxis=true shows the local frame attached to the Pawn */
	void drawPawn(bool showAxis);

protected:

	virtual void draw() = 0;

	/* Orientation */
	GLdouble roll = 0;
	GLdouble pitch = 0;
	GLdouble yaw = 0;

	/* Position */
	GLdouble x = 0;
	GLdouble y = 0;
	GLdouble z = 0;

	/* Homogeneous Trasformation Matrix in array form */
	/* 1 column  a0 a1 a2 a3
	   2 column  a4 a5 a6 a7
	   3 column  a8 a9 a10 a11
	   4 column  a12 a13 a14 a15 */
	GLdouble* hTransform = nullptr;

private:
	void drawAxis();
	void enableGLTexture2D();
	void disableGLTexture2D();
	glTexture texture;
};
#endif