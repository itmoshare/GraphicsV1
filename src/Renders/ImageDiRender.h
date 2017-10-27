#pragma once

#include "IRender.h"
#include "../Transform.h"
#include <string>

class ImageDiRender : public IRender
{
public:
	ImageDiRender(const Transform & position);
	const auto & getImagePath() const
	{
		return imagePath;
	};
	void loadImage(std::string path);
	void fitImageSize();
	void render(const Camera & camera) const;

	void setSize(glm::tvec2<int32_t> value) { size = value; }
	const auto & getSize() const { return size; }
private:
	const Transform & transform;
	glm::tvec2<int32_t> size;
	std::string imagePath;
	HBITMAP image = nullptr;
};