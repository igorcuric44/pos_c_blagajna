#include<windows.h>
#include<iostream>
#include<sstream>
#include "sqlite3.h"
using namespace std;

#define hBUTTON1 1001
#define hBUTTON2 1002

#define eID 2001
#define eARTIKL 2002
#define eKOLICINA 2003
#define eMJERA 2004
#define ePDV 2005
#define eCIJENA 2006
#define huBUTTON1 2007
#define huBUTTON2 2008

HWND hId,hArtikl,hKolicina,hMjera,hPdv,hCijena,huButton1,huButton2;

LRESULT CALLBACK WndProc(HWND, UINT , WPARAM , LPARAM );
LRESULT CALLBACK drugiprozor(HWND, UINT , WPARAM , LPARAM );
LRESULT CALLBACK treciprozor(HWND, UINT , WPARAM , LPARAM );

HWND hButton1,hButton2;

HWND drugi,treci;

HINSTANCE hins;


template <typename T>
bool GetDlgItemNumber(HWND aHwndDlg, int aDlgItemId, T &aVal)
{
   char Buffer[256];
   if(!GetDlgItemText(aHwndDlg, aDlgItemId, Buffer, sizeof(Buffer)))
      return false;
   std::stringstream ss(Buffer);
   return ss >> aVal;
}






int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    hins=hInstance;

    const char g_szClassName[] = "myWindowClass";

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&wc);
  

wc.lpszClassName = "blagajna";
	 wc.lpfnWndProc = (WNDPROC)drugiprozor;
     RegisterClassEx(&wc);

wc.lpszClassName = "unos";
	 wc.lpfnWndProc = (WNDPROC)treciprozor;
     RegisterClassEx(&wc);

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "The title of my window",
        WS_OVERLAPPED | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT,
	 300,500,NULL, NULL, hInstance, NULL);

  

//drugi = CreateWindowEx(0,"blagajna","BLAGAJNA",WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,300,500,0,0,hInstance,0);
//treci = CreateWindowEx(0,"unos","UNOS",WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,300,500,0,0,hInstance,0);


    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
case WM_CREATE:
         {
drugi = CreateWindowEx(0,"blagajna","BLAGAJNA",WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,300,500,hwnd,0,hins,0);
treci = CreateWindowEx(0,"unos","UNOS",WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,300,500,hwnd,0,hins,0);

	hButton1 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "Blagajna",
                                   WS_CHILD | WS_VISIBLE,
                                   60,30,180,30,
                                   hwnd,
                                   (HMENU)hBUTTON1,
                                    hins,
                                   NULL);
                                   
             hButton2 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "Unos",
                                   WS_CHILD | WS_VISIBLE,
                                   60,70,180,30,
                                   hwnd,
                                   (HMENU)hBUTTON2,
                                    hins,
                                   NULL);

}
break;
case WM_COMMAND:
         {
             if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hBUTTON1)   
                 {        
                 
                ShowWindow(drugi,SW_SHOW);  
                 
             }
if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hBUTTON2)   
                 {        
                 
                ShowWindow(treci,SW_SHOW);  
                 
             }
             
         }
break;
case WM_SIZE:
         {
        
        MoveWindow(hButton1, LOWORD(lParam) / 2 - 80, 20, 160, 30, TRUE);
        MoveWindow(hButton2, LOWORD(lParam) / 2 - 80, 70, 160, 30, TRUE);     
                  
             }
	break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    
}


LRESULT CALLBACK drugiprozor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:

            ShowWindow(hwnd,SW_HIDE);

        break;
        case WM_DESTROY:
            {
               
            } break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
     
}


