#include "Mesh.h"

Mesh::Mesh()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;

}
MeshColor::MeshColor()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	vertexCount = 0;

}

void Mesh::CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numberOfIndices)
{

	indexCount = numberOfIndices;
	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numberOfIndices, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tama�o, los datos y en este caso es est�tico pues no se modificar�n los valores

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(vertices[0]*3), 0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0] * 6), (void*)(sizeof(vertices[0]) * 3));
	//glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void MeshColor::CreateMeshColor(GLfloat *vertices, unsigned int numOfVertices)
{
	vertexCount = numOfVertices;
	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tama�o, los datos y en este caso es est�tico pues no se modificar�n los valores
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 6, 0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 6, (void*)(sizeof(vertices[0]) * 3));//Offset de los 3 v�rtices para tomar los 3 de color
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(sizeof(GL_FLOAT)* 3));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Mesh::RenderMesh()
{
	////////////Para dibujar desde los �ndices
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void MeshColor::RenderMeshColor()
{
	////////////Para dibujar desde los v�rtices
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);
}

void Mesh::ClearMesh()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO); ///LIMPIAR BUFFER PARAE EVITAR OCUPAR LA MEMORIA
		IBO = 0;
	}
	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO); ///LIMPIAR BUFFER PARAE EVITAR OCUPAR LA MEMORIA
		VBO = 0;
	}
	if(VAO!=0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
	indexCount = 0;
}

void MeshColor::ClearMeshColor()
{
	
	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO); ///LIMPIAR BUFFER PARAE EVITAR OCUPAR LA MEMORIA
		VBO = 0;
	}
	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
	vertexCount= 0;
}
Mesh::~Mesh()
{
	ClearMesh();
}
MeshColor::~MeshColor()
{
	ClearMeshColor();
}
