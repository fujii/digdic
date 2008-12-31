// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 履歴クラス
 * 
 * $Date: 2006/06/07 07:06:08 $
 */
#ifndef DICHISTORY_H_
#define DICHISTORY_H_

#include "DicReferences.h"

/**
 * 履歴クラス
 */
class DicHistory : public DicReferences {
public:
	DicHistory();
	virtual ~DicHistory() {};
	virtual bool HasPrev();
	virtual bool HasNext();
	virtual void SetCurrent(DicReference* ref);
	virtual DicReference* GetCurrent();
	virtual DicReference* Back();
	virtual DicReference* Forward();

protected:
	unsigned int m_pos;
};

#endif /*DICHISTORY_H_*/
