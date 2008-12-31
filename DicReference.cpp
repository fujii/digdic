// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * �Q�ƃN���X
 * 
 * $Date: 2006/07/11 13:45:14 $
 */
#include "DicSubbook.h"
#include "DicReference.h"

/**
 * �R���X�g���N�^ (Reference)
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
 * �R���X�g���N�^ (Hit)
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
 * ���{�̑薼���擾
 */
wxString DicReference::GetSubbookTitle()
{
//	m_book->SetCurSubbook(m_subbook);
//	return m_book->GetCurSubbookTitle();
	return m_subbook->GetAlias();
}

/**
 * ���o�����擾
 */
wxString DicReference::GetHeading()
{
//	m_book->SetCurSubbook(m_subbook);
//	return m_book->GetHeading(&m_heading);
	return m_subbook->GetHeading(&m_heading);
}

/**
 * �e�L�X�g�f�[�^���擾
 */
wxString DicReference::GetText()
{
//	m_book->SetCurSubbook(m_subbook);
//	return m_book->GetText(&m_pos);
	return m_subbook->GetText(&m_pos);
}

/**
 * �O�̃e�L�X�g�f�[�^���擾
 */
wxString DicReference::GetPrevText()
{
	return m_subbook->GetPrevText();
}

/**
 * ���̃e�L�X�g�f�[�^���擾
 */
wxString DicReference::GetNextText()
{
	return m_subbook->GetNextText();
}

/**
 * ==���Z�q (Hit��r�p)
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
