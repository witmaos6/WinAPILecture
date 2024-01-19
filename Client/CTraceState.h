#pragma once
#include "CState.h"
class CTraceState :
    public CState
{
public:
    CTraceState();
    ~CTraceState();
private:

public:
    virtual void Update();

    virtual void Enter();

    virtual void Exit();
};

