// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 本クラス
 * 
 * $Date: 2006/07/11 13:45:14 $
 */
#ifndef _DICBOOK_H_
#define _DICBOOK_H_

#include <wx/strconv.h>
#include <wx/filename.h>
#include <eb/eb.h>
#include <eb/error.h>

/**
 * 本クラス
 */
class DicBook {
public:
	DicBook();
	virtual ~DicBook();
	virtual EB_Book* GetEbBook();
	virtual EB_Error_Code Bind(const wxString& path);
	virtual wxFileName GetPath();
	virtual int GetSubbookCount();
	virtual EB_Subbook_Code GetSubbook(int index);
	virtual void SetCurSubbook(EB_Subbook_Code code);
	virtual EB_Subbook_Code GetCurSubbook();
	virtual wxString GetCurSubbookTitle();
	virtual void CheckCurVol();

public:	
	static wxCSConv convEuc;

protected:
	wxFileName m_fn;
    EB_Book m_book;
    EB_Subbook_Code m_subbooks[EB_MAX_SUBBOOKS];
    int m_subbookCount;
};

#endif //_DICBOOK_H_
