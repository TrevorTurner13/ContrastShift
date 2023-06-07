#include "Level2.h"
#include "PhysEntity.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Level2* Level2::sInstance = nullptr;

Level2* Level2::Instance() {
	if (sInstance == nullptr) {
		sInstance = new Level2();
	}

	return sInstance;
}

void Level2::Release() {
	delete sInstance;
	sInstance = nullptr;
}

Level2::Level2() {

	mCollider = new GLTexture("Collider.png", 0, 0, 100, 70);
	mCollider->Parent(this);
	mCollider->Position(50, 520);
	mCollider->Scale(Vector2(2.0f, 1.0f));

	mGround = new GLTexture("Sprite-0017.png", 0, 0, 1000, 400);
	mGround->Position(960.0f, 1100.0f);
	mGround->Scale(Vector2(2.0f, 1.0f));

	mGroundBlack = new GLTexture("Black.png", 0, 0, 1000, 400);
	mGroundBlack->Position(960.0f, 1100.0f);
	mGroundBlack->Scale(Vector2(2.0f, 1.0f));

	// white elements
	mPillar1 = new GLTexture("ruins.png", 650, 160, 310, 480);
	mPillar1->Parent(this);
	mPillar1->Position(0.0f, 705.0f);
	mPillar1->Scale(Vector2(0.9f, 0.9f));

	mPillar2 = new GLTexture("PillarLarge.png", 0, 0, 480, 960);
	mPillar2->Parent(this);
	mPillar2->Position(1900.0f, 600.0f);
	mPillar2->Scale(Vector2(0.6f, 0.75f));

	mBlock1 = new GLTexture("platforms.png", 0, 0, 480, 480);
	mBlock1->Parent(this);
	mBlock1->Position(300.0f, 793.0f);
	mBlock1->Scale(Vector2(0.45f, 0.45f));

	mColliderBlock1 = new GLTexture("Collider.png", 0, 0, 100, 70);
	mColliderBlock1->Parent(mBlock1);
	mColliderBlock1->Position(0.0f, -200.0f);
	mColliderBlock1->Scale(Vector2(1.35f, 1.0f));

	mBlock2 = new GLTexture("platforms.png", 640, 0, 480, 480);
	mBlock2->Parent(this);
	mBlock2->Position(1400.0f, 745.0f);
	mBlock2->Scale(Vector2(0.65f, 0.65f));

	mColliderBlock2 = new GLTexture("Collider.png", 0, 0, 100, 70);
	mColliderBlock2->Parent(mBlock2);
	mColliderBlock2->Position(0.0f, -210.0f);
	mColliderBlock2->Scale(Vector2(3.5f, 1.0f));

	mLedge1 = new GLTexture("PillarPlatform.png", 0, 0, 800, 70);
	mLedge1->Parent(this);
	mLedge1->Position(1800.0f, 225.0f);
	mLedge1->Scale(Vector2(0.5f, 0.5f));

	//mLedge2 = new GLTexture("PillarPlatform.png", 0, 0, 800, 70);
	//mLedge2->Parent(this);
	//mLedge2->Position(1500.0f, 550.0f);
	//mLedge2->Scale(Vector2(0.55f, 0.55f));

	mSword1 = new GLTexture("swords.png", 0, 0, 320, 480);
	mSword1->Parent(this);
	mSword1->Position(1750.0f, 400.0f);
	mSword1->Scale(Vector2(0.4f, 0.4f));

	mSword2 = new GLTexture("swords.png", 640, 0, 320, 480);
	mSword2->Parent(this);
	mSword2->Position(450, 805);
	mSword2->Scale(Vector2(0.4f, 0.4f));

	mSword3 = new GLTexture("swords.png", 1280, 0, 160, 480);
	mSword3->Parent(this);
	mSword3->Position(1100, 805);
	mSword3->Scale(Vector2(0.4f, 0.4f));

	mSword4 = new GLTexture("BlackSwords.png", 640, 0, 320, 480);
	mSword4->Parent(mBlackBlock1);
	mSword4->Position(50, 50);
	mSword4->Scale(Vector2(0.4f, 0.4f));

	

	// Black Elements
	mBlackPillar1 = new GLTexture("BlackRuins.png", 650, 160, 310, 480);
	mBlackPillar1->Parent(this);
	mBlackPillar1->Position(0.0f, 705.0f);
	mBlackPillar1->Scale(Vector2(0.9f, 0.9f));

	mBlackPillar2 = new GLTexture("BlackPillarLarge.png", 0, 0, 480, 960);
	mBlackPillar2->Parent(this);
	mBlackPillar2->Position(1900.0f, 600.0f);
	mBlackPillar2->Scale(Vector2(0.6f, 0.75f));

	mBlackBlock1 = new GLTexture("BlackPlatforms.png", 640, 640, 160, 480);
	mBlackBlock1->Parent(this);
	mBlackBlock1->Position(700.0f, 700.0f);
	mBlackBlock1->Scale(Vector2(0.85f, 0.85f));

	mColliderBlackBlock1 = new GLTexture("Collider.png", 0, 0, 100, 70);
	mColliderBlackBlock1->Parent(mBlackBlock1);
	mColliderBlackBlock1->Position(0.0f, -200.0f);
	mColliderBlackBlock1->Scale(Vector2(1.36f, 1.0f));

	mBlackLedge1 = new GLTexture("BlackPillarPlatformt.png", 0, 0, 800, 70);
	mBlackLedge1->Parent(this);
	mBlackLedge1->Position(1800.0f, 225.0f);
	mBlackLedge1->Scale(Vector2(0.5f, 0.5f));

	mBlackSword1 = new GLTexture("BlackSwords.png", 0, 0, 320, 480);
	mBlackSword1->Parent(this);
	mBlackSword1->Position(1800, 700);
	mBlackSword1->Scale(Vector2(0.4f, 0.4f));

	mBlackSword2 = new GLTexture("BlackSwords.png", 1280, 0, 160, 480);
	mBlackSword2->Parent(this);
	mBlackSword2->Position(1100, 805);
	mBlackSword2->Scale(Vector2(0.4f, 0.4f));

	mBlackFlag1 = new AnimatedGLTexture("BlackFlag.png", 0, 0, 320, 320, 12, 1.5f, Animation::Layouts::Horizontal);
	mBlackFlag1->Parent(this);
	mBlackFlag1->Position(1850.0f, 160.0f);
	mBlackFlag1->Scale(Vector2(0.35f, 0.35f));

	mBlackFlag2 = new AnimatedGLTexture("BlackFlag2.png", 0, 0, 320, 320, 14, 1.5f, Animation::Layouts::Horizontal);
	mBlackFlag2->Parent(this);
	mBlackFlag2->Position(1000.0f, 750.0f);
	mBlackFlag2->Scale(Vector2(1.0f, 1.0f));

}

