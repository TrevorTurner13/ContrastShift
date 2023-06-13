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

	delete mLevelEnd;
	mLevelEnd = new LevelEnd();

	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Position(300.0f, 590.0f);

	mEnding = false;
	
	mFade = new AnimatedGLTexture("fade out1.png", 0, 0, 1920, 1080, 30, 3.0f, Animation::Layouts::Horizontal);
	mFade->Position(Vector2(Graphics::SCREEN_WIDTH/2 - 100, Graphics::SCREEN_HEIGHT/2) + 50);
	mFade->SetWrapMode(Animation::WrapModes::Once);

	mFade1 = new GLTexture("fade out.png", 0, 0, 1920, 1080);

	mMoveBoundsLeft = Vector2(130.0f, 1980.0f);
	mIsWhite = false;
	
	level = 4;
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	mLevel1->Release();
	mLevel2->Release();
	mLevel3->Release();
	mLevelEnd->Release();

	delete mPlayer;
	mPlayer = nullptr;
}

void PlayScreen::Update() {
	mPlayer->Update();

	switch (level) {
	case 1:
		Level1Update();
		mLevel1->Update();
		break;
	case 2:
		Level2Update();
		mLevel2->Update();
		break;
	case 3:
		Level3Update();
		mLevel3->Update();
		break;
	case 4:
		LevelEndUpdate();
		mLevelEnd->Update();
		
		if (mEnding) {

			mFade->Update();
		}
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
				mLevel1->RenderBlack();
			}
			break;
		case 2:
			//Level1::Release();
			if (!mIsWhite) {
				mLevel2->Render();
			}
			else {
				mLevel2->RenderBlack();
			}
			break;
		case 3:
			if (!mIsWhite) {
				mLevel3->Render();
			}
			else {
				mLevel3->RenderBlack();
			}
			break;	
		case 4:
			
			if (!mIsWhite) {
				mLevelEnd->Render();
			}
			else {
				mLevelEnd->RenderBlack();
			}
			
			if (mEnding) {
 				mFade->Render();
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
			< object->Position().y && player->GetVelocityY() > 0) {
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
	//mAudio->PlayMusic("SFX/Push.wav", 0);
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

void PlayScreen::Level1Update() {
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

void PlayScreen::Level2Update() {
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

void PlayScreen::Level3Update() {
	Vector2 pos = mPlayer->Position(Local);
	if (pos.x < mMoveBoundsLeft.x - 170) {
		pos.x = mMoveBoundsLeft.x - 170;
	}
	else if (pos.x >= mMoveBoundsLeft.y) {
		pos.x = mMoveBoundsLeft.y;
	}
	mPlayer->Position(pos);
	if (!CheckBlockCollision(mLevel3->GetBlackBlock1Texture(), mLevel3->GetLedgeEndTexture()) || !CheckBlockCollision(mLevel3->GetBlackBlock1Texture(), mLevel3->GetGroundTexture())) {
		mLevel3->SetBlockGrounded(false);
	}
	if (!mLevel3->GetBlockGrounded()) {
		mLevel3->SetBlockVelocity(mLevel3->GetVelocity(), mLevel3->GetGravity());
		if (CheckBlockCollision(mLevel3->GetBlackBlock1Texture(), mLevel3->GetLedgeEndTexture())) {
			mLevel3->SetBlockGrounded(true);
			mLevel3->SetBlockVelocity(0, 0);
			
		}
		else if (CheckBlockCollision(mLevel3->GetBlackBlock1Texture(), mLevel3->GetGroundTexture())) {
			mLevel3->SetBlockGrounded(true);
			mLevel3->SetBlockVelocity(0, 0);
			if (mLevel3->GetBlackBlock1Texture()->Position().y > 880.0f) {
				mLevel3->GetBlackBlock1Texture()->Position(mLevel3->GetBlackBlock1Texture()->Position().x, 880.0f);
			}
		}
	}
	mLevel3->GetBlackBlock1Texture()->Position(mLevel3->GetBlackBlock1Texture()->Position() + mLevel3->GetVelocity());

	if (mPlayer->GetIsGrounded() && !mPlayer->GetIsJumping()) {
		if (!mIsWhite) {
			if (!CheckCollision(mPlayer, mLevel3->GetLedgeStartTexture())
				&& !CheckCollision(mPlayer, mLevel3->GetSmallPillar1Collider())
				&& !CheckCollision(mPlayer, mLevel3->GetMedPillar1Collider())
				&& !CheckCollision(mPlayer, mLevel3->GetTallPillar1Collider())
				&& !CheckCollision(mPlayer, mLevel3->GetTallPillar2Collider())
				&& !CheckCollision(mPlayer, mLevel3->GetLedgeEndTexture())
				&& !CheckCollision(mPlayer, mLevel3->GetPillarEndCollider())
				&& !CheckCollision(mPlayer, mLevel3->GetGroundTexture())) {

				mPlayer->SetIsGrounded(false);
			}
		}
		else {
			if (!CheckCollision(mPlayer, mLevel3->GetLedgeStartTexture())
				&& !CheckCollision(mPlayer, mLevel3->GetMedBlackPillar1Collider())
				&& !CheckCollision(mPlayer, mLevel3->GetMedBlackPillar2Collider())
				&& !CheckCollision(mPlayer, mLevel3->GetTallBlackPillar1Collider())
				&& !CheckCollision(mPlayer, mLevel3->GetTallBlackPillar2Collider())
				&& !CheckCollision(mPlayer, mLevel3->GetBlackLedgeEndTexture())
				&& !CheckCollision(mPlayer, mLevel3->GetBlackBlock1Texture())
				&& !CheckCollision(mPlayer, mLevel3->GetPillarEndCollider())
				&& !CheckCollision(mPlayer, mLevel3->GetGroundTexture())) {

				mPlayer->SetIsGrounded(false);
			}
		}
		if (mInput->KeyDown(SDL_SCANCODE_CAPSLOCK)) {
			mPlayer->SetIsPushing(true);

			if (CheckCollision(mPlayer, mLevel3->GetBlackBlock1Texture()) && !HorizontallyAligned(mPlayer, mLevel3->GetBlackBlock1Texture())) {
				ResolvePushCollision(mPlayer, mLevel3->GetBlackBlock1Texture());
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
			if (CheckCollision(mPlayer, mLevel3->GetLedgeStartTexture())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetLedgeStartTexture());
			}
			else if (CheckCollision(mPlayer, mLevel3->GetSmallPillar1Collider())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetSmallPillar1Collider());
			}
			else if (CheckCollision(mPlayer, mLevel3->GetMedPillar1Collider())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetMedPillar1Collider());
			}
			else if (CheckCollision(mPlayer, mLevel3->GetTallPillar1Collider())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetTallPillar1Collider());
			}
			else if (CheckCollision(mPlayer, mLevel3->GetTallPillar2Collider())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetTallPillar2Collider());
			}
			else if (CheckCollision(mPlayer, mLevel3->GetLedgeEndTexture())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetLedgeEndTexture());
			}
			else if (CheckCollision(mPlayer, mLevel3->GetPillarEndCollider())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetPillarEndCollider());
			}
			if (CheckCollision(mPlayer, mLevel3->GetGroundTexture())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetGroundTexture());
			}
		}
	}
	else if (mIsWhite) {
		if (!mPlayer->GetIsGrounded() && !mPlayer->GetIsJumping()) {
			if (CheckCollision(mPlayer, mLevel3->GetLedgeStartTexture())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetLedgeStartTexture());
			}
			else if (CheckCollision(mPlayer, mLevel3->GetMedBlackPillar1Collider())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetMedBlackPillar1Collider());
			}
			else if (CheckCollision(mPlayer, mLevel3->GetMedBlackPillar2Collider())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetMedBlackPillar2Collider());
			}
			else if (CheckCollision(mPlayer, mLevel3->GetTallBlackPillar1Collider())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetTallBlackPillar1Collider());
			}
			else if (CheckCollision(mPlayer, mLevel3->GetTallBlackPillar2Collider())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetTallBlackPillar2Collider());
			}
			else if (CheckCollision(mPlayer, mLevel3->GetBlackLedgeEndTexture())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetBlackLedgeEndTexture());
			}
			else if (CheckCollision(mPlayer, mLevel3->GetBlackBlock1Texture())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetBlackBlock1Texture());
			}
			else if (CheckCollision(mPlayer, mLevel3->GetPillarEndCollider())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetPillarEndCollider());
			}
			if (CheckCollision(mPlayer, mLevel3->GetGroundTexture())) {
				ResolvePlatformCollision(mPlayer, mLevel3->GetGroundTexture());
			}
		}
	}
	//if player exits right side of screen the level is incremented up 1 and player position is set
	//where we want it to be on next level.
	if (mPlayer->Position().x > 1960 && mPlayer->Position().y <= 475 && mPlayer->Position().y >= 235) {
		level += 1;
		mPlayer->Position(0.0f, mPlayer->Position().y);
	}
	if (mPlayer->Position().x < -10 && mPlayer->Position().y <= 225) {
		level -= 1;
		mPlayer->Position(1900.0f, mPlayer->Position().y);
	}
}

