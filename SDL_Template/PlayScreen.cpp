#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mInput = InputManager::Instance();

	delete mForeground;
	mForeground = new Foreground();

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
	if (!mPlayer->GetIsGrounded()) {
		if (!mIsWhite) {
			if (CheckCollision(mPlayer->GetCurrentTexture(), mForeground->GetLedge1Texture())) {
				std::cout << "Collision!" << std::endl;
				mPlayer->Position(mPlayer->Position().x, mForeground->GetLedge1Texture()->Position().y + mForeground->GetLedge1Texture()->ScaledDimensions().y / 2 + mPlayer->GetCurrentTexture()->ScaledDimensions().y / 2 + 95);
				mPlayer->SetIsGrounded(true);
				mPlayer->SetVelocity(0);
			}
		}
		else {
			if (CheckCollision(mPlayer->GetCurrentTexture(), mForeground->GetBlackLedge1Texture())) {
				std::cout << "Collision!" << std::endl;
				mPlayer->Position(mPlayer->Position().x, mForeground->GetBlackLedge1Texture()->Position().y + mForeground->GetBlackLedge1Texture()->ScaledDimensions().y / 2 + mPlayer->GetCurrentTexture()->ScaledDimensions().y / 2 + 95);
				mPlayer->SetIsGrounded(true);
				mPlayer->SetVelocity(0);

			}
			
		}

	}

	
	
	
	
	
	if (CheckCollision(mPlayer->GetCurrentTexture(), mForeground->GetGroundTexture()) && !mPlayer->GetIsGrounded()) {
		std::cout << "Collision!" << std::endl;
		mPlayer->Position(mPlayer->Position().x, mForeground->GetGroundTexture()->Position().y + mForeground->GetGroundTexture()->ScaledDimensions().y / 2 - mPlayer->GetCurrentTexture()->ScaledDimensions().y / 2 - 95);
		mPlayer->SetIsGrounded(true);
		mPlayer->SetVelocity(0);
	}
}

void PlayScreen::Render() {
	if (!mIsWhite) {
		mForeground->Render();
		mPlayer->Render();
	}
	else {
		mForeground->RenderWhite();
		mPlayer->RenderDark();
	}
}

void PlayScreen::SetIsWhite(bool shift) {
	mIsWhite = shift;
}

bool PlayScreen::CheckCollision(AnimatedGLTexture* currentTexture, GLTexture* object) {
	//With locals it's common usage to use underscores instead of camelCasing
	float playerLeft = currentTexture->Position().x - currentTexture->ScaledDimensions().x / 2 + 50;
	float playerRight = currentTexture->Position().x + currentTexture->ScaledDimensions().x / 2 - 50;
	float playerTop = currentTexture->Position().y - currentTexture->ScaledDimensions().y / 2 + 40;
	float playerBottom = currentTexture->Position().y + currentTexture->ScaledDimensions().y / 2 - 40;

	float objectLeft = object->Position().x - object->ScaledDimensions().x / 2;
	float objectRight = object->Position().x + object->ScaledDimensions().x / 2;
	float objectTop = object->Position().y - object->ScaledDimensions().y / 2;
	float objectBottom = object->Position().y + object->ScaledDimensions().y / 2;

	//If Red's right side is further to the right than Blue's left side.
	//and Red's left side is further to the left than Blue's right side.
	//and Red's bottom side is further to the bottom than Blue's top side.
	//and Red's top side is further to the top than Blue's bottom side then..
	//There is collision!
	if (playerRight > objectLeft && playerLeft < objectRight
		&& playerBottom > objectTop && playerTop < objectBottom) {
		return true;
	}
	else {
		//If one of these statements is false, return false.
		return false;
	}
}
