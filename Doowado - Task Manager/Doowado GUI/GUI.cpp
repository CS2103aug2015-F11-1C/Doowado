#include "GUI.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	DoowadoGUI::GUI mainWindow;
	Application::Run(%mainWindow);

	return 0;
}