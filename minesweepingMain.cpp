/***************************************************************
 * Name:      minesweepingMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Lupin Long (longxia102@gmail.com)
 * Created:   2013-04-09
 * Copyright: Lupin Long (http://www.cnzui.com)
 * License:
 **************************************************************/

#include "minesweepingMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(minesweepingFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/dcclient.h>
#include "SettingsDialog.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxT("Mine-Sweeping 1.0 "));

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(minesweepingFrame)
const long minesweepingFrame::idMenuStart = wxNewId();
const long minesweepingFrame::idMenuSettings = wxNewId();
const long minesweepingFrame::idMenuQuit = wxNewId();
const long minesweepingFrame::idMenuAbout = wxNewId();
const long minesweepingFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(minesweepingFrame,wxFrame)
    //(*EventTable(minesweepingFrame)
    //*)
END_EVENT_TABLE()

minesweepingFrame::minesweepingFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(minesweepingFrame)
    wxMenuItem* MenuAbout;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;
    wxMenuItem* MenuQuit;

    Create(parent, id, _("Mine-Sweeping"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxDEFAULT_FRAME_STYLE|wxCLOSE_BOX|wxMINIMIZE_BOX, _T("id"));
    SetClientSize(wxSize(336,311));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, idMenuStart, _("Start\tF5"), _("Start game"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuSettings = new wxMenuItem(Menu1, idMenuSettings, _("Settings\tF3"), _("Game Settings"), wxITEM_NORMAL);
    Menu1->Append(MenuSettings);
    MenuQuit = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuQuit);
    MenuBar1->Append(Menu1, _("&Game"));
    Menu2 = new wxMenu();
    MenuAbout = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("About this application"), wxITEM_NORMAL);
    Menu2->Append(MenuAbout);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(idMenuStart,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&minesweepingFrame::OnMenuStartSelected);
    Connect(idMenuSettings,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&minesweepingFrame::OnMenuSettintsSelected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&minesweepingFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&minesweepingFrame::OnAbout);
    Connect(wxEVT_PAINT,(wxObjectEventFunction)&minesweepingFrame::OnPaint);
    Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&minesweepingFrame::OnLeftDown);
    Connect(wxEVT_RIGHT_DOWN,(wxObjectEventFunction)&minesweepingFrame::OnRightDown);
    Connect(wxEVT_RIGHT_UP,(wxObjectEventFunction)&minesweepingFrame::OnRightUp);
    //*)

    m_bGameStatu=false;
    SetLevel();
    this->Center();
}

minesweepingFrame::~minesweepingFrame()
{
    //(*Destroy(minesweepingFrame)
    //*)
    if(m_arrMines.GetCount()>0)
    {
        m_arrMines.Clear();
    }
}

void minesweepingFrame::Init()
{
    this->SetClientSize(wxSize(m_nRectUnit*30,m_nRectUnit*30));

    m_nRectSize=m_nRectUnit*m_nRectUnit;

    m_arrMines.Clear();
    for(int i=0;i<m_nRectSize;i++)
    {
        m_arrMines.Add(new Mine);
    }

    srand((int)time(0));

    m_nAllMineNum=m_nRectSize*m_nProportion/100;
    m_nCurMineNum=m_nAllMineNum;

    for(int i=0;i<m_nAllMineNum;i++)
    {
        int pos=rand()%m_nRectSize;
        m_arrMines.Item(pos)->flag=10;
    }

    //make nums around of the mines
    for(int i=0;i<m_nRectSize;i++)
    {
        if(m_arrMines.Item(i)->flag>=10)
        {
            int aroundpos[8]= { i-(m_nRectUnit+1),i-m_nRectUnit,i-(m_nRectUnit-1),     //up
                                i-1,i+1,                                               //left and right
                                i+(m_nRectUnit-1),i+m_nRectUnit,i+(m_nRectUnit+1)      //down
                            };

            for(int j=0;j<8;j++)
            {
                //when in the edge
                if(EdgeCheck(i,aroundpos[j]))   continue;
                CreateMinesTips(aroundpos[j]);
            }
        }
    }
}

