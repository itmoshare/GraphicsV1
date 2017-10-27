#pragma once

#include "windows.h"
#include <string>
#include <glm/glm.hpp>
#include "IRender.h"

class UITextRender : public IRender
{
public:
	void setText(const std::string text) { this->text = text; };

	void setLeft(int32_t value) { left = value; }
	void setTop(int32_t value) { top = value; }

	void render(const Camera & camera) const;
private:
	std::string text;
	int32_t left;
	int32_t top;
};