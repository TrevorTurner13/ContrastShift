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

	GLTexture* mBlackPillarStart;
	GLTexture* mBlackLedgeStart;
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

	GLTexture* GetBlackPillarStartTexture() { return mBlackPillarStart; }
	GLTexture* GetBlackLedgeStartTexture() { return mBlackLedgeStart; }
};

#endif