#ifndef __FOREGROUND_H
#define __FOREGROUND_H
#include "GLTexture.h"
#include "AnimatedGLTexture.h"
#include "Player.h"


using namespace SDLFramework;

class Level1 : public PhysEntity {
private:
	static Level1* sInstance;


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


	GLTexture* mBlackBlock2;

	GLTexture* mBlackLedge1;
	GLTexture* mBlackLedge2;

	GLTexture* mBlackSword1;
	GLTexture* mBlackSword2;
	GLTexture* mBlackSword3;

	AnimatedGLTexture* mBlackFlag1;
	// player


public:

	static Level1* Instance();
	static void Release();
	Level1();
	~Level1();

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

	GLTexture* GetBlackPillarTexture() { return mBlackPillar1; }
	GLTexture* GetBlackLedge1Texture() { return mBlackLedge1; }
	
	GLTexture* GetBlackBlock2Texture() { return mBlackBlock2; }

};


#endif