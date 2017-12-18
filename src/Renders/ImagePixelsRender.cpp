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
	bitmapInfo.bmiHeader.biWidth = size.x;
	bitmapInfo.bmiHeader.biHeight = size.y;
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;

	auto t = ((size.x * 24 + 31) / 32) * 4;
	DWORD dwBmpSize = t * size.y;
	unsigned char *bits = new unsigned char[dwBmpSize];
	GetDIBits(camera.getMainDC(), image, 0, size.y, bits, &bitmapInfo, DIB_RGB_COLORS);

	for (int lx = 0; lx < bitmapInfo.bmiHeader.biWidth; lx++)
		for (int ly = 0; ly < bitmapInfo.bmiHeader.biHeight; ly++)
		{
			int ax = transform.getPosition().x + lx;
			int ay = transform.getPosition().y + ly;

			if (ax * 3 >= camera.getSize().x * 3 || 
				ay * 3 >= camera.getSize().y * 3 ||
				ax < 0 ||
				ay < 0)
				continue;

			int cameraPixel = ax * 3 + ay * camera.getSize().x * 3;
			int imagePixel = lx * 3 + ly * t;
			if (bits[imagePixel] == 0 && bits[imagePixel + 1] == 0 || bits[imagePixel + 2] == 0)
				continue;
			camera.bytes[cameraPixel] = bits[imagePixel];
			camera.bytes[cameraPixel + 1] = bits[imagePixel + 1];
			camera.bytes[cameraPixel + 2] = bits[imagePixel + 2];
		}

	delete bits;
}