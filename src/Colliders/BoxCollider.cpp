#include "../Colliders/BoxCollider.h"

bool BoxCollider::areInterset(const BoxCollider & a, const BoxCollider & b)
{
	const auto aLeftDownCorner = a.getLeftDownCornerGlobal();
	const auto aRightTopCorner = a.getRightTopCornerGlobal();
	const auto bLeftDownCorner = b.getLeftDownCornerGlobal();
	const auto bRightTopCorner = b.getRightTopCornerGlobal();
	if (aLeftDownCorner.x > bRightTopCorner.x || aRightTopCorner.x < aLeftDownCorner.x || aRightTopCorner.y < bLeftDownCorner.y || aLeftDownCorner.y > aRightTopCorner.y) return false;
	return true;
}

void BoxCollider::fitSize(glm::tvec2<float> size)
{
	this->setLeftDownCornerLocal(glm::tvec2<float>(- size.x / 2, - size.y / 2));
	this->setRightTopCornerLocal(glm::tvec2<float>(size.x / 2, size.y / 2));
}