void minesweepingFrame::DrawGrid()
{
    wxClientDC dc(this);

    int row=0;
    int col=0;
    for(int i=0;i<m_nRectSize;i++)
    {
        if(m_arrMines.Item(i)->flag>=0 && m_arrMines.Item(i)->statu>0)
        {
            dc.SetBrush(*wxLIGHT_GREY_BRUSH);
            dc.SetPen(*wxBLACK_PEN);
            dc.DrawRectangle(wxPoint(col*30,row*30),wxSize(30,30));

                wxString gridstr=wxString::Format("%d",m_arrMines.Item(i)->flag);
                if(m_arrMines.Item(i)->flag<=0)
                {
                    gridstr="";
                }

                if(m_arrMines.Item(i)->flag>=10)
                {
                    if(m_arrMines.Item(i)->statu==1)
                    {
                        gridstr="œ";
                    }
                    else
                    {
                        gridstr="~";
                    }
                }
                else
                {
                    if(m_arrMines.Item(i)->statu==2)
                    {
                        gridstr="~";
                    }
                }

                dc.SetFont(wxFont(14,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD));
                dc.SetTextForeground(wxColor(80,160,50));
                if(m_arrMines.Item(i)->flag>=10 || m_arrMines.Item(i)->statu==2)
                {
                    dc.SetTextForeground(*wxRED);
                }

                dc.DrawText(gridstr,col*30+8,row*30+8);

        }
        else
        {
            dc.SetBrush(*wxMEDIUM_GREY_BRUSH);
            if(m_arrMines.Item(i)->tips)
            {
                dc.SetPen(*wxWHITE_PEN);
            }
            else
            {
                dc.SetPen(*wxBLACK_PEN);
            }
            dc.DrawRectangle(wxPoint(col*30,row*30),wxSize(30,30));

            if(m_arrMines.Item(i)->statu==2)
            {
                dc.SetFont(wxFont(14,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD));
                dc.SetTextForeground(*wxRED);
                dc.DrawText("~",col*30+8,row*30+8);
            }
        }

        if((i+1)%m_nRectUnit==0)
        {
            row++;
            col=0;
        }
        else
        {
            col++;
        }
    }

    //show status
    StatusBar1->SetStatusText(wxString::Format("Total %dC%d left.",m_nAllMineNum,m_nCurMineNum));
}

void minesweepingFrame::CreateMinesTips(int pos)
{
    if(pos>0 && pos<m_nRectSize)
    {
        if(m_arrMines.Item(pos)->flag<10)
        {
            m_arrMines.Item(pos)->flag++;
        }
    }
}

void minesweepingFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void minesweepingFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("About the game..."));
}

void minesweepingFrame::OnMenuStartSelected(wxCommandEvent& event)
{
    if(!m_bGameStatu)
    {
        Init();
        DrawGrid();
        m_bGameStatu=true;
    }
    else
    {
        if(wxMessageBox("Game not finished, sure to restart?","Confirm...",wxYES_NO|wxCENTER)==wxYES)
        {
            Init();
            DrawGrid();
        }
    }
}

void minesweepingFrame::OnPaint(wxPaintEvent& event)
{
    if(m_arrMines.GetCount()!=0)
    {
        DrawGrid();
    }
}

void minesweepingFrame::OnLeftDown(wxMouseEvent& event)
{
    if(!m_bGameStatu)   return;

    wxPoint point=event.GetPosition();
    int pos=HitTest(point);
    HitCheck(pos);
}

int minesweepingFrame::HitTest(wxPoint &point)
{
    if(!m_bGameStatu)   return -1;

    int row=0;
    int col=0;
    for(int i=0;i<m_nRectSize;i++)
    {
        if(point.x>=30*col && point.x<30*(col+1))
        {
            if(point.y>=30*row && point.y<30*(row+1))
            {
                //grid position finded
                return i;
            }
        }

        if((i+1)%m_nRectUnit==0)
        {
            row++;
            col=0;
        }
        else
        {
            col++;
        }
    }
    return -1;
}

void minesweepingFrame::HitCheck(int pos)
{
    if(!m_bGameStatu)   return;
    if(pos<0 || pos>m_nRectSize) return;

    if(m_arrMines.Item(pos)->statu==0)
    {
        m_arrMines.Item(pos)->statu=1;
        if(m_arrMines.Item(pos)->flag>=10)
        {
            OpenAll();
            wxMessageBox("It's a mine,you lost! ");
            m_bGameStatu=false;

        }
        else if(m_arrMines.Item(pos)->flag<=1)
        {
            //find other space grid nearby
            FindSpaceNearby(pos);
        }
    }
    DrawGrid();
}

