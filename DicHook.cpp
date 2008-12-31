// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * フッククラス
 * 
 * $Date: 2007/10/01 12:53:46 $
 */
// フックのcontainer引数にDicBookを渡しているがやめる？ 20060419

#include <eb/text.h>
#include <eb/font.h>
#include <eb/binary.h>
#include <wx/string.h>
#include <wx/image.h>
#include <wx/mstream.h>
#include <wx/file.h>
#include "DicHook.h"
#include "DicSubbook.h"
#include "DicShare.h"

#define HOOK_FUNC(name) \
	EB_Error_Code name(EB_Book* book, EB_Appendix* appendix, void* container, EB_Hook_Code code, int argc, const unsigned int* argv)
	
static HOOK_FUNC(Initialize);
static HOOK_FUNC(BeginNarrow);
static HOOK_FUNC(EndNarrow);
static HOOK_FUNC(BeginSubscript);
static HOOK_FUNC(EndSubscript);
static HOOK_FUNC(SetIndent);
static HOOK_FUNC(Newline);
static HOOK_FUNC(BeginSuperscript);
static HOOK_FUNC(EndSuperscript);
static HOOK_FUNC(BeginNoNewline);
static HOOK_FUNC(EndNoNewline);
static HOOK_FUNC(BeginEmphasis);
static HOOK_FUNC(EndEmphasis);
static HOOK_FUNC(BeginCandidate);
static HOOK_FUNC(EndCandidateLeaf);
static HOOK_FUNC(EndCandidateGroup);
static HOOK_FUNC(BeginReference);
static HOOK_FUNC(EndReference);
static HOOK_FUNC(BeginKeyword);
static HOOK_FUNC(EndKeyword);
static HOOK_FUNC(BeginDecoration);
static HOOK_FUNC(EndDecoration);
static HOOK_FUNC(NarrowFont);
static HOOK_FUNC(WideFont);
static HOOK_FUNC(Iso8859_1);
static HOOK_FUNC(NarrawJisx0208_1);
static HOOK_FUNC(WideJisx0208_1);
static HOOK_FUNC(Gb2312);
static HOOK_FUNC(BeginMonoGraphic);
static HOOK_FUNC(EndMonoGraphic);
//static HOOK_FUNC(BeginGrayGraphic);
//static HOOK_FUNC(EndGrayGraphic);
static HOOK_FUNC(BeginColorBmp);
static HOOK_FUNC(BeginColorJpeg);
static HOOK_FUNC(EndColorGraphic);
static HOOK_FUNC(BeginInColorBmp);
static HOOK_FUNC(BeginInColorJpeg);
static HOOK_FUNC(EndInColorGraphic);
static HOOK_FUNC(BeginGraphicReference);
static HOOK_FUNC(EndGraphicReference);
static HOOK_FUNC(GraphicReference);
static HOOK_FUNC(BeginWave);
static HOOK_FUNC(EndWave);
static HOOK_FUNC(BeginMpeg);
static HOOK_FUNC(EndMpeg);

static void PutIndent(EB_Book* book);
static wxString ReadGraphic(DicBook* b, int page, int offset,
							long type = wxBITMAP_TYPE_ANY);
static char RevChar(char c);

static bool m_firstLine;	// 最初の行か
static bool m_firstIndent;
static bool m_indent;
static int m_ref;
static int m_width;
static int m_height;
static wxString m_graphKey;

static wxCharBuffer m_keywordHead;
static wxCharBuffer m_keywordFoot;
static wxCharBuffer m_decorationHead;
static wxCharBuffer m_decorationFoot;
static wxCharBuffer m_emphasisHead;
static wxCharBuffer m_emphasisFoot;
static wxCharBuffer m_superscriptHead;
static wxCharBuffer m_superscriptFoot;
static wxCharBuffer m_subscriptHead;
static wxCharBuffer m_subscriptFoot;
static wxCharBuffer m_newLine;
static wxCharBuffer m_noNewlineHead;
static wxCharBuffer m_noNewlineFoot;

