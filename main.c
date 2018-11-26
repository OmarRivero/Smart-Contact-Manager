#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <w32api.h>
#include "resources.h"
#include "estructuras.h"

#define FILE_MEN_NEW 1

//La clase ventana no tiene que ver con c++
const char g_szClassName[] = "MyWindowClass";
HMENU hMenu;
LRESULT CALLBACK Wnd1(HWND hwnd1, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Wnd2(HWND hwnd2, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Wnd3(HWND hwnd3, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Wnd4(HWND hwnd4, UINT msg, WPARAM wParam, LPARAM lParam);
void AddMenus(HWND hwn1);

LRESULT CALLBACK Wnd1(HWND hwnd1, UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg){
        case WM_COMMAND:
            switch(wParam){
                case 1:
                    MessageBeep(MB_OK);
                    break;
            }
            break;
        case WM_CREATE:
            AddMenus(hwnd1);
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd1);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd1, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd1;
    MSG msg;

    // Registrando la clase Window
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = Wnd1;
    wc.cbClsExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)){
        MessageBox(NULL, "Fallo el registro de la clase window!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    //Creacion de la ventana
    hwnd1 = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Smart Contact Manager",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 520,
        NULL, NULL, hInstance, NULL);

    if(hwnd1 == NULL){
        MessageBox(NULL, "Fallo la creacion de la ventana!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd1, nCmdShow);
    UpdateWindow(hwnd1);

    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

void AddMenus(HWND hwnd1){
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "Opciones");
    SetMenu(hwnd1, hMenu);
}
