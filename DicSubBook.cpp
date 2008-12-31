// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 副本クラス
 * 
 * $Date: 2007/10/01 13:04:41 $
 */
#include <eb/text.h>
#include <wx/tokenzr.h>
#include "DicSubbook.h"
#include "DicShare.h"

#define MAXLEN_HEADING 127
#define MAXLEN_TEXT 1023

/**
 * コンストラクタ
 */
DicSubbook::DicSubbook() :
	m_enabled(true),
	m_dicBook(NULL),
	m_book(NULL)
{
}

/**
 * コンストラクタ
 */
/*
DicSubbook::DicSubbook(DicBook* book, EB_Subbook_Code subbook) :
	m_dicBook(book),
	m_book(book->GetEbBook()),
	m_subbook(subbook),
	m_enabled(true)
{
	m_book = book->GetEbBook();
}
*/

/**
 * 本のパスを設定
 */
void DicSubbook::SetBookPath(const wxString& path)
{
	m_bookPath = path;
}

/**
 * Appendixのパスを設定
 */
void DicSubbook::SetAppendixPath(const wxString& path)
{
	m_appendixPath = path;
}

/**
 * 副本コードを設定
 */
void DicSubbook::SetSubbookCode(EB_Subbook_Code subbook)
{
	m_subbook = subbook;
}

/**
 * 別名を設定
 */
void DicSubbook::SetAlias(const wxString& alias)
{
	m_alias = alias;
}

/**
 * 有効か設定する
 */
void DicSubbook::Enable(bool b)
{
	m_enabled = b;
}

/**
 * 本のパスを取得
 */
wxString DicSubbook::GetBookPath()
{
	return m_bookPath;
}

/**
 * Appendixのパスを取得
 */
wxString DicSubbook::GetAppendixPath()
{
	return m_appendixPath;
}

/**
 * 副本コードを取得
 */
EB_Subbook_Code DicSubbook::GetSubbookCode()
{
	return m_subbook;
}

/**
 * 別名を取得
 */
wxString DicSubbook::GetAlias()
{
	return m_alias;
}

/**
 * 有効か
 */
bool DicSubbook::IsEnabled()
{
	return m_enabled;
}

/**
 * バインド
 */
bool DicSubbook::Bind()
{
	if (DicShare::books.Exists(m_bookPath)) {
		m_dicBook = DicShare::books[m_bookPath];
	} else {
		m_dicBook = new DicBook;
		if (m_dicBook->Bind(m_bookPath) == EB_SUCCESS) {
			DicShare::books[m_bookPath] = m_dicBook;
		} else {
			delete m_dicBook;
			m_dicBook = NULL;
			return false;
		}
	}
	
	// Appendixの設定が必要
	// 未

	m_book = m_dicBook->GetEbBook();
	
	return true;
}

/**
 * 本を取得
 */
DicBook* DicSubbook::GetBook()
{
	m_dicBook->SetCurSubbook(m_subbook);
	return m_dicBook;
}

/**
 * 前方一致検索が可能か
 */
bool DicSubbook::HasWordSearch()
{
	CheckCurVol();
	
	if (::eb_have_word_search(m_book)) {
		return true;
	}
	return false;
}

/**
 * 後方一致検索が可能か
 */
bool DicSubbook::HasEndWordSearch()
{
	CheckCurVol();
	
	if (::eb_have_endword_search(m_book)) {
		return true;
	}
	return false;
}

/**
 * 完全一致検索が可能か
 */
bool DicSubbook::HasExactWordSearch()
{
	CheckCurVol();
	
	if (::eb_have_exactword_search(m_book)) {
		return true;
	}
	return false;
}

/**
 * 条件検索が可能か
 */
bool DicSubbook::HasKeywordSearch()
{
	CheckCurVol();
	
	if (::eb_have_keyword_search(m_book)) {
		return true;
	}
	return false;
}

/**
 * クロス検索が可能か
 */
bool DicSubbook::hasCrossSearch()
{
	CheckCurVol();
	
	if (::eb_have_cross_search(m_book)) {
		return true;
	}
	return false;
}

/**
 * 複合検索が可能か
 */
bool DicSubbook::HasMultiSearch()
{
	CheckCurVol();
	
	if (::eb_have_multi_search(m_book)) {
		return true;
	}
	return false;
}

/**
 * 著作権表示があるか
 */
bool DicSubbook::HasCopyright()
{
	CheckCurVol();
	
	if (::eb_have_copyright(m_book)) {
		return true;
	}
	return false;
}

