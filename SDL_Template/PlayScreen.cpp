#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mInput = InputManager::Instance();

	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.8f);
	mPlayer->Active(true);

	mIsWhite = false;
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mPlayer;
	mPlayer = nullptr;
}

void PlayScreen::Update() {
	mPlayer->Update();	
}

void PlayScreen::Render() {
	if (!mIsWhite) {
		mPlayer->Render();
	}
	else {
		mPlayer->RenderDark();
	}
}

void PlayScreen::SetIsWhite(bool shift) {
	mIsWhite = shift;
}
