#ifndef __LEVEL2_H
#define __LEVEL2_H
#include "GLTexture.h"
#include "AnimatedGLTexture.h"
#include "Player.h"

using namespace SDLFramework;

class Level2 : public PhysEntity {
private:
	static Level2* sInstance;

	GLTexture* mCollider;
	GLTexture* mGround;
	GLTexture* mGroundBlack;

	//white elements
	GLTexture* mPillar1;
	GLTexture* mPillar2;

	GLTexture* mBlock1;
	GLTexture* mBlock2;

	GLTexture* mColliderBlock2;

	GLTexture* mLedge1;
	/*GLTexture* mLedge2;

	GLTexture* mSword1;
	GLTexture* mSword2;
	GLTexture* mSword3;*/

	//AnimatedGLTexture* mFlag1;
	// black elemets
	GLTexture* mBlackPillar1;
	GLTexture* mBlackPillar2;

	GLTexture* mBlackBlock1;

	GLTexture* mBlackLedge1;
	/*GLTexture* mBlackLedge2;

	GLTexture* mBlackSword1;
	GLTexture* mBlackSword2;
	GLTexture* mBlackSword3;

	AnimatedGLTexture* mBlackFlag1;*/
	// player
public:
	static Level2* Instance();
	static void Release();
	Level2();
	~Level2();

	void Update();
	void Render();
	void RenderWhite();

	GLTexture* GetGroundTexture() { return mGround; }
	GLTexture* GetDarkGroundTexture() { return mGroundBlack; }

	GLTexture* GetBlock1Texture() { return mBlock1; }
	GLTexture* GetColliderBlock2Texture() { return mColliderBlock2; }
	GLTexture* GetBlock2Texture() { return mBlock2; }
	GLTexture* GetColliderTexture() { return mCollider; }

	GLTexture* GetLedge1Texture() { return mLedge1; }
	//GLTexture* GetLedge2Texture() { return mLedge2; }

	//GLTexture* GetBlackPillarTexture() { return mBlackPillar1; }
	GLTexture* GetBlackLedge1Texture() { return mBlackLedge1; }
	GLTexture* GetBlackBlock1Texture() { return mBlackBlock1; }
};

#endif 

