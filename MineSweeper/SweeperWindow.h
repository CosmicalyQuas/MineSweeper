#pragma once
#include "wx/wx.h"

class SweeperWindow : public wxFrame
{
public:
	int mineFieldWidth = 10;
	int mineFieldHeight = 10;
	wxButton** buttonArray;
	int* mineField = nullptr;
	bool bFirstClick = true; //populate minefield after they have clicked one mine

	SweeperWindow();
	~SweeperWindow();

	void OnButtonClicked(wxCommandEvent &evt);

	wxDECLARE_EVENT_TABLE();
};

