// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * HTMLウィンドウクラス
 * 
 * $Date: 2007/10/01 13:04:41 $
 */
#include <wx/utils.h>
#include "DicHtmlWindow.h"
#include "DicShare.h"
#include "DicReferences.h"

/**
 * コンストラクタ
 */
DicHtmlWindow::DicHtmlWindow(wxWindow *parent, wxWindowID id,
                 const wxPoint& pos,
                 const wxSize& size,
                 long style,
                 const wxString& name)
{
    Init();
    Create(parent, id, pos, size, style, name);
}

/**
 * 初期化
 */
void DicHtmlWindow::Init()
{
	wxHtmlWindow::Init();
	delete m_Parser;
    m_Parser = new DicHtmlWinParser(this);
    m_Parser->SetFS(m_FS);
}

/**
 * リンククリック
 */
void DicHtmlWindow::OnLinkClicked(const wxHtmlLinkInfo& link)
{
	wxString href = link.GetHref();
	unsigned long idx;
	href.ToULong(&idx);
	DicReference* ref = new DicReference(*DicShare::references[idx]);

	wxBusyCursor wait;
	
//	DicShare::bitmaps.DeleteAll();
	DicShare::references.DeleteAll();
	
	DicShare::history.SetCurrent(ref);

	Freeze();
	SetPage(ref->GetText());
	Thaw();
}
