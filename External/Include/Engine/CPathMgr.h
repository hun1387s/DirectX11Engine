#pragma once
#include "singleton.h"
class CPathMgr :
    public CSingleton<CPathMgr>
{


    //SINGLE(CPathMgr);
private:
    wchar_t     ContentPath[255];
public:
    void init();
    const wchar_t* GetContentPath() { return ContentPath; }

private:
    CPathMgr();
    CPathMgr(const CPathMgr& _origin) = delete;
public:
    ~CPathMgr();
    friend class CSingleton<CPathMgr>;
};

