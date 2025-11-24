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

#ifndef SPHERE_H
#define SPHERE_H
#include "Pawn.h"
#include "vector3.h"
#include "TextureLoader.h"
#ifndef PI
#define PI 3.14159265359
#endif

class Sphere : public virtual Pawn {

public:
	void setSize(GLdouble radius, GLint angleSize);
	void draw();

private:
	GLdouble radius;
	GLdouble angleSize;
	glTexture texture;

	void vertexMapping(const Vector3& p);
	void vertexNormalMapping(const Vector3& p);
	void vertexTextureMapping(GLdouble azimuthAngle, GLdouble polarAngle);
};
#endif

