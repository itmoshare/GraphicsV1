//
// Created by Dmitriy on 22.10.2017.
//

#ifndef GRAPHICSV1_POSITION_H
#define GRAPHICSV1_POSITION_H

#include <glm/glm.hpp>

class Transform {
public:
	Transform() {};
    glm::tvec2<float> movePosition(glm::tvec2<float> delta) { return setPosition(position + delta); }

    const glm::tvec2<float> getPosition() const { return position; }
    glm::tvec2<float> setPosition(glm::tvec2<float> value)
    {
        position = value;
        return position;
    }
private:
	glm::tvec2<float> position = { 0.0f, 0.0f };
};


#endif //GRAPHICSV1_POSITION_H
