//
// Created by Dmitriy on 22.10.2017.
//

#ifndef GRAPHICSV1_IMAGERENDER_H
#define GRAPHICSV1_IMAGERENDER_H

#include <string>
#include <windows.h>
#include "../Transform.h"
#include <glm/glm.hpp>

class ImageRender {
public:
    ImageRender(const Transform & position);
    const auto & getImagePath() const
    {
        return imagePath;
    };
	void loadImage(std::string path);
	void fitImageSize();
    void render(HDC hdc) const;

	void setSize(glm::tvec2<int32_t> value) { size = value; }
	const auto & getSize() const { return size; }
private:
    const Transform & transform;
	glm::tvec2<int32_t> size;
    std::string imagePath;
    HBITMAP image = nullptr;
};


#endif //GRAPHICSV1_IMAGERENDER_H