/**
 * コンストラクタ
 */
DicHook::DicHook()
{
	::eb_initialize_hookset(&m_hookset);
	const EB_Hook hooks[] = {
		{EB_HOOK_INITIALIZE,			Initialize},
		{EB_HOOK_BEGIN_NARROW,			BeginNarrow},
		{EB_HOOK_END_NARROW,			EndNarrow},
		{EB_HOOK_BEGIN_SUBSCRIPT,		BeginSubscript},
		{EB_HOOK_END_SUBSCRIPT,			EndSubscript},
		{EB_HOOK_SET_INDENT,			SetIndent},
		{EB_HOOK_NEWLINE,				Newline},
		{EB_HOOK_BEGIN_SUPERSCRIPT,		BeginSuperscript},
		{EB_HOOK_END_SUPERSCRIPT,		EndSuperscript},
		{EB_HOOK_BEGIN_NO_NEWLINE,		BeginNoNewline},
		{EB_HOOK_END_NO_NEWLINE,		EndNoNewline},
		{EB_HOOK_BEGIN_EMPHASIS,		BeginEmphasis},
		{EB_HOOK_END_EMPHASIS,			EndEmphasis},
		{EB_HOOK_BEGIN_CANDIDATE,		BeginCandidate},
		{EB_HOOK_END_CANDIDATE_LEAF,	EndCandidateLeaf},
		{EB_HOOK_END_CANDIDATE_GROUP,	EndCandidateGroup},
		{EB_HOOK_BEGIN_REFERENCE,		BeginReference},
		{EB_HOOK_END_REFERENCE,			EndReference},
		{EB_HOOK_BEGIN_KEYWORD,			BeginKeyword},
		{EB_HOOK_END_KEYWORD,			EndKeyword},
		{EB_HOOK_BEGIN_DECORATION,		BeginDecoration},
		{EB_HOOK_END_DECORATION,		EndDecoration},
		{EB_HOOK_NARROW_FONT,			NarrowFont},
		{EB_HOOK_WIDE_FONT,				WideFont},
		{EB_HOOK_ISO8859_1,				Iso8859_1},
		{EB_HOOK_NARROW_JISX0208,		NarrawJisx0208_1},
		{EB_HOOK_WIDE_JISX0208,			WideJisx0208_1},
		{EB_HOOK_GB2312,				Gb2312},
		{EB_HOOK_BEGIN_MONO_GRAPHIC,	BeginMonoGraphic},
		{EB_HOOK_END_MONO_GRAPHIC,		EndMonoGraphic},
//		{EB_HOOK_BEGIN_GRAY_GRAPHIC,	BeginGrayGraphic},
//		{EB_HOOK_END_GRAY_GRAPHIC,		EndGrayGraphic},
		{EB_HOOK_BEGIN_COLOR_BMP,		BeginColorBmp},
		{EB_HOOK_BEGIN_COLOR_JPEG,		BeginColorJpeg},
		{EB_HOOK_END_COLOR_GRAPHIC,		EndColorGraphic},
		{EB_HOOK_BEGIN_IN_COLOR_BMP,	BeginInColorBmp},
		{EB_HOOK_BEGIN_IN_COLOR_JPEG,	BeginInColorJpeg},
		{EB_HOOK_END_IN_COLOR_GRAPHIC,	EndInColorGraphic},
		{EB_HOOK_BEGIN_GRAPHIC_REFERENCE, BeginGraphicReference},
		{EB_HOOK_END_GRAPHIC_REFERENCE,	EndGraphicReference},
		{EB_HOOK_GRAPHIC_REFERENCE,		GraphicReference},
		{EB_HOOK_BEGIN_WAVE,			BeginWave},
		{EB_HOOK_END_WAVE,				EndWave},
		{EB_HOOK_BEGIN_MPEG,			BeginMpeg},
		{EB_HOOK_END_MPEG,				EndMpeg},
		{EB_HOOK_NULL,					NULL}
	};
	::eb_set_hooks(&m_hookset, hooks);
}

