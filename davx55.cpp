#include<windows.h>
#include <cstring>
#include<iostream>
#include<sstream>
#include<commctrl.h>
#include "sqlite3.h"
#include<string>
#include <ctime>
using namespace std;

#define hBUTTON1 1001
#define hBUTTON2 1002
#define hBUTTON3 1003
#define hBUTTON4 1004
#define hBUTTON5 1005
#define hBUTTON6 1006
#define hBUTTON7 1007
#define hBUTTON8 1008
#define hBUTTON9 1009
#define hBUTTON10 1010
#define hSTATIC1 1011

#define eID 2001
#define eARTIKL 2002
#define eKOLICINA 2003
#define eMJERA 2004
#define ePDV 2005
#define eCIJENA 2006
#define huBUTTON1 2007
#define huBUTTON2 2008


#define hsSIFRA 3001
#define hsUSLUGA 3002
#define hsID1 3003
#define hsID1_MJERA 3004
#define hsID1_CIJENA 3005
#define hsPDV1 3006
#define hsID2 3007
#define hsID2_MJERA 3008
#define hsID2_CIJENA 3009
#define hsPDV2 3010
#define hsSKLADISTE1 3011
#define hsBUTTON1 3012
#define hsBUTTON2 3013
#define IDB_RADIO1 3014
#define IDB_RADIO2 3015

#define htBUTTON1 4001
#define htBUTTON2 4002
#define htSIFRARNIK 4003

#define HSKLADISTE 5001

#define HBLAGAJNA 6001
#define hbBUTTON1 6002
#define hbBUTTON2 6003
#define hbBUTTON3 6004
#define hbUKUPNO 6005
#define hbDATUM 6006
#define hbVRIJEME 6007
#define hbRACUN 6008
#define hbOPERATOR 6009

#define uaBUTTON1 7001
#define uaBUTTON2 7002
#define uaID 7003
#define uaKOLICINA 7004

#define baBUTTON1 8001
#define baBUTTON2 8002
#define baID 8003

#define bsBUTTON1 9001
#define bsBUTTON2 9002
#define bsID 9003

#define dBUTTON1 10001
#define dBUTTON2 10002
#define dID 10003
#define dIME 10004
#define dPREZIME 10005
#define dOIB 10006
#define dZAPORKA 10007

#define pBUTTON1 11001
#define pBUTTON2 11002
#define pPODUZECE 11003
#define pIME 11004
#define pPREZIME 11005
#define pADRESA 11006
#define pMJESTO 11007
#define pOIB 11008
#define pTELEFON 11009


HWND pButton1,pButton2,pPoduzece,pIme,pPrezime,pAdresa,pMjesto,pOib,pTelefon;

HWND dButton1,dButton2,dId,dIme,dPrezime,dOib,dZaporka;

HWND baButton1,baButton2,baId;

HWND bsButton1,bsButton2,bsId;

HWND uaButton1,uaButton2,uaId,uaKolicina;

HWND hblagajna,hbButton1,hbButton2,hbButton3,hbUkupno,hbDatum,hbVrijeme,hbRacun,hbOperator;

HWND hId,hArtikl,hKolicina,hMjera,hPdv,hCijena,huButton1,huButton2;
HWND font1;

HWND hsSifra,hsUsluga,hsId1,hsId1_mjera,hsId1_cijena,hsPdv1,hsId2,hsId2_mjera,hsId2_cijena,hsPdv2,hskladiste1,hWndGroupbox,hWndButton1,hWndButton2;

HWND hsButton1,hsButton2;
HWND htButton1,htButton2,htSifrarnik;

LVCOLUMN LvCol1; // Make Coluom struct for ListView
LVITEM LvItem1;

LRESULT CALLBACK WndProc(HWND, UINT , WPARAM , LPARAM );
LRESULT CALLBACK drugiprozor(HWND, UINT , WPARAM , LPARAM );
LRESULT CALLBACK treciprozor(HWND, UINT , WPARAM , LPARAM );
LRESULT CALLBACK cetvrtiprozor(HWND, UINT , WPARAM , LPARAM );
LRESULT CALLBACK petiprozor(HWND, UINT , WPARAM , LPARAM );
LRESULT CALLBACK sestiprozor(HWND, UINT , WPARAM , LPARAM );
LRESULT CALLBACK sedmiprozor(HWND, UINT , WPARAM , LPARAM );
LRESULT CALLBACK osmiprozor(HWND, UINT , WPARAM , LPARAM );
LRESULT CALLBACK devetiprozor(HWND, UINT , WPARAM , LPARAM );
LRESULT CALLBACK desetiprozor(HWND, UINT , WPARAM , LPARAM );
LRESULT CALLBACK jedanaestiprozor(HWND, UINT , WPARAM , LPARAM );

HWND hButton1,hButton2,hButton3,hButton4,hButton5,hButton6,hButton7,hButton8,hButton9,hButton10,hStatic1;
HWND hskladiste;
HWND drugi,treci,cetvrti,peti,sesti,sedmi,osmi,deveti,deseti,jedanaesti;

HINSTANCE hins;
	

int p=0,s=1,i=0, iItem;;
double cijena=0,suma=0;
string str="";
string sql=""; 

sqlite3 *db;
char *err_msg = 0;
sqlite3_stmt *res;
int step,rc = sqlite3_open("baza.db", &db);




template <typename T>
bool GetDlgItemNumber(HWND aHwndDlg, int aDlgItemId, T &aVal)
{
   char Buffer[256];
   if(!GetDlgItemText(aHwndDlg, aDlgItemId, Buffer, sizeof(Buffer)))
      return false;
   std::stringstream ss(Buffer);
   return ss >> aVal;
}

template<typename T>
string to_string(T val)
{
    std::stringstream ss("");
    ss << val;
    return ss.str();
}

template<typename T>
bool GetDlgItemString(HWND aHwndDlg, int aDlgItemId, T &aVal)
{
char* buf;
int len = GetWindowTextLength(GetDlgItem(aHwndDlg,aDlgItemId));
buf = new char[len+1];
GetWindowText(GetDlgItem(aHwndDlg,aDlgItemId), buf, len+1 );
string stri;
stringstream si;
si<<buf;
aVal=si.str();
delete buf;
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
    wc.style         = CS_HREDRAW | CS_VREDRAW;
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

wc.lpszClassName = "skladiste";
	 wc.lpfnWndProc = (WNDPROC)cetvrtiprozor;
     RegisterClassEx(&wc);

wc.lpszClassName = "unos_sifara";
	 wc.lpfnWndProc = (WNDPROC)petiprozor;
     RegisterClassEx(&wc);

wc.lpszClassName = "sifrarnik";
	 wc.lpfnWndProc = (WNDPROC)sestiprozor;
     RegisterClassEx(&wc);

wc.lpszClassName = "unos_artikla";
	 wc.lpfnWndProc = (WNDPROC)sedmiprozor;
     RegisterClassEx(&wc);

wc.lpszClassName = "brisanje_artikla";
	 wc.lpfnWndProc = (WNDPROC)osmiprozor;
     RegisterClassEx(&wc);

wc.lpszClassName = "brisanje_usluge";
	 wc.lpfnWndProc = (WNDPROC)devetiprozor;
     RegisterClassEx(&wc);

wc.lpszClassName = "djelatnici";
	 wc.lpfnWndProc = (WNDPROC)desetiprozor;
     RegisterClassEx(&wc);

wc.lpszClassName = "postavke";
	 wc.lpfnWndProc = (WNDPROC)jedanaestiprozor;
     RegisterClassEx(&wc);


    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "PC KASA",
        WS_OVERLAPPED | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT,
	 300,700,NULL, NULL, hInstance, NULL);


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
HFONT MyFontt;
    switch(msg)
    {
case WM_CREATE:
         {



MyFontt=CreateFont(24,0,0,0,0,0,0,0,0,0,0,0,0,LPSTR("Arial"));

hStatic1 = CreateWindowEx(0,
                                   "static",
                                   "Static",
                                   WS_CHILD | WS_VISIBLE | ES_CENTER,
                                   60,30,180,30,
                                   hwnd,
                                   (HMENU)hSTATIC1,
                                    hins,
                                   NULL);
SendMessage(hStatic1, WM_SETFONT, (WPARAM)(MyFontt), true);

	hButton1 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "BLAGAJNA",
                                   WS_CHILD | WS_VISIBLE,
                                   60,30,180,30,
                                   hwnd,
                                   (HMENU)hBUTTON1,
                                    hins,
                                   NULL);
                                   
             hButton2 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "UNOS",
                                   WS_CHILD | WS_VISIBLE,
                                   60,70,180,30,
                                   hwnd,
                                   (HMENU)hBUTTON2,
                                    hins,
                                   NULL);

hButton3 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "SKLADISTE",
                                   WS_CHILD | WS_VISIBLE,
                                   60,110,180,30,
                                   hwnd,
                                   (HMENU)hBUTTON3,
                                    hins,
                                   NULL);
hButton4 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "UNOS SIFARA",
                                   WS_CHILD | WS_VISIBLE,
                                   60,150,180,30,
                                   hwnd,
                                   (HMENU)hBUTTON4,
                                    hins,
                                   NULL);

hButton5 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "SIFRARNIK",
                                   WS_CHILD | WS_VISIBLE,
                                   60,190,160,30,
                                   hwnd,
                                   (HMENU)hBUTTON5,
                                    hins,
                                   NULL);

hButton6 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "UNOS ARTIKLA",
                                   WS_CHILD | WS_VISIBLE,
                                   60,190,160,30,
                                   hwnd,
                                   (HMENU)hBUTTON6,
                                    hins,
                                   NULL);

