#ifndef RENDERANIMATION_H
#define RENDERANIMATION_H

#include "Display.h"
#include "Sprites.h"
#include "GameState.h"

// this file contains all the code describing the
// sprite animations

enum AnimationType {
  ANIM_IDLE,
  ANIM_EAT,
  ANIM_PLAY,
  ANIM_RAVE,
  ANIM_DEATH
};

class RenderAnimation {
  public:
    RenderAnimation(Display* disp);

    void renderStats(int hunger, int play, int rave);
    void renderPet(AnimationType animType, int x, int y, int direction);
    void paint();
    void playFeedAnimation(int x, int y, int direction);
    void playPlayAnimation(int x, int y, int direction);
    void playRaveAnimation(int x, int y, int direction);
    void playDeathAnimation();

  private:
    Display* displayPtr;

    const unsigned char* getSpriteForAnimation(AnimationType type);
};

#endif
