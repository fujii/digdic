// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 履歴クラス
 * 
 * $Date: 2006/06/05 12:07:15 $
 */
#include "DicHistory.h"

/**
 * コンストラクタ
 */
DicHistory::DicHistory() :
	m_pos(0)
{
}

/**
 * 前の要素があるか
 */
bool DicHistory::HasPrev()
{
	if (m_pos == 0) {
		return false;
	}
	return true;
}

/**
 * 次の要素があるか
 */
bool DicHistory::HasNext()
{
	if (!GetCount()
		|| m_pos == GetCount() - 1) {
		return false;
	}
	return true;
}

/**
 * 現在の要素を設定
 */
void DicHistory::SetCurrent(DicReference* ref)
{
	if (GetCount()) {
		// 現在位置が最後の要素でない場合、現在位置より後の要素を消す。
		unsigned int last = GetCount() - 1;
		if (m_pos < last) {
			for (unsigned int i = m_pos + 1; i <= last; ++i) {
				delete Item(i);
			}
			RemoveAt(m_pos + 1, last - m_pos);
		}
	}
	
	// 末尾に追加する。
	Add(ref);
	m_pos = GetCount() - 1;
}

/**
 * 現在の要素を取得
 */
DicReference* DicHistory::GetCurrent()
{
	return Item(m_pos);
}

/**
 * 戻る
 */
DicReference* DicHistory::Back()
{
	--m_pos;
	return GetCurrent();
}

/**
 * 進む
 */
DicReference* DicHistory::Forward()
{
	++m_pos;
	return GetCurrent();
}
