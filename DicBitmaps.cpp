// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * �r�b�g�}�b�v�̔z��(�}�b�v)�N���X
 * 
 * $Date: 2006/06/05 05:03:24 $
 */
#include "DicBitmaps.h"

/**
 * �S�č폜
 */
void DicBitmaps::DeleteAll()
{
	WX_CLEAR_HASH_MAP(DicBitmaps, *this);
}
