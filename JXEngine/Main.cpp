#include<windows.h>

#define WINDOW_TITLE L"Engine Toy"

// Win32����������
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// ��Ȼû�п���̨����ô����OutputDebugString����������ڴ�ӡ��Ϣ
	OutputDebugString(L"hello world!");
	return 0;
}