#ifndef __BACKGROUNDCLOUDS_H
#define __BACKGROUNDCLOUDS_H
#include "CloudLayer.h"


class BackgroundClouds {
private:
	static BackgroundClouds* sInstance;
	static const int LAYER_COUNT = 3;
	CloudLayer* mLayers[LAYER_COUNT];

	//GLTexture* mSky;
	GLTexture* mMoon;
	GLTexture* mMoonBlack;
	GLTexture* mMoonColor;

	GLTexture* mMountains;
	GLTexture* mMountains2;
	GLTexture* mHills;
	GLTexture* mGround;

	GLTexture* mPillarStart;
	GLTexture* mRuinStart;

	GLTexture* mPillar1;
	GLTexture* mPillar2;

	GLTexture* mLedge1;
	GLTexture* mLedge2;


	GLTexture* mLedgeEnd;
	GLTexture* mRuinEnd;

	GLTexture* mSword1;
	GLTexture* mSword2;
	GLTexture* mSword3;
	GLTexture* mSword4;
	GLTexture* mSword5;
	GLTexture* mSword6;
	
public:
	static BackgroundClouds* Instance();
	static void Release();
	void Scroll(bool b);

	void Update();
	void Render();
	void RenderBlack();
	void RenderColor();

private:
	BackgroundClouds();
	~BackgroundClouds();
};


#endif