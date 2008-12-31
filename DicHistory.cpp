// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * �����N���X
 * 
 * $Date: 2006/06/05 12:07:15 $
 */
#include "DicHistory.h"

/**
 * �R���X�g���N�^
 */
DicHistory::DicHistory() :
	m_pos(0)
{
}

/**
 * �O�̗v�f�����邩
 */
bool DicHistory::HasPrev()
{
	if (m_pos == 0) {
		return false;
	}
	return true;
}

/**
 * ���̗v�f�����邩
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
 * ���݂̗v�f��ݒ�
 */
void DicHistory::SetCurrent(DicReference* ref)
{
	if (GetCount()) {
		// ���݈ʒu���Ō�̗v�f�łȂ��ꍇ�A���݈ʒu����̗v�f�������B
		unsigned int last = GetCount() - 1;
		if (m_pos < last) {
			for (unsigned int i = m_pos + 1; i <= last; ++i) {
				delete Item(i);
			}
			RemoveAt(m_pos + 1, last - m_pos);
		}
	}
	
	// �����ɒǉ�����B
	Add(ref);
	m_pos = GetCount() - 1;
}

/**
 * ���݂̗v�f���擾
 */
DicReference* DicHistory::GetCurrent()
{
	return Item(m_pos);
}

/**
 * �߂�
 */
DicReference* DicHistory::Back()
{
	--m_pos;
	return GetCurrent();
}

/**
 * �i��
 */
DicReference* DicHistory::Forward()
{
	++m_pos;
	return GetCurrent();
}
