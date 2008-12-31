// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * ���{�N���X
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
 * �R���X�g���N�^
 */
DicSubbook::DicSubbook() :
	m_enabled(true),
	m_dicBook(NULL),
	m_book(NULL)
{
}

/**
 * �R���X�g���N�^
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
 * �{�̃p�X��ݒ�
 */
void DicSubbook::SetBookPath(const wxString& path)
{
	m_bookPath = path;
}

/**
 * Appendix�̃p�X��ݒ�
 */
void DicSubbook::SetAppendixPath(const wxString& path)
{
	m_appendixPath = path;
}

/**
 * ���{�R�[�h��ݒ�
 */
void DicSubbook::SetSubbookCode(EB_Subbook_Code subbook)
{
	m_subbook = subbook;
}

/**
 * �ʖ���ݒ�
 */
void DicSubbook::SetAlias(const wxString& alias)
{
	m_alias = alias;
}

/**
 * �L�����ݒ肷��
 */
void DicSubbook::Enable(bool b)
{
	m_enabled = b;
}

/**
 * �{�̃p�X���擾
 */
wxString DicSubbook::GetBookPath()
{
	return m_bookPath;
}

/**
 * Appendix�̃p�X���擾
 */
wxString DicSubbook::GetAppendixPath()
{
	return m_appendixPath;
}

/**
 * ���{�R�[�h���擾
 */
EB_Subbook_Code DicSubbook::GetSubbookCode()
{
	return m_subbook;
}

/**
 * �ʖ����擾
 */
wxString DicSubbook::GetAlias()
{
	return m_alias;
}

/**
 * �L����
 */
bool DicSubbook::IsEnabled()
{
	return m_enabled;
}

/**
 * �o�C���h
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
	
	// Appendix�̐ݒ肪�K�v
	// ��

	m_book = m_dicBook->GetEbBook();
	
	return true;
}

/**
 * �{���擾
 */
DicBook* DicSubbook::GetBook()
{
	m_dicBook->SetCurSubbook(m_subbook);
	return m_dicBook;
}

/**
 * �O����v�������\��
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
 * �����v�������\��
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
 * ���S��v�������\��
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
 * �����������\��
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
 * �N���X�������\��
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
 * �����������\��
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
 * ���쌠�\�������邩
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
 * ���j���[�����邩
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
 * �O����v����
 */
int DicSubbook::SearchWord(const wxString& key, DicReferences& hits)
{
	CheckCurVol();

    EB_Error_Code ebErr;
	
	if (!::eb_have_word_search(m_book)) {
		return 0;
	}

	// �������N�G�X�g�𑗏o
	char buf[EB_MAX_WORD_LENGTH + 1];
	GetSearchWord(buf, sizeof(buf), key);
	ebErr = ::eb_search_word(m_book, buf);
    if (ebErr != EB_SUCCESS) {
        return 0;
    }

	// �q�b�g���擾
    return GetHits(hits);
}

/**
 * �����v����
 */
int DicSubbook::SearchEndWord(const wxString& key, DicReferences& hits)
{
	CheckCurVol();

    EB_Error_Code ebErr;

	if (!::eb_have_endword_search(m_book)) {
		return 0;
	}
	
	// �������N�G�X�g�𑗏o
	char buf[EB_MAX_WORD_LENGTH + 1];
	GetSearchWord(buf, sizeof(buf), key);
	ebErr = ::eb_search_endword(m_book, buf);
    if (ebErr != EB_SUCCESS) {
        return 0;
    }

	// �q�b�g���擾
	return GetHits(hits);
}

/**
 * ���S��v����
 */
int DicSubbook::SearchExactWord(const wxString& key, DicReferences& hits)
{
	CheckCurVol();

    EB_Error_Code ebErr;

	if (!::eb_have_exactword_search(m_book)) {
		return 0;
	}

	// �������N�G�X�g�𑗏o
	char buf[EB_MAX_WORD_LENGTH + 1];
	GetSearchWord(buf, sizeof(buf), key);
	ebErr = ::eb_search_exactword(m_book, buf);
    if (ebErr != EB_SUCCESS) {
        return 0;
    }

	// �q�b�g���擾
	return GetHits(hits);
}

/**
 * ��������
 */
