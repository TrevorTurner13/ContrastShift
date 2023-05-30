#ifndef __CLOUDS_H
#define __CLOUDS_H
#include "GLTexture.h"
#include "Timer.h"
#include "Random.h"

using namespace SDLFramework;

class Clouds : public GLTexture {

private:
	static bool mScroll;

	Timer* mTimer;
	Random* mRand;

	bool mVisible;
	float mScrollSpeed;

public:
	Clouds(int layer);
	~Clouds();

	static void Scroll(bool b);

	void Update() override;
	void Render() override;

protected:
	void ScrollCloud();
};

#endif
