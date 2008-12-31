// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * プロパティグリッドクラス
 * 
 * $Date: 2007/10/01 13:04:41 $
 */
#ifndef DICPROPERTYGRID_H_
#define DICPROPERTYGRID_H_

#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>

/**
 * プロパティグリッドクラス
 */
class DicPropertyGrid : public wxPropertyGrid {
public:
    DicPropertyGrid() : wxPropertyGrid() {};
    DicPropertyGrid(wxWindow *parent, wxWindowID id = wxID_ANY,
					const wxPoint& pos = wxDefaultPosition,
					const wxSize& size = wxDefaultSize,
					long style = wxPG_DEFAULT_STYLE,
					const wxChar* name = wxPropertyGridNameStr) :
		wxPropertyGrid(parent, id, pos, size, style, name) {};
    virtual ~DicPropertyGrid() {};
    virtual void DoSetVirtualSize(int x, int y);
	virtual void CommitChanges();
};

#endif /*DICPROPERTYGRID_H_*/
