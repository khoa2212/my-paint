#include "SimplePaint.h"

//Main
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SIMPLEPAINT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    registerDialogClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SIMPLEPAINT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}


//FUNCTION FOR PARENT WINDOWS
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(CTLCOLOR_BTN + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SIMPLEPAINT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON2));

    return RegisterClassExW(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWndWinmain = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWndWinmain)
   {
      return FALSE;
   }

   ShowWindow(hWndWinmain, nCmdShow);
   UpdateWindow(hWndWinmain);

   return TRUE;
}
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
    InitCommonControls();
    TBBUTTON tbButtons[] =
    {
        { STD_FILENEW,	ID_FILE_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { STD_FILEOPEN,	ID_FILE_LOAD, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { STD_FILESAVE,	ID_FILE_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }
    };
    HWND hToolBarWnd = CreateToolbarEx(hwnd,
        WS_CHILD | WS_VISIBLE | CCS_ADJUSTABLE | TBSTYLE_TOOLTIPS,
        ID_TOOLBAR, sizeof(tbButtons) / sizeof(TBBUTTON), HINST_COMMCTRL,
        0, tbButtons, sizeof(tbButtons) / sizeof(TBBUTTON),
        BUTTON_WIDTH, BUTTON_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT,
        sizeof(TBBUTTON));
    TBBUTTON userButtons[] =
    {
        { 0, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 },
        { 0, ID_DRAW_CIRCLE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { 1, ID_DRAW_RECTANGLE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { 2, ID_DRAW_LINE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { 3, ID_DRAW_SQUARE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
    };
    TBADDBITMAP	tbBitmap[] = { {hInst, IDB_BITMAP1} };
    int idx = (int)SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM)sizeof(tbBitmap) / sizeof(TBADDBITMAP),
        (LPARAM)(LPTBADDBITMAP)&tbBitmap);
    // Xác định chỉ mục hình ảnh của mỗi button từ ảnh bự liên hoàn nhiều tấm
    userButtons[1].iBitmap += idx;
    userButtons[2].iBitmap += idx;
    userButtons[3].iBitmap += idx;
    userButtons[4].iBitmap += idx;
    // Thêm nút bấm vào toolbar
    SendMessage(hToolBarWnd, TB_ADDBUTTONS, (WPARAM)sizeof(userButtons) / sizeof(TBBUTTON),
        (LPARAM)(LPTBBUTTON)&userButtons);
    return TRUE;
}
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
    case ID_CHOOSE_COLOR:
    {
        ZeroMemory(&cc, sizeof(CHOOSECOLOR));
        cc.lStructSize = sizeof(CHOOSECOLOR);
        cc.hwndOwner = hwnd;
        cc.lpCustColors = (LPDWORD)acrCustClr;
        cc.rgbResult = rgbCurrent;
        cc.Flags = CC_FULLOPEN | CC_RGBINIT;
        if (ChooseColor(&cc))
        {
            hbrush = CreateSolidBrush(cc.rgbResult);
            rgbCurrent = cc.rgbResult;
        }
        break;
    }
    case ID_FILE_NEW:
    {
        fileAction = ID_FILE_NEW;
        displayDialog(hwnd);
        break;
    }
    case ID_FILE_LOAD:
    {
        fileAction = ID_FILE_LOAD;
        displayDialogLoad(hwnd);
        break;
    }
    case ID_FILE_SAVE:
    {
        int value = MessageBox(hwnd, L"Chọn Yes để lưu", L"Bạn có muốn lưu file", MB_YESNO | MB_ICONQUESTION);
        if (IDYES == value)
        {
            WCHAR bufferIn[100];
            bool f_Save = saveShape(currentFile, shapes, saveRGB);
            if (f_Save) {
                wsprintf(bufferIn, L"Lưu file thành công");
            }
            else {
                wsprintf(bufferIn, L"Lưu file thất bại");
            }
            MessageBox(hwnd, bufferIn, L"Lưu file", MB_OK);
        }
        else if (IDNO == value)
        {
            //do nothing
        }
        break;
    }
    case ID_DRAW_LINE:
    {
        TypeOfShape = ID_DRAW_LINE;
        break;
    }
    case ID_DRAW_RECTANGLE:
    {
        TypeOfShape = ID_DRAW_RECTANGLE;
        break;
    }
    case ID_DRAW_CIRCLE:
    {
        TypeOfShape = ID_DRAW_CIRCLE;
        break;
    }
    case ID_DRAW_SQUARE:
    {
        TypeOfShape = ID_DRAW_SQUARE;
        break;
    }
    default:
        break;
    }
}
void OnDestroy(HWND hwnd)
{
    PostQuitMessage(0);
}
void OnPaint(HWND hwnd)
{
    PAINTSTRUCT ps;
    hdc = BeginPaint(hwnd, &ps);

    HPEN hPen = CreatePen(PS_DASHDOT, 3, rgbCurrent);
    SelectObject(hdc, hPen);
    if (IDC_LOADFILE == Loadfile)
    {
        for (int i = 0; i < (int)shapes.size(); i++)
        {
            HPEN hPenLoad = CreatePen(PS_DASHDOT, 3, saveRGB[i]);
            SelectObject(hdc, hPenLoad);
            string type = shapes[i]->type();
            string ShapesInformation = shapes[i]->toString();
            vector<string>tokens = Tokenizer::Split(ShapesInformation, " ");
            Point startPoint = getPointOfShapes(tokens[0]);
            Point endPoint = getPointOfShapes(tokens[1]);
            if (type == "Line")
            {
                MoveToEx(hdc, startPoint.x(), startPoint.y(), NULL);
                LineTo(hdc, endPoint.x(), endPoint.y());
            }
            else if (type == "Rectangle")
            {
                //vẽ hình chữ nhật từ file
                Rectangle(hdc, startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y());
            }
            else if (type == "Square")
            {
                //vẽ hình vuông từ file
                Square(hdc, startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y());
            }
            else
            {
                //vẽ hình tròn từ file
                Circle(hdc, startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y());
            }
        }
        Loadfile = 0;
    }
    else 
    {
        switch (TypeOfShape)
        {
        case ID_DRAW_LINE:
        {
            shape = ShapeFactory::instance()->create(LINE, start, End);
            MoveToEx(hdc, start.x(), start.y(), NULL);
            LineTo(hdc, End.x(), End.y());
            break;
        }
        case ID_DRAW_RECTANGLE:
        {
            shape = ShapeFactory::instance()->create(RECTANGLE, start, End);
            Rectangle(hdc, start.x(), start.y(), End.x(), End.y());
            break;
        }
        case ID_DRAW_CIRCLE:
        {
            shape = ShapeFactory::instance()->create(CIRCLE, start, End);
            Circle(hdc, start.x(), start.y(), End.x(), End.y());
            break;
        }
        case ID_DRAW_SQUARE:
        {
            shape = ShapeFactory::instance()->create(SQUARE, start, End);
            Square(hdc, start.x(), start.y(), End.x(), End.y());
            break;
        }
        }
    }
    EndPaint(hwnd, &ps);
}
void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
    isPreview = true;
    isDrawing = true;
    start = Point(x, y);
}
void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
    shapes.push_back(shape);
    saveRGB.push_back(rgbCurrent);
    isDrawing = false;
    // Báo hiệu cần xóa đi toàn bộ màn hình & vẽ lại
    InvalidateRect(hwnd, NULL, TRUE);
}
void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
    if (isDrawing) {
        End = Point(x, y);

        // Báo hiệu cần xóa đi toàn bộ màn hình
        InvalidateRect(hwnd, NULL, TRUE);
    }
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
        HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
        HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
        HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
        HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLButtonDown);
        HANDLE_MSG(hWnd, WM_LBUTTONUP, OnLButtonUp);
        HANDLE_MSG(hWnd, WM_MOUSEMOVE, OnMouseMove);
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


