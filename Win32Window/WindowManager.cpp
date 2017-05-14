

#include "WindowManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

UIManager::WindowManager::WindowManager(HINSTANCE & hInstance, std::string wiName)
{
	this->wiName = wiName;
	winClass.cbSize = sizeof(winClass);
	winClass.hInstance = hInstance;
	winClass.lpszClassName = wiName.c_str();
	//Load default editable ellements
	winClass.hCursor = LoadCursor(0, IDC_ARROW); /*Default*/
	//winClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); /*Default*/		//Alt+Tab Dialog
	winClass.lpfnWndProc = WndProc;
	winClass.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	//winClass.lpszMenuName = NULL; /* No menu */

	if (!RegisterClassEx(&winClass)) {

	}

	//Create Window
	hwnd = CreateWindowEx(
		0,
		winClass.lpszClassName,         /* Title Class */
		winClass.lpszClassName,			/* Title Text */
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		startX,							/* X Start */
		startY,							/* Y Start */
		endX,							/* The programs width */
		endY,							/* and height in pixels */
		HWND_DESKTOP,					/* The window is a child-window to desktop */
		NULL,							/* No menu */
		winClass.hInstance,				/* Program Instance handler */
		NULL
	);
}

int UIManager::WindowManager::build()
{
	return 0;

	//Pending to put here create

}

int UIManager::WindowManager::create(int nCmdShow)
{
	ShowWindow(hwnd, nCmdShow);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_CREATE:
	{

		//Start Action -- Aquí podemos añadir una acción al iniciar el programa
		//Ejemplo:
		MessageBox(0, "Mensaje de Bienvenida", "Título del mensaje", MB_OK); //También se puede en vez de MB_OK colocar MB_ABORTRETRYIGNORE MB_CANCELTRYCONTINUE

																			 //Aquí añadimos los elementos dentro del formulario
																			 //En este caso un Label

																			 //Empezamos con su localización:
		static int xloclabel = 100;
		static int yloclabel = 100;
		static int xsizelabel = 150;
		static int ysizelabel = 25;

		//Load Label1
		CreateWindowW(L"Static", L"Esto es un mensaje", // L"Static" no debe ser tocado, pero lo de la derecha es el texto
			WS_CHILD | WS_VISIBLE, //Siempre tiene que ser CHILD(hijo del formulario) y visible(si queremos que se vea xD)
			xloclabel, yloclabel, xsizelabel, ysizelabel, //Aquí van dimensiones de el label y loc. del label(Recomiendo modificar hasta que se vea todo) XD
			hwnd, (HMENU)1, NULL, NULL); //Lo que hay despues de HMENU es la ID del elemento, importante para "trabajar" con el elemento más adelante.

		break;
	}

	case WM_COMMAND:
	{
		//Por ahora no hay que tocar aquí
		break;
	}

	case WM_DESTROY:
	{
		//Aquí se destruye el form
		PostQuitMessage(0);
		break;
	}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}