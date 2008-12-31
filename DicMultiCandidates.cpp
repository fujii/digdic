// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 複合検索の値候補の配列クラス
 * 
 * $Date: 2006/06/14 13:39:46 $
 */
#include "DicMultiCandidates.h"

/**
 * 全て削除
 */
void DicMultiCandidates::DeleteAll()
{
	WX_CLEAR_ARRAY(*this);
}
