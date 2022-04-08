#include "SweeperWindow.h"

wxBEGIN_EVENT_TABLE(SweeperWindow, wxFrame)
wxEND_EVENT_TABLE()

SweeperWindow::SweeperWindow() : wxFrame(nullptr, wxID_ANY, "Main", wxPoint(200, 200), wxSize(400, 400))
{
	buttonArray = new wxButton*[mineFieldWidth * mineFieldHeight];
	wxGridSizer *grid = new wxGridSizer(mineFieldWidth, mineFieldHeight, 0, 0);

	mineField = new int[mineFieldWidth * mineFieldHeight];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < mineFieldWidth; x++)
	{
		for (int y = 0; y < mineFieldHeight; y++)
		{
			buttonArray[y * mineFieldWidth + x] = new wxButton(this, 10000 + (y * mineFieldWidth + x));
			buttonArray[y*mineFieldWidth+x]->SetFont(font);
			grid->Add(buttonArray[y * mineFieldWidth + x], 1, wxEXPAND | wxALL);

			buttonArray[y * mineFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &SweeperWindow::OnButtonClicked, this);
			mineField[y * mineFieldWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();
}

SweeperWindow::~SweeperWindow()
{
	delete[]buttonArray;
}

void SweeperWindow::OnButtonClicked(wxCommandEvent &evt)
{
	int x = (evt.GetId() - 10000) % mineFieldWidth;
	int y = (evt.GetId() - 10000) / mineFieldWidth;

	if (bFirstClick)
	{
		int mines = 30;

		while (mines)
		{
			int rx = rand() % mineFieldWidth;
			int ry = rand() % mineFieldHeight;

			if (mineField[ry * mineFieldWidth + rx] == 0 && rx != x && ry != y)
			{
				mineField[ry * mineFieldWidth + rx] = -1;
				mines--;
			}
		}

		bFirstClick = false;
	}

	buttonArray[y * mineFieldWidth + x]->Enable(false);

	if (mineField[y * mineFieldWidth + x] == -1)
	{
		wxMessageBox("BOOOOM!! Game Over.");

		bFirstClick = true;
		for (int x = 0; x < mineFieldWidth; x++)
		{
			for (int y = 0; y < mineFieldHeight; y++)
			{
				mineField[y * mineFieldWidth + x] = 0;
				buttonArray[y * mineFieldWidth + x]->SetLabel(""); //number of mines around clicked location
				buttonArray[y * mineFieldWidth + x]->Enable(true);
				buttonArray[y * mineFieldWidth + x]->SetBackgroundColour(wxNullColour);
			}
		}
	}
	else
	{	//count mines around clicked square
		int mineCount = 0;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + i < mineFieldWidth && y + j >= 0 && y + j < mineFieldHeight)
				{
					if (mineField[(y + j) * mineFieldWidth + (x + i)] == -1)
					{
						mineCount++;
					}
				}
			}
		}

		if (mineCount > 0)
		{
			buttonArray[y * mineFieldWidth + x]->SetLabel(std::to_string(mineCount));
		}

		if (mineCount == 2)
		{
			buttonArray[y * mineFieldWidth + x]->SetBackgroundColour(*wxYELLOW);
		}
		else if (mineCount >= 3)
		{
			buttonArray[y * mineFieldWidth + x]->SetBackgroundColour(*wxRED);
		}
	}

	evt.Skip();
}