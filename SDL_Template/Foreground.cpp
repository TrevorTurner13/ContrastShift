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

	mPillar = new GLTexture("Pillarlarge.png", 0, 0, 480, 960);
	mPillar->Parent(this);
	mPillar->Position(0.0f, 450.0f);
	mPillar->Scale(Vector2(0.75f, 1.0f));
	
	mBlock = new GLTexture("Sprite-0015.png", 0, 0, 494, 330);
	mBlock->Parent(this);
	mBlock->Position(265.0f, 695.0f);
	mBlock->Scale(Vector2(0.65f, 0.65f));

	mLedge = new GLTexture("PillarPlatform.png", 0, 0, 800, 70);
	mLedge->Parent(this);
	mLedge->Position(250.0f, 565.0f);
	mLedge->Scale(Vector2(0.65f, 0.65f));

	//mLedge1 = new GLTexture("PillarPlatform.png", 0, 0, 800, 70);
	//mLedge1->Parent(this);
	//mLedge1->Position(-50.0f, 50.0f);
	//mLedge1->Scale(Vector2(1.2f, 1.2f));

	mSword1 = new GLTexture("swords.png", 0, 0, 320, 480);
	mSword1->Parent(this);
	mSword1->Position(160, 250);
	mSword1->Scale(Vector2(0.4f, 0.4f));
	
	mSword2 = new GLTexture("swords.png", 640, 0, 320, 480 );
	mSword2->Parent(this);
	mSword2->Position(750, 705);
	mSword2->Scale(Vector2(0.4f, 0.4f));
	
	mSword3 = new GLTexture("swords.png", 1280 , 0, 160, 480);
	mSword3->Parent(this);
	mSword3->Position(900, 705);
	mSword3 ->Scale(Vector2(0.4f, 0.4f));

}

Foreground::~Foreground() {

	delete mPillar;
	mPillar = nullptr;
	delete mBlock;
	mBlock = nullptr;
	delete mLedge;
	mLedge = nullptr;
	//delete mLedge1;
	//mLedge1 = nullptr;
	delete mSword1;
	mSword1 = nullptr;
	delete mSword2;
	mSword2 = nullptr;
	delete mSword3;
	mSword3 = nullptr;
	
}

void Foreground::Update() {
	mPillar->Update();
	mBlock->Update();
	mLedge->Update();
	/*mLedge1->Update();*/
	mSword1->Update();
	mSword2->Update();
	mSword3->Update();
	
}

void Foreground::Render() {
	mPillar->Render();
	mBlock->Render();
	mLedge->Render();
	/*mLedge1->Render();*/
	mSword1->Render();
	mSword2->Render();
	mSword3->Render();
	
}

