#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

//(*Headers(SettingsDialog)
#include <wx/sizer.h>
#include <wx/radiobut.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class SettingsDialog: public wxDialog
{
	public:

		SettingsDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~SettingsDialog();

		//(*Declarations(SettingsDialog)
		wxRadioButton* rdoLearner;
		wxButton* btnClose;
		wxButton* btnOK;
		wxRadioButton* rdoPlayer;
		wxRadioButton* rdoExpert;
		//*)

	protected:

		//(*Identifiers(SettingsDialog)
		static const long ID_RADIOLEARNER;
		static const long ID_RADIOPLAYER;
		static const long ID_RADIOEXPERT;
		static const long ID_BTNOK;
		static const long ID_BTNCLOSE;
		//*)

	private:

		//(*Handlers(SettingsDialog)
		void OnbtnOKClick(wxCommandEvent& event);
		void OnbtnCloseClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