hButton7 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "BRISANJE ARTIKLA",
                                   WS_CHILD | WS_VISIBLE,
                                   60,190,160,30,
                                   hwnd,
                                   (HMENU)hBUTTON7,
                                    hins,
                                   NULL);

hButton8 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "BRISANJE SIFRE",
                                   WS_CHILD | WS_VISIBLE,
                                   60,190,160,30,
                                   hwnd,
                                   (HMENU)hBUTTON8,
                                    hins,
                                   NULL);

hButton9 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "DJELATNICI",
                                   WS_CHILD | WS_VISIBLE,
                                   60,190,160,30,
                                   hwnd,
                                   (HMENU)hBUTTON9,
                                    hins,
                                   NULL);


hButton10 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "POSTAVKE",
                                   WS_CHILD | WS_VISIBLE,
                                   60,190,160,30,
                                   hwnd,
                                   (HMENU)hBUTTON10,
                                    hins,
                                   NULL);

sqlite3 *db;
sqlite3_stmt *res;
int rc;

rc=sqlite3_open("baza.db",&db);

stringstream sql;

sql<<"select poduzece from poduzece;";
rc=sqlite3_prepare(db,sql.str().c_str(),-1,&res,NULL);
rc=sqlite3_step(res);
string st=LPSTR(sqlite3_column_text(res, 0));
SetDlgItemText(hwnd, hSTATIC1,st.c_str());


sqlite3_finalize(res);
sqlite3_close(db);
}
break;
case WM_COMMAND:
         {
             if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hBUTTON1)   
                 {        
                drugi = CreateWindowEx(0,"blagajna","BLAGAJNA",WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,800,700,0,0,hins,0); 
                ShowWindow(drugi,SW_SHOW);
		  UpdateWindow(drugi);
                 EnableWindow (hButton1, FALSE);
             }
if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hBUTTON2)   
                 {        
             treci = CreateWindowEx(0,"unos","UNOS",WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,300,500,0,0,hins,0);    
                ShowWindow(treci,SW_SHOW);
		UpdateWindow(treci);  
               EnableWindow (hButton2, FALSE);  
             }
  if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hBUTTON3)   
                 {        
              cetvrti = CreateWindowEx(0,"skladiste","SKLADISTE",WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,800,600,hwnd,0,hins,0);   
                ShowWindow(cetvrti,SW_SHOW);
		UpdateWindow(cetvrti);  
                 EnableWindow (hButton3, FALSE);
             } 
 if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hBUTTON4)   
                 {        
               peti = CreateWindowEx(0,"unos_sifara","UNOS SIFARA",WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,800,550,hwnd,0,hins,0);  
                ShowWindow(peti,SW_SHOW);  
                 UpdateWindow(peti);
EnableWindow (hButton4, FALSE);
             } 

if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hBUTTON5)   
                 {        
    sesti = CreateWindowEx(0,"sifrarnik","SIFRARNIK",WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,900,550,hwnd,0,hins,0);             
                ShowWindow(sesti,SW_SHOW); 
		UpdateWindow(sesti); 
              EnableWindow (hButton5, FALSE);   
             } 
if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hBUTTON6)   
                 {        
          sedmi = CreateWindowEx(0,"unos_artikla","UNOS ARTIKLA",WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,300,250,hwnd,0,hins,0);       
                ShowWindow(sedmi,SW_SHOW);
		UpdateWindow(sedmi); 
                 EnableWindow (hButton6, FALSE);
             }  
if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hBUTTON7)   
                 {        
        osmi = CreateWindowEx(0,"brisanje_artikla","BRISANJE_ARTIKLA",WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,300,250,hwnd,0,hins,0);         
                ShowWindow(osmi,SW_SHOW);  
                 UpdateWindow(osmi);
EnableWindow (hButton7, FALSE);
             }

if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hBUTTON8)   
                 {        
   deveti = CreateWindowEx(0,"brisanje_usluge","BRISANJE_USLUGE",WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,300,250,hwnd,0,hins,0);              
                ShowWindow(deveti,SW_SHOW);  
                UpdateWindow(deveti); 
EnableWindow (hButton8, FALSE);
             } 
if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hBUTTON9)   
                 {        
   deseti = CreateWindowEx(0,"djelatnici","DJELATNICI",WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,300,450,hwnd,0,hins,0);              
                ShowWindow(deseti,SW_SHOW);  
                UpdateWindow(deseti); 
EnableWindow (hButton9, FALSE);
             } 
if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hBUTTON10)   
                 {        
   jedanaesti= CreateWindowEx(0,"postavke","POSTAVKE",WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,300,450,hwnd,0,hins,0);              
                ShowWindow(jedanaesti,SW_SHOW);  
                UpdateWindow(jedanaesti); 
EnableWindow (hButton10, FALSE);
             } 
             
         }
