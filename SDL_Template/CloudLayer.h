#ifndef __CLOUDLAYER_H
#define __CLOUDLAYER_H

#include "Clouds.h"
#include "CloudsBlack.h"


class CloudLayer {
private:
	static const int CLOUD_COUNT = 3;
	Clouds* mClouds[CLOUD_COUNT];
	CloudsBlack* mCloudsBlack[CLOUD_COUNT];

public:
	CloudLayer(int layer);
	~CloudLayer();

	void Update();
	void Render();
	void RenderBlack();

};

#endif 
