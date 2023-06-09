#include "CreditsScreen.h"

CreditsScreen::CreditsScreen() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	//play mode entities
	mPlayModes = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.55f);
	mPlayModes->Parent(this);
	
	// bottom bar entities
	mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.85f);
	mBottomBar->Parent(this);
	

	// screen animation variables
	ResetAnimation();
}


CreditsScreen::~CreditsScreen() {
	
	// play mode entities
	delete mPlayModes;
	mPlayModes = nullptr;

	// bottom bar entities
	delete mBottomBar;
	mBottomBar = nullptr;
	
	mTimer = nullptr;
	mInput = nullptr;
}

void CreditsScreen::ResetAnimation() {
	mAnimationStartPos = Vector2(0.0f, Graphics::SCREEN_HEIGHT);
	mAnimationEndPos = Vec2_Zero;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	Position(mAnimationStartPos);
}




void CreditsScreen::Update() {
	if (!mAnimationDone) {
		mAnimationTimer += mTimer->DeltaTime();
		Position(Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));

		if (mAnimationTimer >= mAnimationTotalTime) {
			mAnimationDone = true;
			//mStars->Scroll(false);
		}

		if (mInput->KeyPressed(SDL_SCANCODE_DOWN) || mInput->KeyPressed(SDL_SCANCODE_UP)) {
			mAnimationTimer = mAnimationTotalTime;
		}
	}

	mTimer->Update();
	
}

void CreditsScreen::Render() {

	if (!mAnimationDone) {
		
	}
	else {
		
	}


}