//
// Created by Dmitriy on 12.10.2017.
//

#ifndef GRAPHICSV1_GAMEOBJECT_H
#define GRAPHICSV1_GAMEOBJECT_H

#include "windows.h"
#include "Colliders/BoxCollider.h"
#include "Renders/ImageRender.h"
#include "Transform.h"
#include <glm/vec2.hpp>

class GameObject {
public:
	GameObject() : collider(transform), render(transform) { };
	auto & getTransformMut() { return transform; }

	auto & getColliderMut() { return collider; }
	const auto & getCollider() { return collider; }

	auto & getRenderMut() { return render; }
	const auto & getRender() const { return render; }
private:
	Transform transform;
	BoxCollider collider;
	ImageRender render;
};


#endif //GRAPHICSV1_GAMEOBJECT_H
