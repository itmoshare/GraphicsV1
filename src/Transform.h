//
// Created by Dmitriy on 22.10.2017.
//

#ifndef GRAPHICSV1_POSITION_H
#define GRAPHICSV1_POSITION_H

#include <glm/glm.hpp>

class Transform {
public:
	Transform() {};
    glm::tvec3<float> movePosition(glm::tvec3<float> delta) { return setPosition(position + delta); }

    const auto getPosition() const { return position; }
	const auto getPosition2() const { return glm::vec2(position.x, position.y); }
    glm::tvec3<float> setPosition(glm::tvec3<float> value)
    {
		position = glm::vec3(value.x, value.y, 0);
        return position;
    }
private:
	glm::tvec3<float> position = { 0.0f, 0.0f, 0.0f };
};


#endif //GRAPHICSV1_POSITION_H
