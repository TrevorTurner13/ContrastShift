#include "CreditsScreen.h"

CreditsScreen::CreditsScreen() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	//top bar entities
	mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.1);
	mThanks = new GLTexture("Thanks For Playing!", "Dragon Fire.ttf", 100, { 230,230,230 });
	mTopBar->Parent(this);
	mThanks->Parent(mTopBar);
	
	mThanks->Position(Vec2_Zero);

	//play mode entities
	mPlayModes = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.3f);
	mCreators = new GLTexture("Created By:", "Dragon Fire.ttf", 80, {230, 230, 230});
	mTrevor = new GLTexture("Trevor Turner", "Dragon Fire.ttf", 60, { 230,230,230 });
	mBrad = new GLTexture("Bradley Brooker", "Dragon Fire.ttf", 60, { 230,230,230 });
	mAndrew = new GLTexture("Andrew Hawboldt", "Dragon Fire.ttf", 60, { 230,230,230 });

	mPlayModes->Parent(this);
	mCreators->Parent(mPlayModes);
	mTrevor->Parent(mPlayModes);
	mBrad->Parent(mPlayModes);
	mAndrew->Parent(mPlayModes);

	mCreators->Position(Vec2_Zero);
	mTrevor->Position(0.0f, 60.0f);
	mBrad->Position(0.0f, 120.0f);
	mAndrew->Position(0.0f, 180.0f);

	//bottom bar entities
	mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.55f);
	mMusic = new GLTexture("Music & SFX", "Dragon Fire.ttf", 80, { 230, 230, 230 });
	mAndrew2 = new GLTexture("Andrew Hawboldt", "Dragon Fire.ttf", 60, { 230,230,230 });
	
	mArtwork = new GLTexture("Artwork", "Dragon Fire.ttf", 80, { 230, 230, 230 });
	mTrevor2 = new GLTexture("Trevor Turner", "Dragon Fire.ttf", 60, { 230,230,230 });
	mItchGuy = new GLTexture("penusbmic.itch.io", "Dragon Fire.ttf", 60, { 230,230,230 });

	mBottomBar->Parent(this);
	mMusic->Parent(mBottomBar);
	mAndrew2->Parent(mBottomBar);
	
	mArtwork->Parent(mBottomBar);
	mTrevor2->Parent(mBottomBar);
	mItchGuy->Parent(mBottomBar);
	
	mMusic -> Position(0,0);
	mAndrew2->Position(0.0f, 60.0f);
	
	mArtwork->Position(0.0f, 160.0f);
	mTrevor2->Position(0.0f, 220.0f);
	mItchGuy->Position(0.0f, 280.0f);

	

	//screen animation variables
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
	mThanks->Render();
	
	mCreators->Render();
	mTrevor->Render();
	mBrad->Render();
	mAndrew->Render();

	mMusic->Render();
	mAndrew2->Render();

	mArtwork->Render();
	mTrevor2->Render();
	mItchGuy->Render();
}