LRESULT CALLBACK treciprozor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_CREATE:
{

	
CreateWindowEx(0,"Static","Id",WS_CHILD | WS_VISIBLE,20,10,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Artikl",WS_CHILD | WS_VISIBLE,20,60,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Pdv",WS_CHILD | WS_VISIBLE,20,110,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Kolicina",WS_CHILD | WS_VISIBLE,20,160,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Mjera",WS_CHILD | WS_VISIBLE,20,210,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Cijena",WS_CHILD | WS_VISIBLE,20,260,80,30,hwnd,0,hins,NULL);
	
hId=CreateWindowEx(0,"Edit","Id",WS_CHILD | WS_VISIBLE| WS_BORDER,140,10,130,30,hwnd,(HMENU)eID,hins,NULL);
hArtikl=CreateWindowEx(0,"Edit","Artikl",WS_CHILD | WS_VISIBLE| WS_BORDER,140,60,130,30,hwnd,(HMENU)eARTIKL,hins,NULL);
hPdv=CreateWindowEx(0,"Edit","Pdv",WS_CHILD | WS_VISIBLE| WS_BORDER,140,110,130,30,hwnd,(HMENU)ePDV,hins,NULL);
hKolicina=CreateWindowEx(0,"Edit","Kolicina",WS_CHILD | WS_VISIBLE| WS_BORDER,140,160,130,30,hwnd,(HMENU)eKOLICINA,hins,NULL);
hMjera=CreateWindowEx(0,"Edit","Mjera",WS_CHILD | WS_VISIBLE| WS_BORDER,140,210,130,30,hwnd,(HMENU)eMJERA,hins,NULL);
hCijena=CreateWindowEx(0,"Edit","Cijena",WS_CHILD | WS_VISIBLE| WS_BORDER,140,260,130,30,hwnd,(HMENU)eCIJENA,hins,NULL);

huButton1 = CreateWindowEx(BS_PUSHBUTTON,"button","Potvrdi",WS_CHILD | WS_VISIBLE,60,30,180,30,hwnd,(HMENU)huBUTTON1,hins,NULL);
huButton2 = CreateWindowEx(BS_PUSHBUTTON,"button","Odustani",WS_CHILD | WS_VISIBLE,60,30,180,30,hwnd,(HMENU)huBUTTON2,hins,NULL);

}
break;

case WM_COMMAND:
         {

		if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==huBUTTON1)   
                 {        
                int Id;
		string Artikl;
		double Kolicina,Mjera,Cijena,Pdv; 
		GetDlgItemNumber(hwnd,eID,Id);
		GetDlgItemNumber(hwnd,eARTIKL,Artikl);
		GetDlgItemNumber(hwnd,ePDV,Pdv);
		GetDlgItemNumber(hwnd,eKOLICINA,Kolicina);
		GetDlgItemNumber(hwnd,eMJERA,Mjera);
		GetDlgItemNumber(hwnd,eCIJENA,Cijena);

                 ShowWindow(hwnd,SW_HIDE);
		cout<<Id<<endl;
		cout<<Artikl<<endl;
		cout<<Pdv<<endl;
		cout<<Kolicina<<endl;
  		cout<<Mjera<<endl;
		cout<<Cijena<<endl;
sqlite3 *db;
sqlite3_stmt *res;
int rc;

rc=sqlite3_open("baza.db",&db);
if(rc!=SQLITE_OK)
{
    cout<<sqlite3_errmsg(db);
}else {
stringstream sql;
sql<<"INSERT INTO skladiste (id,artikl,pdv,kolicina,mjera,cijena) VALUES ("<<Id<<",'"<<Artikl<<"',"<<Pdv<<","<<Kolicina<<","<<Mjera<<","<<Cijena<<");";
rc=sqlite3_prepare(db,sql.str().c_str(),-1,&res,NULL);
    if(rc!=SQLITE_OK)
    {
        cout<<sqlite3_errmsg(db);
        sqlite3_close(db);
    }
    rc=sqlite3_step(res);
}

sqlite3_finalize(res);
sqlite3_close(db);
                 
             }
		if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==huBUTTON2)   
                 {        
                 
                 ShowWindow(hwnd,SW_HIDE);  
                 
             }
}
break;
case WM_SIZE:
         {
        
        MoveWindow(huButton1,  40, HIWORD(lParam)-60, 80, 30, TRUE);
        MoveWindow(huButton2, LOWORD(lParam)-120, HIWORD(lParam)-60, 80, 30, TRUE);     
                  
             }
	break;
       case WM_CLOSE:
           ShowWindow(hwnd,SW_HIDE);

      break; 
        case WM_DESTROY:
            {
               
            } break;
      default:  
     return DefWindowProc(hwnd,msg,wParam,lParam);
}

}