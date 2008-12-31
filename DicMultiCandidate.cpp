// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 複合検索の値候補クラス
 * 
 * $Date: 2006/06/22 10:18:38 $
 */
 
#include "DicMultiCandidate.h"
#include "DicBook.h"

/**
 * コンストラクタ(グループなし)
 */
DicMultiCandidate::DicMultiCandidate(const char* data) :
	m_hasGroup(false)
{
	m_data = new char[::strlen(data) + 1];
	::strcpy(m_data, data);
}

/**
 * コンストラクタ(グループあり)
 */
DicMultiCandidate::DicMultiCandidate(const char* data, const EB_Position& groupPos) :
	m_hasGroup(true),
	m_groupPos(groupPos)
{
	m_data = new char[::strlen(data) + 1];
	::strcpy(m_data, data);
}

/**
 * デストラクタ
 */
DicMultiCandidate::~DicMultiCandidate()
{
	delete [] m_data;
}

/**
 * 文字列を取得
 */
wxString DicMultiCandidate::DicMultiCandidate::GetString()
{
	wxString str(m_data, DicBook::convEuc);
	if (str == wxT("")) {
		str = wxT("?");
	}
	return str;
}

/**
 * グループがあるか
 */
bool DicMultiCandidate::HasGroup()
{
	return m_hasGroup;
}

/**
 * グループの位置を取得
 */
EB_Position DicMultiCandidate::GetGroupPos()
{
	return m_groupPos;	
}

