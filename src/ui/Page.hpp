#pragma once

#include <rk_types.h>

#include <decomp.h>

#include "ui/ControlGroup.hpp"

namespace UI {

// Todo this is definitely overriding a bunch of stuff.
class MenuInputManager {
public:
  MenuInputManager* activate();
  virtual void virt_unknown_0x08() = 0;
  virtual void virt_unknown_0x0c() = 0;
  virtual void virt_unknown_0x10() = 0;
  virtual void virt_unknown_0x14() = 0;
  virtual void virt_unknown_0x18() = 0;
  virtual void virt_unknown_0x1c() = 0;
  virtual void virt_unknown_0x20() = 0;
  virtual void virt_unknown_0x24() = 0;
  virtual void virt_unknown_0x28() = 0;
  virtual void virt_unknown_0x2c() = 0;
  virtual void virt_unknown_0x30() = 0;
};

class Page {
public:
  Page();
  virtual ~Page();
  virtual char* getName();
  virtual void getReplacement();
  virtual void virt_unknown_0x14() = 0;
  virtual void virt_unknown_0x18() = 0;
  virtual void changeSection();
  virtual void virt_unknown_0x20() = 0;
  virtual void push();
  virtual void onInit();
  virtual void onFini();
  virtual void onActivate();
  virtual void onDeactivate();
  virtual void virt_unknown_0x38() = 0;
  virtual void virt_unknown_0x3C() = 0;
  virtual void virt_unknown_0x40() = 0;
  virtual void virt_unknown_0x44() = 0;
  virtual void beforeCalc();
  virtual void afterCalc();
  virtual void virt_unknown_0x50() = 0;
  virtual void onRefocus();
  virtual void virt_unknown_0x58() = 0;
  virtual void virt_unknown_0x5C() = 0;
  virtual void getTypeInfo();

  void init(s32 id);
  void activate();
  void draw(u32 pass);
  void setAnimationDirection(s32 animationDirection);
  void initChildren(s32 capacity);
  void insert(s32 index, UIControl* control, u32 drawPass);
  void setInputManager(MenuInputManager* inputManager);
  void skipInAnimation(void);
  void startReplace(s32 animationDirection, f32 delay);
  void skipOutAnimation(void);

private:
  s32 mId; //1*4
  s32 mState;//2*4
  bool mNextStateRequested;//3*4
  u8 _0d[0x10 - 0x0d];//13,14,15
  s32 mAnimationDirection;//4*4
  f32 mAnimationStartFrame;//5*4
  f32 mAnimationDelay; //6*4
  s32 mFrame;//7*4
  u32 mUnknown;//8*4
  ControlGroup mControlGroup; //(9,a,b,c,d) *4
  MenuInputManager* mInputManager;//e
  u32 mNextAnimationSfxId;//f
  u32 mPrevAnimationSfxId;//0x10
};

static_assert(sizeof(Page) == 0x44);

class unknownInputManager1: MenuInputManager {

};

} // namespace UI

