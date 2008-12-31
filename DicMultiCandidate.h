// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 複合検索の値候補クラス
 * 
 * $Date: 2006/06/22 10:18:38 $
 */
#ifndef DICMULTICANDIDATE_H_
#define DICMULTICANDIDATE_H_

#include <eb/eb.h>
#include <wx/string.h>

/**
 * 複合検索の値候補クラス
 */
class DicMultiCandidate {
public:
	DicMultiCandidate(const char* data);
	DicMultiCandidate(const char* data, const EB_Position& groupPos);
	virtual ~DicMultiCandidate();
	virtual wxString GetString();
	virtual bool HasGroup();
	virtual EB_Position GetGroupPos();
	
protected:
	char* m_data;
	bool m_hasGroup;
	EB_Position m_groupPos;
};

#endif /*DICMULTICANDIDATE_H_*/
