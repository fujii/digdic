// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * ‹¤—L‚·‚é‚à‚Ì
 * 
 * $Date: 2007/10/31 16:13:50 $
 */
#include "DicShare.h"

wxString DicShare::iniFile;
DicBooks DicShare::books;
DicSubbooks DicShare::subbooks;
DicGroups DicShare::groups;
DicReferences DicShare::hits;
DicHistory DicShare::history;
DicBitmaps DicShare::bitmaps;
DicReferences DicShare::references;

int DicShare::pageMaxResults;
int DicShare::pageMaxBytes;
int DicShare::searchMaxResults;

wxString DicShare::htmlHead;
wxString DicShare::htmlFoot;
wxString DicShare::keywordHead;
wxString DicShare::keywordFoot;
wxString DicShare::decorationHead;
wxString DicShare::decorationFoot;
wxString DicShare::emphasisHead;
wxString DicShare::emphasisFoot;
wxString DicShare::superscriptHead;
wxString DicShare::superscriptFoot;
wxString DicShare::subscriptHead;
wxString DicShare::subscriptFoot;
wxString DicShare::newLine;
wxString DicShare::noNewlineHead;
wxString DicShare::noNewlineFoot;

/**
 * Œã•Ð•t‚¯
 */
void DicShare::Clean()
{
    DicShare::books.DeleteAll();
    DicShare::subbooks.DeleteAll();
    DicShare::groups.DeleteAll();
	DicShare::hits.DeleteAll();
	DicShare::history.DeleteAll();
	DicShare::bitmaps.DeleteAll();
	DicShare::references.DeleteAll();
}

/**
 * Ý’è‚ð“Ç‚Ýž‚Þ
 * 
 * @param config Ý’è
 */
void DicShare::LoadConfig(wxConfigBase* config)
{
	if (!config)
	{
		config = wxConfigBase::Get();
	}
	
	config->SetPath(wxT("/Common"));
	pageMaxResults = config->Read(wxT("PageMaxResults"), (long)100);
	pageMaxBytes = config->Read(wxT("PageMaxBytes"), (long)30000);
	searchMaxResults = config->Read(wxT("SearchMaxResults"), (long)1000);
	
	config->SetPath(wxT("/Html"));
	htmlHead = config->Read(wxT("HtmlHead"), wxT("<html><body>"));
	htmlFoot = config->Read(wxT("HtmlFoot"), wxT("</body></html>"));
	keywordHead = config->Read(wxT("KeywordHead"), wxT("<font color=blue><b>"));
	keywordFoot = config->Read(wxT("KeywordFoot"), wxT("</b></font>"));
	decorationHead = config->Read(wxT("DecorationHead"), wxT("<b>"));
	decorationFoot = config->Read(wxT("DecorationFoot"), wxT("</b>"));
	emphasisHead = config->Read(wxT("EmphasisHead"), wxT("<i>"));
	emphasisFoot = config->Read(wxT("EmphasisFoot"), wxT("</i>"));
	superscriptHead = config->Read(wxT("SuperscriptHead"), wxT("<sup>"));
	superscriptFoot = config->Read(wxT("SuperscriptFoot"), wxT("</sup>"));
	subscriptHead = config->Read(wxT("SubscriptHead"), wxT("<sub>"));
	subscriptFoot = config->Read(wxT("SubscriptFoot"), wxT("</sub>"));
	newLine = config->Read(wxT("NewLine"), wxT("<br>\n"));
	noNewlineHead = config->Read(wxT("NoNewlineHead"), wxT("<nobr>"));
	noNewlineFoot = config->Read(wxT("NoNewlineFoot"), wxT("</nobr>"));
}

/**
 * Ý’è‚ð•Û‘¶
 * 
 * @param config Ý’è
 */
void DicShare::SaveConfig(wxConfigBase* config)
{
	if (!config)
	{
		config = wxConfigBase::Get();
	}
	
	config->SetPath(wxT("/Common"));
	config->Write(wxT("PageMaxResults"), pageMaxResults);
	config->Write(wxT("PageMaxBytes"), pageMaxBytes);
	config->Write(wxT("SearchMaxResults"), searchMaxResults);
	
	config->SetPath(wxT("/Html"));
	config->Write(wxT("HtmlHead"), htmlHead);
	config->Write(wxT("HtmlFoot"), htmlFoot);
	config->Write(wxT("KeywordHead"), keywordHead);
	config->Write(wxT("KeywordFoot"), keywordFoot);
	config->Write(wxT("DecorationHead"), decorationHead);
	config->Write(wxT("DecorationFoot"), decorationFoot);
	config->Write(wxT("EmphasisHead"), emphasisHead);
	config->Write(wxT("EmphasisFoot"), emphasisFoot);
	config->Write(wxT("SuperscriptHead"), superscriptHead);
	config->Write(wxT("SuperscriptFoot"), superscriptFoot);
	config->Write(wxT("SubscriptHead"), subscriptHead);
	config->Write(wxT("SubscriptFoot"), subscriptFoot);
	config->Write(wxT("NewLine"), newLine);
	config->Write(wxT("NoNewlineHead"), noNewlineHead);
	config->Write(wxT("NoNewlineFoot"), noNewlineFoot);
}
