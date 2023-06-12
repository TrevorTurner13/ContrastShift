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
};

#endif 
