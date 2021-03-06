//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"

//-------------------------------------------------------------------------

class Abs_Entity  // abstract class
{
public:
	Abs_Entity(): mModelMat(1.0), mColor(1) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };
	
#pragma region Implementación Enunciado
	void setMColor(dvec4 newColor) { mColor = newColor; }; //Aplica color a la malla
	virtual void update() = 0;

#pragma endregion
protected:

	Mesh* mMesh = nullptr;   // the mesh
	glm::dmat4 mModelMat;    // modeling matrix
	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const; 

#pragma region Implementación Enunciado
	dvec4 mColor;
#pragma endregion
};
//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity 
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};
};

#pragma region Implementación Enunciado
class Poligono : public Abs_Entity
{
private:
	GLuint numL = 1;
	GLdouble rd = 1;
public:
	explicit Poligono(GLuint numL_, GLdouble rd_);
	~Poligono();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};


};

class Sierpinski : public Abs_Entity
{
private:
	GLuint numP = 1;
	GLdouble rd = 1;
public:
	Sierpinski(GLdouble rd_, GLuint numP_);
	~Sierpinski();
	virtual void render(glm::dmat4 const& modelViewMat) const;	
	virtual void update() {};

};

class TrianguloRGB : public Abs_Entity
{
private:
	GLdouble rd = 1;
	//Parametros para el movimiento
	dvec3 posOriginal{ (0.0, 0.0, 0.0) };
	dvec3 posCfc{ (0.0,0.0,0.0) };
	GLdouble angulo = 1.0f;
	
public:
	TrianguloRGB(GLdouble rd_);
	~TrianguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

class RectanguloRGB : public Abs_Entity {
private:
	GLdouble width = 0;
	GLdouble height = 0;
public:
	RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};


};
#pragma endregion
#endif //_H_Entities_H_