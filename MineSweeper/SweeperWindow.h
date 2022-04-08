#pragma once
#include "wx/wx.h"

class SweeperWindow : public wxFrame
{
private:
	wxButton* button = nullptr;
	wxButton* buttonMe = nullptr;
	wxTextCtrl* text = nullptr;
public:
	int nFieldWidth = 10;
	int nFieldHeight = 10;
	wxButton** btn;
	int* nField = nullptr;
	bool bFirstClick = true; //populate minefield after they have clicked one mine

	SweeperWindow();
	~SweeperWindow();

	void OnButtonClicked(wxCommandEvent &evt);

	wxDECLARE_EVENT_TABLE();
};

