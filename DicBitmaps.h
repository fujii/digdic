// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * �r�b�g�}�b�v�̔z��(�}�b�v)�N���X
 * 
 * $Date: 2006/06/07 07:06:08 $
 */
#ifndef _DICBITMAPS_H_
#define _DICBITMAPS_H_

#include <wx/dynarray.h>
#include <wx/bitmap.h>

WX_DECLARE_STRING_HASH_MAP(wxBitmap*, DicBitmapMap);

/**
 * �r�b�g�}�b�v�̔z��(�}�b�v)�N���X
 */
class DicBitmaps : public DicBitmapMap {
public:
	virtual ~DicBitmaps() {};
	virtual void DeleteAll();
};

#endif //_DICBITMAPS_H_
