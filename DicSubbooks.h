// Copyright (C) 2006-2007 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 副本の配列クラス
 * 
 * $Date: 2007/10/31 16:13:50 $
 */
#ifndef DICSUBBOOKS_H_
#define DICSUBBOOKS_H_

#include <wx/confbase.h>
#include <wx/dynarray.h>
#include <wx/dir.h>
#include <wx/progdlg.h>
#include "DicSubbook.h"

WX_DEFINE_ARRAY(DicSubbook*, DicSubbookArray);

/**
 * 副本の配列クラス
 */
class DicSubbooks : public DicSubbookArray {
public:
	virtual ~DicSubbooks() {};
	virtual void SetName(const wxString& name);
	virtual wxString GetName();
	virtual void DeleteAll();
	virtual void EnableAll(bool b = true);
	virtual void LoadConfig(wxConfigBase* config = NULL, bool bind = true);
	virtual void SaveConfig(wxConfigBase* config = NULL);
	virtual bool SearchBook();

protected:
	wxString m_name;
};

/**
 * ディレクトリトラバーサ
 */
class DicDirTraverser : public wxDirTraverser
{
public:
	DicDirTraverser(DicSubbooks* subbooks, wxProgressDialog* pd, bool automatic = false);
	virtual wxDirTraverseResult OnFile(const wxString& filename);
    virtual wxDirTraverseResult OnDir(const wxString& dirname);
	virtual bool IsAdded();
	
protected:
	DicSubbooks* m_subbooks;
	wxProgressDialog* m_pd;
	bool m_automatic;
	int m_count;
	bool m_added;
};

#endif /*DICSUBBOOKS_H_*/
