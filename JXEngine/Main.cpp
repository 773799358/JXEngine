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
/// ��Ϣ�ص�����
/// </summary>
/// <param name="hwnd">����</param>
/// <param name="message">��Ϣ����</param>
/// <param name="wParam">��Ϣ�ľ�������</param>
/// <param name="lParam">��Ϣ�ľ�������</param>
/// <returns>result</returns>
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// ��ʼ������
void InitWindow();

// ��ʼ������
void Init();

// ���»�������
void UpdateScene();

// �����߼�����
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
			PostQuitMessage(0);	// ����һ��WM_QUIT��Ϣ
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
	// ע�ᴰ����
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

	// ��������
	g_hwnd = CreateWindow(TEXT("JXEngine"), // class name
		WINDOW_TITLE, // window title 
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, g_windowWidth, g_windowHeight, nullptr, nullptr, g_hInstance, nullptr);

	if (!g_hwnd)
	{
		// ��message box���Խ���������ֱ��������ȽϺ����ڵ������
		MessageBox(0, TEXT("CreawteWindow Faild."), 0, 0);
		return;
	}

	// �����ƶ�����ʾ������
	MoveWindow(g_hwnd, 250, 80, g_windowWidth, g_windowHeight, true);
	ShowWindow(g_hwnd, SW_SHOWNORMAL);
	UpdateWindow(g_hwnd); // �������޸���ֵ��Ҫ�Դ��ڽ��и��£�һ��ShowWindow֮��ǵõ��ü���
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
	// ������Ϣ�ṹ�壬��ʼ��Ϣѭ��������ʼ���о���
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)	// �˳���Ϣ
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))	// �鿴��Ϣ���������Ƿ�����Ϣ������Ϣ�ͻ����msg�У�û�оͻ᷵��0
		{
			TranslateMessage(&msg);	// �������Ϣ��Ԥ����˵���˾�������һЩû�õ���Ϣ
			DispatchMessage(&msg);	// ���͵����ڴ�������wndClass.lpfnWndProc = DefWindowProc������ָ����ϵͳĬ�ϵ���Ϣ�������Proc = Procedure��Ҳ����ָ���Լ�����Ϣ������
		}
		else
		{
			UpdateScene(); 
			DrawScene();
		}
	}
}