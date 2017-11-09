#include <windows.h>
#include "buffer.h"
#include "resource.h"

#define UWM_CHANGEICON WM_APP
#define UWM_NOTIFYICON (WM_APP+1)

BOOL NotificationIcon(HWND hWnd, DWORD dwMessage, WORD wIcon)
{
	HICON hIcon = NULL;
	if(wIcon != 0)
	{
		hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(wIcon),
			IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0);
		if(!hIcon)
		{
			return FALSE;
		}
	}

	NOTIFYICONDATA nid;
	ZeroMemory(&nid, sizeof(nid));
	nid.cbSize = NOTIFYICONDATA_V1_SIZE;
	nid.hWnd = hWnd;
	nid.uID = 1;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = UWM_NOTIFYICON;
	nid.hIcon = hIcon;
	lstrcpy(nid.szTip, L"TinyTrayIndicator");
	return Shell_NotifyIcon(dwMessage, &nid);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		NotificationIcon(hWnd, NIM_ADD, IDI_ICON1);
		break;

	case UWM_CHANGEICON:
		if((WORD)wParam != 0)
		{
			NotificationIcon(hWnd, NIM_MODIFY, (WORD)wParam);
		}
		break;

	case UWM_NOTIFYICON:
		if(wParam == 1)
		{
			switch(lParam)
			{
			case WM_RBUTTONUP:
				SendMessage(hWnd, WM_CLOSE, 0, 0);
				break;
			}
		}
		break;

	case WM_CLOSE:
		NotificationIcon(hWnd, NIM_DELETE, 0);
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

void main()
{
	int argc;
	WCHAR **argv = CommandLineToArgvW(GetCommandLine(), &argc);
	if(!argv)
	{
		MessageBox(NULL, L"CommandLineToArgvW failed", L"Error", MB_ICONERROR);
		ExitProcess(1);
	}

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = WndProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = argc > 1 ? argv[1] : L"TinyTrayIndicator";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Class registration failed", L"Error", MB_ICONERROR);
		ExitProcess(1);
	}

	HWND hWnd = CreateWindow(wc.lpszClassName, NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, wc.hInstance, NULL);
	if(!hWnd)
	{
		MessageBox(NULL, L"Window creation failed", L"Error", MB_ICONERROR);
		ExitProcess(1);
	}

	//ShowWindow(hWnd, nCmdShow);
	//UpdateWindow(hWnd);

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	ExitProcess(msg.wParam);
}
