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
	
}

void BackgroundClouds::RenderBlack() {
	mMoonBlack->Render();
	for (int i = LAYER_COUNT - 1; i > -1; i--) {
		mLayers[i]->RenderBlack();
	}
	
}

BackgroundClouds::BackgroundClouds() {
	mMoon = new GLTexture("Moon.png", 0, 0, 640, 640);
	mMoon->Position(1550.0f, 200.0f);
	mMoon->Scale(Vector2(0.5f, 0.5f));

	mMoonBlack = new GLTexture("BlackMoon.png", 0, 0, 640, 640);
	mMoonBlack->Position(1550.0f, 200.0f);
	mMoonBlack->Scale(Vector2(0.5f, 0.5f));

	for (int i = 0; i < LAYER_COUNT; i++) {
		mLayers[i] = new CloudLayer(i + 1);
	}
}

BackgroundClouds::~BackgroundClouds() {
	delete mMoon;
	mMoon = nullptr;
	
	for (int i = 0; i < LAYER_COUNT; i++) {
		delete mLayers[i];
		mLayers[i] = nullptr;
	}
}