#ifndef __LEVEL3_H
#define __LEVEL3_H
#include "GLTexture.h"
#include "AnimatedGLTexture.h"
#include "Player.h"

using namespace SDLFramework;

class Level3 : public PhysEntity {
private:
	static Level3* sInstance;

	GLTexture* mGround;
	GLTexture* mGroundBlack;

	GLTexture* mPillarStart;
	GLTexture* mLedgeStart;

	GLTexture* mSmallPillar1Collider;
	GLTexture* mMedPillar1Collider;
	GLTexture* mTallPillar1Collider;
	GLTexture* mTallPillar2Collider;

	GLTexture* mSmallPillar1;
	GLTexture* mMedPillar1;
	GLTexture* mTallPillar1;
	GLTexture* mTallPillar2;

	GLTexture* mBlackPillarStart;
	GLTexture* mBlackLedgeStart;

	GLTexture* mMedBlackPillar1Collider;
	GLTexture* mMedBlackPillar2Collider;
	GLTexture* mTallBlackPillar1Collider;
	GLTexture* mTallBlackPillar2Collider;

	GLTexture* mMedBlackPillar1;
	GLTexture* mMedBlackPillar2;
	GLTexture* mTallBlackPillar1;
	GLTexture* mTallBlackPillar2;

	AnimatedGLTexture* mBlackFlag2;
	
public:
	static Level3* Instance();
	static void Release();
	Level3();
	~Level3();

	void Update();
	void Render();
	void RenderWhite();

	GLTexture* GetGroundTexture() { return mGround; }

	GLTexture* GetPillarStartTexture() { return mPillarStart; }
	GLTexture* GetLedgeStartTexture() { return mLedgeStart; }

	GLTexture* GetSmallPillar1Collider() { return mSmallPillar1Collider; }
	GLTexture* GetMedPillar1Collider() { return mMedPillar1Collider; }
	GLTexture* GetTallPillar1Collider() { return mTallPillar1Collider; }
	GLTexture* GetTallPillar2Collider() { return mTallPillar2Collider; }

	GLTexture* GetMedBlackPillar1Collider() { return mMedBlackPillar1Collider; }
	GLTexture* GetMedBlackPillar2Collider() { return mMedBlackPillar2Collider; }
	GLTexture* GetTallBlackPillar1Collider() { return mTallBlackPillar1Collider; }
	GLTexture* GetTallBlackPillar2Collider() { return mTallBlackPillar2Collider; }

	GLTexture* GetBlackPillarStartTexture() { return mBlackPillarStart; }
	GLTexture* GetBlackLedgeStartTexture() { return mBlackLedgeStart; }
};

#endif