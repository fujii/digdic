// Copyright (C) 2006-2007 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 副本の配列クラス
 * 
 * $Date: 2007/10/31 16:13:50 $
 */
#include <wx/intl.h>
#include <wx/config.h>
#include <wx/tokenzr.h>
#include <wx/dirdlg.h>
#include <wx/msgdlg.h>
#include "DicSubbooks.h"
#include "DicShare.h"

const int PROGRESS_BAR_MAX = 1000;

/**
 * 名前(グループ名)を設定
 */
void DicSubbooks::SetName(const wxString& name)
{
	m_name = name;
}

/**
 * 名前(グループ名)を取得
 */
wxString DicSubbooks::GetName()
{
	return m_name;
}

/**
 * 全て削除
 */
void DicSubbooks::DeleteAll()
{
	WX_CLEAR_ARRAY(*this);
}

/**
 * 全て有効(か無効)にする
 */
void DicSubbooks::EnableAll(bool b)
{
	for (unsigned int i = 0; i < GetCount(); ++i)
	{
		Item(i)->Enable(b);
	}
}

/**
 * 設定を読み込む
 * 
 * @param config 設定
 * @param bind バインドするか
 */
void DicSubbooks::LoadConfig(wxConfigBase* config, bool bind)
{
	if (!config)
	{
	  	config = wxConfigBase::Get();
	}

	DeleteAll();
	
	config->SetPath(wxT("/dictionary"));
	wxString key;
	long index = 0;
	if (config->GetFirstEntry(key, index))
	{
		do
		{
			DicSubbook* subbook = new DicSubbook();

			wxStringTokenizer tkz(config->Read(key, wxT("")), wxT(";"));

			subbook->SetAlias(tkz.GetNextToken());
			subbook->SetBookPath(tkz.GetNextToken());
			long code;
			tkz.GetNextToken().ToLong(&code);
			subbook->SetSubbookCode((EB_Subbook_Code)code);
			subbook->SetAppendixPath(tkz.GetNextToken());
			
			// bind引数が真の時だけバインドする。
			if (bind)
			{
				if (!subbook->Bind())
				{
					delete subbook;
				}
				else
				{
					Add(subbook);
				}
			}
			else
			{			
				Add(subbook);
			}
		}
		while (config->GetNextEntry(key, index));
	}
}

/**
 * 設定を保存
 * 
 * @param config 設定
 */
void DicSubbooks::SaveConfig(wxConfigBase* config)
{
	if (!config)
	{
		config = wxConfigBase::Get();
	}
	
	config->DeleteGroup(wxT("/dictionary"));
	config->SetPath(wxT("/dictionary"));
	for (unsigned int i = 0; i < GetCount(); ++i)
	{
		DicSubbook* subbook = (*this)[i];
		wxString key = wxString::Format(wxT("%04d"), i);
		wxString value = subbook->GetAlias();
		value << wxT(";");
		value << subbook->GetBookPath();
		value << wxT(";");
		value << subbook->GetSubbookCode();
		value << wxT(";");
		// value << appendixのパス
		config->Write(key, value);
    }
    config->Flush();
}

/**
 * 本を探す
 * 
 * @return 追加したか
 */
bool DicSubbooks::SearchBook()
{
	wxString dir;
	while (dir.empty())
	{
		wxDirDialog dd(NULL, _("Choose a directory."), wxT(""),
			wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);
		if (dd.ShowModal() == wxID_CANCEL)
		{
			// OKでも空のときはここに来る・・・バグ？(2005/5/7)
			return false;
		}
		dir = dd.GetPath();
	}
	
	bool automatic = false;
	if (::wxMessageBox(_("Do you register all books automatically?"),
			_("digdic"), wxICON_QUESTION | wxYES_NO) == wxYES)
	{
		automatic = true;
	}
	
	wxBusyCursor wait;

	wxProgressDialog pd(_("Search book"), wxT("12345678901234567890123456789012345678901234567890"),
		PROGRESS_BAR_MAX, NULL, wxPD_CAN_ABORT | wxPD_ELAPSED_TIME);

	wxDir d(dir);
	DicDirTraverser dt(this, &pd, automatic);
	dt.OnDir(dir); // 直下を調べる。
	d.Traverse(dt, wxT(""), wxDIR_DIRS);
	
	pd.Update(PROGRESS_BAR_MAX, _("Search book ended."));
	
	// 追加された場合、設定ファイルを更新するか選択する。
	if (dt.IsAdded())
	{
	 	if (::wxMessageBox(_("Save book list?"),
	 			_("digdic"), wxICON_QUESTION | wxYES_NO) == wxYES)
	 	{
	 		SaveConfig();
	 	}
	 	return true;
	}
	
	return false;
}

/**
 * コンストラクタ
 */
DicDirTraverser::DicDirTraverser(DicSubbooks* subbooks, wxProgressDialog* pd, bool automatic) :
	m_subbooks(subbooks),
	m_pd(pd),
	m_automatic(automatic),
	m_count(0),
	m_added(false)
{
}

/**
 * ファイルの時
 */
wxDirTraverseResult DicDirTraverser::OnFile(const wxString& filename)
{
	return wxDIR_CONTINUE;
}

/**
 * ディレクトリの時
 */
wxDirTraverseResult DicDirTraverser::OnDir(const wxString& dirname)
{
	++m_count;
	if (m_count == PROGRESS_BAR_MAX)
	{
		m_count = 0;
	}
	if (!m_pd->Update(m_count, dirname))
	{	
		return wxDIR_STOP;
	}
	
	DicBook* book = new DicBook;
	if (book->Bind(dirname) != EB_SUCCESS)
	{
		delete book;
		return wxDIR_CONTINUE;
	}

	// 既に登録済みの場合は省く
	if (DicShare::books.Exists(dirname))
	{
		delete book;
		return wxDIR_CONTINUE;
	}
	
	wxString bookName;
	for (int i = 0; i < book->GetSubbookCount(); ++i)
	{
		book->SetCurSubbook(book->GetSubbook(i));
		bookName += book->GetCurSubbookTitle();
		bookName += wxT("\n");
	}
	bool adding = false;
	if (m_automatic)
	{
		adding = true;
	}
	else
	{
		wxString message = _("Do you add this dictionary?");
		message	+= wxT("\n\ndir:\n");
		message	+= dirname;
		message	+= wxT("\nsubbook:\n");
		message	+= bookName;
		int ret = ::wxMessageBox(message, _("digdic"),
						wxICON_QUESTION | wxYES_NO | wxCANCEL);
		switch (ret)
		{
		case wxYES:
			adding = true;
			break;
		case wxCANCEL:
			delete book;
			return wxDIR_STOP;
			break;
		default:
			break;
		}
	}
	if (adding)
	{
 		DicShare::books[dirname] = book;
 		for (int i = 0; i < book->GetSubbookCount(); ++i)
 		{
 			EB_Subbook_Code code = book->GetSubbook(i);
 			book->SetCurSubbook(code);
 			wxString alias = book->GetCurSubbookTitle();
 			
			DicSubbook* subbook = new DicSubbook();
			subbook->SetBookPath(dirname);
			subbook->SetSubbookCode(code);
 			subbook->SetAlias(alias);
 			subbook->Bind();
 			m_subbooks->Add(subbook);
 		}
 		m_added = true;
		return wxDIR_IGNORE;
 	}
 	
	delete book;
	return wxDIR_CONTINUE;
}

/**
 * 追加されたか
 */
bool DicDirTraverser::IsAdded()
{
	return m_added;
}
