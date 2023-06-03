#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mInput = InputManager::Instance();

	delete mForeground;
	mForeground = new Foreground();

	delete mPlayer;
	mPlayer = new Player();

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
	mForeground->Update();
	if (mPlayer->GetIsGrounded() && !mPlayer->GetIsJumping()) {
		if (!mIsWhite) {
			if (!CheckCollision(mPlayer->GetCurrentTexture(), mForeground->GetLedge1Texture())
				&& !CheckCollision(mPlayer->GetCurrentTexture(), mForeground->GetLedge2Texture())
				&& !CheckCollision(mPlayer->GetCurrentTexture(), mForeground->GetBlock2Texture())
				&& !CheckCollision(mPlayer->GetCurrentTexture(), mForeground->GetGroundTexture())) {

				mPlayer->SetIsGrounded(false);
			}
		}
		else {
			if (!CheckCollision(mPlayer->GetCurrentTexture(), mForeground->GetBlackLedge1Texture())
				&& !CheckCollision(mPlayer->GetCurrentTexture(), mForeground->GetBlackBlock2Texture())
				&& !CheckCollision(mPlayer->GetCurrentTexture(), mForeground->GetGroundTexture())) {

				mPlayer->SetIsGrounded(false);
			}
		}
	}
	else if (mPlayer->GetIsJumping() && !mPlayer->GetIsGrounded()) {
		mPlayer->SetIsJumping(false);
	}
	else if (!mIsWhite) {
		if (CheckCollision(mPlayer->GetCurrentTexture(), mForeground->GetLedge1Texture())) {
			ResolveCollision(mPlayer, mForeground->GetLedge1Texture());
		}
		else if (CheckCollision(mPlayer->GetCurrentTexture(), mForeground->GetLedge2Texture())) {
			ResolveCollision(mPlayer, mForeground->GetLedge2Texture());
		}
		else if (CheckCollision(mPlayer->GetCurrentTexture(), mForeground->GetBlock2Texture())) {
			ResolveCollision(mPlayer, mForeground->GetBlock2Texture());
		}
		if (CheckCollision(mPlayer->GetCurrentTexture(), mForeground->GetGroundTexture())) {
			ResolveCollision(mPlayer, mForeground->GetGroundTexture());
		}
	}
	else if (mIsWhite) {
		if (CheckCollision(mPlayer->GetCurrentTexture(), mForeground->GetBlackLedge1Texture())) {
			ResolveCollision(mPlayer, mForeground->GetBlackLedge1Texture());
		}
		if (CheckCollision(mPlayer->GetCurrentTexture(), mForeground->GetBlackBlock2Texture())) {
			ResolveCollision(mPlayer, mForeground->GetBlackBlock2Texture());
		}
		if (CheckCollision(mPlayer->GetCurrentTexture(), mForeground->GetGroundTexture())) {
			ResolveCollision(mPlayer, mForeground->GetGroundTexture());
		}
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

bool PlayScreen::CheckCollision(AnimatedGLTexture* player, GLTexture* object) {
	//With locals it's common usage to use underscores instead of camelCasing
	float playerLeft = player->Position().x - player->ScaledDimensions().x / 2 + 50;
	float playerRight = player->Position().x + player->ScaledDimensions().x / 2 - 50;
	float playerTop = player->Position().y - player->ScaledDimensions().y / 2 + 20;
	float playerBottom = player->Position().y + player->ScaledDimensions().y / 2 - 20;

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

void PlayScreen::ResolveCollision(Player* player, GLTexture* object) {
	if (!player->GetIsGrounded() && !player->GetIsJumping()) {
		if (CheckCollision(player->GetCurrentTexture(), object)) {
			
			/*if (VerticallyAligned(player->GetCurrentTexture(), object)) {
				if (player->Position().x + player->GetCurrentTexture()->ScaledDimensions().x
					< object->Position().x + object->ScaledDimensions().x) {
					player->Position(object->Position().x, player->GetLastPosition().y);
					std::cout << "Collision! VERTICAL" << std::endl;
				}
			}
			else {
				player->Position(object->Position().x + object->ScaledDimensions().x, player->GetLastPosition().y);
			}
			if (HorizontallyAligned(player->GetCurrentTexture(), object)) {
				if (player->Position().y + player->GetCurrentTexture()->ScaledDimensions().y
					< object->Position().y + object->ScaledDimensions().y) {
					player->Position(player->GetLastPosition().x, player->GetLastPosition().y + 2);
					std::cout << "Collision! HORIZONTAL" << std::endl;
				}
				else {
					player->Position(player->GetLastPosition().x, player->GetLastPosition().y + 2);
				}
			}*/
			player->Position(player->GetLastPosition().x, player->GetLastPosition().y + 2);
			player->SetIsGrounded(true);
			player->SetVelocity(0);

		}
	}
}

bool PlayScreen::VerticallyAligned(AnimatedGLTexture* player, GLTexture* object) {
	float playerLeft = player->Position().x - player->ScaledDimensions().x / 2 + 50;
	float playerRight = player->Position().x + player->ScaledDimensions().x / 2 - 50;
	float objectLeft = object->Position().x - object->ScaledDimensions().x / 2;
	float objectRight = object->Position().x + object->ScaledDimensions().x / 2;
	if (playerRight > objectLeft && playerLeft < objectRight) {
		return true;
	}
}

bool PlayScreen::HorizontallyAligned(AnimatedGLTexture* player, GLTexture* object) {
	float playerTop = player->Position().y - player->ScaledDimensions().y / 2 + 20;
	float playerBottom = player->Position().y + player->ScaledDimensions().y / 2 - 20;
	float objectTop = object->Position().y - object->ScaledDimensions().y / 2;
	float objectBottom = object->Position().y + object->ScaledDimensions().y / 2;
	if (playerBottom > objectTop && playerTop < objectBottom) {
		return true;
	}
}




	

