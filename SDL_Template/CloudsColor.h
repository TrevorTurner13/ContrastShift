#ifndef __CLOUDSCOLOR_H
#define __CLOUDSCOLOR_H
#include "GLTexture.h"
#include "Timer.h"
#include "Random.h"

using namespace SDLFramework;

class CloudsColor : public GLTexture {

private:
	static bool mScroll;

	Timer* mTimer;
	Random* mRand;

	bool mVisible;
	float mScrollSpeed;

public:
	CloudsColor(int layer);
	~CloudsColor();

	static void Scroll(bool b);

	void Update() override;
	void Render() override;

protected:
	void ScrollCloud();
};

#endif
