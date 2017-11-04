//
// Created by Dmitriy on 12.10.2017.
//

#ifndef GRAPHICSV1_GAMEOBJECT_H
#define GRAPHICSV1_GAMEOBJECT_H

#include <memory>
#include "windows.h"
#include "Colliders/BoxCollider.h"
#include "Renders/ObjRender.h"
#include "Transform.h"
#include <glm/vec2.hpp>

class GameObject {
public:
	GameObject() : collider(transform) { };
	auto & getTransformMut() { return transform; }

	auto & getColliderMut() { return collider; }
	const auto & getCollider() { return collider; }

	void setRender(std::unique_ptr<IRender> &render) 
	{
		this->render = std::move(render); 
	}
	const auto & getRender() const { return render; }
	auto * getRenderMut() { return render.get(); }
private:
	Transform transform;
	BoxCollider collider;
	std::unique_ptr<IRender> render = nullptr;
};


#endif //GRAPHICSV1_GAMEOBJECT_H
