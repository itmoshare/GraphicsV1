//
// Created by Dmitriy on 12.10.2017.
//

#ifndef GRAPHICSV1_USERINPUT_H
#define GRAPHICSV1_USERINPUT_H

#include "windows.h"

class UserInput {
public:
    static int IsKeyDown(int keyCode)			{ return GetAsyncKeyState(keyCode) & 0x8000; }

    static int HandleWindowsMessages();
};


#endif //GRAPHICSV1_USERINPUT_H
