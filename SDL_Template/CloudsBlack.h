#ifndef __CLOUDSBLACK_H
#define __CLOUDSBLACK_H
#include "GLTexture.h"
#include "Timer.h"
#include "Random.h"

using namespace SDLFramework;

class CloudsBlack : public GLTexture {

private:
	static bool mScroll;

	Timer* mTimer;
	Random* mRand;

	bool mVisible;
	float mScrollSpeed;

public:
	CloudsBlack(int layer);
	~CloudsBlack();

	static void Scroll(bool b);

	void Update() override;
	void Render() override;

protected:
	void ScrollCloud();
};

#endif