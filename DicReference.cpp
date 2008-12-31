// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 参照クラス
 * 
 * $Date: 2006/07/11 13:45:14 $
 */
#include "DicSubbook.h"
#include "DicReference.h"

/**
 * コンストラクタ (Reference)
 */
DicReference::DicReference(DicSubbook* subbook, const EB_Position& pos) :
	m_subbook(subbook),
	m_pos(pos)
{
}
/*
DicReference::DicReference(DicBook* book, EB_Subbook_Code subbook, const EB_Position& pos) :
	m_book(book),
	m_subbook(subbook),
	m_pos(pos)
{
}
*/

/**
 * コンストラクタ (Hit)
 */
DicReference::DicReference(DicSubbook* subbook, const EB_Hit& hit) :
	m_subbook(subbook),
	m_pos(hit.text),
	m_heading(hit.heading)
{
}
/*
DicReference::DicReference(DicBook* book, EB_Subbook_Code subbook, const EB_Hit& hit) :
	m_book(book),
	m_subbook(subbook),
	m_pos(hit.text),
	m_heading(hit.heading)
{
}
*/

/**
 * 副本の題名を取得
 */
wxString DicReference::GetSubbookTitle()
{
//	m_book->SetCurSubbook(m_subbook);
//	return m_book->GetCurSubbookTitle();
	return m_subbook->GetAlias();
}

/**
 * 見出しを取得
 */
wxString DicReference::GetHeading()
{
//	m_book->SetCurSubbook(m_subbook);
//	return m_book->GetHeading(&m_heading);
	return m_subbook->GetHeading(&m_heading);
}

/**
 * テキストデータを取得
 */
wxString DicReference::GetText()
{
//	m_book->SetCurSubbook(m_subbook);
//	return m_book->GetText(&m_pos);
	return m_subbook->GetText(&m_pos);
}

/**
 * 前のテキストデータを取得
 */
wxString DicReference::GetPrevText()
{
	return m_subbook->GetPrevText();
}

/**
 * 次のテキストデータを取得
 */
wxString DicReference::GetNextText()
{
	return m_subbook->GetNextText();
}

/**
 * ==演算子 (Hit比較用)
 */
bool DicReference::operator==(DicReference& hit)
{
	if (m_subbook == hit.m_subbook
		&& m_subbook == hit.m_subbook
		&& m_pos.page == hit.m_pos.page
		&& m_pos.offset == hit.m_pos.offset
		&& ((m_heading.page == hit.m_heading.page
			&& m_heading.offset == hit.m_heading.offset)
			|| GetHeading() == hit.GetHeading())
		) {
		return true;
	}
	return false;
}
