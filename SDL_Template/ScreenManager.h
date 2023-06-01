#ifndef __SCREENMANAGER_H
#define __SCREENMANAGER_H
#include "StartScreen.h"
#include "PlayScreen.h"
#include "BackgroundClouds.h"
#include "Foreground.h"


class ScreenManager {
private:
	static ScreenManager * sInstance;

	enum Screens { Start, Play };
	Screens mCurrentScreen;

	InputManager * mInput;

	StartScreen * mStartScreen;
	PlayScreen * mPlayScreen;
	AnimatedGLTexture* mGuy;
	BackgroundClouds* mClouds;
	Foreground* mForeground;

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