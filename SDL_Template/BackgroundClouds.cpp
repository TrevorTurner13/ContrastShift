#include "BackgroundClouds.h"

BackgroundClouds* BackgroundClouds::sInstance = nullptr;

BackgroundClouds* BackgroundClouds::Instance() {
	if (sInstance == nullptr) {
		sInstance = new BackgroundClouds();
	}

	return sInstance;
}

void BackgroundClouds::Release() {
	delete sInstance;
	sInstance = nullptr;
}

void BackgroundClouds::Scroll(bool b) {
	Clouds::Scroll(b);
}

void BackgroundClouds::Update() {
	for (auto layer : mLayers) {
		layer->Update();
	}
}

void BackgroundClouds::Render() {
	mMoon->Render();
	for (int i = LAYER_COUNT - 1; i > -1; i--) {
		mLayers[i]->Render();
	}
	mGround->Render();
}

BackgroundClouds::BackgroundClouds() {
	mMoon = new GLTexture("Moon.png", 0, 0, 64, 64);
	mMoon->Position(650.0f, 200.0f);
	mMoon->Scale(Vector2(3.0f, 3.0f));

	for (int i = 0; i < LAYER_COUNT; i++) {
		mLayers[i] = new CloudLayer(i + 1);
	}

	mGround = new GLTexture("Sprite-0017.png", 0, 0, 1000, 400);
	mGround->Position(300.0f, 1000.0f);
	mGround->Scale(Vector2(2.0f, 1.0f));
}

BackgroundClouds::~BackgroundClouds() {
	delete mMoon;
	mMoon = nullptr;
	delete mGround;
	mGround = nullptr;
	for (int i = 0; i < LAYER_COUNT; i++) {
		delete mLayers[i];
		mLayers[i] = nullptr;
	}
}