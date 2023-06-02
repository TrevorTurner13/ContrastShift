#ifndef __FOREGROUND_H
#define __FOREGROUND_H
#include "GLTexture.h"
#include "AnimatedGLTexture.h"
#include "Player.h"


using namespace SDLFramework;

class Foreground : public PhysEntity {
private:
	static Foreground* sInstance;

	GLTexture* mGround;
	GLTexture* mGroundBlack;

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


public:

	static Foreground* Instance();
	static void Release();
	Foreground();
	~Foreground();

	void Update();
	void Render();
	void RenderWhite();

	GLTexture* GetGroundTexture() { return mGround; }
	GLTexture* GetDarkGroundTexture() { return mGroundBlack; }

	GLTexture* GetPillarTexture() { return mPillar1; }
	GLTexture* GetBlock1Texture() { return mBlock1; }
	GLTexture* GetBlock2Texture() { return mBlock2; }

	GLTexture* GetLedge1Texture() { return mLedge1; }
	GLTexture* GetLedge2Texture() { return mLedge2; }

	GLTexture* GetBlackLedge1Texture() { return mBlackLedge1; }
	GLTexture* GetBlackBlockTexture() { return mBlackBlock; }
	GLTexture* GetBlackBlock2Texture() { return mBlackBlock2; }

};


#endif