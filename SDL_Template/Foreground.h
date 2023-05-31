#ifndef __FOREGROUND_H
#define __FOREGROUND_H
#include "GLTexture.h"
#include "AnimatedGLTexture.h"
#include "Player.h"

using namespace SDLFramework;

class Foreground : public PhysEntity {
private:
	static Foreground* sInstance;
	//white elements
	GLTexture* mPillar1;
	GLTexture* mPillar2;

	GLTexture* mBlock1;
	GLTexture* mBlock2;
	
	GLTexture* mLedge1;
	GLTexture* mLedge2;

	GLTexture* mSword1;
	GLTexture* mSword2;
	GLTexture* mSword3;

	AnimatedGLTexture* mFlag1;
	// black elemets
	GLTexture* mBlackPillar1;
	GLTexture* mBlackPillar2;

	GLTexture* mBlackBlock;
	GLTexture* mBlackBlock2;

	GLTexture* mBlackLedge1;
	GLTexture* mBlackLedge2;

	GLTexture* mBlackSword1;
	GLTexture* mBlackSword2;
	GLTexture* mBlackSword3;

	AnimatedGLTexture* mBlackFlag1;
	// player
	Player* mPlayer;

public:

	static Foreground* Instance();
	static void Release();
	Foreground();
	~Foreground();

	void Update();
	void Render();
	void RenderWhite();

};


#endif