// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * カスタムタグのハンドラ
 * 
 * $Date: 2007/03/25 16:17:14 $
 */
#include <wx/html/m_templ.h>
#include <wx/html/htmlwin.h>
#include <wx/string.h>
#include <wx/statbmp.h>
#include "DicShare.h"

TAG_HANDLER_BEGIN(INDENT, "INDENT")
	TAG_HANDLER_PROC(tag)
	{
		if (!tag.HasParam(wxT("width"))) {
			return false;
		}
		int width;
		tag.GetParamAsInt(wxT("width"), &width);
        m_WParser->GetContainer()->SetIndent(
        	width * m_WParser->GetCharWidth() * 2,
        	wxHTML_INDENT_LEFT);
        return false;
	}
TAG_HANDLER_END(INDENT)

TAG_HANDLER_BEGIN(EXTCHAR, "EXTCHAR")
	TAG_HANDLER_PROC(tag)
	{
		if (!tag.HasParam(wxT("key"))) {
			return false;
		}
		wxString key = tag.GetParam(wxT("key"));
		DicBitmaps& bitmaps = DicShare::bitmaps;
		DicBitmaps::iterator it = bitmaps.find(key);
		if (it == bitmaps.end()) {
			return false;
		}
		wxWindow* wnd = new wxStaticBitmap(
			(wxWindow*)m_WParser->GetWindowInterface()->GetHTMLWindow(), -1, *it->second);
//		wnd->Show(true);
		m_WParser->GetContainer()->InsertCell(new wxHtmlWidgetCell(wnd));
		return false;
	}
TAG_HANDLER_END(EXTCHAR)

TAG_HANDLER_BEGIN(GRAPH, "GRAPH")
	TAG_HANDLER_PROC(tag)
	{
		if (!tag.HasParam(wxT("key"))) {
			return false;
		}
		wxString key = tag.GetParam(wxT("key"));
		DicBitmaps& bitmaps = DicShare::bitmaps;
		DicBitmaps::iterator it = bitmaps.find(key);
		if (it == bitmaps.end()) {
			return false;
		}
		wxWindow* wnd = new wxStaticBitmap(
			(wxWindow*)m_WParser->GetWindowInterface()->GetHTMLWindow(), -1, *it->second);
//		wnd->Show(true);
		m_WParser->GetContainer()->InsertCell(new wxHtmlWidgetCell(wnd));
		return false;
	}
TAG_HANDLER_END(GRAPH)

TAGS_MODULE_BEGIN(DicCustomTag)
	TAGS_MODULE_ADD(INDENT)
	TAGS_MODULE_ADD(EXTCHAR)
	TAGS_MODULE_ADD(GRAPH)
TAGS_MODULE_END(DicCustomTag)
