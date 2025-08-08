#include "Page.hpp"
#include "ControlGroup.hpp"
#include "UIControl.hpp"
#include "rk_types.h"

namespace UI {
const f32 some_const = 0.1;

Page::Page() : mId(0xffffffff), mState(0), mNextStateRequested(false), mAnimationDirection(0), mAnimationStartFrame(0), mAnimationDelay(0), mFrame(0xffffffff), mUnknown(0xffffffff), mInputManager(nullptr), mNextAnimationSfxId(0), mPrevAnimationSfxId(6) {
}

Page::~Page() {}

void Page::init(s32 id) {
  this->mId = id;

  this->onInit();

  this->mControlGroup.init();

  // void (UI::Page::*ptr)() = (&Page::virt_unknown_0x0c);

  ClampToAnimStartFrame initreal = ClampToAnimStartFrame();
  this->mControlGroup.transform(initreal);
  this->mAnimationStartFrame = initreal.val;

  // this->mAnimationStartFrame = *(f32*)(void*&)ptr;
  this->mState = 1;
}


void Page::activate() {
  bool good;
  this->mState = 2;
  this->mNextStateRequested = true;
  this->mFrame = -1;
  this->mUnknown = -1;
  this->mInputManager->activate();
  this->onActivate();
  this->mInputManager->virt_unknown_0x28();
  // Doesn't match but looking at ghidra I'm convinced its some sort of dynamic_cast-like thing that's inlined
  unknownInputManager1* specialInputManager = (unknownInputManager1*)(this->mInputManager);
  if (specialInputManager != nullptr) {
    int iVar4 = 0;
    do {
      ((void(*)(unknownInputManager1*, int, int))0x800e1e2)(specialInputManager,iVar4,0);
      iVar4 = iVar4 + 1;
    } while (iVar4 < 5);
  }
  this->mControlGroup.init();
  return;
}

void Page::draw(u32 pass) {
    if (mState > 5 || mState < 3) {
        return;
    }

    mControlGroup.draw(pass);
}

void Page::setAnimationDirection(s32 animationDirection) {
    if (animationDirection == -1) {
        return;
    }

    mAnimationDirection = animationDirection;
}

void Page::initChildren(s32 capacity) {
    mControlGroup.create(this, capacity);
}

void Page::insert(s32 index, UIControl* control, u32 drawPass) {
    mControlGroup.insert(index, control, drawPass);
}

void Page::setInputManager(MenuInputManager* inputManager) {
    mInputManager = inputManager;
}

void Page::skipInAnimation(void) {
    mNextStateRequested = true;
}

void Page::startReplace(s32 animationDirection, f32 delay) {
  setAnimationDirection(animationDirection);
  mAnimationDelay = delay;
  mNextStateRequested = true;
}

void Page::skipOutAnimation(void) {
    mNextStateRequested = true;
}

// Virtual functions

char* Page::getName() {
  return "(unknown page)";
}

void Page::onInit() {}

}
