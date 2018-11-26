#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <w32api.h>
#include "resources.h"
#include "estructuras.h"

// Identificadores de menu
#define FILE_MENU_AGREGAR 1
#define FILE_MENU_BUSCAR 2
#define FILE_MENU_VER 3
#define MENU_SALIR 4
#define FILE_MENU_NAME 5


// Identificadores de controles
#define BTN_ADD_CONTACT 6
#define BTN_FIND_CONTACT 7
#define BTN_SEEA_CONTACT 8

//La clase ventana no tiene que ver con c++
const char g_szClassName[] = "MyWindowClass";

HMENU hMenu;
HWND hEdit; //Variable para trabajar con el text box

// Prototipos de funciones
LRESULT CALLBACK Wnd1(HWND hwnd1, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Wnd2(HWND hwnd2, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Wnd3(HWND hwnd3, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Wnd4(HWND hwnd4, UINT msg, WPARAM wParam, LPARAM lParam);
void AddMenus(HWND hwn1);
void AddControles(HWND hwnd1);

LRESULT CALLBACK Wnd1(HWND hwnd1, UINT msg, WPARAM wParam, LPARAM lParam){
    char nuevoTitulo[200];
    switch(msg){
        case WM_COMMAND:
            switch(wParam){
                case FILE_MENU_AGREGAR:
                    MessageBeep(MB_OK);
                    break;
                case FILE_MENU_BUSCAR:
                    MessageBeep(MB_OK);
                    break;
                case FILE_MENU_VER:
                    MessageBeep(MB_OK);
                    break;
                case FILE_MENU_NAME:
                    GetWindowText(hEdit, nuevoTitulo, 100);
                    SetWindowText(hwnd1, nuevoTitulo);
                    break;
                case MENU_SALIR:
                    DestroyWindow(hwnd1);
                    break;
                case BTN_ADD_CONTACT:
                    MessageBeep(MB_OK);
                    break;
                case BTN_FIND_CONTACT:
                    MessageBeep(MB_OK);
                    break;
                case BTN_SEEA_CONTACT:
                    MessageBeep(MB_OK);
                    break;
            }
            break;
        case WM_CREATE:
            AddMenus(hwnd1);
            AddControles(hwnd1);
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
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
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

    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_AGREGAR, "Agregar contactos");
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_BUSCAR, "Buscar contactos");
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_VER, "Ver todos los contactos");
    //AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NAME, "Cambiar titulo de ventana"); Opcion de menu para cambiar el titulo de ventana
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "Opciones");
    AppendMenu(hMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hMenu, MF_STRING, MENU_SALIR,"Salir");
    SetMenu(hwnd1, hMenu);
}

void  AddControles(HWND hwnd1){
    //CreateWindowW(L"static", L"Introduce texto aqui: ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 300, 100, 200, 50, hwnd1, NULL, NULL, NULL);
    //hEdit = CreateWindowW(L"Edit", L"...", WS_VISIBLE | WS_CHILD | WS_BORDER, 300, 170, 200, 50, hwnd1, NULL, NULL, NULL);
    CreateWindowW(L"Button", L"Anadir contacto", WS_VISIBLE | WS_CHILD | WS_BORDER, 300, 100, 200, 50, hwnd1, BTN_ADD_CONTACT, NULL, NULL);
    CreateWindowW(L"Button", L"Buscar contacto", WS_VISIBLE | WS_CHILD | WS_BORDER, 300, 170, 200, 50, hwnd1, BTN_FIND_CONTACT, NULL, NULL);
    CreateWindowW(L"Button", L"Ver todos los contactos", WS_VISIBLE | WS_CHILD | WS_BORDER, 300, 240, 200, 50, hwnd1, BTN_SEEA_CONTACT, NULL, NULL);
}
