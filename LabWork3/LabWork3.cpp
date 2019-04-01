//������������ ���� ����������� ������ CBallsArray.
#include "CBallsArray.h"

// ������������ ���� ����������� ������ CBallSettingsMonitor
#include "CBallSettingsMonitor.h"

// ������ ����������� ������� "G"
#define VK_G 0x47

// ������������ ���� ����������� ������ CTrap
#include "CTrap.h"
#include "CTrap2.h"
// ������������ ����

//�������� ������� ��������� ���������.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*
HWND - ������������� ����,��� ������������ ���������;
UINT - ��������� ���� ���������;
WPARAM � LPARAM - ��������� ���������.
*/

// ���������� ����������:
HINSTANCE g_hInstance;
int g_nCmdShow;
HWND g_mainWnd;
RECT g_rectWnd;
DWORD g_prevFrameTime;
CBallsArray balls(50);// ������ ������ CBallsArray
CBallSettingsMonitor monitor;// ������ ������ CBallSettingsMonitor
BOOL g_isGrav = FALSE; // ���� ��������� ����������



void OnIdle()
{
	DWORD cur_time = GetTickCount();
	DWORD delta_time = cur_time - g_prevFrameTime;

	//���� ������� ����������
	if (g_isGrav)
		balls.SetGravityFactor(1.0);
	else
		balls.SetGravityFactor(0.0);

	// ����������� ������.
	balls.Move(delta_time);

	g_prevFrameTime = cur_time;

	InvalidateRect(g_mainWnd, NULL, TRUE);
}

/*BOOL TextOut(
	HDC hDC, // �������� ����������
	int nXStart, // ���������� X ������ ������
	int nYStart, // ���������� Y ������ ������
	LPCTSTR lpString, // ������
	int cbString // ����� �������� � ������
	);*/

//�������, ��������� � �������������� ����� ���� ����������.
BOOL InitAppClass()
{
	// ������������� ������.
	ATOM class_id;

	// ������ ������ ���� ����������.
	WNDCLASS wc;

	// ���������� ����� ������.
	memset(&wc, 0, sizeof(wc));

	// �������� ������� ������ ���� ���������� ���������.
	wc.lpszMenuName = NULL; // ���� ��� ����
	wc.style = CS_HREDRAW | CS_VREDRAW; // �������� � ����������� ���� ��� ��������� ��� ������ � ������.
	wc.lpfnWndProc = (WNDPROC)WndProc; // ��������� �� ������� ���������.
	wc.cbClsExtra = 0; // ��������� ����� �������������� ����, ������� ����������� ����� �� ���������� ������ ����, ������ 0.
	wc.cbWndExtra = 0; // ��������� ����� �������������� ����, ������� ����������� ����� �� ����������� ����, ������ 0.
	wc.hInstance = g_hInstance; // ���������� ����������, ������� �������� ������� ��������� ��� ������.
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ���������� ������ ������.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // ���������� ������� ������.
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ���������� ����� ���� ������.
	wc.lpszClassName = L"LabWork3"; // ������� ����� ������ ����.

	// ����������� ������.
	class_id = RegisterClass(&wc);

	// �������� ����������� ������.
	if (class_id != 0)
		return TRUE;

	return FALSE;
}

//�������, ���������� �� �������� ������������ ���� ������� � ������� �� 400 ��������.
BOOL InitWindow()
{
	//�������� ����.
	g_mainWnd = CreateWindow(L"LabWork3", L"������������ ������ �3", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, 0, 0 , g_hInstance, 0);

	//���� ���� �� �������.
	if (!g_mainWnd)
		return FALSE;

	//���������� ����(����������� �����).
	ShowWindow(g_mainWnd, g_nCmdShow);

	//�������� ���� (�����������).
	UpdateWindow(g_mainWnd);

	return TRUE;

}

// ������� ��� ������ � ������ ���������� ��������� � �������.

//���� ��������� ���������.
WPARAM StartMessageLoop()
{
	MSG msg;

	while(1)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			DispatchMessage(&msg);
		}
		else
		{
			Sleep(20);
			OnIdle();
	    }
	}
	return msg.wParam;

	/*while (GetMessage(&msg, 0, 0, 0))// ������������� ������ ��������� �� ������� ������ ��������� �� ������������ ��� �������.
		DispatchMessage(&msg); // ������� ���������� ��������� ������� ��������� ���������.
	return msg.wParam;*/
}







 /*�������� ������� ��������� �����.
BOOL Ellipse
	(
	HDC hdc, // ������������� ��������� ���������.
	int nLeftRect, // ���������� X ������ �������� ���� ������������ ��������������.
	int nTopRect, // ���������� Y ������ �������� ���� ������������ ��������������.
	int nRightRect, // ���������� X ������� ������� ���� ������������ ��������������.
	int nBottomRect // ���������� Y ������� ������� ���� ����������� ��������������.
	);
*/