break;
case WM_SIZE:
         {
        
	MoveWindow(hStatic1, LOWORD(lParam) / 2 - 80, 20, 160, 30, TRUE);
        MoveWindow(hButton1, LOWORD(lParam) / 2 - 80, 70, 160, 30, TRUE);
        MoveWindow(hButton2, LOWORD(lParam) / 2 - 80, 120, 160, 30, TRUE);     
        MoveWindow(hButton3, LOWORD(lParam) / 2 - 80, 170, 160, 30, TRUE);
	MoveWindow(hButton4, LOWORD(lParam) / 2 - 80, 220, 160, 30, TRUE);
	MoveWindow(hButton5, LOWORD(lParam) / 2 - 80, 270, 160, 30, TRUE); 
	MoveWindow(hButton6, LOWORD(lParam) / 2 - 80, 320, 160, 30, TRUE);
	MoveWindow(hButton7, LOWORD(lParam) / 2 - 80, 370, 160, 30, TRUE);
	MoveWindow(hButton8, LOWORD(lParam) / 2 - 80, 420, 160, 30, TRUE); 
	MoveWindow(hButton9, LOWORD(lParam) / 2 - 80, 470, 160, 30, TRUE);
	MoveWindow(hButton10, LOWORD(lParam) / 2 - 80, 520, 160, 30, TRUE);
        
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
char Temp11[7][200];
char Temp[255]={0};
char Temp1[255]={0};
char Text[255]={0};
char znak[200]="";
char znak1[200]="";
char znak2[200]="";
HFONT MyFontx,MyFontx1;
char datum[64];
char vrijeme[64];
time_t t = time(NULL);
strftime(datum, 64, "%d.%m.%Y", localtime(&t));
strftime(vrijeme, 64, "%H.%M.%S", localtime(&t));
string** ary;
int id1;
int id2;
double mjera1;
double mjera2;
string st1,st2,stx;
 
    switch(msg)
    {
case WM_NOTIFY:
{
if(((LPNMHDR)lParam)->code ==NM_SETFOCUS && LOWORD(wParam) ==HBLAGAJNA)   
                 { 
SetFocus(hwnd);
}
}
break;
 

	case WM_CREATE:
	{




CreateWindowEx(0,"Static","Datum",WS_CHILD | WS_VISIBLE | ES_CENTER,20,10,80,25,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Vrijeme",WS_CHILD | WS_VISIBLE | ES_CENTER,20,50,80,25,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Racun",WS_CHILD | WS_VISIBLE | ES_CENTER,20,90,80,25,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Operator",WS_CHILD | WS_VISIBLE | ES_CENTER,20,130,80,25,hwnd,0,hins,NULL);


hbDatum=CreateWindowEx(0,"Static","Datum",WS_CHILD | WS_VISIBLE | ES_CENTER,120,10,120,25,hwnd,(HMENU)hbDATUM,hins,NULL);
hbVrijeme=CreateWindowEx(0,"Static","Vrijeme",WS_CHILD | WS_VISIBLE | ES_CENTER,120,50,120,25,hwnd,(HMENU)hbVRIJEME,hins,NULL);
hbRacun=CreateWindowEx(0,"Static","Racun",WS_CHILD | WS_VISIBLE | ES_CENTER,120,90,120,25,hwnd,(HMENU)hbRACUN,hins,NULL);
hbOperator=CreateWindowEx(0,"Static","Operator",WS_CHILD | WS_VISIBLE | ES_CENTER,120,130,120,25,hwnd,(HMENU)hbOPERATOR,hins,NULL);

hbUkupno=CreateWindowEx(0,"EDIT","Id",WS_CHILD | WS_VISIBLE,140,10,130,30,hwnd,(HMENU)hbUKUPNO,hins,NULL);

MyFontx=CreateFont(24,0,0,0,0,0,0,0,0,0,0,0,0,LPSTR("Arial"));
SendMessage(hbUkupno, WM_SETFONT, (WPARAM)(MyFontx), true);


hbButton1 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "OBRISI",
                                   WS_CHILD | WS_VISIBLE,
                                   60,30,180,30,
                                   hwnd,
                                   (HMENU)hbBUTTON1,
                                    hins,
                                   NULL);
                                   
             hbButton2 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "Tipka1",
                                   WS_CHILD | WS_VISIBLE,
                                   60,70,180,30,
                                   hwnd,
                                   (HMENU)hbBUTTON2,
                                    hins,
                                   NULL);

hbButton3 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "Tipka3",
                                   WS_CHILD | WS_VISIBLE,
                                   60,70,180,30,
                                   hwnd,
                                   (HMENU)hbBUTTON3,
                                    hins,
                                   NULL);
	InitCommonControls();
	hblagajna= CreateWindowEx(0,
				WC_LISTVIEW, 
                                     0,
                                     WS_VISIBLE|WS_BORDER|WS_CHILD | LVS_REPORT | LVS_EDITLABELS,
                                     10, 10, 500, 200,
                                     hwnd,
                                     (HMENU)HBLAGAJNA,
                                     hins,
                                     NULL);

MyFontx1=CreateFont(18,0,0,0,0,0,0,0,0,0,0,0,0,LPSTR("Arial"));
SendMessage(hblagajna, WM_SETFONT, (WPARAM)(MyFontx1), true);

LvCol1;
SendMessage(hblagajna, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES);
memset(&LvCol1,0,sizeof(LvCol1)); // Reset Coluom
LvCol1.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM; // Type of mask
LvCol1.cx=0x33;
LvCol1.pszText=LPSTR("Id");                     // First Header
SendMessage(hblagajna,LVM_INSERTCOLUMN,0,(LPARAM)&LvCol1);
LvCol1.cx=0x75;
LvCol1.pszText=LPSTR("Artikl");                     // First Header
SendMessage(hblagajna,LVM_INSERTCOLUMN,1,(LPARAM)&LvCol1);
LvCol1.pszText=LPSTR("Kolicina");
SendMessage(hblagajna,LVM_INSERTCOLUMN,2,(LPARAM)&LvCol1); // ...
LvCol1.pszText=LPSTR("Mjera");                       //
SendMessage(hblagajna,LVM_INSERTCOLUMN,3,(LPARAM)&LvCol1); //
LvCol1.pszText=LPSTR("Cijena");                       //
SendMessage(hblagajna,LVM_INSERTCOLUMN,4,(LPARAM)&LvCol1); //
LvCol1.pszText=LPSTR("Pdv");                       //
SendMessage(hblagajna,LVM_INSERTCOLUMN,5,(LPARAM)&LvCol1); //
LvCol1.pszText=LPSTR("Iznos");                       //
SendMessage(hblagajna,LVM_INSERTCOLUMN,6,(LPARAM)&LvCol1);                       //

SetDlgItemText(hwnd, hbDATUM,LPSTR(datum));
SetDlgItemText(hwnd, hbVRIJEME,LPSTR(vrijeme));
stringstream sql;

sql<<"select ime,prezime from djelatnici;";
rc=sqlite3_prepare(db,sql.str().c_str(),-1,&res,NULL);
rc=sqlite3_step(res);
st1=LPSTR(sqlite3_column_text(res, 0));
st2=LPSTR(sqlite3_column_text(res, 1));
stx=st1+" "+st2;
SetDlgItemText(hwnd, hbOPERATOR,stx.c_str());       
	

        }
	break;


	case WM_CHAR: 
	{

 
if((wParam)=='\r' && p==0){
if(str=="" || str=="0") break;
cout<<"return"<<endl;



sql="select * from sifrarnik where id="+str+";";
cout<<sql<<endl;
rc = sqlite3_prepare(db, sql.c_str(), -1, &res, 0);
 
 if( rc!=SQLITE_OK ){
    
    sqlite3_close(db);
cout<<"izlaz"<<endl;
}

step = sqlite3_step(res);

cout<<"izlaz"<<step<<endl;
if(step==101){
    
sqlite3_close(db);    
cout<<"izlazx"<<endl;
str="";
break;
}

     
iItem=SendMessage(hblagajna,LVM_GETITEMCOUNT,0,0);
cout<<"   "<<iItem<<endl;
  
memset(&LvItem1,0,sizeof(LvItem1));
LvItem1.mask=LVIF_TEXT;
LvItem1.cchTextMax=256;
LvItem1.iItem=iItem;

LvItem1.iSubItem=0;
LvItem1.pszText=LPSTR(sqlite3_column_text(res, 0));

SendMessage(hblagajna,LVM_INSERTITEM,0,(LPARAM)&LvItem1);  

LvItem1.iSubItem=1;         // Put in first coluom
LvItem1.pszText=LPSTR(sqlite3_column_text(res, 1));   // Text to display (can be from a char variable) (Items)
SendMessage(hblagajna,LVM_SETITEM,0,(LPARAM)&LvItem1);

LvItem1.iSubItem=2;         // Put in first coluom
LvItem1.pszText=LPSTR(sqlite3_column_text(res, 3));   // Text to display (can be from a char variable) (Items)
SendMessage(hblagajna,LVM_SETITEM,0,(LPARAM)&LvItem1);


LvItem1.iSubItem=3;         // Put in first coluom
sprintf(znak2,"%05.2f",(sqlite3_column_double(res,3)+sqlite3_column_double(res,7)));
LvItem1.pszText=LPSTR(znak2);   // Text to display (can be from a char variable) (Items)
SendMessage(hblagajna,LVM_SETITEM,0,(LPARAM)&LvItem1);


cijena=sqlite3_column_double(res, 4)+sqlite3_column_double(res, 8);
sprintf(znak2,"%05.2f",cijena);
LvItem1.iSubItem=4;         // Put in first coluom
LvItem1.pszText=LPSTR(znak2);   // Text to display (can be from a char variable) (Items)
SendMessage(hblagajna,LVM_SETITEM,0,(LPARAM)&LvItem1);

LvItem1.iSubItem=5;         // Put in first coluom
LvItem1.pszText=LPSTR(sqlite3_column_text(res, 5));   // Text to display (can be from a char variable) (Items)
SendMessage(hblagajna,LVM_SETITEM,0,(LPARAM)&LvItem1);

LvItem1.iSubItem=6;         // Put in first coluom
LvItem1.pszText=LPSTR(sqlite3_column_text(res, 6));   // Text to display (can be from a char variable) (Items)
SendMessage(hblagajna,LVM_SETITEM,0,(LPARAM)&LvItem1);



cout<<"iItem "<<iItem<<endl;
LvItem1.iItem=iItem-1;
str="";
p=1;



}	

if((wParam)!='\r'){ 
p=0;
s=0;}	

if((wParam)=='\r' && p==1){ 

s=s+1;
LvItem1.iItem=iItem;
LvItem1.iSubItem=2;         // Put in first coluom
LvItem1.pszText=LPSTR(to_string(s).c_str());   // Text to display (can be from a char variable) (Items)
SendMessage(hblagajna,LVM_SETITEM,0,(LPARAM)&LvItem1);
LvItem1.iSubItem=6;         // Put in first coluom
sprintf(znak1,"%05.2f",s*cijena);
LvItem1.pszText=LPSTR(znak1);
suma+=cijena;
sprintf(znak,"%05.2f",suma);
SendMessage(hblagajna,LVM_SETITEM,0,(LPARAM)&LvItem1);
SetDlgItemText(hwnd, hbUKUPNO,LPSTR(znak));


}	
        if((wParam)==32){  
	


	
        cout<<"space"<<endl;
int iItem=SendMessage(hblagajna,LVM_GETITEMCOUNT,0,0);
cout<<"****"<<iItem<<endl;
char bufText1[200];
ary= new string*[iItem];
for(i=0;i<iItem;i++){
ary[i]= new string[7];
}



for(i=0;i<iItem;i++){
for(int j=0;j<=6;j++)
		{
LvItem1.iSubItem=j;
LvItem1.mask=LVIF_TEXT;
LvItem1.pszText=Text;
LvItem1.cchTextMax=256;
LvItem1.iItem=i;
SendMessage(hblagajna,LVM_GETITEMTEXT,i, (LPARAM)&LvItem1);	
strcpy(Temp11[j],Text);
ary[i][j] =to_string(Temp11[j]);
}




sql= "select id1,id2,mjera1,mjera2 from sifrarnik where id="+to_string(Temp11[0])+";";
cout<<sql<<endl;
rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
step = sqlite3_step(res);

id1=sqlite3_column_int(res,0);
id2=sqlite3_column_int(res,1);
mjera1=sqlite3_column_double(res,2);
mjera2=sqlite3_column_double(res,3);

cout<<"---"<<endl;
cout<<id1<<endl;
cout<<id2<<endl;
cout<<mjera1<<endl;
cout<<mjera2<<endl;
cout<<"---"<<endl;



double kolicinaxx;

double kolicinaa,kolicinaa1;


if(id1!=0){
sql="select kolicina from skladiste where id="+to_string(id1)+";";
cout<<sql<<endl;
rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
step = sqlite3_step(res);
kolicinaxx=atof(Temp11[2])*mjera1;

kolicinaa1=sqlite3_column_double(res,0);
kolicinaa=kolicinaa1-kolicinaxx;
cout<<"---"<<endl;
cout<<kolicinaa<<endl;
cout<<kolicinaa1<<endl;
cout<<kolicinaxx<<endl;
cout<<"---"<<endl;




sql= "update skladiste set kolicina="+to_string(kolicinaa)+" where id="+to_string(id1)+";";
cout<<sql<<endl;
rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);

step = sqlite3_step(res);

 if (rc != SQLITE_DONE) {
        
        printf("execution failed: %s\n", sqlite3_errmsg(db));
    }

}

if(id2!=0){
sql="select kolicina from skladiste where id="+to_string(id2)+";";
cout<<sql<<endl;
rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
step = sqlite3_step(res);
kolicinaxx=atof(Temp11[2])*mjera2;

kolicinaa1=sqlite3_column_double(res,0);
kolicinaa=kolicinaa1-kolicinaxx;
cout<<"---"<<endl;
cout<<kolicinaa<<endl;
cout<<kolicinaa1<<endl;
cout<<kolicinaxx<<endl;
cout<<"---"<<endl;

sql= "update skladiste set kolicina="+to_string(kolicinaa)+" where id="+to_string(id2)+";";
cout<<sql<<endl;
rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);

step = sqlite3_step(res);

 if (rc != SQLITE_DONE) {
        
        printf("execution failed: %s\n", sqlite3_errmsg(db));
    }

}   




}

cout<<"****************************"<<endl;
SetDlgItemText(hwnd, hbDATUM,LPSTR(datum));
SetDlgItemText(hwnd, hbVRIJEME,LPSTR(vrijeme));

