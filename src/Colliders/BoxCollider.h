#ifndef GRAPHICSV1_BoxCollider_H
#define GRAPHICSV1_BoxCollider_H

#include <glm/glm.hpp>
#include "../Transform.h"

class BoxCollider {
public:
	BoxCollider(Transform & transfotm) : transfotm(transfotm) {};
	const auto getLeftDownCornerLocal() const { return leftDownCorner; }
	void setLeftDownCornerLocal(const glm::tvec2<float> value) { leftDownCorner = value; }
	const auto getRightTopCornerLocal() const { return rightTopCorner; }
	void setRightTopCornerLocal(const glm::tvec2<float> value) { rightTopCorner = value; }

	const auto getLeftDownCornerGlobal() const { return getLeftDownCornerLocal() + transfotm.getPosition(); }
	const auto getRightTopCornerGlobal() const { return getRightTopCornerLocal() + transfotm.getPosition(); }
private:
	const Transform & transfotm;

	glm::tvec2<float> leftDownCorner;
	glm::tvec2<float> rightTopCorner;
};


#endif //GRAPHICSV1_BoxCollider_H