int DicSubbook::SearchKeyword(const wxString& key, DicReferences& hits)
{
	CheckCurVol();

    EB_Error_Code ebErr;

	if (!::eb_have_keyword_search(m_book)) {
		return 0;
	}
	
	// �L�[�̔z����쐬	
	wxStringTokenizer st(key);
	int cnt = st.CountTokens();
	char bufs[cnt][EB_MAX_WORD_LENGTH + 1];
	const char* keys[cnt + 1];
	for (int i = 0; st.HasMoreTokens(); ++i) {
		GetSearchWord(bufs[i], sizeof(bufs[i]), st.GetNextToken());
		keys[i] = bufs[i];
	}
	keys[cnt] = NULL;
    
	// �������N�G�X�g�𑗏o
	ebErr = ::eb_search_keyword(m_book, keys);
    if (ebErr != EB_SUCCESS) {
        return 0;
    }

	// �q�b�g���擾
	return GetHits(hits);
}

/**
 * �N���X����
 */
int DicSubbook::SearchCross(const wxString& key, DicReferences& hits)
{
	CheckCurVol();

    EB_Error_Code ebErr;

	if (!::eb_have_cross_search(m_book)) {
		return 0;
	}
    
	// �L�[�̔z����쐬	
	wxStringTokenizer st(key);
	int cnt = st.CountTokens();
	char bufs[cnt][EB_MAX_WORD_LENGTH + 1];
	const char* keys[cnt + 1];
	for (int i = 0; st.HasMoreTokens(); ++i) {
		GetSearchWord(bufs[i], sizeof(bufs[i]), st.GetNextToken());
		keys[i] = bufs[i];
	}
	keys[cnt] = NULL;
    
	// �������N�G�X�g�𑗏o
	ebErr = ::eb_search_cross(m_book, keys);
    if (ebErr != EB_SUCCESS) {
        return 0;
    }

	// �q�b�g���擾
	return GetHits(hits);
}

/**
 * ��������
 */
int DicSubbook::SearchMulti(EB_Multi_Search_Code multiId, const wxArrayString& keys, DicReferences& hits)
{
	CheckCurVol();

    EB_Error_Code ebErr;

	// �L�[�̔z����쐬
	char bufs[keys.GetCount()][EB_MAX_WORD_LENGTH + 1];
	const char* words[keys.GetCount() + 1];
	for (unsigned int i = 0; i < keys.GetCount(); ++i) {
		GetSearchWord(bufs[i], sizeof(bufs[i]), keys[i]);
		words[i] = bufs[i];
	}
	words[keys.GetCount()] = NULL;
    
	// �������N�G�X�g�𑗏o
	ebErr = ::eb_search_multi(m_book, multiId, words);
    if (ebErr != EB_SUCCESS) {
        return 0;
    }

	// �q�b�g���擾
	return GetHits(hits);
}

/**
 * ���������̎�ނ̐����擾
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
 * ���������̃R�[�h���擾
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
 * ���������̑薼���擾
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
 * ���������̌�����̐����擾
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
 * ���������̌�����̑�ڂ��擾
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
 * ���������̌�����̌��ꗗ�����邩
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
 * ���������̌�����̌��ʒu���擾
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
 * ���������̌�����̌��ꗗ���擾
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
    // �e�L�X�g�f�[�^���擾�B
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
 * ���쌠�\�����擾
 */
DicReference* DicSubbook::GetCopyright()
{
	CheckCurVol();

    EB_Error_Code ebErr;
	
	if (!::eb_have_copyright(m_book)) {
		return NULL;
	}

	// �������N�G�X�g�𑗏o
	EB_Position pos;
	ebErr = ::eb_copyright(m_book, &pos);
    if (ebErr != EB_SUCCESS) {
        return NULL;
    }

  	return new DicReference(this, pos);
}

/**
 * ���j���[���擾
 */
DicReference* DicSubbook::GetMenu()
{
	CheckCurVol();

    EB_Error_Code ebErr;
	
	if (!::eb_have_menu(m_book)) {
		return NULL;
	}

	// �������N�G�X�g�𑗏o
	EB_Position pos;
	ebErr = ::eb_menu(m_book, &pos);
    if (ebErr != EB_SUCCESS) {
        return NULL;
    }

  	return new DicReference(this, pos);
}

/**
 * ���o�����擾
 */
