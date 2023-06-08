#ifndef __TUTORIALSCREEN_H
#define __TUTORIALSCREEN_H
#include "AnimatedGLTexture.h"
#include "InputManager.h"
#include "AudioManager.h"

using namespace SDLFramework;

class TutorialScreen : public GameEntity {

private:
	Texture* mMoveLeft;
	Texture* mMoveRight;
	Texture* mJump;
	Texture* mShift;
	Texture* mPush;

	Texture* mA;
	Texture* mD;
	Texture* mSpace;
	Texture* mShiftKey;
	Texture* mCaps;
	GameEntity* mBottomBar;
	Texture* mNamco;
	Texture* mDates;
	Texture* mRights;

public:
	TutorialScreen();
	~TutorialScreen();

	void Update() override;
	void Render() override;
};
#endif
