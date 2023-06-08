#include "Level3.h"

Level3* Level3::sInstance = nullptr;

Level3* Level3::Instance() {
	if (sInstance == nullptr) {
		sInstance = new Level3();
	}

	return sInstance;
}

void Level3::Release() {
	delete sInstance;
	sInstance = nullptr;
}

Level3::Level3() {

	mGround = new GLTexture("Sprite-0017.png", 0, 0, 1000, 400);
	mGround->Position(960.0f, 1150.0f);
	mGround->Scale(Vector2(2.0f, 1.0f));

	mGroundBlack = new GLTexture("Black.png", 0, 0, 1000, 400);
	mGroundBlack->Position(960.0f, 1150.0f);
	mGroundBlack->Scale(Vector2(2.0f, 1.0f));

	// white entities
	mPillarStart = new GLTexture("PillarLarge.png", 0, 0, 480, 960);
	mPillarStart->Parent(this);
	mPillarStart->Position(0.0f, 600.0f);
	mPillarStart->Scale(Vector2(0.6f, 0.75f));

	mLedgeStart = new GLTexture("PillarPlatform.png", 0, 0, 800, 70);
	mLedgeStart->Parent(this);
	mLedgeStart->Position(0.0f, 225.0f);
	mLedgeStart->Scale(Vector2(0.5f, 0.5f));

	//black entities
	mBlackPillarStart = new GLTexture("BlackPillarLarge.png", 0, 0, 480, 960);
	mBlackPillarStart->Parent(this);
	mBlackPillarStart->Position(0.0f, 600.0f);
	mBlackPillarStart->Scale(Vector2(0.6f, 0.75f));

	mBlackLedgeStart = new GLTexture("BlackPillarPlatformt.png", 0, 0, 800, 70);
	mBlackLedgeStart->Parent(this);
	mBlackLedgeStart->Position(0.0f, 225.0f);
	mBlackLedgeStart->Scale(Vector2(0.5f, 0.5f));
}

Level3::~Level3() {
	delete mPillarStart;
	mPillarStart = nullptr;
	delete mLedgeStart;
	mLedgeStart = nullptr;

	delete mBlackPillarStart;
	mBlackPillarStart = nullptr;
	delete mBlackLedgeStart;
	mBlackLedgeStart = nullptr;

	delete mGround;
	mGround = nullptr;
	delete mGroundBlack;
	mGroundBlack = nullptr;
}

void Level3::Update() {

}

void Level3::Render() {
	mGround->Render();

	mPillarStart->Render();
	mLedgeStart->RenderFlip();
}

void Level3::RenderWhite() {
	mGroundBlack->Render();

	mBlackPillarStart->Render();
	mBlackLedgeStart->RenderFlip();
}
