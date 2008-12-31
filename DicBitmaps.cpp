// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * ビットマップの配列(マップ)クラス
 * 
 * $Date: 2006/06/05 05:03:24 $
 */
#include "DicBitmaps.h"

/**
 * 全て削除
 */
void DicBitmaps::DeleteAll()
{
	WX_CLEAR_HASH_MAP(DicBitmaps, *this);
}