void PlayScreen::LevelEndUpdate() {
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
			if (!CheckCollision(mPlayer, mLevelEnd->GetPillarStartCollider())
				&& !CheckCollision(mPlayer, mLevelEnd->GetMonumentBaseBottom())
				&& !CheckCollision(mPlayer, mLevelEnd->GetMonumentBaseMid())
				&& !CheckCollision(mPlayer, mLevelEnd->GetMonumentBaseTop())
				&& !CheckCollision(mPlayer, mLevelEnd->GetGroundTexture())) {

				mPlayer->SetIsGrounded(false);
			}
		}
		else {
			if (!CheckCollision(mPlayer, mLevelEnd->GetPillarStartCollider())
				&& !CheckCollision(mPlayer, mLevelEnd->GetMonumentBaseBottom())
				&& !CheckCollision(mPlayer, mLevelEnd->GetMonumentBaseMid())
				&& !CheckCollision(mPlayer, mLevelEnd->GetMonumentBaseTop())
				&& !CheckCollision(mPlayer, mLevelEnd->GetGroundTexture())) {

				mPlayer->SetIsGrounded(false);
			}
		}
	}
	else if (mPlayer->GetIsJumping() && !mPlayer->GetIsGrounded()) {
		mPlayer->SetIsJumping(false);
	}

	else if (!mIsWhite) {
		if (!mPlayer->GetIsGrounded() && !mPlayer->GetIsJumping()) {
			if (CheckCollision(mPlayer, mLevelEnd->GetPillarStartCollider())) {
				ResolvePlatformCollision(mPlayer, mLevelEnd->GetPillarStartCollider());
			}
			else if (CheckCollision(mPlayer, mLevelEnd->GetMonumentBaseBottom())) {
				ResolvePlatformCollision(mPlayer, mLevelEnd->GetMonumentBaseBottom());
			}
			else if (CheckCollision(mPlayer, mLevelEnd->GetMonumentBaseMid())) {
				ResolvePlatformCollision(mPlayer, mLevelEnd->GetMonumentBaseMid());
			}
			else if (CheckCollision(mPlayer, mLevelEnd->GetMonumentBaseTop())) {
				ResolvePlatformCollision(mPlayer, mLevelEnd->GetMonumentBaseTop());
			}
			if (CheckCollision(mPlayer, mLevelEnd->GetOrbCollider())) {
				mPlayer->Active(false);
				mPlayer->SetVelocity(Vector2(0.0f, -1.0f));
				if (mPlayer->Position().y <= 400.0f) {
					mPlayer->Position(mPlayer->Position().x, 400.0f);
				}
				mEnding = true;
			}
			if (CheckCollision(mPlayer, mLevelEnd->GetGroundTexture())) {
				ResolvePlatformCollision(mPlayer, mLevelEnd->GetGroundTexture());
			}
		}
	}
	else if (mIsWhite) {
		if (!mPlayer->GetIsGrounded() && !mPlayer->GetIsJumping()) {
			if (CheckCollision(mPlayer, mLevelEnd->GetPillarStartCollider())) {
				ResolvePlatformCollision(mPlayer, mLevelEnd->GetPillarStartCollider());
			}
			else if (CheckCollision(mPlayer, mLevelEnd->GetMonumentBaseBottom())) {
				ResolvePlatformCollision(mPlayer, mLevelEnd->GetMonumentBaseBottom());
			}
			else if (CheckCollision(mPlayer, mLevelEnd->GetMonumentBaseMid())) {
				ResolvePlatformCollision(mPlayer, mLevelEnd->GetMonumentBaseMid());
			}
			else if (CheckCollision(mPlayer, mLevelEnd->GetMonumentBaseTop())) {
				ResolvePlatformCollision(mPlayer, mLevelEnd->GetMonumentBaseTop());
			}
			if (CheckCollision(mPlayer, mLevelEnd->GetOrbCollider())) {
				mPlayer->Active(false);
				mPlayer->SetVelocity(Vector2(0.0f, -1.0f));
				if (mPlayer->Position().y <= 400.0f) {
					mPlayer->Position(mPlayer->Position().x, 400.0f);
					mPlayer->SetVelocity(Vector2(mPlayer->GetVelocityX(), 0.0f));
				}
				mEnding = true;
			}
			if (CheckCollision(mPlayer, mLevelEnd->GetGroundTexture())) {
				ResolvePlatformCollision(mPlayer, mLevelEnd->GetGroundTexture());
			}
		}
	}
	//if player exits right side of screen the level is incremented up 1 and player position is set
	//where we want it to be on next level.
	if (mPlayer->Position().x > 1960 && mPlayer->Position().y <= 475 && mPlayer->Position().y >= 235) {
		level += 1;
		mPlayer->Position(0.0f, mPlayer->Position().y);
	}
	if (mPlayer->Position().x < -10 && mPlayer->Position().y <= 225) {
		level -= 1;
		mPlayer->Position(1900.0f, mPlayer->Position().y);
	}
}