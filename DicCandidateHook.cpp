// Copyright (C) 2006 NISHIMURA Tsuyoshi
// License: GPL v2 or (at your option) any later version
/** @file
 * 
 * 複合検索キー候補フッククラス
 * 
 * $Date: 2006/06/22 10:19:25 $
 */

#include <eb/text.h>
#include "DicCandidateHook.h"
#include "DicMultiCandidates.h"

#define HOOK_FUNC(name) \
	EB_Error_Code name(EB_Book* book, EB_Appendix* appendix, void* container, EB_Hook_Code code, int argc, const unsigned int* argv)

static HOOK_FUNC(BeginCandidate);
static HOOK_FUNC(EndCandidateLeaf);
static HOOK_FUNC(EndCandidateGroup);
static HOOK_FUNC(NarrowFont);
static HOOK_FUNC(WideFont);

/**
 * コンストラクタ
 */
DicCandidateHook::DicCandidateHook()
{
	::eb_initialize_hookset(&m_hookset);
	const EB_Hook hooks[] = {
		{EB_HOOK_BEGIN_CANDIDATE,		BeginCandidate},
		{EB_HOOK_END_CANDIDATE_LEAF,	EndCandidateLeaf},
		{EB_HOOK_END_CANDIDATE_GROUP,	EndCandidateGroup},
		{EB_HOOK_NARROW_FONT,			NarrowFont},
		{EB_HOOK_WIDE_FONT,				WideFont},
		{EB_HOOK_NULL,					NULL}
	};
	::eb_set_hooks(&m_hookset, hooks);
}

/**
 * デストラクタ
 */
DicCandidateHook::~DicCandidateHook()
{
	::eb_finalize_hookset(&m_hookset);
}

/**
 * フックセットを取得
 */
EB_Hookset* DicCandidateHook::GetHookset()
{
	return &m_hookset;
}

HOOK_FUNC(BeginCandidate)
{
	return 0;
}

HOOK_FUNC(EndCandidateLeaf)
{
	DicMultiCandidates* candidates = (DicMultiCandidates*)container;
	candidates->Add(new DicMultiCandidate(::eb_current_candidate(book)));
	return 0;
}

HOOK_FUNC(EndCandidateGroup)
{
	DicMultiCandidates* candidates = (DicMultiCandidates*)container;
	EB_Position pos;
	pos.page = argv[1];
	pos.offset = argv[2];
	candidates->Add(new DicMultiCandidate(::eb_current_candidate(book), pos));
	return 0;
}

HOOK_FUNC(NarrowFont)
{
	char* p = book->text_context.candidate;
	int len = ::strlen(p);
	p += len;
	::snprintf(p, EB_MAX_WORD_LENGTH + 1 - len, "{%04X}", argv[0]);
	return 0;
}

HOOK_FUNC(WideFont)
{
	char* p = book->text_context.candidate;
	int len = ::strlen(p);
	p += len;
	::snprintf(p, EB_MAX_WORD_LENGTH + 1 - len, "{%04X}", argv[0]);
	return 0;
}
