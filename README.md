# simpleWindow

use .sln file to build this project in Visual Studio 2019.

choice you platform x86/x64, and build solution or debug. 

 simpleWindow.cpp : Defines the entry point for the application.
 author: Chino, create date: 2022-07-19-Tue.

the main program used heads:

#include "framework.h"
#include "simpleWindow.h"

and defined variables:

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

then 

// TODO: Place code here.
    // Initialize global strings
    // Perform application initialization:
    // Main message loop:
//
//  FUNCTION: MyRegisterClass()
//  PURPOSE: Registers the window class.
//   FUNCTION: InitInstance(HINSTANCE, int)
//   PURPOSE: Saves instance handle and creates main window
//   COMMENTS:
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//  PURPOSE: Processes messages for the main window.
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
// Message handler for about box.
