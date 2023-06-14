#include "CloudsColor.h"

bool CloudsColor::mScroll = true;

void CloudsColor::Scroll(bool b) {
	mScroll = b;
}

CloudsColor::CloudsColor(int layer) : GLTexture("CloudLargeColor.png", 0, 0, 80, 32) {
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

CloudsColor::~CloudsColor() {
	mTimer = nullptr;
	mRand = nullptr;
}

void CloudsColor::ScrollCloud() {
	Translate(Vec2_Right * mScrollSpeed, World);

	Vector2 pos = Position(Local);

	if (pos.x < -80) {
		pos.x = Graphics::Instance()->SCREEN_WIDTH + 80;
		pos.y = (float)(150 + mRand->RandomInt() % 100);
		Position(pos);
	}
}

void CloudsColor::Update() {

	mVisible = true;
	if (mScroll) {
		ScrollCloud();
	}
}

void CloudsColor::Render() {
	if (mVisible) {
		GLTexture::Render();
	}
}

