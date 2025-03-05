#pragma once
#include "singleton.h"
class CPathMgr :
    public CSingleton<CPathMgr>
{
    SINGLE(CPathMgr);
private:
    wchar_t     ContentPath[255];
public:
    void init();
    const wchar_t* GetContentPath() { return ContentPath; }
};

