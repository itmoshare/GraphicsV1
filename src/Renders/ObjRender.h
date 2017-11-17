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
#include <algorithm>

class ObjRender : public IRender {
public:
    ObjRender(const Transform & position);
	~ObjRender();
    const auto & getObjPath() const
    {
        return objPath;
    };
	void loadObj(std::string path);
	void loadBmp(std::string path);
    void render(const Camera & camera) const;

	void setScale(glm::tvec3<float> value) { scale = glm::scale(value); }
	const auto & getLeftDownCorner() const { return leftDownCorner; }
	const auto & getRightTopCorner() const { return rightTopCorner; }
	void fitSize();
private:
    const Transform & transform;
	glm::tvec2<int32_t> leftDownCorner;
	glm::tvec2<int32_t> rightTopCorner;
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

	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint texture;

	GLuint matrixID;
	GLuint textureID;
};


#endif //GRAPHICSV1_IMAGERENDER_H
