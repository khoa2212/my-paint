#pragma once
#include "resource.h"
#include "framework.h"
#include "Singleton.h"
#include <WindowsX.h>
#include <CommCtrl.h>
#include <fstream>
#include <commdlg.h>
#pragma comment(lib, "Comctl32.lib")
using namespace std;
#define MAX_LOADSTRING 100
#define IMAGE_WIDTH     18
#define IMAGE_HEIGHT    18
#define BUTTON_WIDTH    0
#define BUTTON_HEIGHT   0

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

CHOOSECOLOR  cc; // Thông tin màu chọn
COLORREF  acrCustClr[16]; // Mảng custom color
DWORD  rgbCurrent = RGB(0, 0, 0); // Black
HBRUSH  hbrush; // Tạo ra brush từ màu đã chọn
CHOOSEFONT  cf;
LOGFONT  lf;
HFONT  hfont, hfontPrev;
DWORD rgbPrev;
HDC hdc;
HWND txtfile;// một handle của cửa sổ con và gián tiếp đến các lớp cửa sổ con khi new hoặc load file
HWND hWndWinmain;// một handle của cửa sổ mẹ

//Biến toàn cục xác định hình sẽ thao tác
int LINE = 0;
int RECTANGLE = 1;
int CIRCLE = 2;
int SQUARE = 3;

//Biến toàn cục xử lý vẽ, nạp, tải hình
Point start; // điểm nhấp chuột
Point End; //điểm nhả chuột
bool isPreview;// có nhấn chuột hay không
bool isDrawing;// có đang vẽ hay không
int TypeOfShape = 0; // loại hình
int Loadfile = 0;// xác định có load file hay ko
vector<shared_ptr<Ishapes>>shapes;//lưu các hình đã vẽ
vector<DWORD>saveRGB;// lưu lại màu viền của hình
shared_ptr<Ishapes>shape = NULL;// lưu 1 hình hiện tại

//Biến toàn cục để xử lí newfile và loadfile
int fileAction = 0; // trạng thái file load hay new file
vector<string>saveFilename = { "filename.txt", "data.txt" };// vector lưu những tên file tồn tại trong file filename.txt
string currentFile = "data.txt";// tên file lưu mặc định nếu không newfile
const int BUFFER_SIZE = 255; 
WCHAR buffer[BUFFER_SIZE]; // chứa chuỗi lấy từ hàm GetWindowsText của hệ thống



// Forward declarations of functions included in this code module:
//FUNCTION FOR PARENT WINDOWS
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);// Message handler for about box
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnDestroy(HWND hwnd);
void OnPaint(HWND hwnd);
void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);



//ADDITIONAL FUNCTION
//các hàm thao tác vẽ, lưu và tải hình
void Circle(HDC hDc, int topleft_x, int topleft_y, int rightbot_x, int rightbot_y);
void Square(HDC hDc, int topleft_x, int topleft_y, int rightbot_x, int rightbot_y);
bool saveShape(string, const vector<shared_ptr<Ishapes>>&, const vector<DWORD>&);
bool loadShape(string, vector<shared_ptr<Ishapes>>&, vector<DWORD>&);
Point getPointOfShapes(string);

//các hàm thao tác để tạo file mới và lấy thông tin từ file
string ws2s(const wstring& s); // hàm chuyển WCHAR sang string để lấy tên file qua windowstext
void readfilename(string filename, vector<string>& save);
void writefilename(string filename, vector<string>& save);
bool checkfilename(string filename, vector<string>& save);// kiểm tra tên đã tồn tại hay chưa


//FUNCTION FOR DIALOGBOX(SUB_WINDOWS)
void registerDialogClass(HINSTANCE hinst);
LRESULT CALLBACK dialogWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void displayDialog(HWND hwnd);
void displayDialogLoad(HWND hwnd);
BOOL OnCreateDialog(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommandDialog(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnCloseDialog(HWND hwnd);