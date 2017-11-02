#include "UIPixelsTextRender.h"

void UIPixelsTextRender::render(const Camera & camera) const
{
	RECT rectangle = { 0 };
	rectangle.left = left;
	rectangle.top = top;
	auto hdc = camera.getBackDC();
	SetTextColor(hdc, 0x00000000);
	DrawText(hdc, text.c_str(), text.size(), &rectangle, DT_SINGLELINE | DT_NOCLIP);
}
