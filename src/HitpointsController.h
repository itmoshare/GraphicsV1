#pragma once

#include "Renders\IRender.h"
#include "Renders\ObjRender.h"
#include <vector>
#include "Transform.h"

class HitpointsController : public IRender
{
public:
	HitpointsController(const Transform & position);
	void dec();
	void render(const Camera & camera) const;
	void init(int value);
private:
	const Transform & transform;
	int curValue = 5;
	std::vector<Transform> transforms;
	std::vector<IRender*> renders;
};