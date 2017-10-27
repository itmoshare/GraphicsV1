//
// Created by Dmitriy on 22.10.2017.
//

#include "ImageDiRender.h"
#include "windows.h"

ImageDiRender::ImageDiRender(const Transform & transform) : transform(transform)
{ }

void ImageDiRender::loadImage(std::string path)
{
	if (this->image != nullptr)
	{
		DeleteObject(image);
	}
	imagePath = path;
	image = (HBITMAP)LoadImage(NULL, (LPSTR)path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void ImageDiRender::fitImageSize()
{
	BITMAP info = { 0 };
	// Get the bitmap's information
	GetObject(image, sizeof(BITMAP), &info);
	this->setSize(glm::tvec2<int>(info.bmWidth, info.bmHeight));
}

void ImageDiRender::render(const Camera & camera) const
{
	auto pos = camera.transformGlobalToCamera(transform.getPosition());
	BITMAP info = { 0 };

	// Get the bitmap's information
	GetObject(image, sizeof(BITMAP), &info);
	auto hdcBitmap = CreateCompatibleDC(NULL);
	auto imgCopy = CopyImage(image, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	SelectObject(hdcBitmap, imgCopy);
	auto hdc = camera.getBackDC();
	//StretchBlt(hdc, static_cast<int>(round(pos.x) - size.x / 2), static_cast<int>(round(pos.y) - size.y / 2), size.x, size.y, hdcBitmap, 0, 0, info.bmWidth, info.bmHeight, SRCCOPY);
	TransparentBlt(hdc, static_cast<int>(round(pos.x) - size.x / 2), static_cast<int>(round(pos.y) - size.y / 2), size.x, size.y, hdcBitmap, 0, 0, info.bmWidth, info.bmHeight, RGB(0, 0, 0));

	DeleteDC(hdcBitmap);
	DeleteObject(imgCopy);
}