string ope;        
GetDlgItemString(hwnd,hbOPERATOR,ope);

PRINTDLG pd;
HFONT DisplayFont;
memset( &pd, 0, sizeof( pd ) );
pd.lStructSize = sizeof( pd );
pd.Flags = PD_RETURNDEFAULT | PD_RETURNDC;
PrintDlg(&pd);
DOCINFO di;
HDC hPrinter = pd.hDC;
memset( &di, 0, sizeof( di ) );
di.cbSize = sizeof( di );
StartDoc( hPrinter, &di );
StartPage( hPrinter );

DisplayFont=CreateFont(30,0,0,0,0,0,0,0,0,0,0,0,0,LPSTR("Consolas"));
SelectObject (hPrinter, DisplayFont);
TextOut(hPrinter, 0, 0,"Kod tri praseta",strlen("Kod tri praseta"));;
DisplayFont=CreateFont(30,0,0,0,0,0,0,0,0,0,0,0,0,LPSTR("Consolas"));
SelectObject (hPrinter, DisplayFont);
TextOut(hPrinter, 0, 30,"Datum :",strlen("Datum :"));
TextOut(hPrinter,150, 30,to_string(datum).c_str(),strlen(to_string(datum).c_str()));
TextOut(hPrinter, 0, 60,"Vrijeme :",strlen("Vrijeme :"));
TextOut(hPrinter,150, 60,to_string(vrijeme).c_str(),strlen(to_string(vrijeme).c_str()));
TextOut(hPrinter,0, 90,"Operator",strlen("Operator"));
TextOut(hPrinter,150, 90,ope.c_str(),strlen(ope.c_str()));
TextOut(hPrinter,0, 120,"Racun",strlen("Racun"));
TextOut(hPrinter,150, 120,"Racun",strlen("Racun"));
TextOut(hPrinter,0, 150,"Usluga",strlen("Usluga"));
TextOut(hPrinter,250, 150,"Kolicina",strlen("Kolicina"));
TextOut(hPrinter,0, 180,"Mjera",strlen("Mjera"));
TextOut(hPrinter,90, 180,"Cijena",strlen("Cijena"));
TextOut(hPrinter,200, 180,"Pdv",strlen("Pdv"));
TextOut(hPrinter,290, 180,"Iznos",strlen("Iznos"));
TextOut(hPrinter, 0, 210,"----------------------------",strlen("----------------------------"));;
int x=240;
for(i=0;i<iItem;i++){
for(int j=0;j<=6;j++){
cout<<ary[i][j]<<" ";
TextOut(hPrinter, 0, x, ary[i][1].c_str(),strlen(ary[i][1].c_str()));;
TextOut(hPrinter, 300, x, ary[i][2].c_str(),strlen(ary[i][2].c_str()));
TextOut(hPrinter, 0, x+30, ary[i][3].c_str(),strlen(ary[i][3].c_str()));
TextOut(hPrinter, 100, x+30, ary[i][4].c_str(),strlen(ary[i][4].c_str()));
TextOut(hPrinter, 200, x+30, ary[i][5].c_str(),strlen(ary[i][5].c_str()));
TextOut(hPrinter, 300, x+30, ary[i][6].c_str(),strlen(ary[i][6].c_str()));		
}
cout<<endl;
x+=60;

}
TextOut(hPrinter, 0, x+30,"==============================",strlen("=============================="));;

DisplayFont=CreateFont(35,0,0,0,0,0,0,0,0,0,0,0,0,LPSTR("Consolas"));
SelectObject (hPrinter, DisplayFont);
TextOut(hPrinter,130,x+70,"UKUPNO",strlen("UKUPNO"));
char znak[256];
sprintf(znak,"%05.2f",suma);
TextOut(hPrinter,270,x+70,znak,strlen(znak));

EndPage( hPrinter );
EndDoc( hPrinter );
DeleteDC( hPrinter );

SetDlgItemText(hwnd, hbUKUPNO,LPSTR("00.00"));
suma=0;

for(int i = 0; i < iItem; i++)
    delete [] ary[i];
  delete [] ary;

SendMessage(hblagajna,LVM_DELETEALLITEMS,0,0);
//
//sqlite3_finalize(res);
//sqlite3_close(db);
 }       
       
	if((wParam)==48){          
        cout<<"0"<<endl;
        str+="0";
	cout<<str.c_str()<<endl;
        }
	
	if((wParam)==49){          
        cout<<"1"<<endl;
        str+="1";
	cout<<str.c_str()<<endl;
	}
       
	if((wParam)==50){          
        cout<<"2"<<endl;
	str+="2";
	cout<<str.c_str()<<endl;
        }

	if((wParam)==51){          
        cout<<"3"<<endl;
	str+="3";
	cout<<str.c_str()<<endl;
        }
 
	if((wParam)==52){          
        cout<<"4"<<endl;
	str+="4";
	cout<<str.c_str()<<endl;
        }

	if((wParam)==53){          
        cout<<"5"<<endl;
	str+="5";
	cout<<str.c_str()<<endl;
        }

  	if((wParam)==54){          
        cout<<"6"<<endl;
	str+="6";
	cout<<str.c_str()<<endl;
        }   

	if((wParam)==55){          
        cout<<"7"<<endl;
	str+="7";
	cout<<str.c_str()<<endl;
        }

	if((wParam)==56){          
        cout<<"8"<<endl;
	str+="8";
	cout<<str.c_str()<<endl;
        }

	if((wParam)==57){          
        cout<<"9"<<endl;
	str+="9";
	cout<<str.c_str()<<endl;
        }



 break;
  
        
	           
	
	}
	case WM_SIZE:
         {
        
       
        MoveWindow(hbButton1,  40, HIWORD(lParam)-50, 80, 30, TRUE);
        MoveWindow(hbButton2, LOWORD(lParam)-120, HIWORD(lParam)-50, 80, 30, TRUE);
	MoveWindow(hbButton3, LOWORD(lParam)-220, HIWORD(lParam)-50, 80, 30, TRUE);     
        MoveWindow(hbUkupno, LOWORD(lParam)-120, 50, 80, 30, TRUE);
MoveWindow(hblagajna, 20, 180, LOWORD(lParam)-40, HIWORD(lParam)-240, TRUE);          
             }
	break;
         case WM_COMMAND:
         {

		if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hbBUTTON1)   
                 {

SetDlgItemText(hwnd, hbUKUPNO,LPSTR("99")); 
cout<<"igorxxxx"<<endl;
int iItem=SendMessage(hblagajna,LVM_GETITEMCOUNT,0,0);


LvItem1.iSubItem=6;
LvItem1.mask=LVIF_TEXT;
LvItem1.pszText=Text;
LvItem1.cchTextMax=256;
LvItem1.iItem=iItem-1;
SendMessage(hblagajna,LVM_GETITEMTEXT,iItem-1, (LPARAM)&LvItem1);
	
cout<<"----"<<endl;
cout<<Text<<endl;
cout<<cijena<<endl;
suma=suma-atof(Text);
cout<<suma<<endl;
cout<<"----"<<endl;
char xx[50];
sprintf(xx,"%5.2f",suma);
SendMessage(hblagajna,LVM_DELETEITEM,iItem-1,0);
SetDlgItemText(hwnd, hbUKUPNO,LPSTR(xx));


} 
if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hbBUTTON2)   
                 { 
cout<<"igortttt"<<endl;

SendMessage(hblagajna,LVM_DELETEALLITEMS,0,0);

suma=0.0f;
SetDlgItemText(hwnd, hbUKUPNO,LPSTR("00.00"));
}
 if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hbBUTTON3)   
                 {        
                 
                //SetFocus(hwnd);
                 
             } 


} break;
        case WM_CLOSE:
cout<<"close window and database"<<endl;

EnableWindow (hButton1, TRUE);
            DestroyWindow(drugi);

        break;
        case WM_DESTROY:
            {
//sqlite3_finalize(res);
//sqlite3_close(db);

          cout<<"****close window and database"<<endl;     
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
		GetDlgItemString(hwnd,eARTIKL,Artikl);
		GetDlgItemNumber(hwnd,ePDV,Pdv);
		GetDlgItemNumber(hwnd,eKOLICINA,Kolicina);
		GetDlgItemNumber(hwnd,eMJERA,Mjera);
		GetDlgItemNumber(hwnd,eCIJENA,Cijena);

                 
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
  EnableWindow (hButton2,TRUE);                
             }
		if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==huBUTTON2)   
                 {        
                 
                 DestroyWindow(treci); 
                 
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
		EnableWindow (hButton2, TRUE);
		
            DestroyWindow(treci); 

      break; 
        case WM_DESTROY:
            {
              EnableWindow (hButton2, TRUE); 
            } break;
      default:  
     return DefWindowProc(hwnd,msg,wParam,lParam);
}

}

