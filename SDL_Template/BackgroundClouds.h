#ifndef __BACKGROUNDCLOUDS_H
#define __BACKGROUNDCLOUDS_H
#include "CloudLayer.h"


class BackgroundClouds {
private:
	static BackgroundClouds* sInstance;
	static const int LAYER_COUNT = 3;
	CloudLayer* mLayers[LAYER_COUNT];
	GLTexture* mMoon;
	GLTexture* mMoonBlack;

	
public:
	static BackgroundClouds* Instance();
	static void Release();
	void Scroll(bool b);

	void Update();
	void Render();
	void RenderBlack();

private:
	BackgroundClouds();
	~BackgroundClouds();
};


#endif