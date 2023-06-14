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

void BackgroundClouds::RenderColor() {
	//mSky->Render();
	mMoonColor->Render();
	mMountains2->RenderFlip();
	mMountains->RenderFlip();
	mHills->Render();
	
	mRuinStart->Render();
	mPillar1->Render();
	mPillar2->Render();
	mLedge1->Render();
	mLedge2->Render();
	mLedgeEnd->Render();
	mRuinEnd->Render();
	mSword1->Render();
	mSword2->Render();
	mSword3->Render();
	mSword4->Render();
	mSword5->Render();
	mSword6->Render();
	mGround->Render();
	
	for (int i = LAYER_COUNT - 1; i > -1; i--) {
		mLayers[i]->RenderColor();
	}
	mPillarStart->Render();
}

BackgroundClouds::BackgroundClouds() {

	/*mSky = new GLTexture("Sky.png", 0, 0, 1920, 1080);
	mSky->Position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));*/

	mMoon = new GLTexture("Moon.png", 0, 0, 640, 640);
	mMoon->Position(1550.0f, 200.0f);
	mMoon->Scale(Vector2(0.5f, 0.5f));

	mMoonBlack = new GLTexture("BlackMoon.png", 0, 0, 640, 640);
	mMoonBlack->Position(1550.0f, 200.0f);
	mMoonBlack->Scale(Vector2(0.5f, 0.5f));

	mMoonColor = new GLTexture("ColorMoon.png", 0, 0, 320, 320);
	mMoonColor->Position(1550.0f, 200.0f);


	mMountains = new GLTexture("MountainsColor.png", 0, 144, 640, 176);
	mMountains->Position(1250.0f, 830.0f);
	mMountains->Scale(Vector2(2.0f, 1.5f));

	mMountains2 = new GLTexture("MountainsColor.png", 0, 144, 640, 176);
	mMountains2->Position(400.0f, 830.0f);
	mMountains2->Scale(Vector2(1.5f, 1.0f));

	mHills = new GLTexture("MountainsColor.png", 160, 0, 960, 80);
	mHills->Position(895.0f, 875.0f);
	mHills->Scale(Vector2(2.0f, 1.0f));

	mGround = new GLTexture("Ground.png", 0, 0, 640, 384);
	mGround->Position(960.0f, 1032.0f);
	mGround->Scale(Vector2(3.0f, 1.0f));

	// white elements
	mPillarStart = new GLTexture("ColorPillarlarge.png", 0, 0, 480, 960);
	mPillarStart->Position(0.0f, 435.0f);
	mPillarStart->Scale(Vector2(0.75f, 1.0f));

	mPillar1 = new GLTexture("ColorPillarPlatform.png", 370, 80, 70, 398);
	mPillar1->Position(850.0f, 760.0f);
	mPillar1->Scale(Vector2(0.8f, 0.8f));

	mPillar2 = new GLTexture("ColorPillarPlatform.png", 370, 80, 70, 398);
	mPillar2->Position(1500.0f, 750.0f);
	mPillar2->Scale(Vector2(0.7f, 0.85f));

	mRuinStart = new GLTexture("ColorRuins.png", 0, 320, 480, 320);
	mRuinStart->Position(225.0f, 825.0f);
	mRuinStart->Scale(Vector2(0.65f, 0.65f));

	mRuinEnd = new GLTexture("ColorRuins.png", 650, 160, 310, 480);
	mRuinEnd->Position(1900.0f, 705.0f);
	mRuinEnd->Scale(Vector2(0.9f, 0.9f));

	mLedge1 = new GLTexture("ColorPillarPlatform.png", 0, 0, 800, 70);
	mLedge1->Position(200.0f, 700.0f);
	mLedge1->Scale(Vector2(0.65f, 0.65f));

	mLedge2 = new GLTexture("ColorPillarPlatform.png", 0, 0, 800, 70);
	mLedge2->Position(850.0f, 590.0f);
	mLedge2->Scale(Vector2(0.55f, 0.55f));

	mLedgeEnd = new GLTexture("ColorPillarPlatform.png", 0, 0, 800, 70);
	mLedgeEnd->Position(1500.0f, 570.0f);
	mLedgeEnd->Scale(Vector2(0.55f, 0.55f));

	mSword1 = new GLTexture("ColorSwords.png", 0, 0, 320, 480);
	mSword1->Position(160, 280);
	mSword1->Scale(Vector2(0.4f, 0.4f));

	mSword2 = new GLTexture("ColorSwords.png", 960, 0, 320, 480);
	mSword2->Position(750, 825);
	mSword2->Scale(Vector2(0.4f, 0.4f));

	mSword3 = new GLTexture("ColorSwords.png", 1440, 0, 160, 480);
	mSword3->Position(1600, 825);
	mSword3->Scale(Vector2(0.4f, 0.4f));

	mSword4 = new GLTexture("ColorSwords.png", 0, 0, 320, 480);
	mSword4->Position(940, 700);
	mSword4->Scale(Vector2(0.4f, 0.4f));

	mSword5 = new GLTexture("ColorSwords.png", 640, 0, 320, 480);
	mSword5->Position(200, 845);
	mSword5->Scale(Vector2(0.4f, 0.4f));

	mSword6 = new GLTexture("ColorSwords.png", 1280, 0, 160, 480);
	mSword6->Position(1400, 455);
	mSword6->Scale(Vector2(0.4f, 0.4f));


	for (int i = 0; i < LAYER_COUNT; i++) {
		mLayers[i] = new CloudLayer(i + 1);
	}
}

BackgroundClouds::~BackgroundClouds() {
	delete mMoon;
	mMoon = nullptr;
	
	delete mMoonBlack;
	mMoonBlack = nullptr;

	delete mMoonColor;
	mMoonColor = nullptr;
	
	for (int i = 0; i < LAYER_COUNT; i++) {
		delete mLayers[i];
		mLayers[i] = nullptr;
	}
}