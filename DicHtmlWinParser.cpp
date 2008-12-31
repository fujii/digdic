// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * DicHtmlWinParserクラス
 * 
 * $Date: 2007/03/25 15:27:24 $
 */
#include "DicHtmlWinParser.h"

/**
 * コンストラクタ
 */
//DicHtmlWinParser::DicHtmlWinParser(wxHtmlWindow *wnd) :
DicHtmlWinParser::DicHtmlWinParser(wxHtmlWindowInterface* wnd) :
	wxHtmlWinParser(wnd)
{
	m_lastWordCell = NULL;
};

/**
 * テキスト追加
 */
void DicHtmlWinParser::AddText(const wxChar* txt)
{
	size_t len = wxStrlen(txt);
	wxChar* temp = new wxChar[len + 1];
	while (*txt) {
		const wxChar* next;
		GetWord(temp, txt, &next);
	    wxHtmlCell* c = new wxHtmlWordCell(temp, *(GetDC()));
	    const wxHtmlLinkInfo& link = GetLink();
		if (link.GetHref() != wxEmptyString) {
			c->SetLink(link);
		}
	    GetContainer()->InsertCell(c);
	    txt = next;
	}
	delete[] temp;
/*
    wxChar nbsp = GetEntitiesParser()->GetCharForCode(160); //nbsp
    wxHtmlCell* c;
	size_t len = wxStrlen(txt);
	register wxChar d;
	wxChar temp[2];
	temp[1] = 0;
	for (size_t i = 0; i < len; ++i) {
   		d = temp[0] = txt[i];
        if (d == wxT('\n') || d == wxT('\r') || d == wxT(' ') || d == wxT('\t')) {
        	continue;
        } else if (d == nbsp) {
        	temp[0] = wxT(' ');
        }
        c = new wxHtmlWordCell(temp, *(GetDC()));
	    GetContainer()->InsertCell(c);
//	    ((wxHtmlWordCell*)c)->SetPreviousWord(m_lastWordCell);
//	    m_lastWordCell = (wxHtmlWordCell*)c;
	}
*/
}

/**
 * 単語を取得
 */
void DicHtmlWinParser::GetWord(wxChar* out, const wxChar* txt, const wxChar** p)
{
    wxChar nbsp = GetEntitiesParser()->GetCharForCode(160 /* nbsp */);
	register wxChar d = txt[0];
	if (!d) {
		*p = txt;
		out[0] = 0;
		return;
	}
	if (d == wxT('\n') || d == wxT('\r') || d == wxT(' ') || d == wxT('\t')) {
		*p = txt + 1;
		out[0] = 0;
		return;
	}
    if (d == nbsp) {
    	d = wxT(' ');
    }
	out[0] = d;
	int type = GetCharType(d);
	size_t i = 1;
	size_t n = 1;
	for (; type != 0 && txt[i]; ++i) {
		d = txt[i];
        if (d == wxT('\n') || d == wxT('\r') || d == wxT(' ') || d == wxT('\t')) {
        	continue;
        }
        if (d == nbsp) {
        	d = wxT(' ');
        }
		if (GetCharType(d) != type) {
			break;
		}
		out[n] = d;
		++n;
	}
	out[n] = 0;
	*p = txt + i;
	return;
}

/**
 * 文字の種類を取得
 */
int DicHtmlWinParser::GetCharType(wxChar d)
{
	if ((d >= wxT('0') && d <= wxT('9'))
		||(d >= wxT('a') && d <= wxT('z'))
		|| (d >= wxT('A') && d <= wxT('Z'))) {
		// 英数
		return 1;
	}
#if wxUSE_UNICODE
/*
// 	if (d >= 0x3041 && d < 0x309e) {
 	if (d >= 0x3041 && d < 0x309a) {
		// ひらがな
		return 2;
	}
*/
//	if (d >= 0x30a1 && d <= 0x30fe) {
	if ((d >= 0x309b && d <= 0x309e) // 「゛」等もカタカナ扱いにする
		|| (d >= 0x30a1 && d <= 0x30fa) // 「・」は除く
		|| (d >= 0x30fc && d <= 0x30fe)
		|| (d >= 0xff66 && d <= 0xff9f)) { // 半角カナ
		// カタカナ
		return 3;
	}
	if (d >= 0x4e00 && d <= 0x9fff) {
		// 漢字
		return 4;
	}
	if ((d >= 0xff10 && d <= 0xff19)	// ０～９
		||(d >= 0xff21 && d <= 0xff3a)	// Ａ～Ｚ
		|| (d >= 0xff41 && d <= 0xff5a)) { // ａ～ｚ
		// 全角英数
		return 5;
	}
#endif
	return 0;
}
