#pragma once

#include "windows.h"

class IRender
{
public:
	virtual void render(HDC hdc) const = 0;
	virtual ~IRender() { };
};