LRESULT CALLBACK cetvrtiprozor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
char Temp[255]={0};
HFONT MyFontx1;
    switch(msg)
    {

    case WM_CREATE:
{
InitCommonControls();
hskladiste= CreateWindowEx(0,
				WC_LISTVIEW, 
                                     0,
                                     WS_VISIBLE|WS_BORDER|WS_CHILD | LVS_REPORT | LVS_EDITLABELS,
                                     10, 10, 700, 300,
                                     hwnd,
                                     (HMENU)HSKLADISTE,
                                     hins,
                                     NULL);



LVCOLUMN LvCol;
SendMessage(hskladiste, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES);

MyFontx1=CreateFont(16,0,0,0,0,0,0,0,0,0,0,0,0,LPSTR("Arial"));
SendMessage(hskladiste, WM_SETFONT, (WPARAM)(MyFontx1), true);
memset(&LvCol,0,sizeof(LvCol)); // Reset Coluom
LvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
LvCol.cx=0x52;                               // width between each coloum
LvCol.pszText=LPSTR("Id");                     // First Header
SendMessage(hskladiste,LVM_INSERTCOLUMN,0,(LPARAM)&LvCol);
LvCol.pszText=LPSTR("Artikl");
LvCol.cx=0x82;                          // Next coloum
SendMessage(hskladiste,LVM_INSERTCOLUMN,1,(LPARAM)&LvCol);
LvCol.pszText=LPSTR("Pdv");                       //
SendMessage(hskladiste,LVM_INSERTCOLUMN,2,(LPARAM)&LvCol);
LvCol.pszText=LPSTR("Kolicina");                       //
SendMessage(hskladiste,LVM_INSERTCOLUMN,3,(LPARAM)&LvCol);
LvCol.pszText=LPSTR("Mjera");                       //
SendMessage(hskladiste,LVM_INSERTCOLUMN,4,(LPARAM)&LvCol);
LvCol.pszText=LPSTR("Cijena");                       //
SendMessage(hskladiste,LVM_INSERTCOLUMN,5,(LPARAM)&LvCol);

sqlite3 *db;
char *err_msg = 0;
sqlite3_stmt *res;				
				
int rc = sqlite3_open("baza.db", &db);

const char *sql = "select * from skladiste;";

rc = sqlite3_prepare(db, sql, -1, &res, 0);
int step;
LV_ITEM lvi; 
memset(&lvi,0,sizeof(lvi)); // Reset Item Struct

int u=0;

while(true){
step = sqlite3_step(res);
if (step == SQLITE_DONE) { break;}				
lvi.mask=LVIF_TEXT;   // Text Style
lvi.cchTextMax = 256; // Max size of test
                
lvi.iItem=u;          // choose item  
lvi.iSubItem=0;       // Put in first coluom
lvi.pszText=LPSTR(sqlite3_column_text(res, 0)); // Text to display (can be from a char variable) (Items)
                
SendMessage(hskladiste,LVM_INSERTITEM,0,(LPARAM)&lvi); // Send to the Listview


lvi.iSubItem=1;
sprintf(Temp,"%s",sqlite3_column_text(res, 1));
lvi.pszText=LPSTR(Temp);
SendMessage(hskladiste,LVM_SETITEM,1,(LPARAM)&lvi); // Enter text to SubItems

lvi.iSubItem=2;
sprintf(Temp,"%s",sqlite3_column_text(res, 2));
lvi.pszText=LPSTR(Temp);
SendMessage(hskladiste,LVM_SETITEM,2,(LPARAM)&lvi); // Enter text to SubItems

lvi.iSubItem=3;
sprintf(Temp,"%5.2f",sqlite3_column_double(res, 3));
lvi.pszText=LPSTR(Temp);
SendMessage(hskladiste,LVM_SETITEM,3,(LPARAM)&lvi); // Enter text to SubItems

lvi.iSubItem=4;
sprintf(Temp,"%5.2f",sqlite3_column_double(res, 4));
lvi.pszText=LPSTR(Temp);
SendMessage(hskladiste,LVM_SETITEM,4,(LPARAM)&lvi); // Enter text to SubItems

lvi.iSubItem=5;
sprintf(Temp,"%5.2f",sqlite3_column_double(res, 5));
lvi.pszText=LPSTR(Temp);
SendMessage(hskladiste,LVM_SETITEM,5,(LPARAM)&lvi); // Enter text to SubItems


u++;
}





sqlite3_finalize(res);
sqlite3_close(db);
}
break;
case WM_SIZE:
         {
        
        MoveWindow(hskladiste,  20, 30, LOWORD(lParam)-40, HIWORD(lParam)-60, TRUE);
          
                  
             }
	break;
        case WM_CLOSE:
EnableWindow (hButton3, TRUE);
             DestroyWindow(cetvrti); 

        break;
        case WM_DESTROY:
            {
               
            } break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
     
}


