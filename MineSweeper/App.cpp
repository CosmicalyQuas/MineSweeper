#include "App.h"
#include "SweeperWindow.h"

wxIMPLEMENT_APP(App);

App::App()
{

}

App::~App()
{

}

bool App::OnInit()
{
	sweeperWindow = new SweeperWindow();
	sweeperWindow->Show();

	return true;
}