/**
 * デストラクタ
 */
DicHook::~DicHook()
{
	::eb_finalize_hookset(&m_hookset);
}

/**
 * フックセットを取得
 */
EB_Hookset* DicHook::GetHookset()
{
	return &m_hookset;
}

HOOK_FUNC(Initialize)
{
	m_keywordHead = DicShare::keywordHead.mb_str();
	m_keywordFoot = DicShare::keywordFoot.mb_str();
	m_decorationHead = DicShare::decorationHead.mb_str();
	m_decorationFoot = DicShare::decorationFoot.mb_str();
	m_emphasisHead = DicShare::emphasisHead.mb_str();
	m_emphasisFoot = DicShare::emphasisFoot.mb_str();
	m_superscriptHead = DicShare::superscriptHead.mb_str();
	m_superscriptFoot = DicShare::superscriptFoot.mb_str();
	m_subscriptHead = DicShare::subscriptHead.mb_str();
	m_subscriptFoot = DicShare::subscriptFoot.mb_str();
	m_newLine = DicShare::newLine.mb_str();
	m_noNewlineHead = DicShare::noNewlineHead.mb_str();
	m_noNewlineFoot = DicShare::noNewlineFoot.mb_str();
	
	m_firstLine = true;
	m_indent = 0;
//	::eb_write_text_string(book, "<font color=blue>");
	return 0;
}

HOOK_FUNC(BeginNarrow)
{
	return 0;
}

HOOK_FUNC(EndNarrow)
{
	return 0;
}

HOOK_FUNC(BeginSubscript)
{
	::eb_write_text_string(book, m_subscriptHead);
	return 0;
}

HOOK_FUNC(EndSubscript)
{
	::eb_write_text_string(book, m_subscriptFoot);
	return 0;
}

HOOK_FUNC(SetIndent)
{
	if (m_firstLine) {
		m_firstIndent = argv[1];
		m_indent = 0;
	} else {
		m_indent = argv[1] - m_firstIndent;
	}
	::PutIndent(book);
	return 0;
}

HOOK_FUNC(Newline)
{
	if (m_firstLine) {
//		::eb_write_text_string(book, "</font>\n<br>\n");
		::eb_write_text_string(book, m_newLine);
		m_firstLine = false;
	} else {
		::eb_write_text_string(book, m_newLine);
		::PutIndent(book);
	}
	return 0;
}

HOOK_FUNC(BeginSuperscript)
{
	::eb_write_text_string(book, m_superscriptHead);
	return 0;
}
	
HOOK_FUNC(EndSuperscript)
{
	::eb_write_text_string(book, m_superscriptFoot);
	return 0;
}

HOOK_FUNC(BeginNoNewline)
{
	::eb_write_text_string(book, m_noNewlineHead);
	return 0;
}

HOOK_FUNC(EndNoNewline)
{
	::eb_write_text_string(book, m_noNewlineFoot);
	return 0;
}

HOOK_FUNC(BeginEmphasis)
{
	::eb_write_text_string(book, m_emphasisHead);
	return 0;
}

HOOK_FUNC(EndEmphasis)
{
	::eb_write_text_string(book, m_emphasisFoot);
	return 0;
}

HOOK_FUNC(BeginCandidate)
{
	// メニューの中にCandidateGroupが出てくることがあるので、リンクとして表示する。
	m_ref = DicShare::references.GetCount();
	char tag[32];
	::snprintf(tag, 32, "<a href=%u>", m_ref);
	::eb_write_text_string(book, tag);
	return 0;
}

HOOK_FUNC(EndCandidateLeaf)
{
	return 0;
}

