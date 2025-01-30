#pragma once
#include "singleton.h"


class CTimeMgr :
    public CSingleton<CTimeMgr>
{
    SINGLE(CTimeMgr);

private:
    LARGE_INTEGER   Frequency;  // 초당 카운트 수
    LARGE_INTEGER   CurCount;   // 현재 카운트 수
    LARGE_INTEGER   PrevCount;  // 이전 프레임 카운트 수

    float           DeltaTime;  // 1프레임 동작하는데 걸린 시간
    float           Time;       // 프로세스 실행 이후 누적 시간
    float           AccTime;    // 1초 체크하기 위한 시간 누적 변수

    UINT            FrameCount;
public:
    void init();
    void tick();
};

