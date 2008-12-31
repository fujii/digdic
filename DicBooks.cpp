// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 本の配列クラス
 * 
 * $Date: 2006/08/23 15:44:02 $
 */
#include "DicBooks.h"
#include "DicShare.h"

/**
 * 全て削除
 */
void DicBooks::DeleteAll()
{
	WX_CLEAR_HASH_MAP(DicBooks, *this);
}

/**
 * 存在するか
 */
bool DicBooks::Exists(const wxString& path)
{
	wxFileName fn(path);
	fn.MakeAbsolute();
	if (find(fn.GetFullPath()) == end()) {
		return false;
	}
	return true;
}
