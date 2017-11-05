//
// Created by Dmitriy on 22.10.2017.
//

#include "ObjRender.h"

ObjRender::ObjRender(const Transform & transform) : transform(transform)
{ }

ObjRender::~ObjRender()
{
	const GLuint buffres[] = { vertexbuffer, uvbuffer, normalbuffer };
	glDeleteBuffers(3, buffres);
}

void ObjRender::loadObj(std::string path)
{
	this->objPath = path;

	(void)loadOBJ(this->objPath.c_str(), vertices, uvs, normals);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
}



void ObjRender::loadBmp(std::string path)
{
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char * data;
	FILE * file = fopen(path.c_str(), "rb");
	if (!file) {
		throw std::exception("Can't load bmp");
	}
	if (fread(header, 1, 54, file) != 54) {
		printf("Некорректный BMP-файлn");
		throw std::exception("Invalid bmp header");
	}
	if (header[0] != 'B' || header[1] != 'M') {
		printf("Некорректный BMP-файлn");
		throw std::exception("File is not bmp file");
	}
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	if (imageSize == 0) imageSize = width*height * 3;
	if (dataPos == 0) dataPos = 54;

	data = new unsigned char[imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	textureID = glGetUniformLocation(Camera::programID, "myTextureSampler");
	matrixID = glGetUniformLocation(Camera::programID, "MVP");
}

void ObjRender::render(const Camera & camera) const
{
	glm::mat4 Model = glm::mat4(1.0f) * glm::translate(transform.getPosition()) * scale;
	glm::mat4 MVP = camera.getProjectionMatrix() * camera.getViewMatrix() * Model;

	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(textureID, 0);

	// vertices
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

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

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
	for (unsigned int i = 0; i<vertexIndices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);

	}
	return true;
}

void ObjRender::fitSize()
{
	float minX = std::numeric_limits<float>::max(), maxX = std::numeric_limits<float>::min();
	float minY = std::numeric_limits<float>::max(), maxY = std::numeric_limits<float>::min();
	float minZ = std::numeric_limits<float>::max(), maxZ = std::numeric_limits<float>::min();
	for (int i = 0; i < vertices.size(); i++)
	{
		auto pos = glm::vec3(glm::mat3(scale) * vertices[i]);
		if (pos.x > maxX) maxX = pos.x;
		if (pos.x < minX) minX = pos.x;
		if (pos.y > maxY) maxY = pos.y;
		if (pos.y < minY) minY = pos.y;
		if (pos.z > maxZ) maxZ = pos.z;
		if (pos.z < minZ) minZ = pos.z;
	}
	size = glm::vec2(std::max(std::abs(maxX), std::abs(minX)), std::max(std::abs(maxY), std::abs(minY)));
}
