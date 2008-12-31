// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * ���������L�[���t�b�N�N���X
 * 
 * $Date: 2006/06/16 15:03:07 $
 */
#ifndef DICCANDIDATEHOOK_H_
#define DICCANDIDATEHOOK_H_

#include <eb/eb.h>

/**
 * ���������L�[���t�b�N�N���X
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
