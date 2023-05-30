#ifndef __FOREGROUND_H
#define __FOREGROUND_H
#include "GLTexture.h"
#include "AnimatedGLTexture.h"
#include "Player.h"
#include "ScreenManager.h"

using namespace SDLFramework;

class Foreground : public GameEntity {
private:
	static Foreground* sInstance;
	GLTexture* mPillar1;
	GLTexture* mPillar2;

	GLTexture* mBlock;
	
	GLTexture* mLedge1;
	GLTexture* mLedge2;

	GLTexture* mSword1;
	GLTexture* mSword2;
	GLTexture* mSword3;

	AnimatedGLTexture* mFlag1;

	Player* mPlayer;

public:

	static Foreground* Instance();
	static void Release();
	Foreground();
	~Foreground();

	void Update();
	void Render();

};


#endif