/**
 * メニューがあるか
 */
bool DicSubbook::HasMenu()
{
	CheckCurVol();
	
	if (::eb_have_menu(m_book)) {
		return true;
	}
	return false;
}

/**
 * 前方一致検索
 */
int DicSubbook::SearchWord(const wxString& key, DicReferences& hits)
{
	CheckCurVol();

    EB_Error_Code ebErr;
	
	if (!::eb_have_word_search(m_book)) {
		return 0;
	}

	// 検索リクエストを送出
	char buf[EB_MAX_WORD_LENGTH + 1];
	GetSearchWord(buf, sizeof(buf), key);
	ebErr = ::eb_search_word(m_book, buf);
    if (ebErr != EB_SUCCESS) {
        return 0;
    }

	// ヒットを取得
    return GetHits(hits);
}

/**
 * 後方一致検索
 */
int DicSubbook::SearchEndWord(const wxString& key, DicReferences& hits)
{
	CheckCurVol();

    EB_Error_Code ebErr;

	if (!::eb_have_endword_search(m_book)) {
		return 0;
	}
	
	// 検索リクエストを送出
	char buf[EB_MAX_WORD_LENGTH + 1];
	GetSearchWord(buf, sizeof(buf), key);
	ebErr = ::eb_search_endword(m_book, buf);
    if (ebErr != EB_SUCCESS) {
        return 0;
    }

	// ヒットを取得
	return GetHits(hits);
}

/**
 * 完全一致検索
 */
int DicSubbook::SearchExactWord(const wxString& key, DicReferences& hits)
{
	CheckCurVol();

    EB_Error_Code ebErr;

	if (!::eb_have_exactword_search(m_book)) {
		return 0;
	}

	// 検索リクエストを送出
	char buf[EB_MAX_WORD_LENGTH + 1];
	GetSearchWord(buf, sizeof(buf), key);
	ebErr = ::eb_search_exactword(m_book, buf);
    if (ebErr != EB_SUCCESS) {
        return 0;
    }

	// ヒットを取得
	return GetHits(hits);
}

/**
 * 条件検索
 */
int DicSubbook::SearchKeyword(const wxString& key, DicReferences& hits)
{
	CheckCurVol();

    EB_Error_Code ebErr;

	if (!::eb_have_keyword_search(m_book)) {
		return 0;
	}
	
	// キーの配列を作成	
	wxStringTokenizer st(key);
	int cnt = st.CountTokens();
	char bufs[cnt][EB_MAX_WORD_LENGTH + 1];
	const char* keys[cnt + 1];
	for (int i = 0; st.HasMoreTokens(); ++i) {
		GetSearchWord(bufs[i], sizeof(bufs[i]), st.GetNextToken());
		keys[i] = bufs[i];
	}
	keys[cnt] = NULL;
    
	// 検索リクエストを送出
	ebErr = ::eb_search_keyword(m_book, keys);
    if (ebErr != EB_SUCCESS) {
        return 0;
    }

	// ヒットを取得
	return GetHits(hits);
}

/**
 * クロス検索
 */
int DicSubbook::SearchCross(const wxString& key, DicReferences& hits)
{
	CheckCurVol();

    EB_Error_Code ebErr;

	if (!::eb_have_cross_search(m_book)) {
		return 0;
	}
    
	// キーの配列を作成	
	wxStringTokenizer st(key);
	int cnt = st.CountTokens();
	char bufs[cnt][EB_MAX_WORD_LENGTH + 1];
	const char* keys[cnt + 1];
	for (int i = 0; st.HasMoreTokens(); ++i) {
		GetSearchWord(bufs[i], sizeof(bufs[i]), st.GetNextToken());
		keys[i] = bufs[i];
	}
	keys[cnt] = NULL;
    
	// 検索リクエストを送出
	ebErr = ::eb_search_cross(m_book, keys);
    if (ebErr != EB_SUCCESS) {
        return 0;
    }

	// ヒットを取得
	return GetHits(hits);
}

/**
 * 複合検索
 */