HOOK_FUNC(EndCandidateGroup)
{
	// メニューの中にCandidateGroupが出てくることがあるので、リンクとして表示する。
	DicSubbook* subbook = (DicSubbook*)container;
	EB_Position pos;
	pos.page = argv[1];
	pos.offset = argv[2];

	DicReference* ref = new DicReference(subbook, pos);
	DicShare::references.Add(ref);
	
	::eb_write_text_string(book, "</a>");
	return 0;
}

HOOK_FUNC(BeginReference)
{
	m_ref = DicShare::references.GetCount();
	char tag[32];
	::snprintf(tag, 32, "<a href=%u>", m_ref);
	::eb_write_text_string(book, tag);
	return 0;
}

HOOK_FUNC(EndReference)
{
	DicSubbook* subbook = (DicSubbook*)container;
	EB_Position pos;
	pos.page = argv[1];
	pos.offset = argv[2];

	DicReference* ref = new DicReference(subbook, pos);
	DicShare::references.Add(ref);
	
	::eb_write_text_string(book, "</a>");
	return 0;
}

HOOK_FUNC(BeginKeyword)
{
	::eb_write_text_string(book, m_keywordHead);
	return 0;
}

HOOK_FUNC(EndKeyword)
{
	::eb_write_text_string(book, m_keywordFoot);
	return 0;
}

HOOK_FUNC(BeginDecoration)
{
	::eb_write_text_string(book, m_decorationHead);
	return 0;
}

HOOK_FUNC(EndDecoration)
{
	::eb_write_text_string(book, m_decorationFoot);
	return 0;
}

HOOK_FUNC(NarrowFont)
{
	DicSubbook* subbook = (DicSubbook*)container;
	DicBook* b = subbook->GetBook();
	wxString key = wxString::Format(wxT("%d/%d/narrow/%d"),
//		b->GetIndex(), b->GetSubbook(), argv[0]);
		book, b->GetCurSubbook(), argv[0]);
	DicBitmaps& bitmaps = DicShare::bitmaps;
	if (bitmaps.find(key) == bitmaps.end()) {
		// ビットマップを作成する。
		char data[16];
		::eb_set_font(book, EB_FONT_16);
		::eb_narrow_font_character_bitmap(book, argv[0], data);
		char xbm[16];
		for (int i = 0; i < 16; ++i) {
			xbm[i] = RevChar(data[i]);
		}
		wxBitmap* bitmap = new wxBitmap(xbm, 8, 16);
		bitmaps[key] = bitmap;
	}
	wxString tag = wxT("<extchar key=") + key + wxT(">");
	wxCharBuffer buf = tag.mb_str();
	if (buf.data())
	{
		::eb_write_text_string(book, buf);
	}
	return 0;
}

HOOK_FUNC(WideFont)
{
	DicSubbook* subbook = (DicSubbook*)container;
	DicBook* b = subbook->GetBook();
	wxString key = wxString::Format(wxT("%d/%d/wide/%d"),
//		b->GetIndex(), b->GetSubbook(), argv[0]);
		book, b->GetCurSubbook(), argv[0]);
	DicBitmaps& bitmaps = DicShare::bitmaps;
	if (bitmaps.find(key) == bitmaps.end()) {
		// ビットマップを作成する。
		char data[2*16];
		::eb_set_font(book, EB_FONT_16);
		::eb_wide_font_character_bitmap(book, argv[0], data);
		char xbm[2*16];
		for (int i = 0; i < 32; ++i) {
			xbm[i] = RevChar(data[i]);
		}
		wxBitmap* bitmap = new wxBitmap(xbm, 16, 16);
		bitmaps[key] = bitmap;
	}
	wxString tag = wxT("<extchar key=") + key + wxT(">");
	wxCharBuffer buf = tag.mb_str();
	if (buf.data())
	{
		::eb_write_text_string(book, buf);
	}
	return 0;
}

