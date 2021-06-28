#include <windows.h>
#include <string>
#include <math.h>
using namespace std;
#define ID_FILE_EXIT 1001
#define ID_STUFF_GO 1002

#define PI 3.14159265359


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK drugiprozor(HWND, UINT, WPARAM, LPARAM);

 HWND       hButton1,hButton2;
 HWND drugi;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR 
szCmdLine, int iCmdShow)
{
     MSG         msg;
   HWND        hWnd,hButton1,hButton2;
     WNDCLASS    wc;

     const char  szAppName[] = "DARKstar aplikacija";

     wc.cbClsExtra           = 0;
     wc.cbWndExtra           = 0;
     wc.hbrBackground        = (HBRUSH) GetStockObject(WHITE_BRUSH);
     wc.hCursor              = LoadCursor(NULL, IDC_ARROW);
     wc.hIcon                = LoadIcon(NULL, IDI_APPLICATION);
     wc.hInstance            = hInstance;
     wc.lpfnWndProc          = WndProc;
     wc.lpszClassName        = szAppName;
     wc.lpszMenuName         = NULL;
     wc.style                = CS_HREDRAW | CS_VREDRAW;
RegisterClass(&wc);
     

wc.lpszClassName = "PROZOR";
	 wc.lpfnWndProc = (WNDPROC)drugiprozor;
     RegisterClass(&wc);

     

drugi = CreateWindowEx(0,"PROZOR","Prozor",WS_OVERLAPPED | WS_SYSMENU,200,200,220,340,0,0,hInstance,0);

     hWnd = CreateWindow(    szAppName,
                             szAppName,
                             WS_OVERLAPPED | WS_SYSMENU,
                             CW_USEDEFAULT,
                             CW_USEDEFAULT,
                             300,
                             500,
                             NULL,
                             NULL,
                             hInstance,
                             NULL);

     ShowWindow(hWnd, iCmdShow);
     UpdateWindow(hWnd);
     
    
     

     while (GetMessage(&msg, NULL, 0, 0))
     {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
     }

     return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    
     static HWND        hEdit;
	
     switch (message)
     {
             
        break;
            
         case WM_CREATE:
         {
HMENU hMenu, hSubMenu;
 hMenu = CreateMenu();
hSubMenu = CreatePopupMenu();
 AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "E&xit");
AppendMenu(hMenu, MF_STRING | MF_POPUP,(UINT_PTR) hSubMenu, "&File");

 hSubMenu = CreatePopupMenu(); 
AppendMenu(hSubMenu, MF_STRING, ID_STUFF_GO, "&Go"); 
AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, "&Stuff");
  
SetMenu(hWnd, hMenu);
              hButton1 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "Start",
                                   WS_CHILD | WS_VISIBLE,
                                   0,0,0,0,
                                   hWnd,
                                   (HMENU)4,
                                     ((LPCREATESTRUCT) lParam) -> hInstance,
                                   NULL);
                                   
             hButton2 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "Start",
                                   WS_CHILD | WS_VISIBLE,
                                   0,0,0,0,
                                   hWnd,
                                   (HMENU)5,
                                     ((LPCREATESTRUCT) lParam) -> hInstance,
                                   NULL);
                                    
           return 0;                           
         }
         case WM_SIZE:
         {
             MoveWindow(hButton1, LOWORD(lParam) / 2 - 80, 20, 160, 30, TRUE);
        MoveWindow(hButton2, LOWORD(lParam) / 2 - 80, 70, 160, 30, TRUE);     
             return 0;
         }
         case WM_COMMAND:
         {
             if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == 4)   
                 {        
                 
                ShowWindow(drugi,SW_SHOW);  
                 
             }
             return 0;
         }
         case WM_DESTROY:
         {
             PostQuitMessage(0);
             return 0;
         }
     }
     return DefWindowProc(hWnd, message, wParam, lParam);
}


LRESULT CALLBACK drugiprozor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    
     
	
     switch (message)
     {
             
        
            
         case WM_CREATE:
         {
          break;              
         }
         case WM_SIZE:
         {
             break;     
             
         }
         case WM_COMMAND:
         {
          break;   
         }
         case WM_DESTROY:
         {
             PostQuitMessage(0);
             break;
         }
     }
     return DefWindowProc(hWnd, message, wParam, lParam);
}