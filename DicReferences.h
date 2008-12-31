// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 参照の配列クラス
 * 
 * $Date: 2006/06/07 07:06:08 $
 */
#ifndef _DICREFERENCES_H_
#define _DICREFERENCES_H_

#include <wx/dynarray.h>

#include "DicReference.h"

WX_DEFINE_ARRAY(DicReference*, DicReferenceArray);

/**
 * 参照の配列クラス
 */
class DicReferences : public DicReferenceArray {
public:
	virtual ~DicReferences() {};
	virtual void Append(const DicReferences& a);
	virtual void DeleteAll();
	virtual bool Exists(DicReference* hit, int max = 10);
};

#endif //_DICREFERENCES_H_
