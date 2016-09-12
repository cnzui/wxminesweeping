/***************************************************************
 * Name:      minesweepingApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Lupin Long (longxia102@gmail.com)
 * Created:   2013-04-09
 * Copyright: Lupin Long (http://www.cnzui.com)
 * License:
 **************************************************************/

#include "minesweepingApp.h"

//(*AppHeaders
#include "minesweepingMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(minesweepingApp);

bool minesweepingApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	minesweepingFrame* Frame = new minesweepingFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)

    return wxsOK;

}
