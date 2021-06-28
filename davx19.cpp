#include<windows.h>
#include <cstring>
#include<iostream>
#include<sstream>
#include<commctrl.h>
#include "sqlite3.h"
#include<string>
using namespace std;

#define hBUTTON1 1001
#define hBUTTON2 1002
#define hBUTTON3 1003
#define hBUTTON4 1004


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



#define HSKLADISTE 3001

HWND hId,hArtikl,hKolicina,hMjera,hPdv,hCijena,huButton1,huButton2;

HWND hsSifra,hsUsluga,hsId1,hsId1_mjera,hsId1_cijena,hsPdv1,hsId2,hsId2_mjera,hsId2_cijena,hsPdv2,hskladiste1,hWndGroupbox,hWndButton1,hWndButton2;

HWND hsButton1,hsButton2;

LRESULT CALLBACK WndProc(HWND, UINT , WPARAM , LPARAM );
LRESULT CALLBACK drugiprozor(HWND, UINT , WPARAM , LPARAM );
LRESULT CALLBACK treciprozor(HWND, UINT , WPARAM , LPARAM );
LRESULT CALLBACK cetvrtiprozor(HWND, UINT , WPARAM , LPARAM );
LRESULT CALLBACK petiprozor(HWND, UINT , WPARAM , LPARAM );

HWND hButton1,hButton2,hButton3,hButton4;
HWND hskladiste;
HWND drugi,treci,cetvrti,peti;

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

template<typename T>
string to_string(T val)
{
    std::stringstream ss("");
    ss << val;
    return ss.str();
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

wc.lpszClassName = "skladiste";
	 wc.lpfnWndProc = (WNDPROC)cetvrtiprozor;
     RegisterClassEx(&wc);

wc.lpszClassName = "sifrarnik";
	 wc.lpfnWndProc = (WNDPROC)petiprozor;
     RegisterClassEx(&wc);

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "PC KASA",
        WS_OVERLAPPED | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT,
	 300,500,NULL, NULL, hInstance, NULL);

  

drugi = CreateWindowEx(0,"blagajna","BLAGAJNA",WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,300,500,0,0,hInstance,0);
treci = CreateWindowEx(0,"unos","UNOS",WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,300,500,0,0,hInstance,0);
cetvrti = CreateWindowEx(0,"skladiste","SKLADISTE",WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,600,300,hwnd,0,hins,0);
peti = CreateWindowEx(0,"sifrarnik","UNOS SIFARA",WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,800,550,hwnd,0,hins,0);

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
                                   "SIFRARNIK",
                                   WS_CHILD | WS_VISIBLE,
                                   60,110,180,30,
                                   hwnd,
                                   (HMENU)hBUTTON4,
                                    hins,
                                   NULL);
}
break;
case WM_COMMAND:
         {
             if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hBUTTON1)   
                 {        
                 
                ShowWindow(drugi,SW_SHOW);  
                 EnableWindow (GetDlgItem (hwnd, hBUTTON1), FALSE);
             }
if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hBUTTON2)   
                 {        
                 
                ShowWindow(treci,SW_SHOW);  
                 
             }
  if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hBUTTON3)   
                 {        
                 
                ShowWindow(cetvrti,SW_SHOW);  
                 
             } 
 if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==hBUTTON4)   
                 {        
                 
                ShowWindow(peti,SW_SHOW);  
                 
             }             
         }
