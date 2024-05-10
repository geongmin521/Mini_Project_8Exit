#include "Win32GameProject.h"
#include "GameManager.h"

namespace global
{
    WinApp winApp;

    const WinApp& GetWinApp()
    {
        return winApp;
    }
}

constexpr int SCREEN_Start_LEFT = 10;

constexpr int SCREEN_Start_TOP = 10;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    global::winApp.Initialize(hInstance);

    global::winApp.Run();

    global::winApp.Finalize();

    return EXIT_SUCCESS;
}
void WinApp::Initialize(HINSTANCE hInstance)
{
    m_hInstance = hInstance;

    const TCHAR* appName = TEXT("Test Game Framework");

    //Step 1: Registering the Window Class

    WNDCLASS wndClass;

    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = appName;

    RegisterClass(&wndClass);

    // Step 2: Creating the Window

    RECT rect{ SCREEN_Start_LEFT, SCREEN_Start_TOP,
    SCREEN_Start_LEFT + width, SCREEN_Start_TOP + height };

    ::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    m_hWnd = CreateWindow(appName, appName, WS_OVERLAPPED | WS_SYSMENU,
        SCREEN_Start_LEFT, SCREEN_Start_TOP, 1056, 846, NULL, NULL, hInstance, NULL);

    ShowWindow(m_hWnd, SW_SHOWNORMAL);
    UpdateWindow(m_hWnd);

    // Step 3: Game Initialize Here
    game::GameManager::GetInstance()->Initialize();
}
void WinApp::Run()
{
    // Step 4: Game Loop Here
    game::GameManager::GetInstance()->Run();
}

void WinApp::Finalize()
{
    // Step 5: Game Finalize Here
    game::GameManager::GetInstance()->Finalize();
}

void PlaceInCenterOfScreen(HWND window, DWORD style, DWORD exStyle)
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    RECT clientRect;
    GetClientRect(window, &clientRect);

    int clientWidth = clientRect.right - clientRect.left;
    int clientHeight = clientRect.bottom - clientRect.top;

    SetWindowPos(window, NULL,
        screenWidth / 2 - clientWidth / 2,
        screenHeight / 2 - clientHeight / 2,
        clientWidth, clientHeight, 0
    );
}

LRESULT CALLBACK WinApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        PlaceInCenterOfScreen(hWnd, WS_OVERLAPPEDWINDOW, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
        break;
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}