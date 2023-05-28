#ifndef __FOREGROUND_H
#define __FOREGROUND_H
#include "GLTexture.h"
#include "AnimatedGLTexture.h"

using namespace SDLFramework;

class Foreground : public GameEntity {
private:
	static Foreground* sInstance;
	GLTexture* mPillar;
	GLTexture* mBlock;
	GLTexture* mLedge;
	GLTexture* mSword1;
	GLTexture* mSword2;
	GLTexture* mSword3;

	AnimatedGLTexture* mGuy;

public:

	static Foreground* Instance();
	static void Release();
	Foreground();
	~Foreground();

	void Update();
	void Render();

};


#endif