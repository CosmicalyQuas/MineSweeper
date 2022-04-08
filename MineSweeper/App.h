#pragma once
#include "wx/wx.h"

class SweeperWindow; //predeclaring a class, pointer, make sure we include mainwindow in cpp


class App : public wxApp
{
private:
	SweeperWindow* sweeperWindow = nullptr;

public:
	App();
	~App();

	//virtual since our app needs to inherit from one of the wx classes
	virtual bool OnInit(); //place we can run things after app is running if necessary


};

