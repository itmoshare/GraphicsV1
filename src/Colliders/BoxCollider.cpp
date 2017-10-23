#include "../Colliders/BoxCollider.h"

bool BoxCollider::areIntersect(const BoxCollider & a, const BoxCollider & b)
{
	// TODO: to normal coordinates
	const auto aLeftDownCorner = a.getLeftDownCornerGlobal();
	const auto aRightTopCorner = a.getRightTopCornerGlobal();
	const auto bLeftDownCorner = b.getLeftDownCornerGlobal();
	const auto bRightTopCorner = b.getRightTopCornerGlobal();

	const auto aleft = std::min(aLeftDownCorner.x, aRightTopCorner.x);
	const auto aright = std::max(aLeftDownCorner.x, aRightTopCorner.x);

	const auto atop = std::max(aLeftDownCorner.y, aRightTopCorner.y);
	const auto abottom = std::min(aLeftDownCorner.y, aRightTopCorner.y);

	const auto bleft = std::min(bLeftDownCorner.x, bRightTopCorner.x);
	const auto bright = std::max(bLeftDownCorner.x, bRightTopCorner.x);

	const auto btop = std::max(bLeftDownCorner.y, bRightTopCorner.y);
	const auto bbottom = std::min(bLeftDownCorner.y, bRightTopCorner.y);

	if (aleft > bright || aright < bleft || atop < bbottom || abottom > btop) return false;
	return true;
}

void BoxCollider::fitSize(glm::tvec2<float> size)
{
	this->setLeftDownCornerLocal(glm::tvec2<float>(- size.x / 2, - size.y / 2));
	this->setRightTopCornerLocal(glm::tvec2<float>(size.x / 2, size.y / 2));
}
