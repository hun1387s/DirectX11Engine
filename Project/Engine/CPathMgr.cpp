#include "pch.h"
#include "CPathMgr.h"

CPathMgr::CPathMgr()
	: ContentPath{}
{
}

CPathMgr::~CPathMgr()	
{
}

void CPathMgr::init()
{
	GetCurrentDirectory(255, ContentPath);

	size_t len = wcslen(ContentPath);

	for (size_t i = len - 1; i > 0; i--)
	{
		if (ContentPath[i] == '\\')
		{
			ContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(ContentPath, L"\\contents\\");
}


