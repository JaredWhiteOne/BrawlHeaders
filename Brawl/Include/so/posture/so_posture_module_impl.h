#pragma once

#include <types.h>
#include <StaticAssert.h>
#include <so/so_array.h>
#include <so/posture/so_posture_module_simple.h>
#include <so/so_event_observer.h>
#include <so/so_event_presenter.h>

template <class T>
class soInterpolation {
    T t[4];
};

typedef soInterpolation<Vec3f> interpolationVec3f;

class soPostureModuleImpl : public soPostureModuleSimple, public soStatusEventObserver, public soAnimCmdEventObserver {
    soArray<interpolationVec3f>* m_interpolationArray;
    float m_rotYLr;
    int m_syncConstraintNode;
    float m_ownerScale;
    Vec3f m_prevRoughPos;

public:
    virtual ~soPostureModuleImpl();
    virtual void init(Vec3f* pos, float lr);
    virtual void initPos(Vec3f* pos);
    virtual Vec3f getPrevRoughPos();
    virtual void setPrevRoughPos(Vec3f* roughPos);
    virtual void setLr(float lr);
    virtual void initRot();
    virtual void initRot(u32 index);
    virtual Vec3f getRot(u32 index);
    virtual void setRot(Vec3f* rot, u32 index);
    virtual void initRotYLr();
    virtual bool isRotYLrDifferentInnerLr();
    virtual float getRotYLr();
    virtual void updateRotYLr();
    virtual void reverseRotYLr();
    virtual float getScale();
    virtual float getOwnerScale();
    virtual void setOwnerScale(float ownerScale);
    virtual void begin();
    virtual void rewind();
    virtual void turnBack();
    virtual float interpolate(float);
    virtual bool setStickLR(float stickLR);
    virtual void setSyncConstraintNode(int);
    virtual void fixConstraintNodePosture(int, void*);
    virtual void fixRot();

    virtual u32 isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual void notifyEventChangeStatus(int unk1, int unk2, void* unk3, soModuleAccesser* moduleAccesser);

    STATIC_CHECK(sizeof(soPostureModuleImpl) == 120)

};