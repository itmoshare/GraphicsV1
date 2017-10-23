#include "UITextRender.h"

void UITextRender::render(HDC hdc) const
{
	RECT rectangle = { 0 };
	rectangle.left = left;
	rectangle.top = top;
	SetTextColor(hdc, 0x00000000);
	DrawText(hdc, text.c_str(), text.size(), &rectangle, DT_SINGLELINE | DT_NOCLIP);
}
