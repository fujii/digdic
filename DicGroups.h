// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * �O���[�v(���{�̔z��)�̔z��N���X
 * 
 * $Date: 2006/07/07 15:16:25 $
 */
#ifndef DICGROUPS_H_
#define DICGROUPS_H_

#include <wx/dynarray.h>
#include "DicSubbooks.h"

WX_DEFINE_ARRAY(DicSubbooks*, DicGroupArray);

/**
 * ���{�̔z��N���X
 */
class DicGroups : public DicGroupArray {
public:
	virtual ~DicGroups() {};
	virtual void DeleteAll();
	virtual void Initialize();
	virtual void SaveConfig();
};

#endif /*DICGROUPS_H_*/
