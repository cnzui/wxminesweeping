#include "SettingsDialog.h"

//(*InternalHeaders(SettingsDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "minesweepingMain.h"

//(*IdInit(SettingsDialog)
const long SettingsDialog::ID_RADIOLEARNER = wxNewId();
const long SettingsDialog::ID_RADIOPLAYER = wxNewId();
const long SettingsDialog::ID_RADIOEXPERT = wxNewId();
const long SettingsDialog::ID_BTNOK = wxNewId();
const long SettingsDialog::ID_BTNCLOSE = wxNewId();
//*)

BEGIN_EVENT_TABLE(SettingsDialog,wxDialog)
	//(*EventTable(SettingsDialog)
	//*)
END_EVENT_TABLE()

SettingsDialog::SettingsDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(SettingsDialog)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxStaticBoxSizer* StaticBoxSizer1;

	Create(parent, id, _("Game Settings"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	SetMinSize(wxSize(-1,-1));
	SetMaxSize(wxSize(-1,-1));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Game level"));
	rdoLearner = new wxRadioButton(this, ID_RADIOLEARNER, _("Learner"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOLEARNER"));
	rdoLearner->SetValue(true);
	StaticBoxSizer1->Add(rdoLearner, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	rdoPlayer = new wxRadioButton(this, ID_RADIOPLAYER, _("Player"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOPLAYER"));
	StaticBoxSizer1->Add(rdoPlayer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	rdoExpert = new wxRadioButton(this, ID_RADIOEXPERT, _("Expert"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOEXPERT"));
	StaticBoxSizer1->Add(rdoExpert, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	btnOK = new wxButton(this, ID_BTNOK, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTNOK"));
	BoxSizer2->Add(btnOK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnClose = new wxButton(this, ID_BTNCLOSE, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTNCLOSE"));
	BoxSizer2->Add(btnClose, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BTNOK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SettingsDialog::OnbtnOKClick);
	Connect(ID_BTNCLOSE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SettingsDialog::OnbtnCloseClick);
	//*)

	this->CenterOnScreen();

	int level=((minesweepingFrame*)parent)->GetLevel();
	if(level==0)    rdoLearner->SetValue(true);
	if(level==1)    rdoPlayer->SetValue(true);
	if(level==2)    rdoExpert->SetValue(true);

}

SettingsDialog::~SettingsDialog()
{
	//(*Destroy(SettingsDialog)
	//*)
}


void SettingsDialog::OnbtnOKClick(wxCommandEvent& event)
{
    wxWindow *win=this->GetParent();
    if(win==NULL)   return;

    if(rdoLearner->GetValue())
    {
        ((minesweepingFrame*)win)->SetLevel(0);
    }
    else if(rdoPlayer->GetValue())
    {
        ((minesweepingFrame*)win)->SetLevel(1);
    }
    else
    {
        ((minesweepingFrame*)win)->SetLevel(2);
    }

    this->Close();
}

void SettingsDialog::OnbtnCloseClick(wxCommandEvent& event)
{
    this->Close();
}
