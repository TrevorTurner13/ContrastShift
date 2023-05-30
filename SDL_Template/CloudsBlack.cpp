#include "CloudsBlack.h"

bool CloudsBlack::mScroll = true;

void CloudsBlack::Scroll(bool b) {
	mScroll = b;
}

CloudsBlack::CloudsBlack(int layer) : GLTexture("CloudLarge.png", 0, 0, 80, 32) {
	mTimer = Timer::Instance();
	mRand = Random::Instance();

	mVisible = false;

	int cloudShape = mRand->RandomInt() % 400;

	mSourceRect.x = cloudShape * 80;

	Position(Vector2((float)(mRand->RandomInt() % Graphics::Instance()->SCREEN_WIDTH),
		(float)(150 + mRand->RandomInt() % 100)));

	float inverseLayer = 1.8f / layer;
	Scale(Vec2_One * inverseLayer);

	mScrollSpeed = -0.5f / layer;
}

CloudsBlack::~CloudsBlack() {
	mTimer = nullptr;
	mRand = nullptr;
}

void CloudsBlack::ScrollCloud() {
	Translate(Vec2_Right * mScrollSpeed, World);

	Vector2 pos = Position(Local);

	if (pos.x < -80) {
		pos.x = Graphics::Instance()->SCREEN_WIDTH + 80;
		pos.y = (float)(150 + mRand->RandomInt() % 100);
		Position(pos);
	}
}

void CloudsBlack::Update() {

	mVisible = true;
	if (mScroll) {
		ScrollCloud();
	}
}

void CloudsBlack::Render() {
	if (mVisible) {
		GLTexture::Render();
	}
}

