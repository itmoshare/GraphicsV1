#include "../Colliders/BoxCollider.h"

void BoxCollider::fitSize(glm::tvec2<float> size)
{
	this->setLeftDownCornerLocal(glm::tvec2<float>(- size.x / 2, - size.y / 2));
	this->setRightTopCornerLocal(glm::tvec2<float>(size.x / 2, size.y / 2));
}
