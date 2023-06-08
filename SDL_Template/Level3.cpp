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

	mSmallPillar1 = new GLTexture("PillarPlatform.png", 370, 80, 70, 398);
	mSmallPillar1->Parent(this);
	mSmallPillar1->Position(1350.0f, 870.0f);
	mSmallPillar1->Scale(Vector2(0.7f, 0.45f));

	mSmallPillar1Collider = new GLTexture("Collider.png", 0, 0, 100, 70);
	mSmallPillar1Collider->Parent(mSmallPillar1);
	mSmallPillar1Collider->Position(0, -170);
	mSmallPillar1Collider->Scale(Vector2(0.6f, 1.0f));

	mMedPillar1 = new GLTexture("PillarPlatform.png", 370, 80, 70, 398);
	mMedPillar1->Parent(this);
	mMedPillar1->Position(500.0f, 835.0f);
	mMedPillar1->Scale(Vector2(0.7f, 1.0f));

	mMedPillar1Collider = new GLTexture("Collider.png", 0, 0, 100, 70);
	mMedPillar1Collider->Parent(mMedPillar1);
	mMedPillar1Collider->Position(0, -170);
	mMedPillar1Collider->Scale(Vector2(0.6f, 1.0f));

	mTallPillar1 = new GLTexture("PillarPlatform.png", 370, 80, 70, 398);
	mTallPillar1->Parent(this);
	mTallPillar1->Position(250.0f, 700.0f);
	mTallPillar1->Scale(Vector2(0.7f, 1.85f));

	mTallPillar1Collider = new GLTexture("Collider.png", 0, 0, 100, 70);
	mTallPillar1Collider->Parent(mTallPillar1);
	mTallPillar1Collider->Position(0, -170);
	mTallPillar1Collider->Scale(Vector2(0.6f, 1.0f));

	mTallPillar2 = new GLTexture("PillarPlatform.png", 370, 80, 70, 398);
	mTallPillar2->Parent(this);
	mTallPillar2->Position(800.0f, 700.0f);
	mTallPillar2->Scale(Vector2(0.7f, 2.2f));

	mTallPillar2Collider = new GLTexture("Collider.png", 0, 0, 100, 70);
	mTallPillar2Collider->Parent(mTallPillar2);
	mTallPillar2Collider->Position(0, -170);
	mTallPillar2Collider->Scale(Vector2(0.6f, 1.0f));

	//black entities
	mBlackPillarStart = new GLTexture("BlackPillarLarge.png", 0, 0, 480, 960);
	mBlackPillarStart->Parent(this);
	mBlackPillarStart->Position(0.0f, 600.0f);
	mBlackPillarStart->Scale(Vector2(0.6f, 0.75f));

	mBlackLedgeStart = new GLTexture("BlackPillarPlatformt.png", 0, 0, 800, 70);
	mBlackLedgeStart->Parent(this);
	mBlackLedgeStart->Position(0.0f, 225.0f);
	mBlackLedgeStart->Scale(Vector2(0.5f, 0.5f));

	mMedBlackPillar1 = new GLTexture("BlackPillarPlatformt.png", 370, 80, 70, 398);
	mMedBlackPillar1->Parent(this);
	mMedBlackPillar1->Position(200.0f, 835.0f);
	mMedBlackPillar1->Scale(Vector2(0.7f, 1.0f));

	mMedBlackPillar1Collider = new GLTexture("Collider.png", 0, 0, 100, 70);
	mMedBlackPillar1Collider->Parent(mMedBlackPillar1);
	mMedBlackPillar1Collider->Position(0, -170);
	mMedBlackPillar1Collider->Scale(Vector2(0.6f, 1.0f));

	mMedBlackPillar2 = new GLTexture("BlackPillarPlatformt.png", 370, 80, 70, 398);
	mMedBlackPillar2->Parent(this);
	mMedBlackPillar2->Position(950.0f, 835.0f);
	mMedBlackPillar2->Scale(Vector2(0.7f, 1.0f));

	mMedBlackPillar2Collider = new GLTexture("Collider.png", 0, 0, 100, 70);
	mMedBlackPillar2Collider->Parent(mMedBlackPillar2);
	mMedBlackPillar2Collider->Position(0, -170);
	mMedBlackPillar2Collider->Scale(Vector2(0.6f, 1.0f));

	mTallBlackPillar1 = new GLTexture("BlackPillarPlatformt.png", 370, 80, 70, 398);
	mTallBlackPillar1->Parent(this);
	mTallBlackPillar1->Position(500.0f, 700.0f);
	mTallBlackPillar1->Scale(Vector2(0.7f, 2.1f));

	mTallBlackPillar1Collider = new GLTexture("Collider.png", 0, 0, 100, 70);
	mTallBlackPillar1Collider->Parent(mTallBlackPillar1);
	mTallBlackPillar1Collider->Position(0, -170);
	mTallBlackPillar1Collider->Scale(Vector2(0.6f, 1.0f));

	mTallBlackPillar2 = new GLTexture("BlackPillarPlatformt.png", 370, 80, 70, 398);
	mTallBlackPillar2->Parent(this);
	mTallBlackPillar2->Position(1200.0f, 700.0f);
	mTallBlackPillar2->Scale(Vector2(0.7f, 2.1f));

	mTallBlackPillar2Collider = new GLTexture("Collider.png", 0, 0, 100, 70);
	mTallBlackPillar2Collider->Parent(mTallBlackPillar2);
	mTallBlackPillar2Collider->Position(0, -170);
	mTallBlackPillar2Collider->Scale(Vector2(0.6f, 1.0f));

	mBlackFlag2 = new AnimatedGLTexture("BlackFlag2.png", 0, 0, 320, 320, 14, 1.5f, Animation::Layouts::Horizontal);
	mBlackFlag2->Parent(this);
	mBlackFlag2->Position(800.0f, 850.0f);
	mBlackFlag2->Scale(Vector2(0.85f, 0.85f));
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
	mBlackFlag2->Update();
}

void Level3::Render() {
	mGround->Render();

	mPillarStart->Render();
	mLedgeStart->RenderFlip();

	mSmallPillar1->RenderFlip();
	mMedPillar1->Render();
	mTallPillar1->Render();
	mTallPillar2->Render();
}

void Level3::RenderWhite() {
	mGroundBlack->Render();

	mBlackPillarStart->Render();
	mBlackLedgeStart->RenderFlip();

	mMedBlackPillar2->RenderFlip();
	mMedBlackPillar1->Render();
	mTallBlackPillar1->RenderFlip();
	mTallBlackPillar2->Render();

	mBlackFlag2->Render();
}
