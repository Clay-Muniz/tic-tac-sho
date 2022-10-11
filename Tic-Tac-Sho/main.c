#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <tchar.h>

#include "Resources.h"

int wWidth = /*GetSystemMetrics(SM_CXSCREEN) ou */ 960;
int wHeight = /*GetSystemMetrics(SM_CYSCREEN) ou */ 540;
int fullScreen = 0;

int mouseX = 0, mouseY = 0, mouseL = 0, mouseR = 0, mouseM = 0; //Mouse

HINSTANCE g_instance = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

    switch(uMsg){

        case WM_MOUSEMOVE:
            mouseX = LOWORD(lParam);
            mouseY = HIWORD(lParam);
            return 0;

        case WM_SETFOCUS:
           //printf("WM_SETFOCUS\n");
           return 0;

        case WM_ACTIVATE:
           //printf("WM_ACTIVATE\n");
           return 0;

        case WM_CREATE:
            //printf("WM_CREATE\n");
            return 0;

        case WM_SIZE:
            //printf("WM_SIZE\n");
            return 0;

        case WM_MOVE:
            //printf("WM_MOVE\n");
            return 0;

        case WM_LBUTTONDOWN:
           mouseL = 1;
           return 0;

        case WM_LBUTTONUP:
           mouseL = 0;
           return 0;

        case WM_RBUTTONDOWN:
           mouseR = 1;
           return 0;

        case WM_RBUTTONUP:
           mouseR = 0;
           return 0;

        case WM_PAINT:
            //printf("WM_PAINT\n");
            {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                FillRect(GetDC(hwnd), &ps.rcPaint, (HBRUSH)(GRAY_BRUSH)/*cor cinza janela*/);
                EndPaint(hwnd, &ps);
            }
            return 0;

        case WM_DESTROY:
            //printf("WM_DESTROY\n");
            PostQuitMessage(0);
            return 0;
    }

    if(mouseL){
        printf("%d x %d - L\n", mouseX, mouseY);
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow){

    int wPosX = GetSystemMetrics(SM_CXSCREEN)/2 - wWidth/2;
    int wPosY = GetSystemMetrics(SM_CYSCREEN)/2 - wHeight/2;

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "BasicWindow";
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));

    RegisterClass(&wc);

    // criar janela

    HWND hwnd = CreateWindowEx(
        NULL, // estilo da janela "opcional"
        "BasicWindow", // CLASSE DO WINDOWS
        TEXT("Tic-Tac-Sho"), // nome da janela/texto escrito na janela
        WS_OVERLAPPED | WS_SYSMENU, // estilo da janela "obrigatório" - ex. sobreposta sempre ou opcional
                                    /*WS_POPUP - tela cheia*/

        // tamanho e posição
        wPosX, // posição (x)
        wPosY, // posição (y)
        wWidth, // largura
        wHeight, // altura

        NULL, // janela parente - pra dizer se é filha de alguem
        NULL, // Menu
        hInstance, // id especifico pra criar a janela
        NULL // Dados adicionais da aplicação(ñ mexer)
        );

    RECT wRect = {0, 0, wWidth, wHeight};

    AdjustWindowRectEx(&wRect,
                       GetWindowStyle(hwnd),
                       GetMenu(hwnd) != NULL,
                       GetWindowExStyle(hwnd));

    wPosX = (GetSystemMetrics(SM_CXSCREEN)/2) - ((wRect.right - wRect.left)/2);
    wPosY = (GetSystemMetrics(SM_CYSCREEN)/2) - ((wRect.bottom - wRect.top)/2);

    MoveWindow(hwnd,
               wPosX,
               wPosY,
               wRect.right - wRect.left,
               wRect.bottom - wRect.top,
               TRUE);

    if(hwnd == NULL){
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // rodar loop de mensagens

    MSG msg = {};

    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