HOOK_FUNC(Iso8859_1)
{
	::eb_write_text_byte1(book, argv[0]);
	return 0;
}

HOOK_FUNC(NarrawJisx0208_1)
{
	// 空白の場合は&nbsp;に変換する。
	if (argv[0] == 0xa1a1) {
		::eb_write_text_string(book, "&nbsp;");
		return 0;
	} else {
		return ::eb_hook_euc_to_ascii(book, appendix, container, code, argc, argv);
	}
}

HOOK_FUNC(WideJisx0208_1)
{
	int byte1 = (argv[0] >> 8)& 0xFF;
	int byte2 = argv[0] & 0xFF;
	::eb_write_text_byte2(book, byte1, byte2);
	return 0;
}

HOOK_FUNC(Gb2312)
{
	int byte1 = (argv[0] >> 8)& 0xFF;
	int byte2 = argv[0] & 0xFF;
	::eb_write_text_byte2(book, byte1, byte2);
	return 0;
}

HOOK_FUNC(BeginMonoGraphic)
{
	m_height = argv[2];
	m_width = argv[3];
	return 0;
}

HOOK_FUNC(EndMonoGraphic)
{
	DicSubbook* subbook = (DicSubbook*)container;
	DicBook* b = subbook->GetBook();
	wxString key = wxString::Format(wxT("%d/%d/mono/%d/%d"),
//		b->GetIndex(), b->GetSubbook(), argv[1], argv[2]);
		book, b->GetCurSubbook(), argv[1], argv[2]);

	DicBitmaps& bitmaps = DicShare::bitmaps;
	if (bitmaps.find(key) == bitmaps.end()) {
		EB_Position pos;
		pos.page = argv[1];
		pos.offset = argv[2];
		::eb_set_binary_mono_graphic(book, &pos, m_width, m_height);

		ssize_t len;
		unsigned char head[6];
		::eb_read_binary(book, 6, (char*)head, &len);
		size_t size = head[5];
		size <<= 8;
		size += head[4];
		size <<= 8;
		size += head[3];
		size <<= 8;
		size += head[2];
		char* data = new char[size];
		for (int i = 0; i < 6; ++i) {
			data[i] = head[i];
		}
		::eb_read_binary(book, size - 6, data + 6, &len);
		
		wxMemoryInputStream stream(data, size);
		wxImage image(stream, wxBITMAP_TYPE_BMP);
		wxBitmap* bitmap = new wxBitmap(image);
		bitmaps[key] = bitmap;
		
		delete[] data;
	}

	::eb_write_text_string(book, "<br>\n");
	::PutIndent(book);
	wxString tag = wxT("<graph key=") + key + wxT(">\n<br>\n");
	wxCharBuffer buf = tag.mb_str();
	if (buf.data())
	{
		::eb_write_text_string(book, buf);
	}
	
	return 0;
}

HOOK_FUNC(BeginColorBmp)
{
	DicSubbook* subbook = (DicSubbook*)container;
	DicBook* b = subbook->GetBook();
	m_graphKey = ReadGraphic(b, argv[2], argv[3],
							wxBITMAP_TYPE_BMP);	
	return 0;
}

HOOK_FUNC(BeginColorJpeg)
{
	DicSubbook* subbook = (DicSubbook*)container;
	DicBook* b = subbook->GetBook();
	m_graphKey = ReadGraphic(b, argv[2], argv[3],
							wxBITMAP_TYPE_JPEG);	
	return 0;
}

HOOK_FUNC(EndColorGraphic)
{
	::eb_write_text_string(book, "<br>\n");
	::PutIndent(book);
	wxString tag = wxT("<graph key=") + m_graphKey + wxT(">\n<br>\n");
	wxCharBuffer buf = tag.mb_str();
	if (buf.data())
	{
		::eb_write_text_string(book, buf);
	}
	return 0;
}

