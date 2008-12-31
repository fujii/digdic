// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 参照の配列クラス
 * 
 * $Date: 2006/06/05 05:03:24 $
 */
#include "DicReferences.h"

/**
 * (別の配列の要素を)追加
 */
void DicReferences::Append(const DicReferences& a)
{
	WX_APPEND_ARRAY(*this, a);
}

/**
 * 全て削除
 */
void DicReferences::DeleteAll()
{
	WX_CLEAR_ARRAY(*this);
}

/**
 * (Hitが)存在するか
 * 
 * @param hit 比較対象
 * @param max 比較個数最大
 * @return 存在する:true
 */
bool DicReferences::Exists(DicReference* hit, int max)
{
	int end = GetCount() - 1;
//	for (size_t i = 0; i < GetCount(); ++i) {
	for (int i = end; i >= end - max; --i) {
		if (i < 0) {
			break;
		}
		if (*Item(i) == *hit) {
			return true;
		}
	}
	return false;
}
