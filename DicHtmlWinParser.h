// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * DicHtmlWinParserクラス
 * 
 * $Date: 2007/03/25 15:27:24 $
 */
#ifndef _DICHTMLWINPARSER_H_
#define _DICHTMLWINPARSER_H_

#include <wx/html/winpars.h>

/**
 * DicHtmlWinParserクラス
 */
class DicHtmlWinParser : public wxHtmlWinParser {
public:
//    DicHtmlWinParser(wxHtmlWindow *wnd = NULL);
    DicHtmlWinParser(wxHtmlWindowInterface* wnd = NULL);
    ~DicHtmlWinParser() {};

protected:
    virtual void AddText(const wxChar* txt);

	virtual void GetWord(wxChar* out, const wxChar* txt, const wxChar** p);
	virtual int GetCharType(wxChar c);
	
protected:
    wxHtmlWordCell *m_lastWordCell;
};

#endif //_DICHTMLWINPARSER_H_
