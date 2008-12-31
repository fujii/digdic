// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * ビットマップの配列(マップ)クラス
 * 
 * $Date: 2006/06/07 07:06:08 $
 */
#ifndef _DICBITMAPS_H_
#define _DICBITMAPS_H_

#include <wx/dynarray.h>
#include <wx/bitmap.h>

WX_DECLARE_STRING_HASH_MAP(wxBitmap*, DicBitmapMap);

/**
 * ビットマップの配列(マップ)クラス
 */
class DicBitmaps : public DicBitmapMap {
public:
	virtual ~DicBitmaps() {};
	virtual void DeleteAll();
};

#endif //_DICBITMAPS_H_