//ADDITIONAL FUNCTIONS
//các hàm thao tác vẽ, lưu và tải hình
void Circle(HDC hDc, int topleft_x, int topleft_y, int rightbot_x, int rightbot_y)
{
    Ellipse(hDc, topleft_x, topleft_y, rightbot_x, rightbot_y);
}
void Square(HDC hDc, int topleft_x, int topleft_y, int rightbot_x, int rightbot_y)
{
    Rectangle(hDc, topleft_x, topleft_y, rightbot_x, rightbot_y);
}
bool saveShape(string filename, const vector<shared_ptr<Ishapes>>& arrShapes, const vector<DWORD>& SAVERGB)
{
    if ((int)arrShapes.size() == 0)return false;
    ofstream writter;
    writter.open(filename);
    writter << (int)arrShapes.size() << endl;
    for (int i = 0; i < arrShapes.size(); i++)
    {
        writter << arrShapes[i]->type() << ": ";
        writter << arrShapes[i]->toString() << ": ";
        writter << saveRGB[i] << endl;
    }
    writter.close();
    return true;
}
bool loadShape(string filename, vector<shared_ptr<Ishapes>>& arrShapes, vector<DWORD>& LOADRGB)
{
    ifstream reader;
    string lines;
    vector<string>tokens;
    reader.open(filename);
    getline(reader, lines);
    int size = stoi(lines);
    for (int i = 0; i < size; i++)
    {
        getline(reader, lines);
        tokens = Tokenizer::Split(lines, ": ");
        shape = ShapeFactory::parse(tokens[0], tokens[1]);
        DWORD rgbShape = (DWORD)stoi(tokens[2]);
        arrShapes.push_back(shape);
        LOADRGB.push_back(rgbShape);
    }
    reader.close();
    return true;
}
Point getPointOfShapes(string token)
{
    shared_ptr<Point>temp = Point::parse(token);
    Point result = *temp;
    return result;
}

