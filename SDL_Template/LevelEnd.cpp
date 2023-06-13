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
	mChromaticOrb->SetWrapMode(Animation::WrapModes::Loop);

	mOrbCollider = new GLTexture("Collider.png", 0, 0, 50, 50);
	mOrbCollider->Parent(mChromaticOrb);
	mOrbCollider->Position(Vec2_Zero);
	mOrbCollider->Scale(Vector2(1.8f, 1.8f));

	mMonument = new AnimatedGLTexture("Dias.png", 0, 0, 1024, 592, 33, 3.5f, Animation::Layouts::Horizontal);
	mMonument->Parent(this);
	mMonument->Position(1000.0f, 660.0f);
	mMonument->SetWrapMode(Animation::WrapModes::Loop);

	mMonumentBlack = new AnimatedGLTexture("BlackDias.png", 0, 0, 1024, 592, 33, 3.5f, Animation::Layouts::Horizontal);
	mMonumentBlack->Parent(this);
	mMonumentBlack->Position(1000.0f, 660.0f);
	mMonumentBlack->SetWrapMode(Animation::WrapModes::Loop);

	mMonumentBaseBottom = new GLTexture("Collider.png", 0, 0, 100, 70);
	mMonumentBaseBottom->Parent(mMonument);
	mMonumentBaseBottom->Position(0, 270);
	mMonumentBaseBottom->Scale(Vector2(9.5f, 1.0f));

	mMonumentBaseMid = new GLTexture("Collider.png", 0, 0, 100, 70);
	mMonumentBaseMid->Parent(mMonument);
	mMonumentBaseMid->Position(0, 200);
	mMonumentBaseMid->Scale(Vector2(7.0f, 1.0f));

	mMonumentBaseTop = new GLTexture("Collider.png", 0, 0, 100, 70);
	mMonumentBaseTop->Parent(mMonument);
	mMonumentBaseTop->Position(0, 140);
	mMonumentBaseTop->Scale(Vector2(4.5f, 1.0f));

	mFlag1 = new AnimatedGLTexture("Flag2.png", 0, 0, 320, 320, 14, 1.5f, Animation::Layouts::Horizontal);
	mFlag1->Parent(this);
	mFlag1->Position(500.0f, 760.0f);
	mFlag1->Scale(Vector2(0.85f, 0.85f));
	mFlag1->SetWrapMode(Animation::WrapModes::Loop);

	mFlag2 = new AnimatedGLTexture("Flag2Alt.png", 0, 0, 320, 320, 14, 1.5f, Animation::Layouts::Horizontal);
	mFlag2->Parent(this);
	mFlag2->Position(1480.0f, 760.0f);
	mFlag2->Scale(Vector2(0.85f, 0.85f));
	mFlag2->SetWrapMode(Animation::WrapModes::Loop);

	mBlackFlag1 = new AnimatedGLTexture("BlackFlag2.png", 0, 0, 320, 320, 14, 1.5f, Animation::Layouts::Horizontal);
	mBlackFlag1->Parent(this);
	mBlackFlag1->Position(500.0f, 760.0f);
	mBlackFlag1->Scale(Vector2(0.85f, 0.85f));
	mBlackFlag1->SetWrapMode(Animation::WrapModes::Loop);

	mBlackFlag2 = new AnimatedGLTexture("BlackFlag2Alt.png", 0, 0, 320, 320, 14, 1.5f, Animation::Layouts::Horizontal);
	mBlackFlag2->Parent(this);
	mBlackFlag2->Position(1480.0f, 760.0f);
	mBlackFlag2->Scale(Vector2(0.85f, 0.85f));
	mBlackFlag2->SetWrapMode(Animation::WrapModes::Loop);

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

	mPillarEnd = new GLTexture("Pillarlarge.png", 0, 0, 480, 960);
	mPillarEnd->Parent(this);
	mPillarEnd->Position(1950.0f, 480.0f);
	mPillarEnd->Scale(Vector2(0.75f, 1.0f));

	mBlackPillarEnd = new GLTexture("BlackPillarlarge.png", 0, 0, 480, 960);
	mBlackPillarEnd->Parent(this);
	mBlackPillarEnd->Position(1950.0f, 480.0f);
	mBlackPillarEnd->Scale(Vector2(0.75f, 1.0f));
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

	delete mFlag1;
	mFlag1 = nullptr;

	delete mFlag2;
	mFlag2 = nullptr;

	delete mBlackFlag1;
	mBlackFlag1 = nullptr;

	delete mBlackFlag2;
	mBlackFlag2 = nullptr;

	delete mPillarStart;
	mPillarStart = nullptr;

	delete mPillarEnd;
	mPillarEnd = nullptr;

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
	mBlackFlag1->Update();
	mBlackFlag2->Update();
}

void LevelEnd::Render() {
	mGround->Render();
	mPillarStart->Render();
	mPillarEnd->Render();
	mFlag1->Render();
	mFlag2->Render();
	mMonument->Render();
	mChromaticOrb->Render();
}

void LevelEnd::RenderBlack() {
	mGroundBlack->Render();
	mBlackPillarStart->Render();
	mBlackPillarEnd->Render();
	mBlackFlag1->Render();
	mBlackFlag2->Render();
	mMonumentBlack->Render();
	mChromaticOrb->Render();
}