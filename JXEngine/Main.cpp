#include <Windows.h>
#include <stdio.h>
#include <iostream>

#define WINDOW_TITLE	TEXT("Engine Toy")

// global member
int	g_windowWidth = 800;
int	g_windowHeight = 600;

float g_posX = 0;
float g_posY = 0;

HINSTANCE g_hInstance = 0;
int g_nShowCmd = 0;
HWND g_hwnd = 0;

/// <summary>
/// 消息回调函数
/// </summary>
/// <param name="hwnd">窗口</param>
/// <param name="message">消息类型</param>
/// <param name="wParam">消息的具体内容</param>
/// <param name="lParam">消息的具体内容</param>
/// <returns>result</returns>
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// 初始化窗口
void InitWindow();

// 初始化程序
void Init();

// 更新绘制数据
void UpdateScene();

// 进行逻辑处理
void Run();

int main()
{
	g_hInstance = ::GetModuleHandle(nullptr);

	Init();
	Run();

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)	// esc
		{
			DestroyWindow(hwnd);
			PostQuitMessage(0);	// 发送一个WM_QUIT消息
		}
		else if (wParam == VK_LEFT)
			g_posX -= 1.0f;
		else if (wParam == VK_RIGHT)
			g_posX += 1.0f;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);	// default procedure
	}
	return 0;
}

void InitWindow()
{
	// 注册窗口类
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	//wndClass.lpfnWndProc = DefWindowProc;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = g_hInstance;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hIcon = nullptr;
	wndClass.hCursor = nullptr;
	wndClass.hbrBackground = nullptr;
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = L"JXEngine";

	if (!RegisterClassEx(&wndClass))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return;
	}

	// 创建窗口
	g_hwnd = CreateWindow(TEXT("JXEngine"), // class name
		WINDOW_TITLE, // window title 
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, g_windowWidth, g_windowHeight, nullptr, nullptr, g_hInstance, nullptr);

	if (!g_hwnd)
	{
		// 用message box可以进行阻塞，直到点击，比较好用于调试输出
		MessageBox(0, TEXT("CreawteWindow Faild."), 0, 0);
		return;
	}

	// 窗口移动，显示，更新
	MoveWindow(g_hwnd, 250, 80, g_windowWidth, g_windowHeight, true);
	ShowWindow(g_hwnd, SW_SHOWNORMAL);
	UpdateWindow(g_hwnd); // 别忘记修改完值，要对窗口进行更新，一般ShowWindow之后记得调用即可
}

void Init()
{
	InitWindow();

	g_posX = 400.0f;
	g_posY = 1.0f;
}

void UpdateScene()
{
	g_posY += 0.001f;
	if (g_posY > g_windowHeight)
	{
		g_posY -= g_windowHeight;
	}
}

void DrawScene()
{
	HDC hdc = GetDC(g_hwnd);
	TextOut(hdc, g_posX, g_posY, TEXT("hello"), 5);
	ReleaseDC(g_hwnd, hdc);
}

void Run()
{
	// 定义消息结构体，开始消息循环，不初始化有警告
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)	// 退出消息
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))	// 查看消息队列里面是否有信息，有消息就会放入msg中，没有就会返回0
		{
			TranslateMessage(&msg);	// 会进行消息的预处理，说白了就是舍弃一些没用的信息
			DispatchMessage(&msg);	// 发送到窗口处理函数，wndClass.lpfnWndProc = DefWindowProc，这里指定成系统默认的消息处理程序，Proc = Procedure，也可以指定自己的消息处理函数
		}
		else
		{
			UpdateScene(); 
			DrawScene();
		}
	}
}