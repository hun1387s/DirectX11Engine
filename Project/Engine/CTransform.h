#pragma once
#include "CComponent.h"
class CTransform :
    public CComponent
{
private:
    Vector3     relativePos;
    Vector3     relativeScale;
    Vector3     relativeRotateion;

public:
    virtual void finaltick() override;
    void Binding();

public:
    Vector3 GetRelativePos() { return relativePos; }
    Vector3 GetRelativeScale() { return relativeScale; }
    Vector3 GetRelativeRotateion() { return relativeRotateion; }

    void SetRelativePos(const Vector3& value) { relativePos = value; }
    void SetRelativeScale(const Vector3& value) { relativeScale = value; }
    void SetRelativeRotateion(const Vector3& value) { relativeRotateion = value; }

    void SetRelativePos(float x, float y, float z) { relativePos = Vector3(x,y,z); }
    void SetRelativeScale(float x, float y, float z) { relativeScale = Vector3(x, y, z); }
    void SetRelativeRotateion(float x, float y, float z) { relativeRotateion = Vector3(x, y, z); }

public:
    CTransform();
    ~CTransform();
};