int DicSubbook::SearchMulti(EB_Multi_Search_Code multiId, const wxArrayString& keys, DicReferences& hits)
{
	CheckCurVol();

    EB_Error_Code ebErr;

	// キーの配列を作成
	char bufs[keys.GetCount()][EB_MAX_WORD_LENGTH + 1];
	const char* words[keys.GetCount() + 1];
	for (unsigned int i = 0; i < keys.GetCount(); ++i) {
		GetSearchWord(bufs[i], sizeof(bufs[i]), keys[i]);
		words[i] = bufs[i];
	}
	words[keys.GetCount()] = NULL;
    
	// 検索リクエストを送出
	ebErr = ::eb_search_multi(m_book, multiId, words);
    if (ebErr != EB_SUCCESS) {
        return 0;
    }

	// ヒットを取得
	return GetHits(hits);
}

/**
 * 複合検索の種類の数を取得
 */
int DicSubbook::GetMultiCount()
{
	CheckCurVol();
	
    EB_Error_Code ebErr;
	EB_Multi_Search_Code codes[EB_MAX_MULTI_SEARCHES];
	int count;
	
	ebErr = ::eb_multi_search_list(m_book, codes, &count);
    if (ebErr != EB_SUCCESS) {
        return 0;
    }
    return count;
}

/**
 * 複合検索のコードを取得
 */
EB_Multi_Search_Code DicSubbook::GetMultiCode(int index)
{
	CheckCurVol();
	
    EB_Error_Code ebErr;
	EB_Multi_Search_Code codes[EB_MAX_MULTI_SEARCHES];
	int count;
	
	ebErr = ::eb_multi_search_list(m_book, codes, &count);
    if (ebErr != EB_SUCCESS) {
        return 0;
    }
    return codes[index];
}

/**
 * 複合検索の題名を取得
 */
wxString DicSubbook::GetMultiTitle(EB_Multi_Search_Code code)
{
	CheckCurVol();
	
    EB_Error_Code ebErr;
    char title[EB_MAX_TITLE_LENGTH + 1];
	
	ebErr = ::eb_multi_title(m_book, code, title);
    if (ebErr != EB_SUCCESS) {
        return wxT("");
    }
    return wxString(title, DicBook::convEuc);
}

/**
 * 複合検索の検索語の数を取得
 */
int DicSubbook::GetMultiEntryCount(EB_Multi_Search_Code code)
{
	CheckCurVol();
	
    EB_Error_Code ebErr;
    int count;
	
	ebErr = ::eb_multi_entry_count(m_book, code, &count);
    if (ebErr != EB_SUCCESS) {
        return 0;
    }
    return count;
}

/**
 * 複合検索の検索語の題目を取得
 */
wxString DicSubbook::GetMultiEntryLabel(EB_Multi_Search_Code code, int index)
{
	CheckCurVol();
	
    EB_Error_Code ebErr;
    char label[EB_MAX_MULTI_LABEL_LENGTH + 1];
	
	ebErr = ::eb_multi_entry_label(m_book, code, index, label);
    if (ebErr != EB_SUCCESS) {
        return wxT("");
    }
    return wxString(label, DicBook::convEuc);
}

/**
 * 複合検索の検索語の候補一覧があるか
 */
bool DicSubbook::HasMultiEntryCandidates(EB_Multi_Search_Code code, int index)
{
	CheckCurVol();
	
	if (::eb_multi_entry_have_candidates(m_book, code, index)) {
		return true;
	}
	return false;
}

/**
 * 複合検索の検索語の候補位置を取得
 */
EB_Position DicSubbook::GetMultiEntryCandidatesPos(EB_Multi_Search_Code code, int index)
{
	CheckCurVol();
	
	EB_Error_Code ebErr;

	EB_Position pos;
	ebErr = ::eb_multi_entry_candidates(m_book, code, index, &pos);
/*	if (ebErr == EB_ERR_NO_CANDIDATES) {
		return pos;
	}
	if (ebErr != EB_SUCCESS) {
		return pos;
	}
*/
	return pos;
}

/**
 * 複合検索の検索語の候補一覧を取得
 */
DicMultiCandidates DicSubbook::GetMultiEntryCandidates(EB_Position* pos)
{
	CheckCurVol();
	
	DicMultiCandidates candidates;
	EB_Error_Code ebErr;
	
    ebErr = ::eb_seek_text(m_book, pos);
    if (ebErr != EB_SUCCESS) {
        return candidates;
    }
    
    char text[MAXLEN_TEXT + 1];
    ssize_t textLength;
//    wxString str;
    // テキストデータを取得。
    for (;;) {
	    ebErr = ::eb_read_text(m_book, NULL, m_candidateHook.GetHookset(), &candidates,
	        MAXLEN_TEXT, text, &textLength);
	    if (ebErr != EB_SUCCESS) {
	        break;
	    }
	    if (textLength == 0) {
	    	break;
	    }
//	    str += wxString(text, DicBook::convEuc);
    }
    return candidates;
}

