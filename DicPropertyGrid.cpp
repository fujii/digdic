// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * �v���p�e�B�O���b�h�N���X
 * 
 * $Date: 2006/06/26 15:57:54 $
 */
#include "DicPropertyGrid.h"

/**
 * ���z�T�C�Y��ݒ�
 * 
 * �f�̂܂܂ł͂Ȃ���1�s�������̂ŁA�X�N���[���o�[���v��Ȃ���
 * ���\������Ă��܂��B�����������邽�߂ɃI�[�o�[���C�h�����B
 */
void DicPropertyGrid::DoSetVirtualSize(int x, int y)
{
    wxScrolledWindow::DoSetVirtualSize(x, y - m_lineHeight);
}

/**
 * �ύX�𔽉f
 */
void DicPropertyGrid::CommitChanges() {
	CommitChangesFromEditor();
}
