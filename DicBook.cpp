// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * �{�N���X
 * 
 * $Date: 2007/08/05 13:06:15 $
 */
#include "DicBook.h"

wxCSConv DicBook::convEuc(wxT("EUC-JP"));

/**
 * �R���X�g���N�^
 */
DicBook::DicBook()
{
    ::eb_initialize_book(&m_book);
}

/**
 * �f�X�g���N�^
 */
DicBook::~DicBook()
{
	::eb_finalize_book(&m_book);
}

/**
 * EB_Book�̃|�C���^���擾
 */
EB_Book* DicBook::GetEbBook()
{
	return &m_book;
}

/**
 * �{���o�C���h����
 */
EB_Error_Code DicBook::Bind(const wxString& path)
{
	// �p�X��ݒ肷��B
    m_fn = wxFileName(path);
    m_fn.MakeAbsolute();
	
	CheckCurVol();
	
	wxString fullPath = m_fn.GetFullPath(wxPATH_UNIX);
	wxCharBuffer buf = fullPath.mb_str();
	if (!buf.data())
	{
		// �p�X�̕ϊ��Ɏ��s�B
		return EB_ERR_BAD_FILE_NAME;
	}
	
	// �o�C���h����B
    EB_Error_Code ebErr = ::eb_bind(&m_book, buf);
    if (ebErr != EB_SUCCESS)
    {
        return ebErr;
    }

    // ���{�̈ꗗ���擾�B
    ebErr = ::eb_subbook_list(&m_book, m_subbooks, &m_subbookCount);

	return ebErr;
}

/**
 * �p�X���擾
 */
wxFileName DicBook::GetPath()
{
	return m_fn;
}

/**
 * ���{�̐����擾
 */
int DicBook::GetSubbookCount()
{
	return m_subbookCount;
}

/**
 * ���{���擾
 */
EB_Subbook_Code DicBook::GetSubbook(int index)
{
	return m_subbooks[index];
}

/**
 * ���݂̕��{��ݒ�
 */
void DicBook::SetCurSubbook(EB_Subbook_Code code)
{
	CheckCurVol();

    EB_Error_Code ebErr = ::eb_set_subbook(&m_book, code);
    if (ebErr != EB_SUCCESS) {
        return;
    }
}

/**
 * ���݂̕��{���擾
 */
EB_Subbook_Code DicBook::GetCurSubbook()
{
	CheckCurVol();
	
	EB_Subbook_Code code;
    ::eb_subbook(&m_book, &code);
    return code;
}

/**
 * ���݂̕��{�̑薼���擾
 */
wxString DicBook::GetCurSubbookTitle()
{
	CheckCurVol();
	
    EB_Error_Code ebErr;
    
    char title[EB_MAX_TITLE_LENGTH + 1];
	ebErr = ::eb_subbook_title(&m_book, title);
	if (ebErr != EB_SUCCESS) {
		return wxT("");
	}
    return wxString(title, convEuc);
}

/**
 * ���݂̃{�����[�����`�F�b�N
 */
void DicBook::CheckCurVol()
{
	// ���݂̃f�B���N�g�����t�@�C���̂���{�����[���ȊO�̏ꍇ�A
	// �t�@�C���̂���f�B���N�g���ɕύX����B
	wxFileName fn;
	fn.SetCwd();
	if (fn.GetVolume() != m_fn.GetVolume()) {
		::wxSetWorkingDirectory(m_fn.GetFullPath());
	}
}
