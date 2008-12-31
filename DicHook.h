// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * �t�b�N�N���X
 * 
 * $Date: 2006/06/16 15:04:22 $
 */
#ifndef _DICHOOK_H_
#define _DICHOOK_H_

#include <eb/eb.h>

/**
 * �t�b�N�N���X
 */
class DicHook {
public:
	DicHook();
	virtual ~DicHook();
	virtual EB_Hookset* GetHookset();

protected:
	EB_Hookset m_hookset;
};

#endif //_DICHOOK_H_
