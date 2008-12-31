// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * ���������̒l���N���X
 * 
 * $Date: 2006/06/22 10:18:38 $
 */
 
#include "DicMultiCandidate.h"
#include "DicBook.h"

/**
 * �R���X�g���N�^(�O���[�v�Ȃ�)
 */
DicMultiCandidate::DicMultiCandidate(const char* data) :
	m_hasGroup(false)
{
	m_data = new char[::strlen(data) + 1];
	::strcpy(m_data, data);
}

/**
 * �R���X�g���N�^(�O���[�v����)
 */
DicMultiCandidate::DicMultiCandidate(const char* data, const EB_Position& groupPos) :
	m_hasGroup(true),
	m_groupPos(groupPos)
{
	m_data = new char[::strlen(data) + 1];
	::strcpy(m_data, data);
}

/**
 * �f�X�g���N�^
 */
DicMultiCandidate::~DicMultiCandidate()
{
	delete [] m_data;
}

/**
 * ��������擾
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
 * �O���[�v�����邩
 */
bool DicMultiCandidate::HasGroup()
{
	return m_hasGroup;
}

/**
 * �O���[�v�̈ʒu���擾
 */
EB_Position DicMultiCandidate::GetGroupPos()
{
	return m_groupPos;	
}

