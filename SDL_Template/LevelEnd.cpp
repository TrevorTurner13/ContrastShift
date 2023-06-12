#include "LevelEnd.h"


LevelEnd* LevelEnd::sInstance = nullptr;

LevelEnd* LevelEnd::Instance() {
	if (sInstance == nullptr) {
		sInstance = new LevelEnd();
	}

	return sInstance;
}

void LevelEnd::Release() {
	delete sInstance;
	sInstance = nullptr;
}

LevelEnd::LevelEnd() {
	mTimer = Timer::Instance();

	mGround = new GLTexture("Sprite-0017.png", 0, 0, 1000, 400);
	mGround->Position(960.0f, 1150.0f);
	mGround->Scale(Vector2(2.0f, 1.0f));

	mGroundBlack = new GLTexture("Black.png", 0, 0, 1000, 400);
	mGroundBlack->Position(960.0f, 1150.0f);
	mGroundBlack->Scale(Vector2(2.0f, 1.0f));

	mChromaticOrb = new AnimatedGLTexture("Chromatic Orb.png", 0, 0, 320, 320, 33, 3.5f, Animation::Layouts::Horizontal);
	mChromaticOrb->Parent(this);
	mChromaticOrb->Position(1000.0f, 550.0f);

	mMonument = new AnimatedGLTexture("Dias.png", 0, 0, 1024, 592, 33, 3.5f, Animation::Layouts::Horizontal);
	mMonument->Parent(this);
	mMonument->Position(1000.0f, 660.0f);

	mMonumentBlack = new AnimatedGLTexture("BlackDias.png", 0, 0, 1024, 592, 33, 3.5f, Animation::Layouts::Horizontal);
	mMonumentBlack->Parent(this);
	mMonumentBlack->Position(1000.0f, 660.0f);

	mFlag1 = new AnimatedGLTexture("Flag2.png", 0, 0, 320, 320, 14, 1.5f, Animation::Layouts::Horizontal);
	mFlag1->Parent(this);
	mFlag1->Position(500.0f, 753.0f);
	mFlag1->Scale(Vector2(0.85f, 0.85f));

	mFlag2 = new AnimatedGLTexture("Flag2Alt.png", 0, 0, 320, 320, 14, 1.5f, Animation::Layouts::Horizontal);
	mFlag2->Parent(this);
	mFlag2->Position(1480.0f, 753.0f);
	mFlag2->Scale(Vector2(0.85f, 0.85f));

	mPillarStart = new GLTexture("ruins.png", 650, 160, 310, 480);
	mPillarStart->Parent(this);
	mPillarStart->Position(0.0f, 715.0f);
	mPillarStart->Scale(Vector2(1.0f, 1.0f));

	mPillarStartCollider = new GLTexture("Collider.png", 0, 0, 100, 70);
	mPillarStartCollider->Parent(mPillarStart);
	mPillarStartCollider->Position(0, -210);
	mPillarStartCollider->Scale(Vector2(2.0f, 1.0f));

	mBlackPillarStart = new GLTexture("BlackRuins.png", 650, 160, 310, 480);
	mBlackPillarStart->Parent(this);
	mBlackPillarStart->Position(0.0f, 715.0f);
	mBlackPillarStart->Scale(Vector2(1.0f, 1.0f));
}

LevelEnd::~LevelEnd() {
	delete mGround;
	mGround = nullptr;

	delete mGroundBlack;
	mGroundBlack = nullptr;

	delete mChromaticOrb;
	mChromaticOrb = nullptr;

	delete mMonument;
	mMonument = nullptr;

	delete mMonumentBlack;
	mMonumentBlack = nullptr;

	delete mPillarStart;
	mPillarStart = nullptr;

	delete mPillarStartCollider;
	mPillarStartCollider = nullptr;

	delete mBlackPillarStart;
	mBlackPillarStart = nullptr;

}

void LevelEnd::Update() {
	mChromaticOrb->Update();
	mMonument->Update();
	mMonumentBlack->Update();
	mFlag1->Update();
	mFlag2->Update();
}

void LevelEnd::Render() {
	mGround->Render();
	mPillarStart->Render();
	mFlag1->Render();
	mFlag2->Render();
	mMonument->Render();
	mChromaticOrb->Render();
}

void LevelEnd::RenderBlack() {
	mGroundBlack->Render();
	mBlackPillarStart->Render();
	mMonumentBlack->Render();
	mChromaticOrb->Render();
}