break;
case WM_SIZE:
         {
        
        MoveWindow(hButton1, LOWORD(lParam) / 2 - 80, 20, 160, 30, TRUE);
        MoveWindow(hButton2, LOWORD(lParam) / 2 - 80, 70, 160, 30, TRUE);     
        MoveWindow(hButton3, LOWORD(lParam) / 2 - 80, 120, 160, 30, TRUE);
	MoveWindow(hButton4, LOWORD(lParam) / 2 - 80, 170, 160, 30, TRUE);          
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

LRESULT CALLBACK cetvrtiprozor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {

    case WM_CREATE:
{
InitCommonControls();
hskladiste= CreateWindowEx(0,
				WC_LISTVIEW, 
                                     0,
                                     WS_VISIBLE|WS_BORDER|WS_CHILD | LVS_REPORT | LVS_EDITLABELS,
                                     10, 10, 500, 200,
                                     hwnd,
                                     (HMENU)HSKLADISTE,
                                     hins,
                                     NULL);

char *cnames[100];
LVCOLUMN lvc;
int i;

cnames[0] = LPSTR("Id");
cnames[1] = LPSTR("Artikl");
cnames[2] = LPSTR("Pdv");
cnames[3] = LPSTR("Kolicina");
cnames[4] = LPSTR("Mjera");
cnames[5] = LPSTR("Cijena");
cnames[6] = "";
lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	
for(i=0;cnames[i]!="";i++)
{
lvc.pszText =cnames[i];  
lvc.iSubItem =i;
lvc.fmt = LVCFMT_LEFT;
lvc.cx =80;

ListView_InsertColumn(hskladiste, i, &lvc);
}	
LVITEM lvi;

char *items[100];
int j;
lvi.mask      = LVIF_TEXT | LVIF_PARAM | LVIF_STATE; 
lvi.state     = 0;
lvi.stateMask = 0;


lvi ={0};
lvi.iSubItem = 0;
char znak[200]="";

sqlite3 *db;
char *err_msg = 0;
sqlite3_stmt *res;
    
int rc = sqlite3_open("baza.db", &db);

const char *sql = "select * from skladiste;";

rc = sqlite3_prepare(db, sql, -1, &res, 0);

int cols = sqlite3_column_count(res);
int resx;
int step;
int u=0;
while(true){
lvi.iItem =u;
resx= ListView_InsertItem(hskladiste, &lvi);
step = sqlite3_step(res);

ListView_SetItemText(hskladiste,resx,0,LPSTR(sqlite3_column_text(res, 0)));
ListView_SetItemText(hskladiste,resx,1,LPSTR(sqlite3_column_text(res, 1)));
sprintf(znak,"%0.2f",sqlite3_column_double(res, 2));
ListView_SetItemText(hskladiste,resx,2,LPSTR(znak));
sprintf(znak,"%0.2f",sqlite3_column_double(res, 3));
ListView_SetItemText(hskladiste,resx,3,LPSTR(znak));
sprintf(znak,"%0.2f",sqlite3_column_double(res, 4));
ListView_SetItemText(hskladiste,resx,4,LPSTR(znak));
sprintf(znak,"%0.2f",sqlite3_column_double(res, 5));
ListView_SetItemText(hskladiste,resx,5,LPSTR(znak));

if (step == SQLITE_DONE) {
        // no more rows: exit
        cout << "Done\n";
        break;}
u++;

}
sqlite3_finalize(res);
sqlite3_close(db);

}
break;

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


LRESULT CALLBACK petiprozor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
	case WM_CREATE:
{
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

hsSifra=CreateWindowEx(0,"Edit","Sifra",WS_CHILD | WS_VISIBLE| WS_BORDER,120,10,120,30,hwnd,(HMENU)hsSIFRA,hins,NULL);
hsUsluga=CreateWindowEx(0,"Edit","Usluga",WS_CHILD | WS_VISIBLE| WS_BORDER,120,50,120,30,hwnd,(HMENU)hsUSLUGA,hins,NULL);
hsId1=CreateWindowEx(0,"Edit","Id1",WS_CHILD | WS_VISIBLE| WS_BORDER,120,90,120,30,hwnd,(HMENU)hsID1,hins,NULL);
hsId1_mjera=CreateWindowEx(0,"Edit","Id1 mjera",WS_CHILD | WS_VISIBLE| WS_BORDER,120,130,120,30,hwnd,(HMENU)hsID1_MJERA,hins,NULL);
hsId1_cijena=CreateWindowEx(0,"Edit","Id1 cijena",WS_CHILD | WS_VISIBLE| WS_BORDER,120,170,120,30,hwnd,(HMENU)hsID1_CIJENA,hins,NULL);
hsPdv1=CreateWindowEx(0,"Edit","Pdv1",WS_CHILD | WS_VISIBLE| WS_BORDER,120,210,120,30,hwnd,(HMENU)hsPDV1,hins,NULL);
hsId2=CreateWindowEx(0,"Edit","Id2",WS_CHILD | WS_VISIBLE| WS_BORDER,120,250,120,30,hwnd,(HMENU)hsID2,hins,NULL);
hsId2_mjera=CreateWindowEx(0,"Edit","Id2 mjera",WS_CHILD | WS_VISIBLE| WS_BORDER,120,290,120,30,hwnd,(HMENU)hsID2_MJERA,hins,NULL);
hsId2_cijena=CreateWindowEx(0,"Edit","Id2 cijena",WS_CHILD | WS_VISIBLE| WS_BORDER,120,330,120,30,hwnd,(HMENU)hsID2_CIJENA,hins,NULL);
hsPdv2=CreateWindowEx(0,"Edit","Pdv2",WS_CHILD | WS_VISIBLE| WS_BORDER,120,370,120,30,hwnd,(HMENU)hsPDV2,hins,NULL);


hsButton1 = CreateWindowEx(BS_PUSHBUTTON,"button","Potvrdi",WS_CHILD | WS_VISIBLE,60,30,180,30,hwnd,(HMENU)hsBUTTON1,hins,NULL);
hsButton2 = CreateWindowEx(BS_PUSHBUTTON,"button","Odustani",WS_CHILD | WS_VISIBLE,60,30,180,30,hwnd,(HMENU)hsBUTTON2,hins,NULL);


hskladiste1= CreateWindowEx(0,WC_LISTVIEW, 0,WS_VISIBLE|WS_BORDER|WS_CHILD | LVS_REPORT | LVS_EDITLABELS,450, 10, 300, 300,hwnd,(HMENU)hsSKLADISTE1,hins,NULL);

hWndGroupbox = CreateWindowEx(0,"BUTTON", "Id skladiste", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 300, 5, 120, 120, hwnd, NULL, hins,  NULL); 



hWndButton1 = CreateWindowEx(0, "BUTTON", "Id1", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON, 310, 50, 80, 20, hwnd, (HMENU)IDB_RADIO1, hins, NULL); 
hWndButton2 = CreateWindowEx(0, "BUTTON", "Id2", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON, 310, 90, 80, 20, hwnd, (HMENU)IDB_RADIO2, hins, NULL); 

        


InitCommonControls();
char *cnames[100];
LVCOLUMN lvc;
int i;

cnames[0] = LPSTR("Id");
cnames[1] = LPSTR("Artikl");
cnames[2] = LPSTR("Pdv");

lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	
for(i=0;i<3;i++)
{
lvc.pszText =cnames[i];  
lvc.iSubItem =i;
lvc.fmt = LVCFMT_LEFT;
lvc.cx =100;

ListView_InsertColumn(hskladiste1, i, &lvc);
}

LVITEM lvi;


lvi.mask      = LVIF_TEXT | LVIF_PARAM | LVIF_STATE; 
lvi.state     = 0;
lvi.stateMask = 0;
	
lvi ={0};
lvi.iSubItem = 0;
SendMessage(hskladiste1, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES);
char znak[200]="";
sqlite3 *db;
char *err_msg = 0;
sqlite3_stmt *res;    
int rc = sqlite3_open("baza.db", &db);

const char *sql = "select id,artikl,pdv from skladiste;";

rc = sqlite3_prepare(db, sql, -1, &res, 0);

int cols = sqlite3_column_count(res);
int resx;
int step;
int u=0;

while(true){
lvi.iItem =u;
resx= ListView_InsertItem(hskladiste1, &lvi);
step = sqlite3_step(res);
if (step == SQLITE_DONE) {break;}
sprintf(znak,"%03d",sqlite3_column_int(res, 0));
ListView_SetItemText(hskladiste1,resx,0,LPSTR(znak));
ListView_SetItemText(hskladiste1,resx,1,LPSTR(sqlite3_column_text(res, 1)));
sprintf(znak,"%0.2f",sqlite3_column_double(res, 2));
ListView_SetItemText(hskladiste1,resx,2,LPSTR(znak));

u++;

}

sqlite3_finalize(res);
sqlite3_close(db);
}

	break;
case WM_COMMAND: 

        {
if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) ==IDB_RADIO1)   
                 { 
if (SendDlgItemMessage(hwnd, IDB_RADIO1, BM_GETCHECK, 0, 0) == 0) 

                            {

                                SendDlgItemMessage(hwnd, IDB_RADIO1, BM_SETCHECK, 1, 0);

                                SendDlgItemMessage(hwnd, IDB_RADIO2, BM_SETCHECK, 0, 0);
int iPos;
iPos = ListView_GetNextItem(hskladiste1, iPos, LVNI_SELECTED);
    cout<<iPos<<endl;
    
char *bufText = new char[256];
ListView_GetItemText(GetDlgItem(hwnd,hsSKLADISTE1), iPos, 1, (LPTSTR)bufText, 256);
cout<<bufText<<endl;

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
        case WM_CLOSE:

            ShowWindow(hwnd,SW_HIDE);

        break;

        case WM_DESTROY:
            {
               
            } break;

	case WM_SIZE:
         {
        
        MoveWindow(hsButton1,  40, HIWORD(lParam)-60, 80, 30, TRUE);
        MoveWindow(hsButton2, LOWORD(lParam)-120, HIWORD(lParam)-60, 80, 30, TRUE);     
                  
             }
	break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
     
}


