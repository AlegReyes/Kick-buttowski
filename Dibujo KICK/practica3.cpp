//Práctica 3 semestre 2022-1: índices, mesh. proyecciones
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
//clases para dar orden y limpieza al código
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

//Pirámide irregular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,
		2,0,3,
		3,1,2,
		1,0,3,
	};
	GLfloat vertices[] = {
		-1.0f, 0.0f,0.5f,
		0.0f,2.0f,0.5f,
		1.0f,0.0f, 0.5f,
		0.0f,0.0,0.5f,

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}
//Vértices de un cubo
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
			-10.0f, -5.0f,  0.5f,		0.0f,	0.0f,	1.0f,
			-8.0f, -5.0f,  0.5f,			0.0f,	0.0f,	1.0f,
			-8.0f,  -3.0f,  0.5f,			0.0f,	0.0f,	1.0f,
			
	};
	MeshColor *letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras,5400);
	meshColorList.push_back(letras);

}

void CreateShaders()
{

	Shader *shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
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
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetras(); //unico que usa MeshColor, índice 0 en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//glm::mat4 projection = glm::ortho(-18.0f, 18.0f, -18.0f, 18.0f, 0.1f, 100.0f);//aqui aumentamos el tamaño de la proyeccion,esto es para 2D
	//glm::mat4 projection = glm::frustum(-18.0f, 18.0f, -18.0f, 18.0f, 0.1f, 100.0f);//a diferencia de ortho si visualizo profundidas
	glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);//la mas cercana al ojo humano
	//glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		
		
															
		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		
		
		glm::mat4 model(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();

		//Para el cubo y la pirámide se usa el primer set de shaders con índice 0 en ShaderList


		shaderList[0].useShader(); 
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();

        //instanciamos una piramide
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();//indice 0 para la piramide
		
		//instanciamos otra piramide
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, -4.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.5f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();//indice 0 para la piramide
		
		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}