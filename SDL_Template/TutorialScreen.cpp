#include "TutorialScreen.h"

TutorialScreen::TutorialScreen() {
	mMoveLeft = new GLTexture("Move Left", "emulogic.ttf", 25, { 230,230,230 });
	mMoveRight= new GLTexture("Move Right", "emulogic.ttf", 25, { 230,230,230 });
	mJump= new GLTexture("Jump", "emulogic.ttf", 25, { 230,230,230 });
	mShift= new GLTexture("Shift Contrast", "emulogic.ttf", 25, { 230,230,230 });
	mPush= new GLTexture("Push Object", "emulogic.ttf", 25, { 230,230,230 });

	mA = new GLTexture("A", "Key.ttf", 75, { 230,230,230 });
	mD = new GLTexture("D", "Key.ttf", 75, { 230,230,230 });
	mSpace = new GLTexture("w", "Key.ttf", 75, { 230,230,230 });
	mShiftKey = new GLTexture("g", "Key.ttf", 75, { 230,230,230 });
	mCaps = new GLTexture("f", "Key.ttf", 75, { 230,230,230 });
	
	mMoveLeft->Position(800, 300.0f);
	mA->Position(1100, 300);
	
	mMoveRight->Position(800, 375);
	mD->Position(1100, 375);
	
	mJump->Position(800, 450);
	mSpace->Position(1100, 450);

	mShift->Position(800, 525);
	mShiftKey->Position(1100, 525);

	mPush->Position(800, 600);
	mCaps->Position(1100, 600);

	// bottom bar entities
	mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.85f);
	mNamco = new GLTexture("BRANDVOR", "Dragon Fire.ttf", 70, { 230, 0, 0 });
	mDates = new GLTexture("2023-Forever Brandvor LTD.", "Dragon Fire.ttf", 32, { 230, 0, 0 });
	mRights = new GLTexture("ALL RIGHTS RESERVED", "Dragon Fire.ttf", 32, { 230, 0, 0 });

	mBottomBar->Parent(this);
	mNamco->Parent(mBottomBar);
	mDates->Parent(mBottomBar);
	mRights->Parent(mBottomBar);

	mNamco->Position(0.0f, 26.0f);
	mDates->Position(0.0f, 75.0f);
	mRights->Position(0.0f, 110.0f);
}


TutorialScreen::~TutorialScreen() {
	delete mMoveLeft;
	mMoveLeft = nullptr;

	delete mMoveRight;
	mMoveRight = nullptr;

	delete mJump;
	mJump = nullptr;

	delete mShift;
	mShift = nullptr;

	delete mPush;
	mPush = nullptr;

	delete mA;
	mA = nullptr;

	delete mD;
	mD = nullptr;

	delete mSpace;
	mSpace = nullptr;

	delete mShiftKey;
	mShiftKey = nullptr;

	delete mCaps;
	mCaps = nullptr;

	delete mBottomBar;
	mBottomBar = nullptr;

	delete mNamco;
	mNamco = nullptr;

	delete mDates;
	mDates = nullptr;

	delete mRights;
	mRights = nullptr;


}


void TutorialScreen::Update() {

}

void TutorialScreen::Render() {
	mMoveLeft->Render();
	mMoveRight->Render();
	mJump->Render();
	mShift->Render();
	mPush->Render();
	mA->Render();
	mD->Render();
	mSpace->Render();
	mShiftKey->Render();
	mCaps->Render();
	mNamco->Render();
	mDates->Render();
	mRights->Render();
}