#include "TutorialScreen.h"

TutorialScreen::TutorialScreen() {
	mMoveLeft = new GLTexture("Move Left", "Emulogic.ttf", 50, { 230,0,0 });
	mMoveRight= new GLTexture("Move Right", "Emulogic.ttf", 50, { 230,0,0 });
	mJump= new GLTexture("Jump", "Emulogic.ttf", 50, { 230,0,0 });
	mShift= new GLTexture("Shift Contrast", "Emulogic.ttf", 50, { 230,0,0 });
	mPush= new GLTexture("Push Object", "Emulogic.ttf", 50, { 230,0,0 });
}


TutorialScreen::~TutorialScreen() {

}


void TutorialScreen::Update() {

}

void TutorialScreen::Render() {
	mMoveLeft->Render();
	mMoveRight->Render();
	mJump->Render();
	mShift->Render();
	mPush->Render();

}