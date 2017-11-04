#include "Camera.h"

GLuint Camera::programID = 0;

void Camera::initialize(HWND hwnd)
{
	this->hwnd = hwnd;
	this->mainDC = GetDC(hwnd);
	this->backDC = CreateCompatibleDC(mainDC);

	RECT clientRect;
	GetClientRect(this->hwnd, &clientRect);
	this->size = glm::tvec2<int32_t>(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);

	//auto bitmap = CreateCompatibleBitmap(mainDC, size.x, size.y);
	//SelectObject(backDC, bitmap);

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 16;
	pfd.cDepthBits = 16;

	GLuint iPixelFormat = ChoosePixelFormat(mainDC, &pfd);

	if (iPixelFormat != 0)
	{
		PIXELFORMATDESCRIPTOR bestMatch_pfd;
		DescribePixelFormat(mainDC, iPixelFormat, sizeof(pfd), &bestMatch_pfd);

		if (bestMatch_pfd.cDepthBits < pfd.cDepthBits)
		{
			return;
		}

		if (SetPixelFormat(mainDC, iPixelFormat, &pfd) == FALSE)
		{
			DWORD dwErrorCode = GetLastError();
			return;
		}
	}
	else
	{
		DWORD dwErrorCode = GetLastError();
		return;
	}

	g_hRC = wglCreateContext(mainDC);
	wglMakeCurrent(mainDC, g_hRC);
		
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	glewInit();

	Camera::programID = LoadShaders("D:/projects/GraphicsV1/src/eggsFall.vert", "D:/projects/GraphicsV1/src/eggsFall.frag");
}

void Camera::unInitialize()
{
	ReleaseDC(hwnd, mainDC);
}

void Camera::fillBackground() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Camera::setBackBrush(const HBRUSH value)
{
	this->backBrush = value;
	LOGBRUSH brushInfo = { 0 };
	GetObject(this->backBrush, sizeof(LOGBRUSH), &brushInfo);
	glClearColor(GetRValue(brushInfo.lbColor), GetGValue(brushInfo.lbColor), GetBValue(brushInfo.lbColor), 1.0f); // Цвет вьюпорта OpenGL
}

void Camera::beginRender()
{
	glUseProgram(programID);
	fillBackground();
}

void Camera::endRender()
{
	SwapBuffers(mainDC);
}

const glm::tvec2<int32_t> Camera::transformGlobalToCamera(glm::tvec2<float> globalCoord) const
{
	return glm::tvec2<int32_t>(globalCoord.x, size.y - globalCoord.y);
}

Camera::~Camera()
{
	unInitialize();
}
