#ifndef __SCREENMANAGER_H
#define __SCREENMANAGER_H
#include "StartScreen.h"
#include "PlayScreen.h"
#include "TutorialScreen.h"
#include "BackgroundClouds.h"
#include "Level1.h"
#include "AudioManager.h"
#include "CreditsScreen.h"


class ScreenManager {
private:
	static ScreenManager * sInstance;

	enum Screens { Start, Play, Tutorial, Credits };
	Screens mCurrentScreen;

	InputManager * mInput;
	AudioManager* mAudio;

	StartScreen * mStartScreen;
	PlayScreen * mPlayScreen;
	TutorialScreen* mTutorialScreen;
	CreditsScreen* mCreditsScreen;

	AnimatedGLTexture* mGuy;
	BackgroundClouds* mClouds;
	Level1* mLevel1;
	int mModeSelected;
	
	

public:
	static ScreenManager * Instance();
	static void Release();

	
	
	void Update();
	void Render();

private:
	ScreenManager();
	~ScreenManager();
};
#endif