//các hàm thao tác để tạo file mới và lấy thông tin từ file
string ws2s(const wstring& s)
{
    int len = 0;
    int slength = (int)s.length();
    len = WideCharToMultiByte(CP_UTF8, 0, s.c_str(), slength, 0, 0, 0, 0);
    string r(len, '\0');
    WideCharToMultiByte(CP_UTF8, 0, s.c_str(), slength, &r[0], len, 0, 0);
    return r;
}
void readfilename(string filename, vector<string>& save)
{
    if ((int)save.size() > 0) {
        save.clear();
    }
    ifstream reader;
    string line;
    reader.open(filename);
    getline(reader, line);
    int count = stoi(line);
    for (int i = 0; i < count; i++) {
        getline(reader, line);
        save.push_back(line);
    }
    reader.close();
}
void writefilename(string filename, vector<string>& save)
{
    ofstream writter;
    writter.open(filename);
    writter << save.size() << endl;
    for (int i = 0; i < (int)save.size(); i++)
    {
        writter << save[i] << endl;
    }
    writter.close();
}
bool checkfilename(string filename, vector<string>& save)
{
    for (int i = 0; i < (int)save.size(); i++) {
        if (filename == save[i])
            return false;
    }
    return true;
}


//FUNCTION FOR DIALOGBOX(SUB_WINDOWS)
void registerDialogClass(HINSTANCE hinst)
{
    WNDCLASSW dialog = { 0 };

    dialog.hInstance = hinst;
    dialog.hCursor = LoadCursor(nullptr, IDC_CROSS);
    dialog.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    dialog.lpszClassName = L"myDialogClass";
    dialog.lpfnWndProc = dialogWndProc;
    dialog.hIcon = LoadIcon(dialog.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    RegisterClassW(&dialog);
}
LRESULT CALLBACK dialogWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        HANDLE_MSG(hWnd, WM_CREATE, OnCreateDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, OnCommandDialog);
        HANDLE_MSG(hWnd, WM_CLOSE, OnCloseDialog);
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
void displayDialog(HWND hwnd)
{
    HWND hw = CreateWindowW(L"myDialogClass", L"New File", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
        500, 200, 400, 200, hwnd, nullptr, nullptr, nullptr);
    EnableWindow(hwnd, false);
}
void displayDialogLoad(HWND hwnd)
{
    HWND hw = CreateWindowW(L"myDialogClass", L"Load File", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
        500, 200, 400, 200, hwnd, nullptr, nullptr, nullptr);
    EnableWindow(hwnd, false);
}
BOOL OnCreateDialog(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
    GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
    HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
        lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
        lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
        lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
        lf.lfPitchAndFamily, lf.lfFaceName);

    if (ID_FILE_NEW == fileAction)
    {
        HWND lbl = CreateWindowEx(NULL, L"BUTTON", L"Nhập tên file.txt(không dấu)",
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            10, 30, 365, 70, hwnd,
            NULL, NULL, NULL);
        SetWindowFont(lbl, hFont, TRUE);

        txtfile = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL,
            WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
            20, 58, 330, 25, hwnd,
            NULL, NULL, NULL);
        SetWindowFont(txtfile, hFont, TRUE);

        HWND btnAdd = CreateWindowEx(NULL, L"BUTTON", L"Thêm file",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            150, 90, 75, 30, hwnd, (HMENU)IDC_ADDFILE, NULL, NULL);
        SetWindowFont(btnAdd, hFont, TRUE);
    }
    else if (ID_FILE_LOAD == fileAction)
    {
        HWND lblload = CreateWindowEx(NULL, L"BUTTON", L"Nhập tên file.txt(không dấu)",
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            10, 30, 365, 70, hwnd,
            NULL, NULL, NULL);
        SetWindowFont(lblload, hFont, TRUE);

        txtfile = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL,
            WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
            20, 58, 330, 25, hwnd,
            NULL, NULL, NULL);
        SetWindowFont(txtfile, hFont, TRUE);

        HWND btnLoad = CreateWindowEx(NULL, L"BUTTON", L"Mở file",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            150, 90, 75, 30, hwnd, (HMENU)IDC_LOADFILE, NULL, NULL);
        SetWindowFont(btnLoad, hFont, TRUE);
    }
    fileAction = 0;
    return TRUE;
}
void OnCommandDialog(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    WCHAR bufferinform[100];
    string tempfile = "";
    readfilename("filename.txt", saveFilename);
    if (IDC_ADDFILE == id)
    {
        GetWindowText(txtfile, buffer, BUFFER_SIZE);
        tempfile = ws2s(buffer);
        if (!checkfilename(tempfile, saveFilename) || tempfile == "")
        {
            wsprintf(bufferinform, L"Tên file đã tồn tại(nhập lại)");
            MessageBox(hwnd, bufferinform, L"Lỗi", MB_OK | MB_ICONWARNING);
        }
        else
        {
            wsprintf(bufferinform, L"Tạo file thành công");
            currentFile = tempfile;
            saveFilename.push_back(currentFile);
            writefilename("filename.txt", saveFilename);
            if ((int)shapes.size() > 0 || (int)saveRGB.size() > 0)
            {
                shapes.clear();
                saveRGB.clear();
            }
            rgbCurrent = RGB(0, 0, 0);
            MessageBox(hwnd, bufferinform, L"Tạo file mới", MB_OK);
        }
    }
    else if (IDC_LOADFILE == id)
    {
        GetWindowText(txtfile, buffer, BUFFER_SIZE);
        tempfile = ws2s(buffer);
        if (checkfilename(tempfile, saveFilename) || tempfile == "")
        {
            wsprintf(bufferinform, L"Không tìm thấy tên file(nhập lại)");
            MessageBox(hwnd, bufferinform, L"Lỗi", MB_OK | MB_ICONWARNING);
        }
        else if (tempfile == "filename.txt")
        {
            wsprintf(bufferinform, L"Không được truy cập file này(nhập lại)");
            MessageBox(hwnd, bufferinform, L"Lỗi", MB_OK | MB_ICONERROR);
        }
        else
        {
            currentFile = tempfile;
            if ((int)shapes.size() > 0 || (int)saveRGB.size() > 0)
            {
                shapes.clear();
                saveRGB.clear();
            }
            bool f_Load = loadShape(currentFile, shapes, saveRGB);
            if (f_Load)
            {
                wsprintf(bufferinform, L"Tải file thành công");
                Loadfile = IDC_LOADFILE;
                rgbCurrent = RGB(0, 0, 0);
                InvalidateRect(hWndWinmain, NULL, TRUE);
            }
            else
            {
                wsprintf(bufferinform, L"Tải file thất bại");
            }
            MessageBox(hwnd, bufferinform, L"Tải file", MB_OK);
        }
    }
    EnableWindow(hWndWinmain, true);
}
void OnCloseDialog(HWND hwnd)
{
    DestroyWindow(hwnd);
    EnableWindow(hWndWinmain, true);
}