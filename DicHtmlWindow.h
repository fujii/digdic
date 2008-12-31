// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * HTMLウィンドウクラス
 * 
 * $Date: 2006/06/07 07:06:08 $
 */
#ifndef _DICHTMLWINDOW_H_
#define _DICHTMLWINDOW_H_

#include <wx/html/htmlwin.h>
#include "DicHtmlWinParser.h"

/**
 * HTMLウィンドウクラス
 */
class DicHtmlWindow : public wxHtmlWindow {
public:
    DicHtmlWindow(wxWindow *parent, wxWindowID id = wxID_ANY,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize,
                 long style = wxHW_DEFAULT_STYLE,
                 const wxString& name = wxT("htmlWindow"));
    virtual ~DicHtmlWindow() {};
	virtual void Init();
	virtual void OnLinkClicked(const wxHtmlLinkInfo& link);
};

#endif //_DICHTMLWINDOW_H_