/**
 * 著作権表示を取得
 */
DicReference* DicSubbook::GetCopyright()
{
	CheckCurVol();

    EB_Error_Code ebErr;
	
	if (!::eb_have_copyright(m_book)) {
		return NULL;
	}

	// 検索リクエストを送出
	EB_Position pos;
	ebErr = ::eb_copyright(m_book, &pos);
    if (ebErr != EB_SUCCESS) {
        return NULL;
    }

  	return new DicReference(this, pos);
}

/**
 * メニューを取得
 */
DicReference* DicSubbook::GetMenu()
{
	CheckCurVol();

    EB_Error_Code ebErr;
	
	if (!::eb_have_menu(m_book)) {
		return NULL;
	}

	// 検索リクエストを送出
	EB_Position pos;
	ebErr = ::eb_menu(m_book, &pos);
    if (ebErr != EB_SUCCESS) {
        return NULL;
    }

  	return new DicReference(this, pos);
}

/**
 * 見出しを取得
 */
wxString DicSubbook::GetHeading(EB_Position* pos)
{
    EB_Error_Code ebErr;
    char heading[MAXLEN_HEADING + 1];
    ssize_t headingLength;
    
	CheckCurVol();
	
    // 見出しの位置へ移動。
    ebErr = ::eb_seek_text(m_book, pos);
    if (ebErr != EB_SUCCESS) {
        return wxT("");
    }

	wxString str;
	
    // 見出しを取得。
    for (;;) {
	    ebErr = ::eb_read_heading(m_book, NULL, NULL, NULL,
	        MAXLEN_HEADING, heading, &headingLength);
	    if (ebErr != EB_SUCCESS) {
	        return wxT("");
	    }
	    if (headingLength == 0) {
	    	break;
	    }
	    str += wxString(heading, DicBook::convEuc);
    }
    
    return str;
}

/**
 * テキストデータを取得
 */
wxString DicSubbook::GetText(EB_Position* pos)
{
    EB_Error_Code ebErr;
    char text[MAXLEN_TEXT + 1];
    ssize_t textLength;
	wxString str = DicShare::htmlHead;
    
	CheckCurVol();
	
	m_curPos = *pos;
	EB_Position p = *pos;
	
	for (int i = 0; i < DicShare::pageMaxResults; ++i) {
	    // 長過ぎるときは中断。
	    // ※広辞苑第5版 「馬鹿を見る」検索時など
	    if (str.length() > (wxString::size_type)DicShare::pageMaxBytes) {
	    	break;
	    }
	    
	    // テキストデータの位置へ移動。
	    ebErr = ::eb_seek_text(m_book, &p);
	    if (ebErr != EB_SUCCESS) {
	        break;
	    }
	    
	    // テキストデータを取得。
	    for (;;) {
		    ebErr = ::eb_read_text(m_book, NULL, m_hook.GetHookset(), this,
		        MAXLEN_TEXT, text, &textLength);
		    if (ebErr != EB_SUCCESS) {
		        break;
		    }
		    if (textLength == 0) {
		    	break;
		    }
		    str += wxString(text, DicBook::convEuc);
	    }
	    
	    // 次の単語の説明へ移動。
		ebErr = ::eb_forward_text(m_book, NULL);
		if (ebErr == EB_ERR_END_OF_CONTENT) {
		    break;
		} else if (ebErr != EB_SUCCESS) {
			break;
		}
		::eb_tell_text(m_book, &p);
	}
	
	m_nextPos = p;

	str += DicShare::htmlFoot;    
    return str;
}

/**
 * 前のテキストデータを取得
 */
