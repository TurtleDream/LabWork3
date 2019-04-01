//Заголовочный файл определения класса CBallsArray.
#include "CBallsArray.h"

// заголовочный файл определения класса CBallSettingsMonitor
#include "CBallSettingsMonitor.h"

// Макрос определения клавиши "G"
#define VK_G 0x47

// Заголовочный файл определения класса CTrap
#include "CTrap.h"
#include "CTrap2.h"
// Заголовочный файл

//Прототип функции обработки сообщений.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*
HWND - идентификатор окна,где генерируется сообщение;
UINT - генерация типа сообщения;
WPARAM и LPARAM - параметры сообщения.
*/

// Глобальные переменные:
HINSTANCE g_hInstance;
int g_nCmdShow;
HWND g_mainWnd;
RECT g_rectWnd;
DWORD g_prevFrameTime;
CBallsArray balls(50);// Объект класса CBallsArray
CBallSettingsMonitor monitor;// Объект класса CBallSettingsMonitor
BOOL g_isGrav = FALSE; // Флаг включения гравитации



void OnIdle()
{
	DWORD cur_time = GetTickCount();
	DWORD delta_time = cur_time - g_prevFrameTime;

	//Учёт влияния гравитации
	if (g_isGrav)
		balls.SetGravityFactor(1.0);
	else
		balls.SetGravityFactor(0.0);

	// Перемещение шарика.
	balls.Move(delta_time);

	g_prevFrameTime = cur_time;

	InvalidateRect(g_mainWnd, NULL, TRUE);
}

/*BOOL TextOut(
	HDC hDC, // КОНТЕКСТ УСТРОЙСТВА
	int nXStart, // Координата X начала строки
	int nYStart, // Координата Y начала строки
	LPCTSTR lpString, // Строка
	int cbString // число символов в строке
	);*/

//Функция, создающая и регистрирующая класс окна приложения.
BOOL InitAppClass()
{
	// Идентификатор класса.
	ATOM class_id;

	// Объект класса окна приложения.
	WNDCLASS wc;

	// Заполнение блока памяти.
	memset(&wc, 0, sizeof(wc));

	// Передача объекту класса окна приложения атрибутов.
	wc.lpszMenuName = NULL; // Окно без меню
	wc.style = CS_HREDRAW | CS_VREDRAW; // Указание о перерисовке окна при изменении его ширины и высоты.
	wc.lpfnWndProc = (WNDPROC)WndProc; // Указатель на оконную процедуру.
	wc.cbClsExtra = 0; // Установка числа дополнительных байт, которые размещаются вслед за структурой класса окна, равным 0.
	wc.cbWndExtra = 0; // Установка числа дополнительных байт, которые размещаются вслед за экземпляром окна, равным 0.
	wc.hInstance = g_hInstance; // Дескриптор экземпляра, который содержит оконную процедуру для класса.
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Дескриптор значка класса.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Дескриптор курсора класса.
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // Дескриптор кисти фона класса.
	wc.lpszClassName = L"LabWork3"; // Задание имени класса окна.

	// Регистрация класса.
	class_id = RegisterClass(&wc);

	// Проверка регистрации класса.
	if (class_id != 0)
		return TRUE;

	return FALSE;
}

//Функция, отвечающая за создание стандартного окна шириной и высотой по 400 пикселей.
BOOL InitWindow()
{
	//Создание окна.
	g_mainWnd = CreateWindow(L"LabWork3", L"Лабораторная работа №3", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, 0, 0 , g_hInstance, 0);

	//Если окно не создано.
	if (!g_mainWnd)
		return FALSE;

	//Отобразить окно(Необходимый режим).
	ShowWindow(g_mainWnd, g_nCmdShow);

	//Обновить окно (Перерисовка).
	UpdateWindow(g_mainWnd);

	return TRUE;

}

// Функция для работы в случае отсутствия сообщений в очереди.

