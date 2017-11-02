//
// Created by Dmitriy on 22.10.2017.
//

#include "ImagePixelsRender.h"
#include "windows.h"

ImagePixelsRender::ImagePixelsRender(const Transform & transform) : transform(transform)
{ }

void ImagePixelsRender::loadImage(std::string path)
{
	if (this->image != nullptr)
	{
		DeleteObject(image);
	}
	imagePath = path;
	image = (HBITMAP)LoadImage(NULL, (LPSTR)path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void ImagePixelsRender::fitImageSize()
{
	BITMAP info = { 0 };
	// Get the bitmap's information
	GetObject(image, sizeof(BITMAP), &info);
	this->setSize(glm::tvec2<int>(info.bmWidth, info.bmHeight));
}

void ImagePixelsRender::render(const Camera & camera) const
{
	auto pos = camera.transformGlobalToCamera(transform.getPosition());

	BITMAPINFO bitmapInfo = { 0 };
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biBitCount = 24;
	bitmapInfo.bmiHeader.biWidth = camera.getSize().x;
	bitmapInfo.bmiHeader.biHeight = camera.getSize().y;
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biCompression = 0;

	unsigned char* bits = nullptr;

	auto dibSection = CreateDIBSection(camera.getBackDC(), &bitmapInfo, DIB_RGB_COLORS, (VOID **)&bits, NULL, 0);
	for (int i = 0; i < bitmapInfo.bmiHeader.biWidth * bitmapInfo.bmiHeader.biHeight * 3; i+=3)
	{
		bits[i] = 0;
		bits[i + 1] = 255;
		bits[i + 2] = 0;
	}

	auto hdcMem = CreateCompatibleDC(camera.getBackDC());
	auto bmp = SelectObject(hdcMem, dibSection);

	BitBlt(camera.getBackDC(), 0, 0, camera.getSize().x, camera.getSize().y, hdcMem, 0, 0, SRCCOPY);

	DeleteObject(dibSection);
	DeleteObject(hdcMem);
	DeleteObject(bmp);
}