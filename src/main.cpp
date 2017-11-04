#include <GL/glew.h>
#include "windows.h"

#include "CGame.h"
#include <ctime>

#define WIN_WID 640
#define WIN_HGT 480

#define MAIN_WINDOW_CLASS_NAME "EggsFall"

HWND  g_hWnd;
HINSTANCE g_hInstance;

LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

HWND CreateMainWindow(LPSTR strWindowName, HINSTANCE hInstance)
{
	srand(time(NULL));

    WNDCLASSEX wndclassex = {0};
    char class_name[] = MAIN_WINDOW_CLASS_NAME;

    wndclassex.cbSize = sizeof(WNDCLASSEX);
    wndclassex.style = CS_HREDRAW | CS_VREDRAW;
    wndclassex.lpfnWndProc = WinProc;
    wndclassex.hInstance = hInstance;
    wndclassex.lpszClassName = class_name;
    wndclassex.hCursor = NULL; //(HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR,
    // 0, 0, LR_SHARED);

    RegisterClassEx(&wndclassex);

    HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW,
                               strWindowName,
                               "EggsFall",
                               WS_OVERLAPPED | WS_SYSMENU | WS_CLIPCHILDREN | WS_VISIBLE,
                               CW_USEDEFAULT,
                               CW_USEDEFAULT,
                               WIN_WID,
                               WIN_HGT,
                               NULL,
                               NULL,
                               hInstance,
                               NULL/*&theGame*/);


    ShowWindow(hWnd, SW_SHOWNORMAL);					// Show the window
    UpdateWindow(hWnd);									// Draw the window

    SetFocus(hWnd);										// Sets Keymap Focus To The Window

    return hWnd;
}

void ClearAll()
{
    UnregisterClass(MAIN_WINDOW_CLASS_NAME, g_hInstance);		// Free the window class
    PostQuitMessage(0);									// Post a QUIT message to the window
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprev, PSTR cmdline, int ishow)
{
    auto hWnd = CreateMainWindow((LPSTR)"EggsFall", hinstance);

    // Error Check
    if(!hWnd)
        return EXIT_FAILURE;

    srand(GetTickCount()); // Seed random timer

    CGame theGame; // Our game object that will handle everything
    // Init the game
    if(!theGame.init(hWnd, hinstance))
    {
        MessageBox(NULL, "Couldn't load game!", "FATAL ERROR", MB_OK | MB_ICONERROR);
        return EXIT_FAILURE;
    }

    theGame.StartLoop(); // Run the game until we quit

    ClearAll();
    return 0;
}

// We use the WinProc to check when a button has button been pushed
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
//    static CGame *gamePtr = NULL;

    switch(message)
    {
//        case WM_CREATE:
//        {
//            // Get a pointer to the CGame object to use in the WinProc
//            gamePtr = (CGame*)(((LPCREATESTRUCT)lparam)->lpCreateParams);
//
//            if(gamePtr == NULL)
//                return -1; // An error has occurred
//            else
//                return 0;
//        }

        case WM_COMMAND:

            // If a button was clicked
//            if(HIWORD(wparam) == BN_CLICKED)
//            {
//                gamePtr->handleButtons(LOWORD(wparam));
//            }

            return 0;

        case WM_DESTROY:

            PostQuitMessage(0);
            return 0;

    } // end of switch(message)

    return DefWindowProc(hwnd, message, wparam, lparam);
}
