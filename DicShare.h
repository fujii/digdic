// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * ‹¤—L‚·‚é‚à‚Ì
 * 
 * $Date: 2007/10/31 16:13:50 $
 */
#ifndef DICSHARE_H_
#define DICSHARE_H_

#include <wx/confbase.h>
#include "DicBooks.h"
#include "DicSubbooks.h"
#include "DicGroups.h"
#include "DicReferences.h"
#include "DicHistory.h"
#include "DicBitmaps.h"

/**
 * ‹¤—L‚·‚é‚à‚Ì
 */
class DicShare
{
public:
	static void Clean();
	
	static void LoadConfig(wxConfigBase* config = NULL);
	static void SaveConfig(wxConfigBase* config = NULL);
	
public:
	static wxString iniFile;
	static DicBooks books;
	static DicSubbooks subbooks;
	static DicGroups groups;
	static DicReferences hits;
	static DicHistory history;
	static DicBitmaps bitmaps;
	static DicReferences references;
	
	static int pageMaxResults;
	static int pageMaxBytes;
	static int searchMaxResults;
	
	static wxString htmlHead;
	static wxString htmlFoot;
	static wxString keywordHead;
	static wxString keywordFoot;
	static wxString decorationHead;
	static wxString decorationFoot;
	static wxString emphasisHead;
	static wxString emphasisFoot;
	static wxString superscriptHead;
	static wxString superscriptFoot;
	static wxString subscriptHead;
	static wxString subscriptFoot;
	static wxString newLine;
	static wxString noNewlineHead;
	static wxString noNewlineFoot;
};

#endif /*DICSHARE_H_*/
