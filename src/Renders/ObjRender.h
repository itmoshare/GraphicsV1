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
	/*void loadImage(std::string path);
	void fitImageSize();*/
    void render(const Camera & camera) const;

	void setSize(glm::tvec2<int32_t> value) { size = value; }
	const auto & getSize() const { return size; }
private:
    const Transform & transform;
	glm::tvec2<int32_t> size;
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