LRESULT CALLBACK petiprozor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
char Temp[255]={0};
char Temp1[255]={0};
char Text[255]={0};
char *bufText1 = new char[256];
char *bufText2 = new char[256]; 
LV_ITEM lvi; 

   switch(msg)
    {
case WM_NOTIFY:
{
if(((LPNMHDR)lParam)->code == NM_DBLCLK && LOWORD(wParam) ==hsSKLADISTE1)   
                 {        
 int iSlected=0;
				  int j=0;

				  iSlected=SendMessage(hskladiste1,LVM_GETNEXTITEM,-1,LVNI_FOCUSED);
				  
				  if(iSlected==-1)
				  {
                    MessageBox(hwnd,"No Items in ListView","Error",MB_OK|MB_ICONINFORMATION);
					break;
				  }

				  memset(&lvi,0,sizeof(lvi));
                  		  
				  
				  
                  
				  
		
for(j=0;j<=3;j++)
		{
lvi.iSubItem=j;
lvi.mask=LVIF_TEXT;
lvi.pszText=Text;
lvi.cchTextMax=256;
lvi.iItem=iSlected;
SendMessage(hskladiste1,LVM_GETITEMTEXT, iSlected, (LPARAM)&lvi);
sprintf(Temp1," %s",Text);
lstrcat(Temp,Temp1);

ListView_GetItemText(hskladiste1, iSlected, 0, (LPTSTR)bufText1, 256);	
ListView_GetItemText(hskladiste1, iSlected, 2, (LPTSTR)bufText2, 256);		
}
MessageBox(hwnd,Temp,"test",MB_OK);

if(IsDlgButtonChecked(hwnd, IDB_RADIO1)){
   SetDlgItemText(hwnd, hsID1, bufText1);
SetDlgItemText(hwnd, hsPDV1, bufText2);
}
    
if(IsDlgButtonChecked(hwnd, IDB_RADIO2)){
   SetDlgItemText(hwnd, hsID2, bufText1);
SetDlgItemText(hwnd, hsPDV2, bufText2);}
}

}
break;


	case WM_CREATE:
{
hWndGroupbox = CreateWindowEx(0,"BUTTON", "Id skladiste", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 300, 5, 120, 120, hwnd, NULL, hins,  NULL); 



hWndButton1 = CreateWindowEx(0, "BUTTON", "Id1", WS_VISIBLE | WS_CHILD |WS_GROUP | BS_RADIOBUTTON, 310, 50, 80, 20, hwnd, (HMENU)IDB_RADIO1, hins, NULL); 
hWndButton2 = CreateWindowEx(0, "BUTTON", "Id2", WS_VISIBLE | WS_CHILD | WS_GROUP | BS_RADIOBUTTON, 310, 90, 80, 20, hwnd, (HMENU)IDB_RADIO2, hins, NULL); 



CreateWindowEx(0,"Static","Sifra",WS_CHILD | WS_VISIBLE,20,10,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Usluga",WS_CHILD | WS_VISIBLE,20,50,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Id1",WS_CHILD | WS_VISIBLE,20,90,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Id1 mjera",WS_CHILD | WS_VISIBLE,20,130,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Id1 cijena",WS_CHILD | WS_VISIBLE,20,170,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Pdv1",WS_CHILD | WS_VISIBLE,20,210,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Id2",WS_CHILD | WS_VISIBLE,20,250,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Id2 mjera",WS_CHILD | WS_VISIBLE,20,290,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Id2 cijena",WS_CHILD | WS_VISIBLE,20,330,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Pdv2",WS_CHILD | WS_VISIBLE,20,370,80,30,hwnd,0,hins,NULL);

hsSifra=CreateWindowEx(0,"Edit","",WS_CHILD | WS_VISIBLE| WS_BORDER,120,10,120,30,hwnd,(HMENU)hsSIFRA,hins,NULL);
hsUsluga=CreateWindowEx(0,"Edit","",WS_CHILD | WS_VISIBLE| WS_BORDER,120,50,120,30,hwnd,(HMENU)hsUSLUGA,hins,NULL);
hsId1=CreateWindowEx(0,"Edit","",WS_CHILD | WS_VISIBLE| WS_BORDER,120,90,120,30,hwnd,(HMENU)hsID1,hins,NULL);
hsId1_mjera=CreateWindowEx(0,"Edit","",WS_CHILD | WS_VISIBLE| WS_BORDER,120,130,120,30,hwnd,(HMENU)hsID1_MJERA,hins,NULL);
hsId1_cijena=CreateWindowEx(0,"Edit","",WS_CHILD | WS_VISIBLE| WS_BORDER,120,170,120,30,hwnd,(HMENU)hsID1_CIJENA,hins,NULL);
hsPdv1=CreateWindowEx(0,"Edit","",WS_CHILD | WS_VISIBLE| WS_BORDER,120,210,120,30,hwnd,(HMENU)hsPDV1,hins,NULL);
hsId2=CreateWindowEx(0,"Edit","",WS_CHILD | WS_VISIBLE| WS_BORDER,120,250,120,30,hwnd,(HMENU)hsID2,hins,NULL);
hsId2_mjera=CreateWindowEx(0,"Edit","",WS_CHILD | WS_VISIBLE| WS_BORDER,120,290,120,30,hwnd,(HMENU)hsID2_MJERA,hins,NULL);
hsId2_cijena=CreateWindowEx(0,"Edit","",WS_CHILD | WS_VISIBLE| WS_BORDER,120,330,120,30,hwnd,(HMENU)hsID2_CIJENA,hins,NULL);
hsPdv2=CreateWindowEx(0,"Edit","",WS_CHILD | WS_VISIBLE| WS_BORDER,120,370,120,30,hwnd,(HMENU)hsPDV2,hins,NULL);


hsButton1 = CreateWindowEx(0,"button","Potvrdi",WS_CHILD | WS_VISIBLE,60,30,180,30,hwnd,(HMENU)hsBUTTON1,hins,NULL);
hsButton2 = CreateWindowEx(0,"button","Odustani",WS_CHILD | WS_VISIBLE,60,30,180,30,hwnd,(HMENU)hsBUTTON2,hins,NULL);




        

InitCommonControls();
hskladiste1= CreateWindowEx(0,WC_LISTVIEW, 0,WS_VISIBLE|WS_BORDER|WS_CHILD | LVS_REPORT | LVS_EDITLABELS,450, 10, 300, 300,hwnd,(HMENU)hsSKLADISTE1,hins,NULL);


LVCOLUMN LvCol;
SendMessage(hskladiste1, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES);
memset(&LvCol,0,sizeof(LvCol)); // Reset Coluom
LvCol.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM; // Type of mask
LvCol.cx=0x32;                               // width between each coloum
LvCol.pszText=LPSTR("Id");                     // First Header
SendMessage(hskladiste1,LVM_INSERTCOLUMN,0,(LPARAM)&LvCol);
LvCol.pszText=LPSTR("Artikl");
LvCol.cx=0x62;                          // Next coloum
SendMessage(hskladiste1,LVM_INSERTCOLUMN,1,(LPARAM)&LvCol); // ...
LvCol.pszText=LPSTR("Pdv");                       //
SendMessage(hskladiste1,LVM_INSERTCOLUMN,2,(LPARAM)&LvCol); //


sqlite3 *db;
char *err_msg = 0;
sqlite3_stmt *res;				
				
int rc = sqlite3_open("baza.db", &db);

const char *sql = "select * from skladiste;";

rc = sqlite3_prepare(db, sql, -1, &res, 0);
int step;
memset(&lvi,0,sizeof(lvi)); // Reset Item Struct
int u=0;

while(true){
step = sqlite3_step(res);
if (step == SQLITE_DONE) { break;}				
lvi.mask=LVIF_TEXT;   // Text Style
lvi.cchTextMax = 256; // Max size of test
                
lvi.iItem=u;          // choose item  
lvi.iSubItem=0;       // Put in first coluom
lvi.pszText=LPSTR(sqlite3_column_text(res, 0)); // Text to display (can be from a char variable) (Items)
                
SendMessage(hskladiste1,LVM_INSERTITEM,0,(LPARAM)&lvi); // Send to the Listview

for(int i=1;i<=2 ;i++) // Add SubItems in a loop
{
lvi.iSubItem=i;
sprintf(Temp,"%s",sqlite3_column_text(res, i));
lvi.pszText=LPSTR(Temp);
SendMessage(hskladiste1,LVM_SETITEM,0,(LPARAM)&lvi); // Enter text to SubItems

}
u++;
}










}
break; 
case WM_COMMAND:
         {

		if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hsBUTTON1)   
                 {        
                
                        
                int Sifra,Id1,Id2;
		string Usluga;
		double Id1_mjera,Id2_mjera,Id1_cijena,Id2_cijena,Pdv1,Pdv2; 
		


		GetDlgItemNumber(hwnd,hsSIFRA,Sifra);
		GetDlgItemString(hwnd,hsUSLUGA,Usluga);
		GetDlgItemNumber(hwnd,hsID1,Id1);
		GetDlgItemNumber(hwnd,hsID1_MJERA,Id1_mjera);
		GetDlgItemNumber(hwnd,hsID1_CIJENA,Id1_cijena);
		GetDlgItemNumber(hwnd,hsPDV1,Pdv1);
		GetDlgItemNumber(hwnd,hsID2,Id2);
		GetDlgItemNumber(hwnd,hsID2_MJERA,Id2_mjera);
		GetDlgItemNumber(hwnd,hsID2_CIJENA,Id2_cijena);
		GetDlgItemNumber(hwnd,hsPDV2,Pdv2);

                 DestroyWindow(peti); 
		
sqlite3 *db;
sqlite3_stmt *res;
int rc;

rc=sqlite3_open("baza.db",&db);
if(rc!=SQLITE_OK)
{
    cout<<sqlite3_errmsg(db);
}else {
string sql;
if(Id2==0){
sql="INSERT INTO sifrarnik (id,artikl,id1,mjera1,cijena1,pdv1,id2,mjera2,cijena2,pdv2)";
sql+=" VALUES ("+to_string(Sifra)+",\""+to_string(Usluga)+"\","+to_string(Id1)+","+to_string(Id1_mjera);
sql+=","+to_string(Id1_cijena)+","+to_string(Pdv1)+","+to_string(0)+","+to_string(0)+","+to_string(0)+","+to_string(0)+");";
}else
{
sql="INSERT INTO sifrarnik (id,artikl,id1,mjera1,cijena1,pdv1,id2,mjera2,cijena2,pdv2)";
sql+=" VALUES ("+to_string(Sifra)+",\""+to_string(Usluga)+"\","+to_string(Id1)+","+to_string(Id1_mjera);
sql+=","+to_string(Id1_cijena)+","+to_string(Pdv1)+","+to_string(Id2)+","+to_string(Id2_mjera)+","+to_string(Id2_cijena)+","+to_string(Pdv2)+");";
}

cout<<Usluga<<endl;

rc=sqlite3_prepare(db,sql.c_str(),-1,&res,NULL);
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

if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hsBUTTON2)   
                 {
EnableWindow (hButton4, TRUE); 
DestroyWindow(peti);
}

if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==IDB_RADIO1)   
                 { 
if (SendDlgItemMessage(hwnd, IDB_RADIO1, BM_GETCHECK, 0, 0) == 0) 

                            {

                                SendDlgItemMessage(hwnd, IDB_RADIO1, BM_SETCHECK, 1, 0);

                                SendDlgItemMessage(hwnd, IDB_RADIO2, BM_SETCHECK, 0, 0);

cout<<"IDB_RADIO1"<<endl;

                            }}
if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==IDB_RADIO2)   
                 {
 if (SendDlgItemMessage(hwnd, IDB_RADIO2, BM_GETCHECK, 0, 0) == 0) 

                            {

                               SendDlgItemMessage(hwnd, IDB_RADIO2, BM_SETCHECK, 1, 0);

                                SendDlgItemMessage(hwnd, IDB_RADIO1, BM_SETCHECK, 0, 0);

cout<<"IDB_RADIO2"<<endl;
                            }


}
 
       

}
break;   
case WM_SIZE:
         {
        
        MoveWindow(hsButton1,  40, HIWORD(lParam)-60, 80, 30, TRUE);
        MoveWindow(hsButton2, LOWORD(lParam)-120, HIWORD(lParam)-60, 80, 30, TRUE);     
                  
             }
	break;
case WM_CLOSE:
EnableWindow (hButton4, TRUE);
             DestroyWindow(peti); 

        break;    
case WM_DESTROY:        
       
break;    
default:        
return DefWindowProc(hwnd, msg, wParam, lParam);    
}    
return 0; 
} 


LRESULT CALLBACK sestiprozor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

char Temp[255]={0};

    switch(msg)
	{	
	case WM_CREATE:
	{
htButton1 = CreateWindowEx(0,"button","Potvrdi",WS_CHILD | WS_VISIBLE,60,30,180,30,hwnd,(HMENU)htBUTTON1,hins,NULL);
htButton2 = CreateWindowEx(0,"button","Odustani",WS_CHILD | WS_VISIBLE,60,30,180,30,hwnd,(HMENU)htBUTTON2,hins,NULL);

InitCommonControls();
htSifrarnik= CreateWindowEx(0,WC_LISTVIEW, 0,WS_VISIBLE|WS_BORDER|WS_CHILD | LVS_REPORT | LVS_EDITLABELS,10, 10, 750, 300,hwnd,(HMENU)htSIFRARNIK,hins,NULL);
LVCOLUMN LvCol;
SendMessage(htSifrarnik, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES);
memset(&LvCol,0,sizeof(LvCol)); // Reset Coluom
LvCol.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM; // Type of mask
LvCol.cx=0x32;                               // width between each coloum
LvCol.pszText=LPSTR("Sifra");                     // First Header
SendMessage(htSifrarnik,LVM_INSERTCOLUMN,0,(LPARAM)&LvCol);
LvCol.pszText=LPSTR("Usluga");
LvCol.cx=0x62;                          // Next coloum
SendMessage(htSifrarnik,LVM_INSERTCOLUMN,1,(LPARAM)&LvCol); // ...
LvCol.pszText=LPSTR("Id1");                       //
SendMessage(htSifrarnik,LVM_INSERTCOLUMN,2,(LPARAM)&LvCol); //
LvCol.pszText=LPSTR("Mjera1");                       //
SendMessage(htSifrarnik,LVM_INSERTCOLUMN,3,(LPARAM)&LvCol); //
LvCol.pszText=LPSTR("Cijena1");                       //
SendMessage(htSifrarnik,LVM_INSERTCOLUMN,4,(LPARAM)&LvCol); //
LvCol.pszText=LPSTR("Pdv1");                       //
SendMessage(htSifrarnik,LVM_INSERTCOLUMN,5,(LPARAM)&LvCol); //
LvCol.pszText=LPSTR("Id2");                       //
SendMessage(htSifrarnik,LVM_INSERTCOLUMN,6,(LPARAM)&LvCol); //
LvCol.pszText=LPSTR("Mjera2");                       //
SendMessage(htSifrarnik,LVM_INSERTCOLUMN,7,(LPARAM)&LvCol); //
LvCol.pszText=LPSTR("Cijena2");                       //
SendMessage(htSifrarnik,LVM_INSERTCOLUMN,8,(LPARAM)&LvCol); //
LvCol.pszText=LPSTR("Pdv2");                       //
SendMessage(htSifrarnik,LVM_INSERTCOLUMN,9,(LPARAM)&LvCol); //

sqlite3 *db;
char *err_msg = 0;
sqlite3_stmt *res;				
				
int rc = sqlite3_open("baza.db", &db);

const char *sql = "select * from sifrarnik;";

rc = sqlite3_prepare(db, sql, -1, &res, 0);
int step;
LV_ITEM lvi; 
memset(&lvi,0,sizeof(lvi)); // Reset Item Struct

int u=0;

while(true){
step = sqlite3_step(res);
if (step == SQLITE_DONE) { break;}				
lvi.mask=LVIF_TEXT;   // Text Style
lvi.cchTextMax = 256; // Max size of test
                
lvi.iItem=u;          // choose item  
lvi.iSubItem=0;       // Put in first coluom
lvi.pszText=LPSTR(sqlite3_column_text(res, 0)); // Text to display (can be from a char variable) (Items)
                
SendMessage(htSifrarnik,LVM_INSERTITEM,0,(LPARAM)&lvi); // Send to the Listview

for(int i=1;i<=10 ;i++) // Add SubItems in a loop
{
lvi.iSubItem=i;
sprintf(Temp,"%s",sqlite3_column_text(res, i));
lvi.pszText=LPSTR(Temp);
SendMessage(htSifrarnik,LVM_SETITEM,0,(LPARAM)&lvi); // Enter text to SubItems

}
u++;
}
sqlite3_finalize(res);
sqlite3_close(db);
	}
	break;
case WM_COMMAND:
         {

		if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==htBUTTON2)   
                 {        
                
                        
                

                 DestroyWindow(sesti);}
	}
	break;
	case WM_SIZE:
         {
        
        MoveWindow(htButton1,  40, HIWORD(lParam)-60, 80, 30, TRUE);
        MoveWindow(htButton2, LOWORD(lParam)-120, HIWORD(lParam)-60, 80, 30, TRUE);     
         MoveWindow(htSifrarnik, 20, 20, LOWORD(lParam)-40, HIWORD(lParam)-130, TRUE);          
             }
	break;
        case WM_CLOSE:
