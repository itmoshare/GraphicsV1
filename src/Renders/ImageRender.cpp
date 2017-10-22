//
// Created by Dmitriy on 22.10.2017.
//

#include "ImageRender.h"
#include "windows.h"

ImageRender::ImageRender(const Transform & position) : position(position)
{ }

void ImageRender::setImagePath(std::string value)
{
    imagePath = value;
    if (this->image != nullptr)
    {
        DeleteObject(image);
    }
    image = (HBITMAP)LoadImage(NULL, (LPSTR)value.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
};

void ImageRender::render(HDC hdc) const
{
    auto pos = position.getPosition();
    BITMAP info = {0};

    // Get the bitmap's information
    GetObject(image, sizeof(BITMAP), &info);
    auto hdcBitmap = CreateCompatibleDC(NULL);
    auto imgCopy = CopyImage(image, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
    SelectObject(hdcBitmap, imgCopy);
    BitBlt(hdc, static_cast<int>(round(pos.x) - size.x / 2), static_cast<int>(round(pos.y) - size.y / 2), info.bmWidth, info.bmHeight, hdcBitmap, 0, 0, SRCCOPY);

	DeleteDC(hdcBitmap);
	DeleteObject(imgCopy);
}