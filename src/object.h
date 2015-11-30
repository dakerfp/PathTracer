#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "ray.h"
#include "material.h"
#include "intersection.h"

using namespace glm;

namespace PathTrace {

class Object {
public:
	Object();
	Object(vec3 color, double ka, double kd, double ks, double kt, int n) 
	{
		mat = Material(color, ka, kd, ks, kt, n);
	};
	virtual ~Object();
	virtual Intersection intersect(const Ray& ray) const = 0;

private:
	Material mat;
};

class Quadric : public Object {
public:
	Quadric();
	Quadric(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j,
			vec3 color, float ka, float kd, float ks, float kt, int n) : Object(color, ka, kd, ks, kt, n)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
		this->e = e;
		this->f = f;
		this->g = g;
		this->h = h;
		this->i = i;
		this->j = j;
	};

	virtual ~Quadric() {}

	Intersection intersect(const Ray& ray) const {

	    float  acoef, bcoef, ccoef; // Intersection coefficents
	    float  dx, dy, dz; // Direction - origin coordinates
	    float  disc; // Distance to intersection
	    float  root; // Root of distance to intersection
	    float  t; // Distance along ray to intersection
	    float  x0, y0, z0; // Origin coordinates

	    dx = ray.d.x;
	    dy = ray.d.y;
	    dz = ray.d.z;

	    x0 = ray.o.x;
	    y0 = ray.o.y;
	    z0 = ray.o.z;

	 	// Ax2 + By2 + Cz2 + Dxy+ Exz + Fyz + Gx + Hy + Iz + J = 0

	    acoef = a * dx * dx + b * dy * dy + c * dz * dz + d * dx * dy + e * dx * dz + f * dy * dz;

	    bcoef = 2 * a * x0 * dx + 2 * b * y0 * dy + 2 * c * z0 * dz + d * (x0 * dy + y0 * dx) + 
	    		e * (x0 * dz + z0 * dx) + f * (y0 * dz + dy * z0) + g * dx + h * dy + i * dz;

	    ccoef = a * x0 * x0 + b * y0 * y0 + c * z0 * z0 + d * x0 * y0 + e * x0 * z0 + f * y0 * z0 + g * x0 +
	    		h * y0 + i * z0 + j;

	    if ( 1.0 + acoef == 1.0 ) {
	        if ( 1.0 + bcoef == 1.0 ) {
	            return {};
	        }

	      	t = ( -ccoef ) / ( bcoef );

	    } else {
	        disc = bcoef * bcoef - 4 * acoef * ccoef;  
	      	if ( 1.0 + disc < 1.0 ) {
	         	return {};
	      	}

		    root = sqrt( disc );
		    t = ( -bcoef - root ) / ( acoef + acoef );
		    if ( t < 0.0 ) {
		        t = ( -bcoef + root ) / ( acoef + acoef );
		    }
	    }

	    if (t < 0.001) {
	    	return {};
	    }							

	    vec3 p(x0 + t * dx, y0 + t * dy, z0 + t * dz);

	   	return {p, normal(p)};
	}

	const vec3 normal(vec3 point) const {
		
		const float x = point.x;
		const float y = point.y;
		const float z = point.z;

		float gradx = 2 * a * x + d * y + e * z + g;
		float grady = 2 * b * y + d * x + f * z + h;
		float gradz = 2 * c * z + e * x + f * y + i;

		return normalize(vec3(gradx, grady, gradz));
	}

private:
	float  a, b, c, d, e; // Coefficents of equation of..
   	float  f, g, h, i, j; // ... quadric surface
};

class Mesh : public Object
{
private:
	std::vector<float> vertices;
	std::vector<float> normals; 
	std::vector<unsigned int> indices;
	std::vector<unsigned int> normalIndices;

	void resetObject()
	{
		this->vertices.clear();
		this->indices.clear();
		this->normalIndices.clear();
		this->normals.clear();
	}

public:
	Mesh(vec3 color, float ka, float kd, float ks, float kt, int n) : Object(color, ka, kd, ks, kt, n) {};

	// ToDO
	Intersection intersect(const Ray& ray) const
	{
		return {};
	}

	void addVertex(vec3 vertex)
	{
		vertices.push_back(vertex.x);
		vertices.push_back(vertex.y);
		vertices.push_back(vertex.z);
	}

	void addNormals(vec3 normal)
	{
		normals.push_back(normal.x);
		normals.push_back(normal.y);
		normals.push_back(normal.z);
	}

	void addTriangleIndices(int a, int b, int c)
	{
		indices.push_back(a);
		indices.push_back(b);
		indices.push_back(c);
	}
};

}

#endif