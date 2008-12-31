// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 本クラス
 * 
 * $Date: 2007/08/05 13:06:15 $
 */
#include "DicBook.h"

wxCSConv DicBook::convEuc(wxT("EUC-JP"));

/**
 * コンストラクタ
 */
DicBook::DicBook()
{
    ::eb_initialize_book(&m_book);
}

/**
 * デストラクタ
 */
DicBook::~DicBook()
{
	::eb_finalize_book(&m_book);
}

/**
 * EB_Bookのポインタを取得
 */
EB_Book* DicBook::GetEbBook()
{
	return &m_book;
}

/**
 * 本をバインドする
 */
EB_Error_Code DicBook::Bind(const wxString& path)
{
	// パスを設定する。
    m_fn = wxFileName(path);
    m_fn.MakeAbsolute();
	
	CheckCurVol();
	
	wxString fullPath = m_fn.GetFullPath(wxPATH_UNIX);
	wxCharBuffer buf = fullPath.mb_str();
	if (!buf.data())
	{
		// パスの変換に失敗。
		return EB_ERR_BAD_FILE_NAME;
	}
	
	// バインドする。
    EB_Error_Code ebErr = ::eb_bind(&m_book, buf);
    if (ebErr != EB_SUCCESS)
    {
        return ebErr;
    }

    // 副本の一覧を取得。
    ebErr = ::eb_subbook_list(&m_book, m_subbooks, &m_subbookCount);

	return ebErr;
}

/**
 * パスを取得
 */
wxFileName DicBook::GetPath()
{
	return m_fn;
}

/**
 * 副本の数を取得
 */
int DicBook::GetSubbookCount()
{
	return m_subbookCount;
}

/**
 * 副本を取得
 */
EB_Subbook_Code DicBook::GetSubbook(int index)
{
	return m_subbooks[index];
}

/**
 * 現在の副本を設定
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
 * 現在の副本を取得
 */
EB_Subbook_Code DicBook::GetCurSubbook()
{
	CheckCurVol();
	
	EB_Subbook_Code code;
    ::eb_subbook(&m_book, &code);
    return code;
}

/**
 * 現在の副本の題名を取得
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
 * 現在のボリュームをチェック
 */
void DicBook::CheckCurVol()
{
	// 現在のディレクトリがファイルのあるボリューム以外の場合、
	// ファイルのあるディレクトリに変更する。
	wxFileName fn;
	fn.SetCwd();
	if (fn.GetVolume() != m_fn.GetVolume()) {
		::wxSetWorkingDirectory(m_fn.GetFullPath());
	}
}
