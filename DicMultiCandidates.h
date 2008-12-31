// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * ���������̒l���̔z��N���X
 * 
 * $Date: 2006/06/14 13:39:46 $
 */
#ifndef DICMULTICANDIDATES_H_
#define DICMULTICANDIDATES_H_

#include <wx/dynarray.h>

#include "DicMultiCandidate.h"

WX_DEFINE_ARRAY(DicMultiCandidate*, DicMultiCandidateArray);

/**
 * ���������̒l���̔z��N���X
 */
class DicMultiCandidates : public DicMultiCandidateArray {
public:
	virtual ~DicMultiCandidates() {};
	virtual void DeleteAll();
};

#endif /*DICMULTICANDIDATES_H_*/