wxString DicSubbook::GetPrevText()
{
	// データの有り無しを判定したほうが良いかな・・・(2006/4/23)
	
    EB_Error_Code ebErr;
    char text[MAXLEN_TEXT + 1];
    ssize_t textLength;
	wxString str = DicShare::htmlHead;
    
	CheckCurVol();
	
	EB_Position p = m_curPos;
	
	for (int i = 0; i < DicShare::pageMaxResults; ++i) {
	    // 長過ぎるときは中断。
	    if (str.length() > (wxString::size_type)DicShare::pageMaxBytes) {
	    	break;
	    }
		
	    // テキストデータの位置へ移動。
	    ebErr = ::eb_seek_text(m_book, &p);
	    if (ebErr != EB_SUCCESS) {
	        break;
	    }
    
	    // 前の単語の説明へ移動。
		ebErr = ::eb_backward_text(m_book, NULL);
		if (ebErr == EB_ERR_END_OF_CONTENT) {
		    break;
		} else if (ebErr != EB_SUCCESS) {
			break;
		}
		::eb_tell_text(m_book, &p);
	    
	    // テキストデータの位置へ移動。
	    // ※HookでInitializeが呼ばれるようにするためseekが必要(???)
	    ebErr = ::eb_seek_text(m_book, &p);
	    if (ebErr != EB_SUCCESS) {
	        break;
	    }
	    
	    // テキストデータを取得。
	    wxString strText;
	    for (;;) {
		    ebErr = ::eb_read_text(m_book, NULL, m_hook.GetHookset(), this,
		        MAXLEN_TEXT, text, &textLength);
		    if (ebErr != EB_SUCCESS) {
		        break;
		    }
		    if (textLength == 0) {
		    	break;
		    }
		    strText += wxString(text, DicBook::convEuc);
	    }
	    str = strText + str;
	}
    
    m_nextPos = m_curPos;
    m_curPos = p;
    
	str += DicShare::htmlFoot;    
    return str;
}

/**
 * 次のテキストデータを取得
 */
wxString DicSubbook::GetNextText()
{
	// データの有り無しを判定したほうが良いかな・・・(2006/4/23)
	
	return GetText(&m_nextPos);
}

/**
 * 現在のボリュームをチェック
 */
void DicSubbook::CheckCurVol()
{
	m_dicBook->CheckCurVol();
	
	m_dicBook->SetCurSubbook(m_subbook);
}

/**
 * ヒットを取得
 */
int DicSubbook::GetHits(DicReferences& hits)
{
    EB_Error_Code ebErr;
	EB_Hit ebHits[100];
	int count;
	int total = 0;
	DicReferences tmpHits;

    // ヒットエントリを取得。
//    for (;;)
	for (int i = 0; i < DicShare::searchMaxResults / 100; ++i) // 取得数を制限
	{
		ebErr = ::eb_hit_list(m_book, 100, ebHits, &count);
	    if (ebErr != EB_SUCCESS || !count)
	    {
	        break;
	    }
	    for (int j = 0; j < count; ++j)
	    {
	    	DicReference* hit = new DicReference(this, ebHits[j]);
	    	if (tmpHits.Exists(hit))
	    	{
	    		delete hit;
	    	}
	    	else
	    	{
	    		tmpHits.Add(hit);
	    		++total;
	    	}
	    }
    }
	
	hits.Append(tmpHits);
	
	return total;
}

/**
 * 検索のための語を取得
 */
void DicSubbook::GetSearchWord(char* dst, int len, const wxString& src)
{
	dst[0] = '\0';
	wxString remain = src;
	while (!remain.empty())
	{
		int extStart = remain.Find(wxT("{"));
		if (extStart == -1)
		{
			// 残りを出力する。
			wxCharBuffer buf = remain.mb_str(DicBook::convEuc);
			if (!buf.data())
			{
				// EUCへの変換に失敗。
				return;
			}
			::snprintf(dst, len, buf);
			break;
		}
		if (extStart >= 0)
		{
			// "{"の左側を出力する。
			wxCharBuffer buf = remain.Left(extStart).mb_str(DicBook::convEuc);
			if (!buf.data())
			{
				// EUCへの変換に失敗。
				return;
			}
			::snprintf(dst, len, buf);
			int write = ::strlen(dst);
			dst += write;
			len -= write;
			remain = remain.Mid(extStart);
			
			int extEnd = remain.Find(wxT("}"));
			if (extEnd == 5)
			{
				// "{XXXX}"の形式の時、外字のコードを出力する。
				unsigned long upper = 0;
				unsigned long lower = 0;
				remain.Mid(1, 2).ToULong(&upper, 16);
				remain.Mid(3, 2).ToULong(&lower, 16);
				::snprintf(dst, len, "%c%c", (int)upper, (int)lower);
				dst += 2;
				len -= 2;
				remain = remain.Mid(6);
			}
			else
			{
				// "{XXXX}"の形式でない時、"{"を出力する。
				::snprintf(dst, len, "{");
				++dst;
				--len;
				remain = remain.Mid(1);
			}
		}
	}
}