//������� ��������� ���������.
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// ����������� �������� ��� ��������� ���������:
	switch (msg)
	{

		// ��������� ������ ���� (���������� ������ ����).
	case WM_LBUTTONUP:
		{
			double xpos = GET_X_LPARAM(lParam);
			double ypos = GET_Y_LPARAM(lParam);

			CBall* ball = balls.Add();

			if (ball != NULL)
			{
				double vx, vy;
				monitor.GetVxVy(vx, vy);
				ball->SetParams(xpos, ypos, 8, vx, vy, g_rectWnd);
			}

			return 0;
		}

		// ��������� ������ ������ ������� ���� (���������� ������ ����)
	case WM_RBUTTONUP:
		{
			double xpos = GET_X_LPARAM(lParam);
			double ypos = GET_Y_LPARAM(lParam);

			CColoredBall* ball = balls.AddColoredBall();

			if (ball != NULL)
			{
				double vx, vy;
				monitor.GetVxVy(vx, vy);
				ball->SetParams(xpos, ypos, 8, vx, vy, g_rectWnd);
				ball->SetColor(255, 0, 0);
			}
		}

		//���������.
	case WM_PAINT:
		{
			HDC hDC;
			PAINTSTRUCT ps;

			//������ ���������.
			hDC = BeginPaint(hWnd, &ps);

			// ��������� ������.
			balls.Draw(hDC);

			// ��������� �������� ���������� ������������ � ��������� �����
			monitor.Draw(hDC);

			// ��������� �������
			balls.trap->Draw(hDC);
			balls.trap2->Draw(hDC);

			// ����� � ��������� ��� ���������� ����������
			if (g_isGrav)
				TextOut (hDC, 35, 5, L"���������� ��������", 19);
			else
				TextOut (hDC, 35, 5, L"���������� ���������", 20);

			// ����� ���������.
			EndPaint(hWnd, &ps);

			return 0;
		}

    //��������� �������� ����
	case WM_SIZE:
		{
			

			g_rectWnd.top = 0;
			g_rectWnd.left = 0;
			g_rectWnd.bottom = HIWORD(lParam);
			g_rectWnd.right = LOWORD(lParam);

			//�������� ��������� ������ � ������ CBall.
			balls.SetBounds(g_rectWnd);
			
			return 0;
		}

    

			//��������� ������� ������ ����������
	case WM_KEYDOWN:
		{
			switch (wParam)
			{

			// ������� "����"
			case VK_DOWN:
				monitor.SpeedDown();
				return 0;

			// ������� "�����"
			case VK_UP:
				monitor.SpeedUp();
				return 0;

            // ������� "�����"
			case VK_LEFT:
				monitor.AngleUp();
				return 0;

           // ������� "������"
			case VK_RIGHT:
				monitor.AngleDown();
				return 0;

				//������� "G"
	case VK_G:
		if (g_isGrav)
			g_isGrav = FALSE;
		else
			g_isGrav = TRUE;
		return 0;

			break;
			}

			
		}


			// ���������� ������.
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		
	default: 
		break;
	}
	return DefWindowProc (hWnd, msg, wParam, lParam);

	
}


// ����� ����� ��� Windows-����������:
// hInstance - ������������� ������� ���������� ����� ����������, ������������� ��������;
// hPrevInstance - �������� ��� ������������� � ����������� ��������, ������ ����� �������� NULL;
// lpCmdLine - ������, ���������� � �������� ���������� ��������� ������ ��� ������� ����������;
// nCmdShow - ���������, ������������ ��� ������ ���� �������� ����������.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//������������� ���������� �������� ������ CBallsArray.
	CBall* ball;

	ball = balls.Add();
	ball->SetParams(10, 10, 8, 50, 50, g_rectWnd);

	ball = balls.Add();
	ball->SetParams(100, 10, 8, -70, -70, g_rectWnd);

	g_prevFrameTime = GetTickCount();
	g_hInstance = hInstance;
	g_nCmdShow = nCmdShow;
	

	// ���� ����� ���� �� ���������������.
	if( !InitAppClass())
		return 0;

	// ���� ���� �� �������.
	if ( !InitWindow())
		return 0;
	


    // ������������ ��������.
	return StartMessageLoop();
}