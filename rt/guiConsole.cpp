#include "guiConsole.h"

HWND myconsole;
HDC mydc;

namespace rt {

	boolean doSomething = false;

	int GUImain() {
		doSomething = true;
		//Get a console handle
		myconsole = GetConsoleWindow();
		//Get a handle to device context
		mydc = GetDC(myconsole);
		RECT r;
		GetWindowRect(myconsole, &r); //stores the console's current dimensions

		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(myconsole, 0, 0, 1366, 768, FALSE);

		//ReleaseDC(myconsole, mydc);
		//std::cin.ignore();
		return 0;
	}

	int updateScreen(int width, int height, rt::RGBColor& color) {
		if (doSomething) {
			color = color.clamp();
			SetPixel(mydc, width, height, RGB(color.r * 255, color.g * 255, color.b * 255));
		}
		return 0;
	}

}
