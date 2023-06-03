 #include "ScreenManager.h"

ScreenManager * ScreenManager::sInstance = nullptr;

ScreenManager * ScreenManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ScreenManager();
	}

	return sInstance;
}

void ScreenManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}



void ScreenManager::Update() {

	mClouds->Update();
	
	switch (mCurrentScreen) {
	case Start:
		mGuy->Update();
		mLevel1->Update();
		mStartScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
			mCurrentScreen = Play;
		}
		break;
	case Play:
		mPlayScreen->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_LSHIFT)) {
			if (mPlayScreen->GetIsWhite()) {
				glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
				mAudio->PlaySFX("SFX/ShiftLight.wav", 0);
				mPlayScreen->SetIsWhite(false);
			}
			else {
				glClearColor(250.0f, 250.0f, 250.0f, 1.0f);
				mAudio->PlaySFX("SFX/ShiftDark.wav", 0);
				mPlayScreen->SetIsWhite(true);
			}

		}
		break;
	}
}

void ScreenManager::Render() { 
	if (mPlayScreen->GetIsWhite()) {
		mClouds->RenderBlack();
		//mLevel1->RenderWhite();
	}
	else {
		mClouds->Render();
		//mLevel1->Render();
	}
	switch (mCurrentScreen) {
	case Start:
		mLevel1->Render();
		mGuy->Render();
		mStartScreen->Render();
		break;
	case Play:
		mPlayScreen->Render();
		break;
	}
}

ScreenManager::ScreenManager() {
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();

	mGuy = new AnimatedGLTexture("Character Sprite.png", 0, 1936, 320, 320, 6, 1.0f, Animation::Layouts::Horizontal);
	mGuy->Position(300.0f, 596.0f);
	mGuy->Scale(Vector2(0.5f, 0.5f));
	mGuy->SetWrapMode(Animation::WrapModes::Loop);

	mClouds = BackgroundClouds::Instance();
	mLevel1 = Level1::Instance();

	mCurrentScreen = Start;
}

ScreenManager::~ScreenManager() {
	mInput = nullptr;

	BackgroundClouds::Release();
	mClouds = nullptr;

	Level1::Release();
	mLevel1 = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;

	delete mGuy;
	mGuy = nullptr;
}