HOOK_FUNC(BeginInColorBmp)
{
	DicSubbook* subbook = (DicSubbook*)container;
	DicBook* b = subbook->GetBook();
	m_graphKey = ReadGraphic(b, argv[2], argv[3],
							wxBITMAP_TYPE_BMP);	
	return 0;
}

HOOK_FUNC(BeginInColorJpeg)
{
	DicSubbook* subbook = (DicSubbook*)container;
	DicBook* b = subbook->GetBook();
	m_graphKey = ReadGraphic(b, argv[2], argv[3],
							wxBITMAP_TYPE_JPEG);	
	return 0;
}

HOOK_FUNC(EndInColorGraphic)
{
	wxString tag = wxT("<graph key=") + m_graphKey + wxT(">\n");
	wxCharBuffer buf = tag.mb_str();
	if (buf.data())
	{
		::eb_write_text_string(book, buf);
	}
	return 0;
}

HOOK_FUNC(BeginGraphicReference)
{
// 広辞苑-海亀にサンプルあり。
	return 0;
}

HOOK_FUNC(EndGraphicReference)
{
	return 0;
}

HOOK_FUNC(GraphicReference)
{
	DicSubbook* subbook = (DicSubbook*)container;
	DicBook* b = subbook->GetBook();
	wxString key = ReadGraphic(b, argv[1], argv[2]);	
	::eb_write_text_string(book, "<br>\n");
	::PutIndent(book);
	wxString tag = wxT("<graph key=") + key + wxT(">\n<br>\n");
	wxCharBuffer buf = tag.mb_str();
	if (buf.data())
	{
		::eb_write_text_string(book, buf);
	}
	return 0;
}

HOOK_FUNC(BeginWave)
{
	return 0;
}

HOOK_FUNC(EndWave)
{
	return 0;
}

HOOK_FUNC(BeginMpeg)
{
	return 0;
}

HOOK_FUNC(EndMpeg)
{
	return 0;
}

/**
 * インデントを出力
 */
void PutIndent(EB_Book* book)
{
	char tag[32];
	::snprintf(tag, 32, "<indent width=%d>", m_indent);
	::eb_write_text_string(book, tag);
}

/**
 * 画像を読み込む
 * 
 * @param b	本
 * @param page ページ
 * @param offset オフセット
 * @param type 画像の種類
 * @return キー
 */
wxString ReadGraphic(DicBook* b, int page, int offset, long type)
{
	wxString key = wxString::Format(wxT("%d/%d/graph/%d/%d"),
//		b->GetIndex(), b->GetCurSubbook(), page, offset);
		b->GetEbBook(), b->GetCurSubbook(), page, offset);

	DicBitmaps& bitmaps = DicShare::bitmaps;
	if (bitmaps.find(key) == bitmaps.end()) {
		EB_Position pos;
		pos.page = page;
		pos.offset = offset;
		EB_Book* book = b->GetEbBook();
		::eb_set_binary_color_graphic(book, &pos);
		wxMemoryOutputStream out;
		ssize_t len;
		char data[1024];
		for (;;) {
			::eb_read_binary(book, 1024, data, &len);
			if (len <= 0) {
				break;
			}
			out.Write(data, len);
		}
		wxMemoryInputStream stream(out);
		wxImage image(stream, type);
		wxBitmap* bitmap = new wxBitmap(image);
		bitmaps[key] = bitmap;
	}
	
	return key;
}

/**
 * 0/1とビット順を反転
 */
char RevChar(char c)
{
//	c = ~c;
	char out = 0;
	if (c & 0x80) { out |= 0x01; }
	if (c & 0x40) { out |= 0x02; }
	if (c & 0x20) { out |= 0x04; }
	if (c & 0x10) { out |= 0x08; }
	if (c & 0x08) { out |= 0x10; }
	if (c & 0x04) { out |= 0x20; }
	if (c & 0x02) { out |= 0x40; }
	if (c & 0x01) { out |= 0x80; }
	return out;
}