//Цикл обработки сообщений.
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

	/*while (GetMessage(&msg, 0, 0, 0))// Останавливает работу программы до прихода нового сообщения от пользователя или системы.
		DispatchMessage(&msg); // Передаёт полученное сообщение функции обработки сообщений.
	return msg.wParam;*/
}







 /*Прототип функции рисования круга.
BOOL Ellipse
	(
	HDC hdc, // идентификатор контекста рисования.
	int nLeftRect, // Координата X левого верхнего угла описывающего прямоугольника.
	int nTopRect, // Координата Y левого верхнего угла описывающего прямоугольника.
	int nRightRect, // Координата X правого нижнего угла описывающего прямоугольника.
	int nBottomRect // Координата Y правого нижнего угла описыающего прямоугольника.
	);
*/

//Функция обработки сообщений.
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Организация действий при получении сообщений:
	switch (msg)
	{

		// Обработка щелчка мыши (отпускания кнопки мыши).
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

		// Обработка щелчка правой кнопкой мыши (отпускания кнопки мыши)
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

		//Отрисовка.
	case WM_PAINT:
		{
			HDC hDC;
			PAINTSTRUCT ps;

			//Начало рисования.
			hDC = BeginPaint(hWnd, &ps);

			// Рисование шарика.
			balls.Draw(hDC);

			// Рисование монитора управления направлением и скоростью шаров
			monitor.Draw(hDC);

			// Рисование ловушки
			balls.trap->Draw(hDC);
			balls.trap2->Draw(hDC);

			// Текст о включении или выключении гравитации
			if (g_isGrav)
				TextOut (hDC, 35, 5, L"Гравитация включена", 19);
			else
				TextOut (hDC, 35, 5, L"Гравитация выключена", 20);

			// Конец рисования.
			EndPaint(hWnd, &ps);

			return 0;
		}

    //Изменение размеров окна
	case WM_SIZE:
		{
			

			g_rectWnd.top = 0;
			g_rectWnd.left = 0;
			g_rectWnd.bottom = HIWORD(lParam);
			g_rectWnd.right = LOWORD(lParam);

			//Передача изменённых границ в классе CBall.
			balls.SetBounds(g_rectWnd);
			
			return 0;
		}

    

			//Обработка нажатия клавиш клавиатуры
	case WM_KEYDOWN:
		{
			switch (wParam)
			{

			// Клавиша "вниз"
			case VK_DOWN:
				monitor.SpeedDown();
				return 0;

			// Клавиша "вверх"
			case VK_UP:
				monitor.SpeedUp();
				return 0;

            // Клавиша "влево"
			case VK_LEFT:
				monitor.AngleUp();
				return 0;

           // Клавиша "вправо"
			case VK_RIGHT:
				monitor.AngleDown();
				return 0;

				//Клавиша "G"
	case VK_G:
		if (g_isGrav)
			g_isGrav = FALSE;
		else
			g_isGrav = TRUE;
		return 0;

			break;
			}

			
		}


			// Завершение работы.
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


// Точка входа для Windows-приложений:
// hInstance - идентификатор текущей запущенной копии приложения, присваивается системой;
// hPrevInstance - оставлен для совместимости с предыдущими версиями, всегда имеет значение NULL;
// lpCmdLine - строка, переданная в качестве параметров командной строки при запуске приложения;
// nCmdShow - константа, показывающая как должно быть запущено приложение.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Инициализация параметров объектов класса CBallsArray.
	CBall* ball;

	ball = balls.Add();
	ball->SetParams(10, 10, 8, 50, 50, g_rectWnd);

	ball = balls.Add();
	ball->SetParams(100, 10, 8, -70, -70, g_rectWnd);

	g_prevFrameTime = GetTickCount();
	g_hInstance = hInstance;
	g_nCmdShow = nCmdShow;
	

	// Если класс окна не инициализирован.
	if( !InitAppClass())
		return 0;

	// Если окно не создано.
	if ( !InitWindow())
		return 0;
	


    // Возвращаемое значение.
	return StartMessageLoop();
}