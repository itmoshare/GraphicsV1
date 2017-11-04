//
// Created by Dmitriy on 22.10.2017.
//

#include "ObjRender.h"

ObjRender::ObjRender(const Transform & transform) : transform(transform)
{ }

void ObjRender::loadObj(std::string path)
{
	this->objPath = path;

	(void)loadOBJ(this->objPath.c_str(), vertices, uvs, normals);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
}

void ObjRender::render(const Camera & camera) const
{
	glm::mat4 Model = glm::translate(glm::mat4(1.0f), transform.getPosition3());
	glm::mat4 MVP = camera.getProjectionMatrix() * camera.getViewMatrix() * Model;
	// TODO: move
	GLuint MatrixID = glGetUniformLocation(Camera::programID, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  
		3,                  
		GL_FLOAT,           
		GL_FALSE,           
		0,                  
		(void*)0            
	);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glDisableVertexAttribArray(0);
}

bool ObjRender::loadOBJ(const char * path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cerr << "Impossible to open the file !" << std::endl;
		return false;
	}

	while (1) 
	{
		std::string type;
		if (!(file >> type))
		{
			break;
		}

		if (type == "v")
		{
			glm::vec3 vertex;
			file >> vertex.x >> vertex.y >> vertex.z;
			temp_vertices.push_back(vertex);
		}
		else if (type == "vt") 
		{
			glm::vec2 uv;
			file >> uv.x >> uv.y;
			temp_uvs.push_back(uv);
		}
		else if (type == "vn")
		{
			glm::vec3 normal;
			file >> normal.x >> normal.y >> normal.z;
			temp_normals.push_back(normal);
		}
		else if (type == "#") 
		{
			std::string str;
			std::getline(file, str);
		}
		else if (type == "f") 
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			char ch;
			file >> vertexIndex[0] >> ch >> uvIndex[0] >> ch >> normalIndex[0] >> vertexIndex[1] >> ch >> uvIndex[1] >> ch >> normalIndex[1] >> vertexIndex[2] >> ch >> uvIndex[2] >> ch >> normalIndex[2];
			
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}
	return true;
}
