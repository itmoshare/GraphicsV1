#pragma once

#include <GL/glew.h>
#include "windows.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GL/gl.h>
#include <GL/glu.h>

#include "../LoadShaders.h"

class Camera
{
public:
	void initialize(HWND hwnd);
	void unInitialize();

	const auto getMainDC() const { return mainDC; }
	const HDC getBackDC() const { return backDC; }

	const auto getSize() const { return size; }

	void setBackBrush(const HBRUSH value);

	void beginRender();
	void endRender();

	const glm::tvec2<int32_t> transformGlobalToCamera(glm::tvec2<float> globalCoord) const;

	const auto getProjectionMatrix() const { return projectionMatrix; }
	void setProjectionMatrix(const glm::mat4 value) { projectionMatrix = value; }
	const auto getViewMatrix() const { return viewMatrix; }
	void setViewMatrix(const glm::mat4 value) { viewMatrix = value; }

	// TODO: move
	static GLuint programID;

	~Camera();
private:
	HWND hwnd;
	HDC mainDC;
	HDC backDC;
	HGLRC g_hRC = nullptr;

	glm::tvec2<int32_t> size;

	HBRUSH backBrush;
	void fillBackground() const;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
};