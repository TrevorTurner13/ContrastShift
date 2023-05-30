#include "Foreground.h"

Foreground* Foreground::sInstance = nullptr;

Foreground* Foreground::Instance() {
	if (sInstance == nullptr) {
		sInstance = new Foreground();
	}

	return sInstance;
}

void Foreground::Release() {
	delete sInstance;
	sInstance = nullptr;
}

Foreground::Foreground() {

	mPillar1 = new GLTexture("Pillarlarge.png", 0, 0, 480, 960);
	mPillar1->Parent(this);
	mPillar1->Position(0.0f, 450.0f);
	mPillar1->Scale(Vector2(0.75f, 1.0f));

	mPillar2 = new GLTexture("PillarPlatform.png", 370, 80, 70, 398);
	mPillar2->Parent(this);
	mPillar2->Position(1500.0f, 721.0f);
	mPillar2->Scale(Vector2(0.90f, 0.90f));
	
	mBlock = new GLTexture("Sprite-0015.png", 0, 0, 494, 330);
	mBlock->Parent(this);
	mBlock->Position(265.0f, 793.0f);
	mBlock->Scale(Vector2(0.65f, 0.65f));

	mLedge1 = new GLTexture("PillarPlatform.png", 0, 0, 800, 70);
	mLedge1->Parent(this);
	mLedge1->Position(250.0f, 665.0f);
	mLedge1->Scale(Vector2(0.65f, 0.65f));

	mLedge2 = new GLTexture("PillarPlatform.png", 0, 0, 800, 70);
	mLedge2->Parent(this);
	mLedge2->Position(1500.0f, 520.0f);
	mLedge2->Scale(Vector2(0.65f, 0.65f));

	mSword1 = new GLTexture("swords.png", 0, 0, 320, 480);
	mSword1->Parent(this);
	mSword1->Position(160, 250);
	mSword1->Scale(Vector2(0.4f, 0.4f));
	
	mSword2 = new GLTexture("swords.png", 640, 0, 320, 480 );
	mSword2->Parent(this);
	mSword2->Position(750, 805);
	mSword2->Scale(Vector2(0.4f, 0.4f));
	
	mSword3 = new GLTexture("swords.png", 1280 , 0, 160, 480);
	mSword3->Parent(this);
	mSword3->Position(900, 805);
	mSword3 ->Scale(Vector2(0.4f, 0.4f));

	mFlag1 = new AnimatedGLTexture("flag.png", 0, 0, 320, 320, 12, 1.5f, Animation::Layouts::Horizontal);
	mFlag1->Parent(this);
	mFlag1->Position(1670, 450);
	mFlag1->Scale(Vector2(0.3f, 0.3f));

}

Foreground::~Foreground() {

	delete mPillar1;
	mPillar1 = nullptr;
	delete mPillar2;
	mPillar2 = nullptr;
	delete mBlock;
	mBlock = nullptr;
	delete mLedge1;
	mLedge1 = nullptr;
	delete mLedge2;
	mLedge2 = nullptr;
	delete mSword1;
	mSword1 = nullptr;
	delete mSword2;
	mSword2 = nullptr;
	delete mSword3;
	mSword3 = nullptr;

	delete mFlag1;
	mFlag1 = nullptr;
	
}

void Foreground::Update() {
	mPillar1->Update();
	mPillar2->Update();
	mBlock->Update();
	mLedge1->Update();
	mLedge2->Update();
	mSword1->Update();
	mSword2->Update();
	mSword3->Update();
	mFlag1->Update();
}

void Foreground::Render() {
	mPillar1->Render();
	mPillar2->Render();
	mBlock->Render();
	mLedge1->Render();
	mLedge2->Render();
	mSword1->Render();
	mSword2->Render();
	mSword3->Render();
	mFlag1->Render();
	
}

