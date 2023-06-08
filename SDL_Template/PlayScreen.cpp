#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mInput = InputManager::Instance();

	delete mLevel1;
	mLevel1 = new Level1();

	delete mLevel2;
	mLevel2 = new Level2();

	delete mLevel3;
	mLevel3 = new Level3();

	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Position(300.0f, 590.0f);

	mMoveBoundsLeft = Vector2(130.0f, 1980.0f);
	mIsWhite = false;
	
	level = 1;
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mPlayer;
	mPlayer = nullptr;
}

void PlayScreen::Update() {
	mPlayer->Update();

	switch (level) {
	case 1:
		level1Update();
		mLevel1->Update();
		break;
	case 2:
		level2Update();
		mLevel2->Update();
		break;
	case 3:
		level3Update();
		mLevel3->Update();
		break;
	}
}

void PlayScreen::Render() {
	switch (level) {
		case 1:
			if (!mIsWhite) {
				mLevel1->Render();
			}
			else {
				mLevel1->RenderWhite();
			}
			break;
		case 2:
			//Level1::Release();
			if (!mIsWhite) {
				mLevel2->Render();
			}
			else {
				mLevel2->RenderWhite();
			}
			break;
		case 3:
			if (!mIsWhite) {
				mLevel3->Render();
			}
			else {
				mLevel3->RenderWhite();
			}
			break;	
	}
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

bool PlayScreen::CheckCollision(Player* player, GLTexture* object) {
	//With locals it's common usage to use underscores instead of camelCasing
	float playerLeft = player->Position().x - player->GetCurrentTexture()->ScaledDimensions().x / 2 + 50;
	float playerRight = player->Position().x + player->GetCurrentTexture()->ScaledDimensions().x / 2 - 50;
	float playerTop = player->Position().y - player->GetCurrentTexture()->ScaledDimensions().y / 2 + 20;
	float playerBottom = player->Position().y + player->GetCurrentTexture()->ScaledDimensions().y / 2 - 20;

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

void PlayScreen::ResolvePlatformCollision(Player* player, GLTexture* object) {
   	if (HorizontallyAligned(player, object)) {
		if (player->Position().y + 60
			< object->Position().y && player->GetVelocity() > 0) {
			float pushback = (player->Position().y + player->GetCurrentTexture()->ScaledDimensions().y / 2. - 30) - (object->Position().y - object->ScaledDimensions().y / 2);

			player->Position(player->GetLastPosition().x, player->GetLastPosition().y - pushback);
			player->SetIsGrounded(true);
			player->SetVelocity(0);
		}
	}
}
	
void PlayScreen::ResolvePushCollision(Player* player, GLTexture* block) {
	float mMoveSpeedTemp = 100.0f;
	if (VerticallyAligned(player, block)) {
		if (player->Position().x < block->Position().x && mInput->KeyDown(SDL_SCANCODE_D)) {
			block->Translate(Vec2_Right * mMoveSpeedTemp * mTimer->DeltaTime(), World);
		}
		else {
			block->Translate(-Vec2_Right * mMoveSpeedTemp * mTimer->DeltaTime(), World);
		}
	}
}

bool PlayScreen::CheckBlockCollision(GLTexture* block1, GLTexture* block2) {
	//With locals it's common usage to use underscores instead of camelCasing
	float block1Left = block1->Position().x - block1->ScaledDimensions().x / 2;
	float block1Right = block1->Position().x + block1->ScaledDimensions().x / 2;
	float block1Top = block1->Position().y - block1->ScaledDimensions().y / 2;
	float block1Bottom = block1->Position().y + block1->ScaledDimensions().y / 2;

	float block2Left = block2->Position().x - block2->ScaledDimensions().x / 2;
	float block2Right = block2->Position().x + block2->ScaledDimensions().x / 2;
	float block2Top = block2->Position().y - block2->ScaledDimensions().y / 2;
	float block2Bottom = block2->Position().y + block2->ScaledDimensions().y / 2;

	//If Red's right side is further to the right than Blue's left side.
	//and Red's left side is further to the left than Blue's right side.
	//and Red's bottom side is further to the bottom than Blue's top side.
	//and Red's top side is further to the top than Blue's bottom side then..
	//There is collision!
	if (block1Right > block2Left && block1Left < block2Right
		&& block1Bottom > block2Top && block1Top < block2Bottom) {
		return true;
	}
	else {
		//If one of these statements is false, return false.
		return false;
	}
}

void PlayScreen::ResolveBlockCollision(GLTexture* block1, GLTexture* block2) {
	float mMoveSpeedTemp = 100.0f;
		if (block1->Position().x < block2->Position().x && mInput->KeyDown(SDL_SCANCODE_D)) {
			block1->Translate(Vec2_Right * mMoveSpeedTemp * mTimer->DeltaTime(), World);
			block2->Translate(Vec2_Right * mMoveSpeedTemp * mTimer->DeltaTime(), World);
		}
		else if (block1->Position().x < block2->Position().x && mInput->KeyDown(SDL_SCANCODE_A)) {
			block1->Translate(-Vec2_Right * mMoveSpeedTemp * mTimer->DeltaTime(), World);
			block2->Translate(-Vec2_Right * mMoveSpeedTemp * mTimer->DeltaTime(), World);
		}
}


bool PlayScreen::VerticallyAligned(Player* player, GLTexture* object) {
	float playerTop = player->GetLastPosition().y - player->GetCurrentTexture()->ScaledDimensions().y / 2 + 20;
	float playerBottom = player->GetLastPosition().y + player->GetCurrentTexture()->ScaledDimensions().y / 2 - 20;
	float objectTop = object->Position().y - object->ScaledDimensions().y / 2;
	float objectBottom = object->Position().y + object->ScaledDimensions().y / 2;
	if (playerBottom > objectTop && playerTop < objectBottom) {
		return true;
	}
	else {
		return false;
	}
}

bool PlayScreen::HorizontallyAligned(Player* player, GLTexture* object) {
	float playerLeft = player->GetLastPosition().x - player->GetCurrentTexture()->ScaledDimensions().x / 2 + 50;
	float playerRight = player->GetLastPosition().x + player->GetCurrentTexture()->ScaledDimensions().x / 2 - 50;
	float objectLeft = object->Position().x - object->ScaledDimensions().x / 2;
	float objectRight = object->Position().x + object->ScaledDimensions().x / 2;
	if (playerLeft < objectRight && playerRight > objectLeft) {
		return true;
	}
	else {
		return false;
	}
}

bool PlayScreen::VerticallyAlignedBlocks(GLTexture* object1, GLTexture* object2) {
	float object1Top = object1->Position().y - object1->ScaledDimensions().y / 2;
	float object1Bottom = object1->Position().y + object1->ScaledDimensions().y / 2;
	float object2Top = object2->Position().y - object2->ScaledDimensions().y / 2;
	float object2Bottom = object2->Position().y + object2->ScaledDimensions().y / 2;
	if (object1Bottom > object2Top && object1Top < object2Bottom) {
		return true;
	}
	else {
		return false;
	}
}

void PlayScreen::level1Update() {
	Vector2 pos = mPlayer->Position(Local);
	if (pos.x < mMoveBoundsLeft.x) {
		pos.x = mMoveBoundsLeft.x;
	}
	else if (pos.x >= mMoveBoundsLeft.y) {
		pos.x = mMoveBoundsLeft.y;
	}
	mPlayer->Position(pos);

	if (mPlayer->GetIsGrounded() && !mPlayer->GetIsJumping()) {
		if (!mIsWhite) {
			if (!CheckCollision(mPlayer, mLevel1->GetLedge1Texture())
				&& !CheckCollision(mPlayer, mLevel1->GetLedge2Texture())
				&& !CheckCollision(mPlayer, mLevel1->GetColliderTexture())
				&& !CheckCollision(mPlayer, mLevel1->GetGroundTexture())) {

				mPlayer->SetIsGrounded(false);
			}
		}
		else {
			if (!CheckCollision(mPlayer, mLevel1->GetBlackLedge1Texture())
				&& !CheckCollision(mPlayer, mLevel1->GetColliderTexture())
				&& !CheckCollision(mPlayer, mLevel1->GetGroundTexture())) {

				mPlayer->SetIsGrounded(false);
			}
		}
	}
	else if (mPlayer->GetIsJumping() && !mPlayer->GetIsGrounded()) {
		mPlayer->SetIsJumping(false);
	}
	
	else if (!mIsWhite) {
		if (!mPlayer->GetIsGrounded() && !mPlayer->GetIsJumping()) {
			if (CheckCollision(mPlayer, mLevel1->GetLedge1Texture())) {
				ResolvePlatformCollision(mPlayer, mLevel1->GetLedge1Texture());
			}
			else if (CheckCollision(mPlayer, mLevel1->GetLedge2Texture())) {
				ResolvePlatformCollision(mPlayer, mLevel1->GetLedge2Texture());
			}
			else if (CheckCollision(mPlayer, mLevel1->GetColliderTexture())) {
				ResolvePlatformCollision(mPlayer, mLevel1->GetColliderTexture());
			}
			if (CheckCollision(mPlayer, mLevel1->GetGroundTexture())) {
				ResolvePlatformCollision(mPlayer, mLevel1->GetGroundTexture());
			}
		}
	}
	else if (mIsWhite) {
		if (!mPlayer->GetIsGrounded() && !mPlayer->GetIsJumping()) {
			if (CheckCollision(mPlayer, mLevel1->GetBlackLedge1Texture())) {
				ResolvePlatformCollision(mPlayer, mLevel1->GetBlackLedge1Texture());
			}
			if (CheckCollision(mPlayer, mLevel1->GetColliderTexture())) {
				ResolvePlatformCollision(mPlayer, mLevel1->GetColliderTexture());
			}
			if (CheckCollision(mPlayer, mLevel1->GetGroundTexture())) {
				ResolvePlatformCollision(mPlayer, mLevel1->GetGroundTexture());
			}
		}
	}
	
	//if player exits right side of screen the level is incremented up 1 and player position is set
	//where we want it to be on next level.
	if (mPlayer->Position().x > 1900 && mPlayer->Position().y <= 520) {
		level += 1;
		mPlayer->Position(0.0f, mPlayer->Position().y);
	}
}

void PlayScreen::level2Update() {
	Vector2 pos = mPlayer->Position(Local);
	if (pos.x < mMoveBoundsLeft.x - 170) {
		pos.x = mMoveBoundsLeft.x - 170;
	}
	else if (pos.x >= mMoveBoundsLeft.y) {
		pos.x = mMoveBoundsLeft.y;
	}
	mPlayer->Position(pos);

	if (mPlayer->GetIsGrounded() && !mPlayer->GetIsJumping()) {
		if (!mIsWhite) {
			if (!CheckCollision(mPlayer, mLevel2->GetLedge1Texture())
				&& !CheckCollision(mPlayer, mLevel2->GetColliderBlock1Texture())
				&& !CheckCollision(mPlayer, mLevel2->GetColliderTexture())
				&& !CheckCollision(mPlayer, mLevel2->GetColliderBlock2Texture())
				&& !CheckCollision(mPlayer, mLevel2->GetGroundTexture())) {

				mPlayer->SetIsGrounded(false);
			}
		}
		else {
			if (!CheckCollision(mPlayer, mLevel2->GetBlackLedge1Texture())
				&& !CheckCollision(mPlayer, mLevel2->GetColliderBlackBlock1Texture())
				&& !CheckCollision(mPlayer, mLevel2->GetColliderTexture())
				&& !CheckCollision(mPlayer, mLevel2->GetGroundTexture())) {

				mPlayer->SetIsGrounded(false);
			}
		}
		if (mInput->KeyDown(SDL_SCANCODE_CAPSLOCK)) {
			mPlayer->SetIsPushing(true);
			if (!mIsWhite) {
				if (CheckBlockCollision(mLevel2->GetBlock1Texture(), mLevel2->GetBlock2Texture())) {
					if (CheckCollision(mPlayer, mLevel2->GetBlock1Texture()) && !HorizontallyAligned(mPlayer, mLevel2->GetBlock1Texture()) && !HorizontallyAligned(mPlayer, mLevel2->GetBlock2Texture())) {
						ResolveBlockCollision(mLevel2->GetBlock1Texture(), mLevel2->GetBlock2Texture());
					}
					else if (CheckCollision(mPlayer, mLevel2->GetBlock2Texture()) && !HorizontallyAligned(mPlayer, mLevel2->GetBlock2Texture()) && !HorizontallyAligned(mPlayer, mLevel2->GetBlock1Texture())) {
						ResolveBlockCollision(mLevel2->GetBlock1Texture(), mLevel2->GetBlock2Texture());
					}
				}
				if (CheckCollision(mPlayer, mLevel2->GetBlock1Texture()) && !HorizontallyAligned(mPlayer, mLevel2->GetBlock1Texture())) {
					ResolvePushCollision(mPlayer, mLevel2->GetBlock1Texture());
				}
				else if (CheckCollision(mPlayer, mLevel2->GetBlock2Texture()) && !HorizontallyAligned(mPlayer, mLevel2->GetBlock2Texture())) {
					ResolvePushCollision(mPlayer, mLevel2->GetBlock2Texture());
				}		
			}
			else {
				if (CheckCollision(mPlayer, mLevel2->GetBlackBlock1Texture()) && !HorizontallyAligned(mPlayer, mLevel2->GetBlackBlock1Texture())) {
					ResolvePushCollision(mPlayer, mLevel2->GetBlackBlock1Texture());
				}
			}
		}
		else {
			mPlayer->SetIsPushing(false);
		}
		
	}
	else if (mPlayer->GetIsJumping() && !mPlayer->GetIsGrounded()) {
		mPlayer->SetIsJumping(false);
	}

	else if (!mIsWhite) {
		if (!mPlayer->GetIsGrounded() && !mPlayer->GetIsJumping()) {
			if (CheckCollision(mPlayer, mLevel2->GetLedge1Texture())) {
				ResolvePlatformCollision(mPlayer, mLevel2->GetLedge1Texture());
			}
			else if (CheckCollision(mPlayer, mLevel2->GetColliderBlock1Texture())) {
				ResolvePlatformCollision(mPlayer, mLevel2->GetColliderBlock1Texture());
			}
			else if (CheckCollision(mPlayer, mLevel2->GetColliderBlock2Texture())) {
				ResolvePlatformCollision(mPlayer, mLevel2->GetColliderBlock2Texture());
			}
			else if (CheckCollision(mPlayer, mLevel2->GetColliderTexture())) {
				ResolvePlatformCollision(mPlayer, mLevel2->GetColliderTexture());
			}
			if (CheckCollision(mPlayer, mLevel2->GetGroundTexture())) {
				ResolvePlatformCollision(mPlayer, mLevel2->GetGroundTexture());
			}
		}
	}
	else if (mIsWhite) {
		if (!mPlayer->GetIsGrounded() && !mPlayer->GetIsJumping()) {
			if (CheckCollision(mPlayer, mLevel2->GetBlackLedge1Texture())) {
				ResolvePlatformCollision(mPlayer, mLevel2->GetBlackLedge1Texture());
			}
			else if (CheckCollision(mPlayer, mLevel2->GetColliderBlackBlock1Texture())) {
				ResolvePlatformCollision(mPlayer, mLevel2->GetColliderBlackBlock1Texture());
			}
			if (CheckCollision(mPlayer, mLevel2->GetColliderTexture())) {
				ResolvePlatformCollision(mPlayer, mLevel2->GetColliderTexture());
			}
			if (CheckCollision(mPlayer, mLevel2->GetGroundTexture())) {
				ResolvePlatformCollision(mPlayer, mLevel2->GetGroundTexture());
			}
		}
	}

	//if player exits right side of screen the level is incremented up 1 and player position is set
	//where we want it to be on next level.
	if (mPlayer->Position().x > 1960 && mPlayer->Position().y <= 225) {
		level += 1;
		mPlayer->Position(0.0f, mPlayer->Position().y);
	}
	if (mPlayer->Position().x < -10 && mPlayer->Position().y <= 520) {
		level -= 1;
		mPlayer->Position(1900.0f, mPlayer->Position().y);
	}
}

void PlayScreen::level3Update() {
	Vector2 pos = mPlayer->Position(Local);
	if (pos.x < mMoveBoundsLeft.x - 170) {
		pos.x = mMoveBoundsLeft.x - 170;
	}
	else if (pos.x >= mMoveBoundsLeft.y) {
		pos.x = mMoveBoundsLeft.y;
	}
	mPlayer->Position(pos);

	if (mPlayer->GetIsGrounded() && !mPlayer->GetIsJumping()) {
		if (!mIsWhite) {
			if (!CheckCollision(mPlayer, mLevel3->GetPillarStartTexture())
				&& !CheckCollision(mPlayer, mLevel3->GetLedgeStartTexture())
				&& !CheckCollision(mPlayer, mLevel3->GetGroundTexture())) {

				mPlayer->SetIsGrounded(false);
			}
		}
		else {
			if (!CheckCollision(mPlayer, mLevel3->GetBlackPillarStartTexture())
				&& !CheckCollision(mPlayer, mLevel3->GetBlackLedgeStartTexture()) 
				&& !CheckCollision(mPlayer, mLevel3->GetGroundTexture())) {

				mPlayer->SetIsGrounded(false);
			}
		}
	//	if (mInput->KeyDown(SDL_SCANCODE_CAPSLOCK)) {
	//		mPlayer->SetIsPushing(true);
	//		if (!mIsWhite) {
	//			/*if (CheckBlockCollision(mLevel3->GetBlock1Texture(), mLevel2->GetBlock2Texture())) {
	//				if (CheckCollision(mPlayer, mLevel2->GetBlock1Texture()) && !HorizontallyAligned(mPlayer, mLevel2->GetBlock1Texture()) && !HorizontallyAligned(mPlayer, mLevel2->GetBlock2Texture())) {
	//					ResolveBlockCollision(mLevel2->GetBlock1Texture(), mLevel2->GetBlock2Texture());
	//				}
	//				else if (CheckCollision(mPlayer, mLevel2->GetBlock2Texture()) && !HorizontallyAligned(mPlayer, mLevel2->GetBlock2Texture()) && !HorizontallyAligned(mPlayer, mLevel2->GetBlock1Texture())) {
	//					ResolveBlockCollision(mLevel2->GetBlock1Texture(), mLevel2->GetBlock2Texture());
	//				}
	//			}*/
	//			if (CheckCollision(mPlayer, mLevel2->GetBlock1Texture()) && !HorizontallyAligned(mPlayer, mLevel2->GetBlock1Texture())) {
	//				ResolvePushCollision(mPlayer, mLevel2->GetBlock1Texture());
	//			}
	//			else if (CheckCollision(mPlayer, mLevel2->GetBlock2Texture()) && !HorizontallyAligned(mPlayer, mLevel2->GetBlock2Texture())) {
	//				ResolvePushCollision(mPlayer, mLevel2->GetBlock2Texture());
	//			}
	//		}
	//		else {
	//			if (CheckCollision(mPlayer, mLevel2->GetBlackBlock1Texture()) && !HorizontallyAligned(mPlayer, mLevel2->GetBlackBlock1Texture())) {
	//				ResolvePushCollision(mPlayer, mLevel2->GetBlackBlock1Texture());
	//			}
	//		}
	//	}
	//	else {
	//		mPlayer->SetIsPushing(false);
	//	}

	}
	/*else */if (mPlayer->GetIsJumping() && !mPlayer->GetIsGrounded()) {
		mPlayer->SetIsJumping(false);
	}

	else if (!mIsWhite) {
		if (!mPlayer->GetIsGrounded() && !mPlayer->GetIsJumping()) {
			if (CheckCollision(mPlayer, mLevel3->GetLedgeStartTexture())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetLedgeStartTexture());
			}
			if (CheckCollision(mPlayer, mLevel3->GetGroundTexture())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetGroundTexture());
			}
		}
	}
	else if (mIsWhite) {
		if (!mPlayer->GetIsGrounded() && !mPlayer->GetIsJumping()) {
			if (CheckCollision(mPlayer, mLevel3->GetBlackLedgeStartTexture())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetBlackLedgeStartTexture());
			}
			if (CheckCollision(mPlayer, mLevel3->GetGroundTexture())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetGroundTexture());
			}
		}
	}

	//if player exits right side of screen the level is incremented up 1 and player position is set
	//where we want it to be on next level.
	if (mPlayer->Position().x > 1960 && mPlayer->Position().y <= 225) {
		level += 1;
		mPlayer->Position(0.0f, mPlayer->Position().y);
	}
	if (mPlayer->Position().x < -10 && mPlayer->Position().y <= 225) {
		level -= 1;
		mPlayer->Position(1900.0f, mPlayer->Position().y);
	}
}