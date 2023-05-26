#include "Clouds.h"

bool Clouds::mScroll = true;

void Clouds::Scroll(bool b) {
	mScroll = b;
}

Clouds::Clouds(int layer) : GLTexture("CloudLargeWhite.png", 0, 0, 80, 32) {
	mTimer = Timer::Instance();
	mRand = Random::Instance();

	mVisible = false;

	int cloudShape = mRand->RandomInt() % 400;

	mSourceRect.x = cloudShape * 80;

	Position(Vector2((float)(mRand->RandomInt() % Graphics::Instance()->SCREEN_WIDTH),
		(float)(150 + mRand->RandomInt() % 100)));

	float inverseLayer = 1.5f / layer;
	Scale(Vec2_One * inverseLayer);

	mScrollSpeed = -1.0f / layer;
}

Clouds::~Clouds() {
	mTimer = nullptr;
	mRand = nullptr;
}

void Clouds::ScrollCloud() {
	Translate(Vec2_Right * mScrollSpeed, World);

	Vector2 pos = Position(Local);

	if (pos.x < -80) {
		pos.x = Graphics::Instance()->SCREEN_WIDTH + 80;
		pos.y = (float)(150 + mRand->RandomInt() % 100);
		Position(pos);
	}
}

void Clouds::Update() {

	mVisible = true;
	if (mScroll) {
		ScrollCloud();
	}
}

void Clouds::Render() {
	if (mVisible) {
		GLTexture::Render();
	}
}

