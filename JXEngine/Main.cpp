#include<windows.h>

#define WINDOW_TITLE L"Engine Toy"

// Win32程序主函数
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// 既然没有控制台，那么就用OutputDebugString在输出窗口内打印信息
	OutputDebugString(L"hello world!");
	return 0;
}