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
		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)&& mStartScreen->SelectedMode()==0) {
			mCurrentScreen = Play;
			mAudio->PauseMusic();
			mAudio->PlayMusic("MUS/light.wav", 100);
			int Mix_MusicVolume(0);
			//mAudio->PlaySFX("MUS/Dark.wav", 100);
			//mAudio->PlaySFX("MUS/light.wav", 100);
		}
		else if (mInput->KeyPressed(SDL_SCANCODE_RETURN) && mStartScreen->SelectedMode() == 1) {
			mCurrentScreen = Tutorial;
		}
		break;
	case Play:
		mPlayScreen->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_LSHIFT)) {
			if (mPlayScreen->GetIsWhite()) {
				glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
				mAudio->PlaySFX("SFX/ShiftLight.wav", 0);
				mPlayScreen->SetIsWhite(false);
				mAudio->PlayMusic("MUS/Light.wav", 100);
				int Mix_MusicVolume(-0.2);
			}
			else {
				glClearColor(250.0f, 250.0f, 250.0f, 1.0f);
				mAudio->PlaySFX("SFX/ShiftDark.wav", 0);
				mPlayScreen->SetIsWhite(true);
				mAudio->PlayMusic("MUS/Dark.wav", 100);
				int Mix_MusicVolume(-0.2);
			}
			
		}
		if (mPlayScreen->GetEnding() && !mPlayScreen->GetAnimationDone()) {
				mCurrentScreen = Credits;
				
				mAudio->PlayMusic("MUS/End Song.wav", -1);
				int Mix_MusicVolume(-0.2);
		}
		break;

	case Tutorial:
		mGuy->Update();
		mLevel1->Update();
		mTutorialScreen->Update();
		
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE)) {
			mCurrentScreen = Start;
		}

		break;

	case Credits:
		
		glClearColor(0.65f, 0.75f, 0.85f, 1.0f);
		mGuyColor->Update();
		mCreditsScreen->Update();
	
		
		
	}
	
}

void ScreenManager::Render() { 
	if (mCurrentScreen != Credits && mPlayScreen->GetIsWhite()) {
		mClouds->RenderBlack();
	}
	else if (mCurrentScreen != Credits && !mPlayScreen->GetIsWhite()) {
		mClouds->Render();
	}
	else {
		mClouds->RenderColor();
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
	case Tutorial:
		mLevel1->Render();
		mGuy->Render();
		mTutorialScreen->Render();
		break;
	case Credits:
		mGuyColor->Render();
		mCreditsScreen->Render();
		
	}
}

ScreenManager::ScreenManager() {
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();
	mTutorialScreen = new TutorialScreen();
	mCreditsScreen = new CreditsScreen();

	mGuy = new AnimatedGLTexture("Character Sprite.png", 0, 1936, 320, 320, 6, 1.0f, Animation::Layouts::Horizontal);
	mGuy->Position(300.0f, 596.0f);
	mGuy->Scale(Vector2(0.5f, 0.5f));
	mGuy->SetWrapMode(Animation::WrapModes::Loop);

	mGuyColor = new AnimatedGLTexture("Character Sprite Color.png", 0, 0, 320, 320, 6, 1.0f, Animation::Layouts::Horizontal);
	mGuyColor->Position(300.0f, 625.0f);
	mGuyColor->Scale(Vector2(0.5f, 0.5f));
	mGuyColor->SetWrapMode(Animation::WrapModes::Loop);

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

	delete mGuyColor;
	mGuyColor = nullptr;
}