#ifndef __CLOUDLAYER_H
#define __CLOUDLAYER_H

#include "Clouds.h"

class CloudLayer {
private:
	static const int CLOUD_COUNT = 3;
	Clouds* mClouds[CLOUD_COUNT];

public:
	CloudLayer(int layer);
	~CloudLayer();

	void Update();
	void Render();
};

#endif 
