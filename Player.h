//
// Created by Dmitriy on 12.10.2017.
//

#ifndef GRAPHICSV1_PLAYER_H
#define GRAPHICSV1_PLAYER_H

#include "windows.h"
#include "Colliders/BoxCollider.h"
#include "Renders/ImageRender.h"
#include "Transform.h"
#include <glm/vec2.hpp>

class Player {
public:
    Player();
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


#endif //GRAPHICSV1_PLAYER_H
