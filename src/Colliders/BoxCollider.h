#ifndef GRAPHICSV1_BoxCollider_H
#define GRAPHICSV1_BoxCollider_H

#include <glm/glm.hpp>
#include "../Transform.h"
#include <algorithm>

class BoxCollider {
public:
	BoxCollider(Transform & transfotm) : transfotm(transfotm) {};
	const auto getLeftDownCornerLocal() const { return leftDownCorner; }
	void setLeftDownCornerLocal(const glm::tvec2<float> value) { leftDownCorner = value; }
	const auto getRightTopCornerLocal() const { return rightTopCorner; }
	void setRightTopCornerLocal(const glm::tvec2<float> value) { rightTopCorner = value; }

	const auto getLeftDownCornerGlobal() const { return getLeftDownCornerLocal() + transfotm.getPosition2(); }
	const auto getRightTopCornerGlobal() const { return getRightTopCornerLocal() + transfotm.getPosition2(); }

	static bool areIntersect(const BoxCollider & a, const BoxCollider & b);

	void fitSize(glm::tvec2<float> size);
private:
	const Transform & transfotm;

	glm::tvec2<float> leftDownCorner;
	glm::tvec2<float> rightTopCorner;
};


#endif //GRAPHICSV1_BoxCollider_H