void minesweepingFrame::FindSpaceNearby(int pos)
{
    if(!m_bGameStatu)   return;
    if(pos<0 || pos>m_nRectSize) return;

    int newpos[4]={pos-m_nRectUnit,pos-1,pos+1,pos+m_nRectUnit};
    for(int i=0;i<4;i++)
    {
        if(newpos[i]>=0 && newpos[i]<m_nRectSize)
        {
            //when in the edge
            if(EdgeCheck(pos,newpos[i]))   continue;

            if(m_arrMines.Item(newpos[i])->flag==0 && m_arrMines.Item(newpos[i])->statu==0)
            {
                m_arrMines.Item(newpos[i])->statu=1;
                FindSpaceNearby(newpos[i]);
            }

            //show simple 1
            if(m_arrMines.Item(newpos[i])->flag==1 && m_arrMines.Item(newpos[i])->statu==0)
            {
                m_arrMines.Item(newpos[i])->statu=1;
            }
        }
    }
}

void minesweepingFrame::ShowTipsAround(int pos)
{
    if(!m_bGameStatu)   return;
    if(pos<0 || pos>m_nRectSize) return;

    int newpos[8]={pos-(m_nRectUnit+1),pos-m_nRectUnit,pos-(m_nRectUnit-1),pos-1,pos+1,pos+(m_nRectUnit-1),pos+m_nRectUnit,pos+(m_nRectUnit+1)};
    for(int i=0;i<8;i++)
    {
        //when in the edge
        if(EdgeCheck(pos,newpos[i]))   continue;

        if(m_arrMines.Item(newpos[i])->statu==0)
        {
            m_arrMines.Item(newpos[i])->tips=true;
        }
    }
}

void minesweepingFrame::OnRightDown(wxMouseEvent& event)
{
    if(!m_bGameStatu)   return;

    //show around
    wxPoint point=event.GetPosition();
    int pos=HitTest(point);
    if(pos<0 || pos>m_nRectSize) return;

    if(m_arrMines.Item(pos)->statu==1)  //if has opened
    {
        if(m_arrMines.Item(pos)->flag>0 && m_arrMines.Item(pos)->flag<10)
        {
            ShowTipsAround(pos);
        }
    }
    else
    {
        if(m_arrMines.Item(pos)->statu!=2)
        {
            //mine sweeped
            m_arrMines.Item(pos)->statu=2;
            if(m_nCurMineNum>=1) m_nCurMineNum--;

            //check result
            bool finished=true;
            for(int i=0;i<m_nRectSize;i++)
            {
                if(m_arrMines.Item(i)->flag==10 && m_arrMines.Item(i)->statu!=2)
                {
                    finished=false;
                    break;
                }
            }

            if(finished)
            {
                OpenAll();

                wxMessageBox("Congratulations! You have sweep all the mines!");
                m_bGameStatu=false;
            }
        }
        else
        {
            //mine cancel sweeped
            m_arrMines.Item(pos)->statu=0;
            if(m_nCurMineNum<m_nRectSize) m_nCurMineNum++;
        }
    }

    DrawGrid();

}

void minesweepingFrame::OnRightUp(wxMouseEvent& event)
{
    if(!m_bGameStatu)   return;

    //reset tips
    for(int i=0;i<m_nRectSize;i++)
    {
        m_arrMines.Item(i)->tips=false;
    }
    DrawGrid();
}

bool minesweepingFrame::EdgeCheck(int pos,int newpos)
{
    if(pos%m_nRectUnit==0)   //left edge
    {
        if(newpos==pos-(m_nRectUnit+1) || newpos==pos-1 || newpos==pos+(m_nRectUnit-1))  return true;
    }
    else if((pos+1)%m_nRectUnit==0)   //right edge
    {
        if(newpos==pos-(m_nRectUnit-1) || newpos==pos+1 || newpos==pos+(m_nRectUnit+1))  return true;
    }

    if(pos-m_nRectUnit<0)    //up edge
    {
        if(newpos==pos-(m_nRectUnit+1) || newpos==pos-m_nRectUnit || newpos==pos-(m_nRectUnit-1))  return true;
    }

    if(pos+m_nRectUnit>=m_nRectSize) //down edge
    {
        if(newpos==pos+(m_nRectUnit+1) || newpos==pos+m_nRectUnit || newpos==pos+(m_nRectUnit-1))  return true;
    }

    return false;
}

void minesweepingFrame::OpenAll()
{
    //set all mines statu to 1
    for(int i=0;i<m_nRectSize;i++)
    {
        if(m_arrMines.Item(i)->statu==0)
        {
            m_arrMines.Item(i)->statu=1;
        }
    }
}

void minesweepingFrame::OnMenuSettintsSelected(wxCommandEvent& event)
{
    if(!m_bGameStatu)
    {
        SettingsDialog *dlg=new SettingsDialog(this);
        dlg->ShowModal();
    }
    else
    {
        wxMessageBox("Game not finished,settings will not effective!");
    }
}
