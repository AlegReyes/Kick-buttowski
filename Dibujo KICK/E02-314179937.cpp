//Pr�ctica 3 semestre 2022-1: �ndices, mesh. proyecciones
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al c�digo
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";

//Pir�mide irregular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.5f,
		0.0f,-0.5f,0.5f,
		0.5f,-0.5f, 0.0f,
		0.0f,0.5f,0.0f,

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}
//V�rtices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,//vertice 0
	0.5f, -0.5f,  0.5f,//vertice 1
	0.5f,  0.5f,  0.5f,//...2
	-0.5f,  0.5f,  0.5f,//...3
	// back
	-0.5f, -0.5f, -0.5f,//...4
	0.5f, -0.5f, -0.5f,//...5
	0.5f,  0.5f, -0.5f,//...6
	-0.5f,  0.5f, -0.5f//...7
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetras()
{
	GLfloat vertices_letras[] = {	
			//X		Y		Z			R		G		B

			//letra A de Alejandro
		/////centro barriga kick
		/////1
			-2.0f, 0.0f,  0.5f,		1.0f,	1.0f,	1.0f,
			2.0f, 0.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			-2.0f,  -6.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			//2
			-2.0f, -6.0f,  0.5f,		1.0f,	1.0f,	1.0f,
			2.0f, -6.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			2.0f,  0.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			//3
			2.0f, 0.0f,  0.5f,		1.0f,	1.0f,	1.0f,
			2.0f, -6.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			3.4f,  -3.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			//4
			2.0f, 0.0f,  0.5f,		1.0f,	1.0f,	1.0f,
			3.2f, 0.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			3.4f,  -3.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			//5
			3.4f, -3.0f,  0.5f,		1.0f,	1.0f,	1.0f,
			2.0f, -6.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			3.0f,  -5.6f,  0.5f,			1.0f,	1.0f,	1.0f,
			//6
			2.0f, -6.0f,  0.5f,		1.0f,	1.0f,	1.0f,
			-2.0f, -6.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			0.0f,  -7.6f,  0.5f,			1.0f,	1.0f,	1.0f,

			3.0f, -5.4f,  0.5f,		1.0f,	1.0f,	1.0f,
			2.0f, -6.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			2.0f,  -6.8f,  0.5f,			1.0f,	1.0f,	1.0f,
			//8
			2.0f, -6.0f,  0.5f,		1.0f,	1.0f,	1.0f,
			2.0f, -6.8f,  0.5f,			1.0f,	1.0f,	1.0f,
			0.0f,  -7.6f,  0.5f,			1.0f,	1.0f,	1.0f,
			//9
			-2.0f, 0.0f,  0.5f,		1.0f,	1.0f,	1.0f,
			-2.0f, -6.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			-3.6f,  -3.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			//10
			-2.0f, 0.0f,  0.5f,		1.0f,	1.0f,	1.0f,
			-3.4f, 0.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			-3.6f,  -3.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			//11
			-3.6f, -3.0f,  0.5f,		1.0f,	1.0f,	1.0f,
			-2.0f, -6.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			-3.4f,  -6.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			//12
			-2.0f, -6.0f,  0.5f,		1.0f,	1.0f,	1.0f,
			-3.4f, -6.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			-2.0f,  -6.8f,  0.5f,			1.0f,	1.0f,	1.0f,
			//13
			-2.0f, -6.0f,  0.5f,		1.0f,	1.0f,	1.0f,
			-2.0f, -6.8f,  0.5f,			1.0f,	1.0f,	1.0f,
			0.0f,  -7.4f,  0.5f,			1.0f,	1.0f,	1.0f,
			//14
			3.0f, -5.6f,  0.5f,		1.0f,	1.0f,	1.0f,
			3.6f, -7.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			1.7f,  -7.8f,  0.5f,			1.0f,	1.0f,	1.0f,
			//114
			0.0f, -6.0f,  0.5f,		1.0f,	1.0f,	1.0f,///
			3.6f, -7.0f,  0.5f,			1.0f,	1.0f,	1.0f,///
			1.7f,  -7.8f,  0.5f,			1.0f,	1.0f,	1.0f,////
			//115
			3.3f, -6.0f,  0.5f,		1.0f,	1.0f,	1.0f,///
			3.6f, -7.0f,  0.5f,			1.0f,	1.0f,	1.0f,///
			1.7f,  -7.8f,  0.5f,			1.0f,	1.0f,	1.0f,////
			//116
			3.0f, -5.6f,  0.5f,		1.0f,	1.0f,	1.0f,
			3.6f, -7.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			0.0f,  -4.0f,  0.5f,			1.0f,	1.0f,	1.0f,//
			//117
			3.0f, -5.6f,  0.5f,		1.0f,	1.0f,	1.0f,
			3.6f, -7.4f,  0.5f,			1.0f,	1.0f,	1.0f,
			0.5f,  -4.0f,  0.5f,			1.0f,	1.0f,	1.0f,//
			//118
			2.9f, -5.6f,  0.5f,		1.0f,	1.0f,	1.0f,//
			3.6f, -7.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			1.7f,  -7.8f,  0.5f,			1.0f,	1.0f,	1.0f,
			//119
			2.8f, -5.6f,  0.5f,		1.0f,	1.0f,	1.0f,//
			3.6f, -7.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			1.7f,  -7.8f,  0.5f,			1.0f,	1.0f,	1.0f,
			//120
			2.7f, -5.6f,  0.5f,		1.0f,	1.0f,	1.0f,//
			3.6f, -7.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			1.7f,  -7.8f,  0.5f,			1.0f,	1.0f,	1.0f,
			//121
			2.6f, -5.6f,  0.5f,		1.0f,	1.0f,	1.0f,//
			3.6f, -7.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			1.7f,  -7.8f,  0.5f,			1.0f,	1.0f,	1.0f,
			//121
			2.5f, -5.6f,  0.5f,		1.0f,	1.0f,	1.0f,//
			3.6f, -7.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			1.7f,  -7.8f,  0.5f,			1.0f,	1.0f,	1.0f,

			//114
			0.0f, -6.0f,  0.5f,		1.0f,	1.0f,	1.0f,///
			-3.6f, -7.0f,  0.5f,			1.0f,	1.0f,	1.0f,///
			-1.7f,  -7.8f,  0.5f,			1.0f,	1.0f,	1.0f,////
			//115
			-3.3f, -6.0f,  0.5f,		1.0f,	1.0f,	1.0f,///
			-3.6f, -7.0f,  0.5f,			1.0f,	1.0f,	1.0f,///
			-1.7f,  -7.8f,  0.5f,			1.0f,	1.0f,	1.0f,////
			//116
			-3.0f, -5.6f,  0.5f,		1.0f,	1.0f,	1.0f,
			-3.6f, -7.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			0.0f,  -4.0f,  0.5f,			1.0f,	1.0f,	1.0f,//
			//117
			-3.0f, -5.6f,  0.5f,		1.0f,	1.0f,	1.0f,
			-3.6f, -7.4f,  0.5f,			1.0f,	1.0f,	1.0f,
			0.5f,  -4.0f,  0.5f,			1.0f,	1.0f,	1.0f,//
			//118
			-2.9f, -5.6f,  0.5f,		1.0f,	1.0f,	1.0f,//
			-3.6f, -7.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			-1.7f,  -7.8f,  0.5f,			1.0f,	1.0f,	1.0f,
			//119
			-2.8f, -5.6f,  0.5f,		1.0f,	1.0f,	1.0f,//
			-3.6f, -7.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			-1.7f,  -7.8f,  0.5f,			1.0f,	1.0f,	1.0f,
			//120
			-2.7f, -5.6f,  0.5f,		1.0f,	1.0f,	1.0f,//
			-3.6f, -7.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			-1.7f,  -7.8f,  0.5f,			1.0f,	1.0f,	1.0f,
			//121
			-2.6f, -5.6f,  0.5f,		1.0f,	1.0f,	1.0f,//
			-3.6f, -7.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			-1.7f,  -7.8f,  0.5f,			1.0f,	1.0f,	1.0f,
			//121
			-2.5f, -5.6f,  0.5f,		1.0f,	1.0f,	1.0f,//
			-3.6f, -7.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			-1.7f,  -7.8f,  0.5f,			1.0f,	1.0f,	1.0f,


			//15
			-3.4f, -6.0f,  0.5f,		1.0f,	1.0f,	1.0f,
			-4.0f, -6.8f,  0.5f,			1.0f,	1.0f,	1.0f,
			-2.0f,  -7.8f,  0.5f,			1.0f,	1.0f,	1.0f,
			//////Botas
			//16
			3.8f, -7.4f,  0.5f,		1.0f,	1.0f,	0.0f,
			3.8f, -9.8f,  0.5f,			1.0f,	1.0f,	0.0f,
			1.6f,  -9.8f,  0.5f,			1.0f,	1.0f,	0.0f,
			//17
			-3.8f, -7.4f,  0.5f,		1.0f,	1.0f,	0.0f,
			-3.8f, -9.8f,  0.5f,			1.0f,	1.0f,	0.0f,
			-1.6f,  -9.8f,  0.5f,			1.0f,	1.0f,	0.0f,
			//18
			3.8f, -9.0f,  0.5f,		1.0f,	1.0f,	0.0f,
			3.8f, -9.8f,  0.5f,			1.0f,	1.0f,	0.0f,
			4.3f,  -9.8f,  0.5f,			1.0f,	1.0f,	0.0f,
			//19
			-3.8f, -9.0f,  0.5f,		1.0f,	1.0f,	0.0f,
			-3.8f, -9.8f,  0.5f,			1.0f,	1.0f,	0.0f,
			-4.3f,  -9.8f,  0.5f,			1.0f,	1.0f,	0.0f,
			//20
			3.8f, -7.4f,  0.5f,		1.0f,	1.0f,	0.0f,
			1.8f, -8.2f,  0.5f,			1.0f,	1.0f,	0.0f,
			2.4f,  -8.95f,  0.5f,			1.0f,	1.0f,	0.0f,
			//122
			3.8f, -7.4f, 0.49f, 0.0f, 0.0f, 0.0f,
			1.8f, -8.2f, 0.49f, 0.0f, 0.0f, 0.0f,
			3.0f, -7.0f, 0.49f, 0.0f, 0.0f, 0.0f,//
			//123
			3.8f, -7.4f, 0.49f, 0.0f, 0.0f, 0.0f,
			1.8f, -8.2f, 0.49f, 0.0f, 0.0f, 0.0f,
			2.5f, -7.0f, 0.49f, 0.0f, 0.0f, 0.0f,//
			//124
				3.8f, -7.4f, 0.49f, 0.0f, 0.0f, 0.0f,
				1.8f, -8.2f, 0.49f, 0.0f, 0.0f, 0.0f,
				2.4f, -7.0f, 0.49f, 0.0f, 0.0f, 0.0f,//
				//125
				3.8f, -7.4f, 0.49f, 0.0f, 0.0f, 0.0f,
				1.8f, -8.2f, 0.49f, 0.0f, 0.0f, 0.0f,
				2.3f, -7.0f, 0.49f, 0.0f, 0.0f, 0.0f,//
				//126
				3.8f, -7.4f, 0.49f, 0.0f, 0.0f, 0.0f,
				1.8f, -8.2f, 0.49f, 0.0f, 0.0f, 0.0f,
				2.2f, -7.0f, 0.49f, 0.0f, 0.0f, 0.0f,//
				//127
				3.8f, -7.4f, 0.49f, 0.0f, 0.0f, 0.0f,
				1.8f, -8.2f, 0.49f, 0.0f, 0.0f, 0.0f,
				2.1f, -7.0f, 0.49f, 0.0f, 0.0f, 0.0f,//
				//128
				-3.8f, -7.4f, 0.49f, 0.0f, 0.0f, 0.0f,
				-1.8f, -8.2f, 0.49f, 0.0f, 0.0f, 0.0f,
				-2.0f, -7.0f, 0.49f, 0.0f, 0.0f, 0.0f,
				//129
				-3.8f, -7.4f, 0.5f, 1.0f, 1.0f, 0.0f,
				-1.8f, -8.2f, 0.5f, 1.0f, 1.0f, 0.0f,
				-2.4f, -8.95f, 0.5f, 1.0f, 1.0f, 0.0f,
				//130
				-3.8f, -7.4f, 0.49f, 0.0f, 0.0f, 0.0f,
				-1.8f, -8.2f, 0.49f, 0.0f, 0.0f, 0.0f,
				-3.0f, -7.0f, 0.49f, 0.0f, 0.0f, 0.0f,//
				//131
				-3.8f, -7.4f, 0.49f, 0.0f, 0.0f, 0.0f,
				-1.8f, -8.2f, 0.49f, 0.0f, 0.0f, 0.0f,
				-2.5f, -7.0f, 0.49f, 0.0f, 0.0f, 0.0f,//
				//132
				-3.8f, -7.4f, 0.49f, 0.0f, 0.0f, 0.0f,
				-1.8f, -8.2f, 0.49f, 0.0f, 0.0f, 0.0f,
				-2.4f, -7.0f, 0.49f, 0.0f, 0.0f, 0.0f,//
				//133
				-3.8f, -7.4f, 0.49f, 0.0f, 0.0f, 0.0f,
				-1.8f, -8.2f, 0.49f, 0.0f, 0.0f, 0.0f,
				-2.3f, -7.0f, 0.49f, 0.0f, 0.0f, 0.0f,//
				//126
				-3.8f, -7.4f, 0.49f, 0.0f, 0.0f, 0.0f,
				-1.8f, -8.2f, 0.49f, 0.0f, 0.0f, 0.0f,
				-2.2f, -7.0f, 0.49f, 0.0f, 0.0f, 0.0f,//
				//134
				-3.8f, -7.4f, 0.49f, 0.0f, 0.0f, 0.0f,
				-1.8f, -8.2f, 0.49f, 0.0f, 0.0f, 0.0f,
				-2.1f, -7.0f, 0.49f, 0.0f, 0.0f, 0.0f,//
				//135
				-3.8f, -7.4f, 0.49f, 0.0f, 0.0f, 0.0f,
				-1.8f, -8.2f, 0.49f, 0.0f, 0.0f, 0.0f,
				-2.0f, -7.0f, 0.49f, 0.0f, 0.0f, 0.0f,
			//21
			-3.8f, -7.4f,  0.5f,		1.0f,	1.0f,	0.0f,
			-1.8f, -8.2f,  0.5f,			1.0f,	1.0f,	0.0f,
			-2.4f,  -8.95f,  0.5f,			1.0f,	1.0f,	0.0f,

			///Parte superior cuerpo
			//22
			0.0f, 0.0f,  0.5f,		1.0f,	1.0f,	1.0f,
			3.2f, 0.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			2.8f,  1.6f,  0.5f,			1.0f,	1.0f,	1.0f,
			//23
			0.0f, 0.0f,  0.5f,		1.0f,	1.0f,	1.0f,
			-3.2f, 0.0f,  0.5f,			1.0f,	1.0f,	1.0f,
			-2.8f,  1.6f,  0.5f,			1.0f,	1.0f,	1.0f,
			//24
			0.0f, 0.0f,  0.5f,		1.0f,	1.0f,	1.0f,
			2.8f, 1.6f,  0.5f,			1.0f,	1.0f,	1.0f,
			-2.8f,  1.6f,  0.5f,			1.0f,	1.0f,	1.0f,
			///Cuello
			//25
			0.0f, 0.0f, 0.51f,		0.7f, 0.2f, 0.0f,
			0.45f, 1.3f, 0.51f,		0.7f, 0.2f, 0.0f,
			-0.45f, 1.3f, 0.51f,		0.7f, 0.2f, 0.0f,
			/////Cara
			//26
			0.0f, 1.2f, 0.51f,		0.7f, 0.2f, 0.0f,
			3.8f, 4.0f, 0.51f,		0.7f, 0.2f, 0.0f,
			3.8f, 7.4f, 0.51f,		 0.7f, 0.2f, 0.0f,
			//27
			0.0f, 1.2f, 0.51f,		0.7f, 0.2f, 0.0f,
			-3.8f, 4.0f, 0.51f,		0.7f, 0.2f, 0.0f,
			-3.8f, 7.4f, 0.51f,		0.7f, 0.2f, 0.0f,
			//28
			0.0f, 1.2f, 0.51f, 0.7f, 0.2f, 0.0f,
			-3.8f, 7.4f, 0.51f, 0.7f, 0.2f, 0.0f,
			3.8f, 7.4f, 0.51f, 0.7f, 0.2f, 0.0f,
			//////Franja roja del casco
			//29
			1.6f, 7.4f, 0.51f, 1.0f, 0.0f, 0.0f,
			-1.6f, 7.4f, 0.51f, 1.0f, 0.0f, 0.0f,
			-1.6f, 10.0f, 0.51f, 1.0f, 0.0f, 0.0f,
			//30
			1.6f, 7.4f, 0.51f, 1.0f, 0.0f, 0.0f,
			1.6f, 10.0f, 0.51f, 1.0f, 0.0f, 0.0f,
			-1.6f, 10.0f, 0.51f, 1.0f, 0.0f, 0.0f,
			//31
			-1.6f, 10.0f, 0.51f, 1.0f, 0.0f, 0.0f,
			-1.4f, 12.0f, 0.51f, 1.0f, 0.0f, 0.0f,
			1.6f, 10.0f, 0.51f, 1.0f, 0.0f, 0.0f,
			//32
			1.6f, 10.0f, 0.51f, 1.0f, 0.0f, 0.0f,
			1.4f, 12.0f, 0.51f, 1.0f, 0.0f, 0.0f,
			-1.6f, 12.0f, 0.51f, 1.0f, 0.0f, 0.0f,
			//33
			-1.4f, 12.0f, 0.51f, 1.0f, 0.0f, 0.0f,
			1.4f, 12.0f, 0.51f, 1.0f, 0.0f, 0.0f,
			-0.8f, 13.2f, 0.51f, 1.0f, 0.0f, 0.0f,
			//34
			1.4f, 12.0f, 0.51f, 1.0f, 0.0f, 0.0f,
			0.8f, 13.2f, 0.51f, 1.0f, 0.0f, 0.0f,
			-0.8f, 13.2f, 0.51f, 1.0f, 0.0f, 0.0f,
			/////////////Casco
			//35
			3.8f, 3.0f, 0.51f, 1.0f, 1.0f, 1.0f,
			3.8f, 7.4f, 0.51f, 1.0f, 1.0f, 1.0f,
			5.6f, 7.4f, 0.51f, 1.0f, 1.0f, 1.0f,
				//96
				3.8f, 3.0f, 0.52f, 0.0f, 0.0f, 0.0f,
				4.7f, 5.7f, 0.52f, 0.0f, 0.0f, 0.0f,
				5.6f, 7.4f, 0.52f, 0.0f, 0.0f, 0.0f,
				//97
				3.8f, 3.0f, 0.52f, 0.0f, 0.0f, 0.0f,
				3.8f, 7.4f, 0.52f, 0.0f, 0.0f, 0.0f,
				3.6f, 5.2f, 0.52f, 0.0f, 0.0f, 0.0f,

			//36
			-3.8f, 3.0f, 0.51f, 1.0f, 1.0f, 1.0f,
			-3.8f, 7.4f, 0.51f, 1.0f, 1.0f, 1.0f,
			-5.6f, 7.4f, 0.51f, 1.0f, 1.0f, 1.0f,
				//98
				-3.8f, 3.0f, 0.52f, 0.0f, 0.0f, 0.0f,
				-4.7f, 5.7f, 0.52f, 0.0f, 0.0f, 0.0f,
				-5.6f, 7.4f, 0.52f, 0.0f, 0.0f, 0.0f,
				//99
				-3.8f, 3.0f, 0.52f, 0.0f, 0.0f, 0.0f,
				-3.8f, 7.4f, 0.52f, 0.0f, 0.0f, 0.0f,
				-3.6f, 5.2f, 0.52f, 0.0f, 0.0f, 0.0f,
			//37
			1.6f, 7.4f, 0.51f, 1.0f, 1.0f, 1.0f,
			5.6f, 7.4f, 0.51f, 1.0f, 1.0f, 1.0f,
			1.6f, 13.0f, 0.51f, 1.0f, 1.0f, 1.0f,
			//38
			-1.6f, 7.4f, 0.51f, 1.0f, 1.0f, 1.0f,
			-5.6f, 7.4f, 0.51f, 1.0f, 1.0f, 1.0f,
			-1.6f, 13.0f, 0.51f, 1.0f, 1.0f, 1.0f,
			//39
			5.6f, 7.4f, 0.51f, 1.0f, 1.0f, 1.0f,
			1.6f, 13.0f, 0.51f, 1.0f, 1.0f, 1.0f,
			4.4f, 10.6f, 0.51f, 1.0f, 1.0f, 1.0f,
			//40
			-5.6f, 7.4f, 0.51f, 1.0f, 1.0f, 1.0f,
			-1.6f, 13.0f, 0.51f, 1.0f, 1.0f, 1.0f,
			-4.4f, 10.6f, 0.51f, 1.0f, 1.0f, 1.0f,
			//41
			4.4f, 10.6f, 0.51f, 1.0f, 1.0f, 1.0f,
			1.6f, 13.0f, 0.51f, 1.0f, 1.0f, 1.0f,
			3.2f, 12.2f, 0.51f, 1.0f, 1.0f, 1.0f,
			//42
			5.6f, 7.4f, 0.51f, 1.0f, 1.0f, 1.0f,
		    4.4f, 10.6f, 0.51f, 1.0f, 1.0f, 1.0f,
			5.2f, 9.2f, 0.51f, 1.0f, 1.0f, 1.0f,
			//43
			5.6f, 7.4f, 0.51f, 1.0f, 1.0f, 1.0f,
			3.8f, 3.0f, 0.51f, 1.0f, 1.0f, 1.0f,
			5.0f, 5.0f, 0.51f, 1.0f, 1.0f, 1.0f,
			//44
			-4.4f, 10.6f, 0.51f, 1.0f, 1.0f, 1.0f,
			-1.6f, 13.0f, 0.51f, 1.0f, 1.0f, 1.0f,
			-3.2f, 12.2f, 0.51f, 1.0f, 1.0f, 1.0f,
			//45
			-5.6f, 7.4f, 0.51f, 1.0f, 1.0f, 1.0f,
			-4.4f, 10.6f, 0.51f, 1.0f, 1.0f, 1.0f,
			-5.2f, 9.2f, 0.51f, 1.0f, 1.0f, 1.0f,
			//46
			-5.6f, 7.4f, 0.51f, 1.0f, 1.0f, 1.0f,
			-3.8f, 3.0f, 0.51f, 1.0f, 1.0f, 1.0f,
			-5.0f, 5.0f, 0.51f, 1.0f, 1.0f, 1.0f,
			//47
			-1.6f, 13.1f, 0.505f, 1.0f, 1.0f, 1.0f,
			1.6f, 13.1f, 0.505f, 1.0f, 1.0f, 1.0f,
			0.0f, 5.0f, 0.505f, 1.0f, 1.0f, 1.0f,
			//48
			1.6f, 13.1f, 0.505f, 1.0f, 1.0f, 1.0f,
			1.6f, 8.0f, 0.505f, 1.0f, 1.0f, 1.0f,
			-4.4f, 10.6f, 0.505f, 1.0f, 1.0f, 1.0f,
			//49
			-1.6f, 13.1f, 0.505f, 1.0f, 1.0f, 1.0f,
			-1.6f, 8.0f, 0.505f, 1.0f, 1.0f, 1.0f,
			4.4f, 10.6f, 0.505f, 1.0f, 1.0f, 1.0f,
			////CARa
			//50
			0.0f, 1.2f, 0.51f, 0.7f, 0.2f, 0.0f,
			3.8f, 4.0f, 0.51f, 0.7f, 0.2f, 0.0f,
			2.0f, 2.2f, 0.51f, 0.7f, 0.2f, 0.0f,
			//51
			0.0f, 1.2f, 0.51f, 0.7f, 0.2f, 0.0f,
			-3.8f, 4.0f, 0.51f, 0.7f, 0.2f, 0.0f,
			-2.0f, 2.2f, 0.51f, 0.7f, 0.2f, 0.0f,
			//52
			3.8f, 4.0f, 0.51f, 0.7f, 0.2f, 0.0f,
			2.0f, 2.2f, 0.51f, 0.7f, 0.2f, 0.0f,
			3.0f, 3.0f, 0.51f, 0.7f, 0.2f, 0.0f,
			//53
			0.0f, 1.2f, 0.51f, 0.7f, 0.2f, 0.0f,
			2.0f, 2.2f, 0.51f, 0.7f, 0.2f, 0.0f,
			1.0f, 1.5f, 0.51f, 0.7f, 0.2f, 0.0f,
			//54
			-3.8f, 4.0f, 0.51f, 0.7f, 0.2f, 0.0f,
			-2.0f, 2.2f, 0.51f, 0.7f, 0.2f, 0.0f,
			-3.0f, 3.0f, 0.51f, 0.7f, 0.2f, 0.0f,
			//55
			0.0f, 1.2f, 0.51f, 0.7f, 0.2f, 0.0f,
			-2.0f, 2.2f, 0.51f, 0.7f, 0.7f, 0.0f,
			-1.0f, 1.5f, 0.51f, 0.7f, 0.2f, 0.0f,
			//BOCA
			//131
			0.6f, 3.6f, 0.52f, 0.0f, 0.0f, 0.0f,
			1.6f, 3.8f, 0.52f, 0.0f, 0.0f, 0.0f,
			1.3f, 3.9f, 0.52f, 0.0f, 0.0f, 0.0f,
			//132
			1.6f, 3.8f, 0.52f, 0.0f, 0.0f, 0.0f,
			1.9f, 4.0f, 0.52f, 0.0f, 0.0f, 0.0f,
			1.675f, 4.1f, 0.52f, 0.0f, 0.0f, 0.0f,
			//133
			1.9f, 4.0f, 0.52f, 0.0f, 0.0f, 0.0f,
			2.1f, 4.2f, 0.52f, 0.0f, 0.0f, 0.0f,
			2.0f, 4.3f, 0.52f, 0.0f, 0.0f, 0.0f,
			////CAPA
			//56
			3.8f, 3.0f, 0.48f, 1.0f, 1.0f, 1.0f,
			3.8f, 9.6f, 0.48f, 1.0f, 1.0f, 1.0f,
			7.6f, 3.0f, 0.48f, 1.0f, 1.0f, 1.0f,
			//57
			6.4f, 3.0f, 0.48f, 1.0f, 1.0f, 1.0f,
			7.6f, 3.0f, 0.48f, 1.0f, 1.0f, 1.0f,
			7.8f, 1.6f, 0.48f, 1.0f, 1.0f, 1.0f,
			//58
			3.8f, 3.0f, 0.48f, 1.0f, 1.0f, 1.0f,
			4.2f, 3.0f, 0.48f, 1.0f, 1.0f, 1.0f,
			3.8f, 2.0f, 0.48f, 1.0f, 1.0f, 1.0f,
			//59
			0.0f, 1.6f, 0.48f, 1.0f, 1.0f, 1.0f,
			4.2f, 1.6f, 0.48f, 1.0f, 1.0f, 1.0f,
			4.2f, 7.4f, 0.48f, 1.0f, 1.0f, 1.0f,
			//60
			-3.8f, 3.0f, 0.48f, 1.0f, 1.0f, 1.0f,
			-3.8f, 9.6f, 0.48f, 1.0f, 1.0f, 1.0f,
			-7.6f, 3.0f, 0.48f, 1.0f, 1.0f, 1.0f,
			//61
			-6.4f, 3.0f, 0.48f, 1.0f, 1.0f, 1.0f,
			-7.6f, 3.0f, 0.48f, 1.0f, 1.0f, 1.0f,
			-7.8f, 1.6f, 0.48f, 1.0f, 1.0f, 1.0f,
			//62
			-3.8f, 3.0f, 0.48f, 1.0f, 1.0f, 1.0f,
			-4.2f, 3.0f, 0.48f, 1.0f, 1.0f, 1.0f,
			-3.8f, 2.0f, 0.48f, 1.0f, 1.0f, 1.0f,
			//63
			0.0f, 1.6f, 0.48f, 1.0f, 1.0f, 1.0f,
			-4.2f, 1.6f, 0.48f, 1.0f, 1.0f, 1.0f,
			-4.2f, 7.4f, 0.48f, 1.0f, 1.0f, 1.0f,
			//////////Brazo derecho
			//64
			5.7f, 6.4f, 0.48f, 1.0f, 1.0f, 1.0f,
			6.7f, 5.6f, 0.48f, 1.0f, 1.0f, 1.0f,
			6.1f, 7.2f, 0.48f, 1.0f, 1.0f, 1.0f,
			//65
			7.2f, 6.0f, 0.48f, 1.0f, 1.0f, 1.0f,
			6.7f, 5.6f, 0.48f, 1.0f, 1.0f, 1.0f,
			6.1f, 7.2f, 0.48f, 1.0f, 1.0f, 1.0f,
			//Brazo izquierdo
			//66
			-5.7f, 6.4f, 0.48f, 1.0f, 1.0f, 1.0f,
			-6.7f, 5.6f, 0.48f, 1.0f, 1.0f, 1.0f,
			-6.1f, 7.2f, 0.48f, 1.0f, 1.0f, 1.0f,
			//67
			-7.2f, 6.0f, 0.48f, 1.0f, 1.0f, 1.0f,
			-6.7f, 5.6f, 0.48f, 1.0f, 1.0f, 1.0f,
			-6.1f, 7.2f, 0.48f, 1.0f, 1.0f, 1.0f,
			/////Mano derecha
			//68
			5.6f, 7.9f, 0.48f, 1.0f, 1.0f, 0.0f,
			7.7f, 5.1f, 0.48f, 1.0f, 1.0f, 0.0f,
			8.0f, 7.0f, 0.48f, 1.0f, 1.0f, 0.0f,
			//69
			5.6f, 7.9f, 0.48f, 1.0f, 1.0f, 0.0f,
			7.2f, 8.2f, 0.48f, 1.0f, 1.0f, 0.0f,
			8.0f, 7.0f, 0.48f, 1.0f, 1.0f, 0.0f,

			//75
			7.8f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,
			7.2f, 8.2f, 0.48f, 1.0f, 1.0f, 0.0f,
			8.0f, 7.0f, 0.48f, 1.0f, 1.0f, 0.0f,

			////76
			7.8f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,
			8.8f, 8.2f, 0.48f, 1.0f, 1.0f, 0.0f,
			8.0f, 7.0f, 0.48f, 1.0f, 1.0f, 0.0f,
			
			//77
			7.8f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,
			8.8f, 8.2f, 0.48f, 1.0f, 1.0f, 0.0f,
			8.6f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,

			//78
			7.8f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,
			8.6f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,
			8.65f, 11.2f, 0.48f, 1.0f, 1.0f, 0.0f,

			//79
			8.8f, 11.0f, 0.48f, 1.0f, 1.0f, 0.0f,
			8.6f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,
			8.65f, 11.2f, 0.48f, 1.0f, 1.0f, 0.0f,
				
			//80
			/*8.8f, 11.0f, 0.48f, 1.0f, 1.0f, 0.0f,
			8.6f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,
			8.65f, 11.2f, 0.48f, 1.0f, 1.0f, 0.0f,*/

			//81
			8.6f, 9.0f, 0.48f, 1.0f, 1.0f, 0.0f,
			8.8f, 8.2f, 0.48f, 1.0f, 1.0f, 0.0f,
			9.8f, 9.0f, 0.48f, 1.0f, 1.0f, 0.0f,

			//82
			8.6f, 9.0f, 0.48f, 1.0f, 1.0f, 0.0f,
			9.7f, 9.2f, 0.48f, 1.0f, 1.0f, 0.0f,
			9.8f, 9.0f, 0.48f, 1.0f, 1.0f, 0.0f,

			//83
			7.8f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,
			7.2f, 8.2f, 0.48f, 1.0f, 1.0f, 0.0f,
			7.5f, 9.5f, 0.48f, 1.0f, 1.0f, 0.0f,
				
			//84
			7.8f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,
			7.65f, 9.75f, 0.48f, 1.0f, 1.0f, 0.0f,
			7.5f, 9.5f, 0.48f, 1.0f, 1.0f, 0.0f,

			//85
			8.4f, 7.3f, 0.48f, 1.0f, 1.0f, 0.0f,
			8.8f, 8.2f, 0.48f, 1.0f, 1.0f, 0.0f,
			8.0f, 7.0f, 0.48f, 1.0f, 1.0f, 0.0f,

			

			////Mano Izquierda
			//70
			-5.6f, 7.9f, 0.48f, 1.0f, 1.0f, 0.0f,
			-7.7f, 5.1f, 0.48f, 1.0f, 1.0f, 0.0f,
			-8.0f, 7.0f, 0.48f, 1.0f, 1.0f, 0.0f,
			//71
			-5.6f, 7.9f, 0.48f, 1.0f, 1.0f, 0.0f,
			-7.2f, 8.2f, 0.48f, 1.0f, 1.0f, 0.0f,
			-8.0f, 7.0f, 0.48f, 1.0f, 1.0f, 0.0f,

			//86
			-7.8f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,
			-7.2f, 8.2f, 0.48f, 1.0f, 1.0f, 0.0f,
			-8.0f, 7.0f, 0.48f, 1.0f, 1.0f, 0.0f,

			////87
			-7.8f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,
			-8.8f, 8.2f, 0.48f, 1.0f, 1.0f, 0.0f,
			-8.0f, 7.0f, 0.48f, 1.0f, 1.0f, 0.0f,

			//88
			-7.8f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,
			-8.8f, 8.2f, 0.48f, 1.0f, 1.0f, 0.0f,
			-8.6f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,

			//89
			-7.8f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,
			-8.6f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,
			-8.65f, 11.2f, 0.48f, 1.0f, 1.0f, 0.0f,

			//90
			-8.8f, 11.0f, 0.48f, 1.0f, 1.0f, 0.0f,
			-8.6f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,
			-8.65f, 11.2f, 0.48f, 1.0f, 1.0f, 0.0f,

			//80
			/*8.8f, 11.0f, 0.48f, 1.0f, 1.0f, 0.0f,
			8.6f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,
			8.65f, 11.2f, 0.48f, 1.0f, 1.0f, 0.0f,*/

			//91
			-8.6f, 9.0f, 0.48f, 1.0f, 1.0f, 0.0f,
			-8.8f, 8.2f, 0.48f, 1.0f, 1.0f, 0.0f,
			-9.8f, 9.0f, 0.48f, 1.0f, 1.0f, 0.0f,

			//92
			-8.6f, 9.0f, 0.48f, 1.0f, 1.0f, 0.0f,
			-9.7f, 9.2f, 0.48f, 1.0f, 1.0f, 0.0f,
			-9.8f, 9.0f, 0.48f, 1.0f, 1.0f, 0.0f,

			//93
			-7.8f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,
			-7.2f, 8.2f, 0.48f, 1.0f, 1.0f, 0.0f,
			-7.5f, 9.5f, 0.48f, 1.0f, 1.0f, 0.0f,

			//94
			-7.8f, 9.6f, 0.48f, 1.0f, 1.0f, 0.0f,
			-7.65f, 9.75f, 0.48f, 1.0f, 1.0f, 0.0f,
			-7.5f, 9.5f, 0.48f, 1.0f, 1.0f, 0.0f,

			//95
			-8.4f, 7.3f, 0.48f, 1.0f, 1.0f, 0.0f,
			-8.8f, 8.2f, 0.48f, 1.0f, 1.0f, 0.0f,
			-8.0f, 7.0f, 0.48f, 1.0f, 1.0f, 0.0f,
			
			////OJOS
			//izquierdo
			//72
			-1.4f, 5.2f, 0.52f, 1.0f, 1.0f, 1.0f,
			-2.0f, 6.4f, 0.52f, 1.0f, 1.0f, 1.0f,
			-0.6f, 6.4f, 0.52f, 1.0f, 1.0f, 1.0f,
				//103
				-1.4f, 5.2f, 0.52f, 1.0f, 1.0f, 1.0f,
				-0.8f, 5.8f, 0.52f, 1.0f, 1.0f, 1.0f,
				-0.6f, 6.4f, 0.52f, 1.0f, 1.0f, 1.0f,
				//108 pupila creo XD
				-2.2f, 6.4f, 0.53f, 0.0f, 0.0f, 0.0f,
				-1.4f, 6.4f, 0.53f, 0.0f, 0.0f, 0.0f,////
				-1.8f, 6.0f, 0.53f, 0.0f, 0.0f, 0.0f,
				//109 
				-1.3f, 6.0f, 0.53f, 0.0f, 0.0f, 0.0f,
				-1.4f, 6.4f, 0.53f, 0.0f, 0.0f, 0.0f,
				-1.8f, 6.0f, 0.53f, 0.0f, 0.0f, 0.0f,
				//110 
				-2.2f, 6.4f, 0.53f, 0.0f, 0.0f, 0.0f,
				-2.3f, 6.2f, 0.53f, 0.0f, 0.0f, 0.0f,
				-1.8f, 6.0f, 0.53f, 0.0f, 0.0f, 0.0f,
			//73
			-1.4f, 5.2f, 0.52f, 1.0f, 1.0f, 1.0f,
			-2.0f, 6.4f, 0.52f, 1.0f, 1.0f, 1.0f,
			-2.8f, 5.5f, 0.52f, 1.0f, 1.0f, 1.0f,
				//104
				-1.4f, 5.2f, 0.52f, 1.0f, 1.0f, 1.0f,
				-2.1f, 4.9f, 0.52f, 1.0f, 1.0f, 1.0f,
				-2.8f, 5.5f, 0.52f, 1.0f, 1.0f, 1.0f,
				
			//74
			-3.4f, 6.4f, 0.52f, 1.0f, 1.0f, 1.0f,
			-2.0f, 6.4f, 0.52f, 1.0f, 1.0f, 1.0f,
			-2.8f, 5.5f, 0.52f, 1.0f, 1.0f, 1.0f,
				//105
				-3.4f, 6.4f, 0.52f, 1.0f, 1.0f, 1.0f,
				-3.2f, 5.95f, 0.52f, 1.0f, 1.0f, 1.0f,
				-2.8f, 5.5f, 0.52f, 1.0f, 1.0f, 1.0f,
			//derecho
			//100
			1.4f, 5.2f, 0.52f, 1.0f, 1.0f, 1.0f,
			2.0f, 6.4f, 0.52f, 1.0f, 1.0f, 1.0f,
			0.6f, 6.4f, 0.52f, 1.0f, 1.0f, 1.0f,
				//106
				1.4f, 5.2f, 0.52f, 1.0f, 1.0f, 1.0f,
				0.8f, 5.8f, 0.52f, 1.0f, 1.0f, 1.0f,
				0.6f, 6.4f, 0.52f, 1.0f, 1.0f, 1.0f,
				//111 pupila creo XD
				2.2f, 6.4f, 0.53f, 0.0f, 0.0f, 0.0f,
				1.4f, 6.4f, 0.53f, 0.0f, 0.0f, 0.0f,////
				1.8f, 6.0f, 0.53f, 0.0f, 0.0f, 0.0f,
				//112 
				1.3f, 6.0f, 0.53f, 0.0f, 0.0f, 0.0f,
				1.4f, 6.4f, 0.53f, 0.0f, 0.0f, 0.0f,
				1.8f, 6.0f, 0.53f, 0.0f, 0.0f, 0.0f,
				//113 
				2.2f, 6.4f, 0.53f, 0.0f, 0.0f, 0.0f,
				2.3f, 6.2f, 0.53f, 0.0f, 0.0f, 0.0f,
				1.8f, 6.0f, 0.53f, 0.0f, 0.0f, 0.0f,
			//101
			1.4f, 5.2f, 0.52f, 1.0f, 1.0f, 1.0f,
			2.0f, 6.4f, 0.52f, 1.0f, 1.0f, 1.0f,
			2.8f, 5.5f, 0.52f, 1.0f, 1.0f, 1.0f,
			//102
			3.4f, 6.4f, 0.52f, 1.0f, 1.0f, 1.0f,
			2.0f, 6.4f, 0.52f, 1.0f, 1.0f, 1.0f,
			2.8f, 5.5f, 0.52f, 1.0f, 1.0f, 1.0f,
				//107
				3.4f, 6.4f, 0.52f, 1.0f, 1.0f, 1.0f,
				3.2f, 5.95f, 0.52f, 1.0f, 1.0f, 1.0f,
				2.8f, 5.5f, 0.52f, 1.0f, 1.0f, 1.0f,



		







			
			//////FONDO
			-30.0f, 30.0f,  -1.0f,		1.0f,	0.5f,	0.0f,
			30.0f, 30.0f,  -1.0f,			1.0f,	0.5f,	0.0f,
			-30.0f,  -30.0f,  -1.0f,			1.0f,	0.5f,	0.0f,

			-30.0f, -30.0f,  -1.0f,		1.0f,	0.5f,	0.0f,
			30.0f, -30.0f,  -1.0f,			1.0f,	0.5f,	0.0f,
			30.0f,  30.0f,  -1.0f,			1.0f,	0.5f,	0.0f,
			///////////////////
			

	};
	MeshColor *letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras,5400);
	meshColorList.push_back(letras);

}

void CreateShaders()
{

	Shader *shader1 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //�ndice 0 en MeshList
	CrearCubo();//�ndice 1 en MeshList
	CrearLetras(); //unico que usa MeshColor, �ndice 0 en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	glm::mat4 projection = glm::ortho(-18.0f, 18.0f, -18.0f, 18.0f, 0.1f, 100.0f);//aqui aumentamos el tama�o de la proyeccion
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	//glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		
		
															
		//Para las letras hay que usar el segundo set de shaders con �ndice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		
		
		glm::mat4 model(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();

		//Para el cubo y la pir�mide se usa el primer set de shaders con �ndice 0 en ShaderList


		shaderList[0].useShader(); 
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshList[1]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}