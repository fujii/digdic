// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 参照クラス
 * 
 * $Date: 2006/07/11 13:45:14 $
 */
#ifndef _DICREFERENCE_H_
#define _DICREFERENCE_H_

#include <eb/eb.h>
#include <wx/string.h>

class DicSubbook;

/**
 * 参照クラス
 */
class DicReference {
public:
	DicReference(DicSubbook* subbook, const EB_Position& pos);
	DicReference(DicSubbook* subbook, const EB_Hit& hit);
//	DicReference(DicBook* book, EB_Subbook_Code subbook, const EB_Position& pos);
//	DicReference(DicBook* book, EB_Subbook_Code subbook, const EB_Hit& hit);
	virtual ~DicReference() {};
	virtual wxString GetSubbookTitle();
	virtual wxString GetHeading();
	virtual wxString GetText();
	virtual wxString GetPrevText();
	virtual wxString GetNextText();
	virtual bool operator==(DicReference& hit);

protected:
	DicSubbook* m_subbook;
//	DicBook* m_book;
//	EB_Subbook_Code m_subbook;
	EB_Position m_pos;
	EB_Position m_heading;
};

#endif //_DICREFERENCE_H_
