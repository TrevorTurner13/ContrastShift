#ifndef __LEVELEND_H
#define __LEVELEND_H
#include "GLTexture.h"
#include "AnimatedGLTexture.h"
#include "Player.h"
#include "Timer.h"

using namespace SDLFramework;

class LevelEnd : public PhysEntity {
private:
	Timer* mTimer;
	static LevelEnd* sInstance;

	GLTexture* mGround;
	GLTexture* mGroundBlack;

	GLTexture* mPillarStart;
	GLTexture* mPillarStartCollider;
	GLTexture* mBlackPillarStart;

	GLTexture* mMonumentBaseBottom;
	GLTexture* mMonumentBaseMid;
	GLTexture* mMonumentBaseTop;

	GLTexture* mOrbCollider;

	GLTexture* mPillarEnd;
	GLTexture* mBlackPillarEnd;

	AnimatedGLTexture* mFlag1;
	AnimatedGLTexture* mFlag2;

	AnimatedGLTexture* mBlackFlag1;
	AnimatedGLTexture* mBlackFlag2;

	AnimatedGLTexture* mChromaticOrb;
	AnimatedGLTexture* mMonument;
	AnimatedGLTexture* mMonumentBlack;


public:
	static LevelEnd* Instance();
	static void Release();
	LevelEnd();
	~LevelEnd();

	void Update();
	void Render();
	void RenderBlack();

	GLTexture* GetPillarStartCollider() { return mPillarStartCollider; }
	GLTexture* GetGroundTexture() { return mGround; }
	GLTexture* GetMonumentBaseBottom() { return mMonumentBaseBottom; }
	GLTexture* GetMonumentBaseMid() { return mMonumentBaseMid; }
	GLTexture* GetMonumentBaseTop() { return mMonumentBaseTop; }

	GLTexture* GetChromaticOrb() { return mChromaticOrb; }
	GLTexture* GetOrbCollider() { return mOrbCollider; }
};

#endif 
