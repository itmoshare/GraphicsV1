#pragma once

#include "windows.h"
#include "Camera.h"

class IRender
{
public:
	virtual void render(const Camera & camera) const = 0;
	virtual ~IRender() { };
};