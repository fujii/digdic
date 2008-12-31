// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 複合検索キー候補フッククラス
 * 
 * $Date: 2006/06/16 15:03:07 $
 */
#ifndef DICCANDIDATEHOOK_H_
#define DICCANDIDATEHOOK_H_

#include <eb/eb.h>

/**
 * 複合検索キー候補フッククラス
 */
class DicCandidateHook {
public:
	DicCandidateHook();
	virtual ~DicCandidateHook();
	virtual EB_Hookset* GetHookset();

protected:
	EB_Hookset m_hookset;
};

#endif /*DICCANDIDATEHOOK_H_*/
