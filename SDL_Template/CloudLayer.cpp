#include "CloudLayer.h"

CloudLayer::CloudLayer(int layer) {
	for (int i = 0; i < CLOUD_COUNT; i++) {
		mClouds[i] = new Clouds(layer);
	}
}

CloudLayer::~CloudLayer() {
	for (int i = 0; i < CLOUD_COUNT; i++) {
		delete mClouds[i];
		mClouds[i] = nullptr;
	}
}

void CloudLayer::Update() {
	for (auto cloud : mClouds) {
		cloud->Update();
	}
}

void CloudLayer::Render() {
	for (auto cloud : mClouds) {
		cloud->Render();
	}
}