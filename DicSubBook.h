// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 副本クラス
 * 
 * $Date: 2007/08/05 13:11:28 $
 */
#ifndef DICSUBBOOK_H_
#define DICSUBBOOK_H_

#include <wx/filename.h>
#include <eb/eb.h>
#include <eb/error.h>
#include "DicBook.h"
#include "DicReferences.h"
#include "DicMultiCandidates.h"
#include "DicHook.h"
#include "DicCandidateHook.h"

/**
 * 副本クラス
 */
class DicSubbook {
public:
	DicSubbook();
//	DicSubbook(DicBook* book, EB_Subbook_Code subbook);
	virtual ~DicSubbook() {};
	virtual void SetBookPath(const wxString& path);
	virtual void SetAppendixPath(const wxString& path);
	virtual void SetSubbookCode(EB_Subbook_Code subbook);
	virtual void SetAlias(const wxString& alias);
	virtual void Enable(bool b = true);
	virtual wxString GetBookPath();
	virtual wxString GetAppendixPath();
	virtual EB_Subbook_Code GetSubbookCode();
	virtual wxString GetAlias();
	virtual bool IsEnabled();
	virtual bool Bind();
	virtual DicBook* GetBook();
	virtual bool HasWordSearch();
	virtual bool HasEndWordSearch();
	virtual bool HasExactWordSearch();
	virtual bool HasKeywordSearch();
	virtual bool hasCrossSearch();
	virtual bool HasMultiSearch();
	virtual bool HasCopyright();
	virtual bool HasMenu();
	virtual int SearchWord(const wxString& key, DicReferences& hits);
	virtual int SearchEndWord(const wxString& key, DicReferences& hits);
	virtual int SearchExactWord(const wxString& key, DicReferences& hits);
	virtual int SearchKeyword(const wxString& key, DicReferences& hits);
	virtual int SearchCross(const wxString& key, DicReferences& hits);
	virtual int SearchMulti(EB_Multi_Search_Code multiId, const wxArrayString& keys, DicReferences& hits);
	virtual int GetMultiCount();
	virtual EB_Multi_Search_Code GetMultiCode(int index);
	virtual wxString GetMultiTitle(EB_Multi_Search_Code code);
	virtual int GetMultiEntryCount(EB_Multi_Search_Code code);
	virtual wxString GetMultiEntryLabel(EB_Multi_Search_Code code, int index);
	virtual bool HasMultiEntryCandidates(EB_Multi_Search_Code code, int index);
	virtual EB_Position GetMultiEntryCandidatesPos(EB_Multi_Search_Code code, int index);
	virtual DicMultiCandidates GetMultiEntryCandidates(EB_Position* pos);
	virtual DicReference* GetCopyright();
	virtual DicReference* GetMenu();
	virtual wxString GetHeading(EB_Position* pos);
	virtual wxString GetText(EB_Position* pos);
	virtual wxString GetPrevText();
	virtual wxString GetNextText();

protected:
	virtual void CheckCurVol();
	virtual int GetHits(DicReferences& hits);

	static void GetSearchWord(char* dst, int len, const wxString& src);
	
protected:
	wxString m_bookPath;
	wxString m_appendixPath;
	EB_Subbook_Code m_subbook;
	wxString m_alias;
	bool m_enabled;
	DicBook* m_dicBook;
	EB_Book* m_book;
	DicHook m_hook;
	DicCandidateHook m_candidateHook;
	EB_Position m_curPos;
	EB_Position m_nextPos;
};

#endif /*DICSUBBOOK_H_*/
