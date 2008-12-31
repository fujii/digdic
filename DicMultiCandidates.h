// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 複合検索の値候補の配列クラス
 * 
 * $Date: 2006/06/14 13:39:46 $
 */
#ifndef DICMULTICANDIDATES_H_
#define DICMULTICANDIDATES_H_

#include <wx/dynarray.h>

#include "DicMultiCandidate.h"

WX_DEFINE_ARRAY(DicMultiCandidate*, DicMultiCandidateArray);

/**
 * 複合検索の値候補の配列クラス
 */
class DicMultiCandidates : public DicMultiCandidateArray {
public:
	virtual ~DicMultiCandidates() {};
	virtual void DeleteAll();
};

#endif /*DICMULTICANDIDATES_H_*/
