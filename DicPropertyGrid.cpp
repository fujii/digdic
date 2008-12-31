// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * プロパティグリッドクラス
 * 
 * $Date: 2006/06/26 15:57:54 $
 */
#include "DicPropertyGrid.h"

/**
 * 仮想サイズを設定
 * 
 * 素のままではなぜか1行分長いので、スクロールバーが要らない時
 * も表示されてしまう。それを回避するためにオーバーライドした。
 */
void DicPropertyGrid::DoSetVirtualSize(int x, int y)
{
    wxScrolledWindow::DoSetVirtualSize(x, y - m_lineHeight);
}

/**
 * 変更を反映
 */
void DicPropertyGrid::CommitChanges() {
	CommitChangesFromEditor();
}
