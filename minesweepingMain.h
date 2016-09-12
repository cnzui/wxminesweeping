/***************************************************************
 * Name:      minesweepingMain.h
 * Purpose:   Defines Application Frame
 * Author:    Lupin Long (longxia102@gmail.com)
 * Created:   2013-04-09
 * Copyright: Lupin Long (http://www.cnzui.com)
 * License:
 **************************************************************/

#ifndef MINESWEEPINGMAIN_H
#define MINESWEEPINGMAIN_H

//(*Headers(minesweepingFrame)
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

struct Mine{
    int flag;   //>=10:mines,0<flag<10:mine number around,0:space
    int statu;  //0:closed,1:opened,2:sweeped
    bool tips;

    Mine()
    {
        flag=0;
        statu=0;
        tips=false;
    }
};

WX_DEFINE_ARRAY(Mine *, ArrayOfMines);


class minesweepingFrame: public wxFrame
{
public:
    int m_nRectUnit;
    int m_nRectSize;
    int m_nProportion;
    int m_nAllMineNum;
    int m_nCurMineNum;
    ArrayOfMines m_arrMines;
    bool m_bGameStatu;

public:
    void SetLevel(int level=0)
    {
        switch(level)
        {
        case 2:
            m_nRectUnit=20;
            m_nProportion=20;   //20%
            break;
        case 1:
            m_nRectUnit=18;
            m_nProportion=15;   //15%
            break;
        case 0:
        default:
            m_nRectUnit=16;
            m_nProportion=10;   //10%
            break;
        }
    }

    int GetLevel()
    {
        if(m_nRectUnit==16) return 0;
        if(m_nRectUnit==18) return 1;
        if(m_nRectUnit==20) return 2;

        return 0;
    }

    public:

        minesweepingFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~minesweepingFrame();
        void Init();
        void DrawGrid();
        void CreateMinesTips(int pos);
        int HitTest(wxPoint &point);
        void HitCheck(int pos);
        void FindSpaceNearby(int pos);
        void ShowTipsAround(int pos);
        bool EdgeCheck(int pos,int newpos);
        void OpenAll();

    private:

        //(*Handlers(minesweepingFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnMenuStartSelected(wxCommandEvent& event);
        void OnPaint(wxPaintEvent& event);
        void OnLeftDown(wxMouseEvent& event);
        void OnRightDown(wxMouseEvent& event);
        void OnRightUp(wxMouseEvent& event);
        void OnMenuSettintsSelected(wxCommandEvent& event);
        //*)

        //(*Identifiers(minesweepingFrame)
        static const long idMenuStart;
        static const long idMenuSettings;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(minesweepingFrame)
        wxMenuItem* MenuSettings;
        wxMenuItem* MenuItem3;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // MINESWEEPINGMAIN_H
