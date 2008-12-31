// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 本の配列クラス
 * 
 * $Date: 2007/03/25 15:22:14 $
 */
#ifndef _DICBOOKS_H_
#define _DICBOOKS_H_

#include <wx/hashmap.h>

#include "DicBook.h"

WX_DECLARE_STRING_HASH_MAP(DicBook*, DicBookMap);

/**
 * 本の配列クラス
 */
class DicBooks : public DicBookMap {
public:
	virtual ~DicBooks() {};
	virtual void DeleteAll();
	virtual bool Exists(const wxString& path);
};

#endif //_DICBOOKS_H_
