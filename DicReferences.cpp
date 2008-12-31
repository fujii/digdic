// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * �Q�Ƃ̔z��N���X
 * 
 * $Date: 2006/06/05 05:03:24 $
 */
#include "DicReferences.h"

/**
 * (�ʂ̔z��̗v�f��)�ǉ�
 */
void DicReferences::Append(const DicReferences& a)
{
	WX_APPEND_ARRAY(*this, a);
}

/**
 * �S�č폜
 */
void DicReferences::DeleteAll()
{
	WX_CLEAR_ARRAY(*this);
}

/**
 * (Hit��)���݂��邩
 * 
 * @param hit ��r�Ώ�
 * @param max ��r���ő�
 * @return ���݂���:true
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