EnableWindow (hButton5, TRUE);
             DestroyWindow(sesti);

        break;
        case WM_DESTROY:
            {
             
            } break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
     
}

LRESULT CALLBACK sedmiprozor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {

    case WM_CREATE:
{
CreateWindowEx(0,"Static","Kolicina",WS_CHILD | WS_VISIBLE,20,10,80,30,hwnd,0,hins,NULL);
uaKolicina=CreateWindowEx(0,"Edit","Kolicina",WS_CHILD | WS_VISIBLE| WS_BORDER,140,10,130,30,hwnd,(HMENU)uaKOLICINA,hins,NULL);
CreateWindowEx(0,"Static","Id",WS_CHILD | WS_VISIBLE,20,50,80,30,hwnd,0,hins,NULL);
uaId=CreateWindowEx(0,"Edit","Id",WS_CHILD | WS_VISIBLE| WS_BORDER,140,50,130,30,hwnd,(HMENU)uaID,hins,NULL);

uaButton1 = CreateWindowEx(BS_PUSHBUTTON,"button","POTVRDI",
WS_CHILD | WS_VISIBLE,60,30,180,30,hwnd,(HMENU)uaBUTTON1,hins,NULL);
                                   
 uaButton2 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "ODUSTANI",
                                   WS_CHILD | WS_VISIBLE,
                                   60,70,180,30,
                                   hwnd,
                                   (HMENU)uaBUTTON2,
                                    hins,
                                   NULL);

}
break;
case WM_SIZE:
         {
        
       
        MoveWindow(uaButton1,  40, HIWORD(lParam)-50, 80, 30, TRUE);
        MoveWindow(uaButton2, LOWORD(lParam)-120, HIWORD(lParam)-50, 80, 30, TRUE);
	       
             }
	break;
         case WM_COMMAND:
         {

		if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==uaBUTTON1)   
                 {
int idx;
double kolicinax;
GetDlgItemNumber(hwnd,uaID,idx);
GetDlgItemNumber(hwnd,uaKOLICINA,kolicinax);

sqlite3 *db;
char *zErrMsg = 0;
sqlite3_stmt *res;
    // Save the result of opening the file
    int rc;

    // Save any SQL
    string sql;

    // Save the result of opening the file
    rc = sqlite3_open("baza.db", &db);

 sql = "SELECT kolicina FROM skladiste WHERE id ="+to_string(idx)+";";
cout<<sql<<endl;
rc = sqlite3_prepare(db, sql.c_str(), -1, &res, 0);
int step;
   
   
     step = sqlite3_step(res); 
double kolicina=sqlite3_column_double(res, 0);  
        printf("%5.2f: ",kolicina);

kolicina+=kolicinax;

sql = "UPDATE skladiste set kolicina ="+to_string(kolicina)+" where id="+to_string(idx)+";";
cout<<sql<<endl;

rc = sqlite3_prepare(db, sql.c_str(), -1, &res, 0);
step = sqlite3_step(res);   
printf("%5.2f: ", sqlite3_column_double(res, 0));


sqlite3_finalize(res);
sqlite3_close(db);
DestroyWindow(sedmi);
}
if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==uaBUTTON2)   
                 {
DestroyWindow(sedmi);
}
}
break;
        case WM_CLOSE:
EnableWindow (hButton6, TRUE);
            DestroyWindow(sedmi);

        break;
        case WM_DESTROY:
            {
               
            } break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
     
}

LRESULT CALLBACK osmiprozor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {

    case WM_CREATE:
{
CreateWindowEx(0,"Static","Id",WS_CHILD | WS_VISIBLE,20,10,80,30,hwnd,0,hins,NULL);
baId=CreateWindowEx(0,"Edit","Id",WS_CHILD | WS_VISIBLE| WS_BORDER,140,10,130,30,hwnd,(HMENU)baID,hins,NULL);

baButton1 = CreateWindowEx(BS_PUSHBUTTON,"button","POTVRDI",
WS_CHILD | WS_VISIBLE,60,30,180,30,hwnd,(HMENU)baBUTTON1,hins,NULL);
                                   
 baButton2 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "ODUSTANI",
                                   WS_CHILD | WS_VISIBLE,
                                   60,70,180,30,
                                   hwnd,
                                   (HMENU)baBUTTON2,
                                    hins,
                                   NULL);

}
break;
case WM_SIZE:
         {
        
       
        MoveWindow(baButton1,  40, HIWORD(lParam)-50, 80, 30, TRUE);
        MoveWindow(baButton2, LOWORD(lParam)-120, HIWORD(lParam)-50, 80, 30, TRUE);
	       
             }
	break;
case WM_COMMAND:
         {

		if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==baBUTTON1)   
                 {

int idx;
GetDlgItemNumber(hwnd,baID,idx);

sqlite3 *db;
char *zErrMsg = 0;
sqlite3_stmt *res;
    // Save the result of opening the file
    int rc;

    // Save any SQL
    string sql;

    // Save the result of opening the file
    rc = sqlite3_open("baza.db", &db);

sql = "delete from skladiste  where id="+to_string(idx)+";";
cout<<sql<<endl;

rc = sqlite3_prepare(db, sql.c_str(), -1, &res, 0);
int step = sqlite3_step(res);  

sqlite3_finalize(res);
sqlite3_close(db);
EnableWindow (hButton7, TRUE);
DestroyWindow(osmi);
}
if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==baBUTTON2)   
                 {
EnableWindow (hButton7, TRUE);
DestroyWindow(osmi);
}
}
break;
        case WM_CLOSE:
EnableWindow (hButton7, TRUE);
            DestroyWindow(osmi);

        break;
        case WM_DESTROY:
            {
               
            } break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
     
}


LRESULT CALLBACK devetiprozor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {

    case WM_CREATE:
{
CreateWindowEx(0,"Static","Id",WS_CHILD | WS_VISIBLE,20,10,80,30,hwnd,0,hins,NULL);
bsId=CreateWindowEx(0,"Edit","Id",WS_CHILD | WS_VISIBLE| WS_BORDER,140,10,130,30,hwnd,(HMENU)bsID,hins,NULL);

bsButton1 = CreateWindowEx(BS_PUSHBUTTON,"button","POTVRDI",
WS_CHILD | WS_VISIBLE,60,30,180,30,hwnd,(HMENU)bsBUTTON1,hins,NULL);
                                   
 bsButton2 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "ODUSTANI",
                                   WS_CHILD | WS_VISIBLE,
                                   60,70,180,30,
                                   hwnd,
                                   (HMENU)bsBUTTON2,
                                    hins,
                                   NULL);

}
break;
case WM_SIZE:
         {
        
       
        MoveWindow(bsButton1,  40, HIWORD(lParam)-50, 80, 30, TRUE);
        MoveWindow(bsButton2, LOWORD(lParam)-120, HIWORD(lParam)-50, 80, 30, TRUE);
	       
             }
	break;
case WM_COMMAND:
         {

		if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==bsBUTTON1)   
                 {

int idx;
GetDlgItemNumber(hwnd,bsID,idx);

sqlite3 *db;
char *zErrMsg = 0;
sqlite3_stmt *res;
    // Save the result of opening the file
    int rc;

    // Save any SQL
    string sql;

    // Save the result of opening the file
    rc = sqlite3_open("baza.db", &db);

sql = "delete from sifrarnik  where id="+to_string(idx)+";";
cout<<sql<<endl;

rc = sqlite3_prepare(db, sql.c_str(), -1, &res, 0);
int step = sqlite3_step(res);  

sqlite3_finalize(res);
sqlite3_close(db);

DestroyWindow(deveti);

}
if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==bsBUTTON2)   
                 {
DestroyWindow(deveti);
EnableWindow (hButton8, TRUE);
}
}
break;
        case WM_CLOSE:
