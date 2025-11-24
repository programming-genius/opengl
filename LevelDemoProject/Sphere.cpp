#include "Sphere.h"

void Sphere::setSize(GLdouble radius, GLint angleSize)
{
	this->radius = radius;
	this->angleSize = angleSize;

}

void Sphere::draw()
{
	glBegin(GL_TRIANGLES);
	for (GLdouble azimuthAngle = 0; azimuthAngle <= 360; azimuthAngle += angleSize)
	{
		for (GLdouble polarAngle = 0; polarAngle <= 180; polarAngle += angleSize)
		{

			/*Current Triangle points: p1-p2-p3 is the first one, p4-p3-p2 is the second one*/
			Vector3 p1 = Geometry::sphericalToCartesian(radius, polarAngle, azimuthAngle);
			Vector3 p2 = Geometry::sphericalToCartesian(radius, polarAngle + angleSize, azimuthAngle);
			Vector3 p3 = Geometry::sphericalToCartesian(radius, polarAngle, azimuthAngle + angleSize);
			Vector3 p4 = Geometry::sphericalToCartesian(radius, polarAngle + angleSize, azimuthAngle + angleSize);

			glColor3f(1, 1, 1);

			/*First triangle*/
			vertexTextureMapping(azimuthAngle, polarAngle);
			vertexNormalMapping(p1);
			vertexMapping(p1);

			vertexTextureMapping(azimuthAngle, polarAngle + angleSize);
			vertexNormalMapping(p2);
			vertexMapping(p2);

			vertexTextureMapping(azimuthAngle + angleSize, polarAngle);
			vertexNormalMapping(p3);
			vertexMapping(p3);

			/*Second triangle*/
			vertexTextureMapping(azimuthAngle + angleSize, polarAngle + angleSize);
			vertexNormalMapping(p4);
			vertexMapping(p4);

			vertexTextureMapping(azimuthAngle + angleSize, polarAngle);
			vertexNormalMapping(p3);
			vertexMapping(p3);

			vertexTextureMapping(azimuthAngle, polarAngle + angleSize);
			vertexNormalMapping(p2);
			vertexMapping(p2);

		}
	}
	glEnd();
}

void Sphere::vertexMapping(const Vector3& p)
{
	glVertex3d(p.x, p.y, p.z);
}

void Sphere::vertexNormalMapping(const Vector3& p)
{
	/*Vertex Normal using Gradient*/
	Vector3 vector3(2 * p.x, 2 * p.y, 2 * p.z);
	vector3 = vector3.Normalize();
	glNormal3d(vector3.x, vector3.y, vector3.z);
}

void Sphere::vertexTextureMapping(GLdouble azimuthAngle, GLdouble polarAngle)
{
	GLdouble u = (azimuthAngle / 360);
	GLdouble v = (polarAngle / 180);
	glTexCoord2d(u, v);
}