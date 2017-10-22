//
// Created by Dmitriy on 12.10.2017.
//

#include "UserInput.h"

int UserInput::HandleWindowsMessages()
{
    MSG msg;

    // Here we check to see if there is a message, and remove it from the queue if so
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        //If we are trying to quit, post a quit message again and return -1 to tell
        // the previous function that call us to quit what ever it's doing.
        if(msg.message == WM_QUIT)
        {
            PostQuitMessage(0);
            return -1;
        }

        // Handle the messages
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        // We got a message so return 1
        return 1;
    }

    // No message, return 0
    return 0;
}
