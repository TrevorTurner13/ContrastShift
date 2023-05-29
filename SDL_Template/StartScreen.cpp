#include "StartScreen.h"

StartScreen::StartScreen() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();


	// logo entities
	mLogo = new GLTexture("ContrastShift.png", 0, 0, 788, 112);
	mAnimatedLogo = new AnimatedGLTexture("ContrastShift.png", 0, 0, 788, 112, 3, 0.2f, Animation::Layouts::Vertical);

	mLogo->Parent(this);
	mAnimatedLogo->Parent(this);

	mLogo->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.32f);
	mAnimatedLogo->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.32f);

	//play mode entities
	mPlayModes = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.55f);
	mOnePlayerMode = new GLTexture( "PlayNew.png", 0,0,146,60);
	mTwoPlayerMode = new GLTexture("HowToPlayNew.png", 0,0,339,43);
	
	mPlayHighlight = new GLTexture("PlayHighlightNew.png", 0, 0, 146, 60);
	mHowToPlayHighlight = new GLTexture("HowToPlayHighLightNew.png", 0, 0, 355, 61);
	mPlayDefault = new GLTexture("PlayNew.png", 0, 0, 128, 42);
	mHowToPlayDefault = new GLTexture("HowToPlayNew.png", 0, 0, 339, 43);

	mPlayModes->Parent(this);
	mOnePlayerMode->Parent(mPlayModes);
	mTwoPlayerMode->Parent(mPlayModes);
	
	mPlayHighlight->Parent(mPlayModes);
	mPlayDefault->Parent(mPlayModes);
	mHowToPlayDefault->Parent(mPlayModes);
	mHowToPlayHighlight->Parent(mPlayModes);

	mOnePlayerMode->Position(0.0f, -35.0f);
	mTwoPlayerMode->Position(0.0f, 35.0f);
	
	mPlayHighlight->Position(0.0f, -35.0f);
	mPlayDefault->Position(0.0f, -35.0f);
	mHowToPlayDefault->Position(0.0f, 35.0f);
	mHowToPlayHighlight->Position(0.0f, 35.0f);
	
	
	mSelectedMode = 0;
	mOnePlayerMode = mPlayHighlight;



	// bottom bar entities
	mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.85f);
	mNamco = new GLTexture("BRANDVOR", "Dragon Fire.ttf", 70, { 230, 0, 0 });
	mDates = new GLTexture("2023-Forever Brandvor LTD.", "Dragon Fire.ttf", 32, { 230, 0, 0 });
	mRights = new GLTexture("ALL RIGHTS RESERVED", "Dragon Fire.ttf", 32, { 230, 0, 0 });

	mBottomBar->Parent(this);
	mNamco->Parent(mBottomBar);
	mDates->Parent(mBottomBar);
	mRights->Parent(mBottomBar);

	mNamco->Position(0.0f,26.0f);
	mDates->Position(0.0f, 75.0f);
	mRights->Position(0.0f, 110.0f);

	// screen animation variables
	ResetAnimation();

	/*mStars = BackgroundStars::Instance();
	mStars->Scroll(true);*/
	mAudio->PlayMusic("MUS/NewTitleSong.mp3", 100);
}


StartScreen::~StartScreen() {

	// logo entities
	delete mLogo;
	mLogo = nullptr;
	delete mAnimatedLogo;
	mAnimatedLogo = nullptr;

	// play mode entities
	delete mPlayModes;
	mPlayModes = nullptr;
	delete mOnePlayerMode;
	mOnePlayerMode = nullptr;
	delete mTwoPlayerMode;
	mTwoPlayerMode = nullptr;
	

	// bottom bar entities
	delete mBottomBar;
	mBottomBar = nullptr;
	delete mNamco;
	mNamco = nullptr;
	delete mDates;
	mDates = nullptr;
	delete mRights;
	mRights = nullptr;

	mTimer = nullptr;
	mInput = nullptr;
}

void StartScreen::ResetAnimation() {
	mAnimationStartPos = Vector2(0.0f, Graphics::SCREEN_HEIGHT);
	mAnimationEndPos = Vec2_Zero;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	Position(mAnimationStartPos);
}

int StartScreen::SelectedMode() {
	return mSelectedMode;
}

void StartScreen::ChangeSelectedMode(int change) {
	mSelectedMode += change;
	mAudio->PlaySFX("SFX/Select.wav", 0);
	if (mSelectedMode < 0) {
		mSelectedMode = 1;
		
	}
	else if (mSelectedMode > 1) {
		mSelectedMode = 0;
	}
	if (mSelectedMode == 0) {
		mOnePlayerMode = mPlayHighlight;
		mTwoPlayerMode = mHowToPlayDefault;
	}
	else if (mSelectedMode == 1) {
		mOnePlayerMode = mPlayDefault;
		mTwoPlayerMode = mHowToPlayHighlight;
	}
		
	

	
}

void StartScreen::Update() {
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
	else {
		mAnimatedLogo->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_DOWN)) {
			ChangeSelectedMode(1);
		}
		else if (mInput->KeyPressed(SDL_SCANCODE_UP)) {
			ChangeSelectedMode(-1);
		}
	}
	mTimer->Update();
	mOnePlayerMode->Update();
	mTwoPlayerMode->Update();
	
}

void StartScreen::Render() {

	if (!mAnimationDone) {
		mLogo->Render();
	}
	else {
		mAnimatedLogo->Render();
	}

	mOnePlayerMode->Render();
	mTwoPlayerMode->Render();

	mNamco->Render();
	mDates->Render();
	mRights->Render();
}