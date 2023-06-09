#pragma once
#ifndef __CREDITS_H
#define __CREDITS_H
#include "AnimatedGLTexture.h"
#include "InputManager.h"
#include "Scoreboard.h"
#include "AudioManager.h"

using namespace SDLFramework;

class CreditsScreen : public GameEntity {

private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	GameEntity* mTopBar;

	GameEntity* mPlayModes;

	GameEntity* mBottomBar;
	
	// Screen Animation Variables
	Vector2 mAnimationStartPos;
	Vector2 mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;


	float mBackgroundColor;


public:
	CreditsScreen();
	~CreditsScreen();

	void ResetAnimation();

	void Update() override;
	void Render() override;

};
#endif