EnableWindow (hButton8, TRUE);
            DestroyWindow(deveti);

        break;
        case WM_DESTROY:
            {
             
            } break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
     
}

LRESULT CALLBACK desetiprozor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {

    case WM_CREATE:
{
CreateWindowEx(0,"Static","Id",WS_CHILD | WS_VISIBLE,20,10,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Ime",WS_CHILD | WS_VISIBLE,20,50,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Prezime",WS_CHILD | WS_VISIBLE,20,90,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Oib",WS_CHILD | WS_VISIBLE,20,130,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Zaporka",WS_CHILD | WS_VISIBLE,20,170,80,30,hwnd,0,hins,NULL);

dId=CreateWindowEx(0,"Edit","Id",WS_CHILD | WS_VISIBLE| WS_BORDER,140,10,130,30,hwnd,(HMENU)dID,hins,NULL);
dIme=CreateWindowEx(0,"Edit","Ime",WS_CHILD | WS_VISIBLE| WS_BORDER,140,50,130,30,hwnd,(HMENU)dIME,hins,NULL);
dPrezime=CreateWindowEx(0,"Edit","Prezime",WS_CHILD | WS_VISIBLE| WS_BORDER,140,90,130,30,hwnd,(HMENU)dPREZIME,hins,NULL);
dOib=CreateWindowEx(0,"Edit","Oib",WS_CHILD | WS_VISIBLE| WS_BORDER,140,130,130,30,hwnd,(HMENU)dOIB,hins,NULL);
dZaporka=CreateWindowEx(0,"Edit","Zaporka",WS_CHILD | WS_VISIBLE| WS_BORDER,140,170,130,30,hwnd,(HMENU)dZAPORKA,hins,NULL);



dButton1 = CreateWindowEx(BS_PUSHBUTTON,"button","POTVRDI",
WS_CHILD | WS_VISIBLE,60,30,180,30,hwnd,(HMENU)dBUTTON1,hins,NULL);
                                   
 dButton2 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "ODUSTANI",
                                   WS_CHILD | WS_VISIBLE,
                                   60,70,180,30,
                                   hwnd,
                                   (HMENU)dBUTTON2,
                                    hins,
                                   NULL);

}
break;
case WM_SIZE:
         {
        
       
        MoveWindow(dButton1,  40, HIWORD(lParam)-50, 80, 30, TRUE);
        MoveWindow(dButton2, LOWORD(lParam)-120, HIWORD(lParam)-50, 80, 30, TRUE);
	       
             }
	break;
case WM_COMMAND:
         {

		if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==dBUTTON1)   
                 {

		int Id;
		string Ime,Prezime,Oib,Zaporka;
		
		


		GetDlgItemNumber(hwnd,dID,Id);
		GetDlgItemString(hwnd,dIME,Ime);
		GetDlgItemString(hwnd,dPREZIME,Prezime);
		GetDlgItemString(hwnd,dOIB,Oib);
		GetDlgItemString(hwnd,dZAPORKA,Zaporka);

cout<<Id<<" "<<Ime<<" "<<Prezime<<" "<<Oib<<" "<<Zaporka<<endl;

sqlite3 *db;
sqlite3_stmt *res;
int rc;

rc=sqlite3_open("baza.db",&db);
if(rc!=SQLITE_OK)
{
    cout<<sqlite3_errmsg(db);
}else {
stringstream sql;
sql<<"INSERT INTO djelatnici (id_djelatnik,ime,prezime,oib,zaporka) VALUES ("<<Id;
sql<<",'"<<Ime<<"','"<<Prezime<<"','"<<Oib<<"','"<<Zaporka<<"');";
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
  

DestroyWindow(deseti);
EnableWindow (hButton9, TRUE);
}
if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==dBUTTON2)   
                 {
DestroyWindow(deseti);
EnableWindow (hButton9, TRUE);
}
}
break;
        case WM_CLOSE:
EnableWindow (hButton9, TRUE);
            DestroyWindow(deseti);

        break;
        case WM_DESTROY:
            {
             
            } break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
     
}

LRESULT CALLBACK jedanaestiprozor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {

    case WM_CREATE:
{
CreateWindowEx(0,"Static","Poduzece",WS_CHILD | WS_VISIBLE,20,10,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Ime",WS_CHILD | WS_VISIBLE,20,50,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Prezime",WS_CHILD | WS_VISIBLE,20,90,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Adresa",WS_CHILD | WS_VISIBLE,20,130,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Mjesto",WS_CHILD | WS_VISIBLE,20,170,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Oib",WS_CHILD | WS_VISIBLE,20,210,80,30,hwnd,0,hins,NULL);
CreateWindowEx(0,"Static","Telefon",WS_CHILD | WS_VISIBLE,20,250,80,30,hwnd,0,hins,NULL);

pPoduzece=CreateWindowEx(0,"Edit","Poduzece",WS_CHILD | WS_VISIBLE| WS_BORDER,140,10,130,30,hwnd,(HMENU)pPODUZECE,hins,NULL);
pIme=CreateWindowEx(0,"Edit","Ime",WS_CHILD | WS_VISIBLE| WS_BORDER,140,50,130,30,hwnd,(HMENU)pIME,hins,NULL);
pPrezime=CreateWindowEx(0,"Edit","Prezime",WS_CHILD | WS_VISIBLE| WS_BORDER,140,90,130,30,hwnd,(HMENU)pPREZIME,hins,NULL);
pAdresa=CreateWindowEx(0,"Edit","Adresa",WS_CHILD | WS_VISIBLE| WS_BORDER,140,130,130,30,hwnd,(HMENU)pADRESA,hins,NULL);
pMjesto=CreateWindowEx(0,"Edit","Mjesto",WS_CHILD | WS_VISIBLE| WS_BORDER,140,170,130,30,hwnd,(HMENU)pMJESTO,hins,NULL);
pOib=CreateWindowEx(0,"Edit","Oib",WS_CHILD | WS_VISIBLE| WS_BORDER,140,210,130,30,hwnd,(HMENU)pOIB,hins,NULL);
pTelefon=CreateWindowEx(0,"Edit","Telefon",WS_CHILD | WS_VISIBLE| WS_BORDER,140,250,130,30,hwnd,(HMENU)pTELEFON,hins,NULL);




pButton1 = CreateWindowEx(BS_PUSHBUTTON,"button","POTVRDI",
WS_CHILD | WS_VISIBLE,60,30,180,30,hwnd,(HMENU)pBUTTON1,hins,NULL);
                                   
 pButton2 = CreateWindowEx(BS_PUSHBUTTON,
                                   "button",
                                   "ODUSTANI",
                                   WS_CHILD | WS_VISIBLE,
                                   60,70,180,30,
                                   hwnd,
                                   (HMENU)pBUTTON2,
                                    hins,
                                   NULL);

}
break;
case WM_SIZE:
         {
        
       
        MoveWindow(pButton1,  40, HIWORD(lParam)-50, 80, 30, TRUE);
        MoveWindow(pButton2, LOWORD(lParam)-120, HIWORD(lParam)-50, 80, 30, TRUE);
	       
             }
	break;
case WM_COMMAND:
         {

		if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==pBUTTON1)   
                 {

		
		string Poduzece,Ime,Prezime,Adresa,Mjesto,Oib,Telefon;
		
		GetDlgItemString(hwnd,pPODUZECE,Poduzece);
		GetDlgItemString(hwnd,pIME,Ime);
		GetDlgItemString(hwnd,pPREZIME,Prezime);
		GetDlgItemString(hwnd,pADRESA,Adresa);
		GetDlgItemString(hwnd,pMJESTO,Mjesto);
		GetDlgItemString(hwnd,pOIB,Oib);
		GetDlgItemString(hwnd,pTELEFON,Telefon);

cout<<Poduzece<<" "<<Ime<<" "<<Prezime<<" "<<Adresa<<" "<<Mjesto<<" "<<Oib<<" "<<Telefon<<endl;
sqlite3 *db;
sqlite3_stmt *res;
int rc;

rc=sqlite3_open("baza.db",&db);

stringstream sql;

sql<<"drop table if exists poduzece;";
rc=sqlite3_prepare(db,sql.str().c_str(),-1,&res,NULL);
rc=sqlite3_step(res);
sql.clear();//clear any bits set
sql.str(string());

sql<<"create table poduzece(poduzece text not null,";
sql<<"ime text not null,prezime text not null,";
sql<<"adresa text not null,mjesto text not null,";
sql<<"oib text not null,telefon text not null);";
rc=sqlite3_prepare(db,sql.str().c_str(),-1,&res,NULL);
rc=sqlite3_step(res);
sql.clear();
sql.str(string());

sql<<"INSERT INTO poduzece (poduzece,ime,prezime,adresa,mjesto,oib,telefon) VALUES ('";
sql<<Poduzece<<"','"<<Ime<<"','"<<Prezime<<"','"<<Adresa<<"','"<<Mjesto<<"','"<<Oib<<"','"<<Telefon<<"');";
rc=sqlite3_prepare(db,sql.str().c_str(),-1,&res,NULL);
  
rc=sqlite3_step(res);


sqlite3_finalize(res);
sqlite3_close(db);


DestroyWindow(jedanaesti);
EnableWindow (hButton10, TRUE);
}
if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==pBUTTON2)   
                 {
DestroyWindow(jedanaesti);
EnableWindow (hButton10, TRUE);
}
}
break;
        case WM_CLOSE:
EnableWindow (hButton10, TRUE);
            DestroyWindow(jedanaesti);

        break;
        case WM_DESTROY:
            {
             
            } break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
     
}