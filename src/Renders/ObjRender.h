//
// Created by Dmitriy on 22.10.2017.
//

#ifndef GRAPHICSV1_IMAGERENDER_H
#define GRAPHICSV1_IMAGERENDER_H

#include <GL/glew.h>
#include <windows.h>

#include <string>
#include "../Transform.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "IRender.h"
#include <vector>
#include <cstdio>
#include <fstream>
#include <iostream>

class ObjRender : public IRender {
public:
    ObjRender(const Transform & position);
    const auto & getObjPath() const
    {
        return objPath;
    };
	void loadObj(std::string path);
	void loadBmp(std::string path);
    void render(const Camera & camera) const;

	void setSize(glm::tvec2<int32_t> value) { size = value; }
	void setScale(glm::tvec3<float> value) { scale = glm::scale(value); }
	const auto & getSize() const { return size; }
private:
    const Transform & transform;
	glm::tvec2<int32_t> size;
	glm::mat4 scale = glm::scale(glm::vec3(1, 1, 1));
	std::string objPath;

	// Obj data
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	bool loadOBJ(
		const char * path,
		std::vector<glm::vec3> & out_vertices,
		std::vector<glm::vec2> & out_uvs,
		std::vector<glm::vec3> & out_normals
	);

	void fitSize()
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
	};

	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint texture;

	GLuint matrixID;
	GLuint textureID;
};


#endif //GRAPHICSV1_IMAGERENDER_H
