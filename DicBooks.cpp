// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * �{�̔z��N���X
 * 
 * $Date: 2006/08/23 15:44:02 $
 */
#include "DicBooks.h"
#include "DicShare.h"

/**
 * �S�č폜
 */
void DicBooks::DeleteAll()
{
	WX_CLEAR_HASH_MAP(DicBooks, *this);
}

/**
 * ���݂��邩
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