wxString DicSubbook::GetHeading(EB_Position* pos)
{
    EB_Error_Code ebErr;
    char heading[MAXLEN_HEADING + 1];
    ssize_t headingLength;
    
	CheckCurVol();
	
    // ���o���̈ʒu�ֈړ��B
    ebErr = ::eb_seek_text(m_book, pos);
    if (ebErr != EB_SUCCESS) {
        return wxT("");
    }

	wxString str;
	
    // ���o�����擾�B
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
 * �e�L�X�g�f�[�^���擾
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
	    // ���߂���Ƃ��͒��f�B
	    // ���L������5�� �u�n��������v�������Ȃ�
	    if (str.length() > (wxString::size_type)DicShare::pageMaxBytes) {
	    	break;
	    }
	    
	    // �e�L�X�g�f�[�^�̈ʒu�ֈړ��B
	    ebErr = ::eb_seek_text(m_book, &p);
	    if (ebErr != EB_SUCCESS) {
	        break;
	    }
	    
	    // �e�L�X�g�f�[�^���擾�B
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
	    
	    // ���̒P��̐����ֈړ��B
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
 * �O�̃e�L�X�g�f�[�^���擾
 */
wxString DicSubbook::GetPrevText()
{
	// �f�[�^�̗L�薳���𔻒肵���ق����ǂ����ȁE�E�E(2006/4/23)
	
    EB_Error_Code ebErr;
    char text[MAXLEN_TEXT + 1];
    ssize_t textLength;
	wxString str = DicShare::htmlHead;
    
	CheckCurVol();
	
	EB_Position p = m_curPos;
	
	for (int i = 0; i < DicShare::pageMaxResults; ++i) {
	    // ���߂���Ƃ��͒��f�B
	    if (str.length() > (wxString::size_type)DicShare::pageMaxBytes) {
	    	break;
	    }
		
	    // �e�L�X�g�f�[�^�̈ʒu�ֈړ��B
	    ebErr = ::eb_seek_text(m_book, &p);
	    if (ebErr != EB_SUCCESS) {
	        break;
	    }
    
	    // �O�̒P��̐����ֈړ��B
		ebErr = ::eb_backward_text(m_book, NULL);
		if (ebErr == EB_ERR_END_OF_CONTENT) {
		    break;
		} else if (ebErr != EB_SUCCESS) {
			break;
		}
		::eb_tell_text(m_book, &p);
	    
	    // �e�L�X�g�f�[�^�̈ʒu�ֈړ��B
	    // ��Hook��Initialize���Ă΂��悤�ɂ��邽��seek���K�v(???)
	    ebErr = ::eb_seek_text(m_book, &p);
	    if (ebErr != EB_SUCCESS) {
	        break;
	    }
	    
	    // �e�L�X�g�f�[�^���擾�B
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
 * ���̃e�L�X�g�f�[�^���擾
 */
wxString DicSubbook::GetNextText()
{
	// �f�[�^�̗L�薳���𔻒肵���ق����ǂ����ȁE�E�E(2006/4/23)
	
	return GetText(&m_nextPos);
}

/**
 * ���݂̃{�����[�����`�F�b�N
 */
void DicSubbook::CheckCurVol()
{
	m_dicBook->CheckCurVol();
	
	m_dicBook->SetCurSubbook(m_subbook);
}

/**
 * �q�b�g���擾
 */
int DicSubbook::GetHits(DicReferences& hits)
{
    EB_Error_Code ebErr;
	EB_Hit ebHits[100];
	int count;
	int total = 0;
	DicReferences tmpHits;

    // �q�b�g�G���g�����擾�B
//    for (;;)
	for (int i = 0; i < DicShare::searchMaxResults / 100; ++i) // �擾���𐧌�
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
 * �����̂��߂̌���擾
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
			// �c����o�͂���B
			wxCharBuffer buf = remain.mb_str(DicBook::convEuc);
			if (!buf.data())
			{
				// EUC�ւ̕ϊ��Ɏ��s�B
				return;
			}
			::snprintf(dst, len, buf);
			break;
		}
		if (extStart >= 0)
		{
			// "{"�̍������o�͂���B
			wxCharBuffer buf = remain.Left(extStart).mb_str(DicBook::convEuc);
			if (!buf.data())
			{
				// EUC�ւ̕ϊ��Ɏ��s�B
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
				// "{XXXX}"�̌`���̎��A�O���̃R�[�h���o�͂���B
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
				// "{XXXX}"�̌`���łȂ����A"{"���o�͂���B
				::snprintf(dst, len, "{");
				++dst;
				--len;
				remain = remain.Mid(1);
			}
		}
	}
}