Level2::~Level2() {
	// white entities
	delete mPillar1;
	mPillar1 = nullptr;
	delete mPillar2;
	mPillar2 = nullptr;

	delete mBlock1;
	mBlock1 = nullptr;
	delete mBlock2;
	mBlock2 = nullptr;

	delete mLedge1;
	mLedge1 = nullptr;
	//delete mLedge2;
	//mLedge2 = nullptr;

	delete mSword1;
	mSword1 = nullptr;
	delete mSword2;
	mSword2 = nullptr;
	delete mSword3;
	mSword3 = nullptr;
	delete mSword4;
	mSword4 = nullptr;

	 //black entities
	delete mBlackPillar1;
	mBlackPillar1 = nullptr;
	delete mBlackPillar2;
	mBlackPillar2 = nullptr;

	delete mBlackBlock1;
	mBlackBlock1 = nullptr;

	delete mBlackLedge1;
	mBlackLedge1 = nullptr;

	delete mBlackSword1;
	mBlackSword1 = nullptr;
	delete mBlackSword2;
	mBlackSword2 = nullptr;
	

	delete mBlackFlag1;
	mBlackFlag1 = nullptr;
	delete mBlackFlag2;
	mBlackFlag2 = nullptr;

	delete mGround;
	mGround = nullptr;

}

void Level2::Update() {
	mBlackFlag2->Update();
	mBlackFlag1->Update();
}

void Level2::Render() {

	mGround->Render();

	mPillar1->Render();
	mPillar2->Render();

	mColliderBlock2->Render();

	mLedge1->RenderFlip();
	//mLedge2->Render();

	mSword1->RenderFlip();
	mSword2->RenderFlip();
	mSword3->RenderFlip();
	mSword4->Render();
	
	mBlock1->Render();
	mBlock2->Render();
}

void Level2::RenderWhite() {
	mGroundBlack->Render();

	mBlackPillar1->Render();
	mBlackPillar2->Render();

	mBlackLedge1->RenderFlip();

	mBlackSword1->RenderFlip();
	mBlackSword2->RenderFlip();

	mBlackFlag1->Render();
	mBlackFlag2->Render();

	mBlackBlock1->Render();
}
