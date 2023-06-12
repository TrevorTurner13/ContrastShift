#ifndef __LEVEL3_H
#define __LEVEL3_H
#include "GLTexture.h"
#include "AnimatedGLTexture.h"
#include "Player.h"
#include "Timer.h"

using namespace SDLFramework;

class Level3 : public PhysEntity {
private:
	Timer* mTimer;
	static Level3* sInstance;

	bool mBlockGrounded;
	Vector2 mBlockVelocity;
	Vector2 mGravity;

	GLTexture* mGround;
	GLTexture* mGroundBlack;

	GLTexture* mPillarStart;
	GLTexture* mLedgeStart;
	GLTexture* mPillarEnd;
	GLTexture* mLedgeEnd;

	GLTexture* mPillarEndCollider;

	GLTexture* mSmallPillar1Collider;
	GLTexture* mMedPillar1Collider;
	GLTexture* mTallPillar1Collider;
	GLTexture* mTallPillar2Collider;

	GLTexture* mSmallPillar1;
	GLTexture* mMedPillar1;
	GLTexture* mTallPillar1;
	GLTexture* mTallPillar2;

	AnimatedGLTexture* mFlag1;

	GLTexture* mBlackPillarStart;
	GLTexture* mBlackLedgeStart;
	GLTexture* mBlackPillarEnd;
	GLTexture* mBlackLedgeEnd;

	GLTexture* mMedBlackPillar1Collider;
	GLTexture* mMedBlackPillar2Collider;
	GLTexture* mTallBlackPillar1Collider;
	GLTexture* mTallBlackPillar2Collider;

	GLTexture* mMedBlackPillar1;
	GLTexture* mMedBlackPillar2;
	GLTexture* mTallBlackPillar1;
	GLTexture* mTallBlackPillar2;

	GLTexture* mBlackBlock1;

	AnimatedGLTexture* mBlackFlag2;
	
public:
	static Level3* Instance();
	static void Release();
	Level3();
	~Level3();

	void Update();
	void Render();
	void RenderBlack();

	void SetBlockVelocity(Vector2 velocity, Vector2 gravity) { mBlockVelocity = velocity += gravity * mTimer->DeltaTime(); }
	Vector2 GetVelocity() { return mBlockVelocity; }
	Vector2 GetGravity() { return mGravity; }

	GLTexture* GetGroundTexture() { return mGround; }

	GLTexture* GetPillarStartTexture() { return mPillarStart; }
	GLTexture* GetLedgeStartTexture() { return mLedgeStart; }
	GLTexture* GetLedgeEndTexture() { return mLedgeEnd; }
	GLTexture* GetBlackLedgeEndTexture() { return mBlackLedgeEnd; }
	GLTexture* GetPillarEndCollider() { return mPillarEndCollider; }

	GLTexture* GetSmallPillar1Collider() { return mSmallPillar1Collider; }
	GLTexture* GetMedPillar1Collider() { return mMedPillar1Collider; }
	GLTexture* GetTallPillar1Collider() { return mTallPillar1Collider; }
	GLTexture* GetTallPillar2Collider() { return mTallPillar2Collider; }

	GLTexture* GetMedBlackPillar1Collider() { return mMedBlackPillar1Collider; }
	GLTexture* GetMedBlackPillar2Collider() { return mMedBlackPillar2Collider; }
	GLTexture* GetTallBlackPillar1Collider() { return mTallBlackPillar1Collider; }
	GLTexture* GetTallBlackPillar2Collider() { return mTallBlackPillar2Collider; }
	
	GLTexture* GetBlackBlock1Texture() { return mBlackBlock1; }
	bool GetBlockGrounded() { return mBlockGrounded; }
	void SetBlockGrounded(bool isGrounded) { mBlockGrounded = isGrounded; }
};

#endif