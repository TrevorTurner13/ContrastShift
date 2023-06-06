#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mInput = InputManager::Instance();

	delete mLevel1;
	mLevel1 = new Level1();

	delete mLevel2;
	mLevel2 = new Level2();

	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Position(300.0f, 590.0f);

	mMoveBoundsLeft = Vector2(130.0f, 1920.0f);
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
		break;
	}
	//std::cout << mPlayer->Position().x << std::endl;
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
		
	//	else {
	//		float pushback = (object->Position().y + object->ScaledDimensions().y / 2) - (player->Position().y - player->GetCurrentTexture()->ScaledDimensions().y / 2);

	//		player->Position(player->GetLastPosition().x, player->GetLastPosition().y + pushback);
	//		player->SetVelocity(0);
	//	}
	//}
	//if (VerticallyAligned(player, object)) {
	//	if (player->Position().x < object->Position().x) {
	//		/*float pushback = (player->Position().x + player->GetCurrentTexture()->ScaledDimensions().x / 2 - 50) - (object->Position().x - object->ScaledDimensions().x / 2);
	//		player->Position(player->GetLastPosition().x - pushback, player->GetLastPosition().y);
	//	*/
	//	}
	//	else {

	//		float pushback = (object->Position().x + object->ScaledDimensions().x / 2) - (player->Position().x - player->GetCurrentTexture()->ScaledDimensions().x / 2 + 50);
	//		player->Position(player->GetLastPosition().x + pushback, player->GetLastPosition().y);


	//	}
	}
	
	/*player->Position(player->GetLastPosition().x, player->GetLastPosition().y - 2);
	player->SetIsGrounded(true);
	player->SetVelocity(0);*/
}
	
void PlayScreen::ResolveBlockCollision(Player* player, GLTexture* block) {
	float mMoveSpeedTemp = 200.0f;
	if (VerticallyAligned(player, block)) {
		if (player->Position().x < block->Position().x && mInput->KeyDown(SDL_SCANCODE_D)) {
			block->Translate(Vec2_Right * mMoveSpeedTemp * mTimer->DeltaTime(), World);
			player->SetMoveSpeed(100.0f);
		}
		else {
			block->Translate(-Vec2_Right * mMoveSpeedTemp * mTimer->DeltaTime(), World);
		}
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
	/*Vector2 pos = mPlayer->Position(Local);
	if (pos.x < mMoveBoundsLeft.x) {
		pos.x = mMoveBoundsLeft.x;
	}
	else if (pos.x >= mMoveBoundsLeft.y) {
		pos.x = mMoveBoundsLeft.y;
	}
	mPlayer->Position(pos);*/

	if (mPlayer->GetIsGrounded() && !mPlayer->GetIsJumping()) {
		if (!mIsWhite) {
			if (!CheckCollision(mPlayer, mLevel2->GetLedge1Texture())
				&& !CheckCollision(mPlayer, mLevel2->GetBlock1Texture())
				&& !CheckCollision(mPlayer, mLevel2->GetColliderTexture())
				&& !CheckCollision(mPlayer, mLevel2->GetGroundTexture())) {

				mPlayer->SetIsGrounded(false);
			}
		}
		else {
			if (!CheckCollision(mPlayer, mLevel2->GetBlackLedge1Texture())
				&& !CheckCollision(mPlayer, mLevel2->GetColliderTexture())
				&& !CheckCollision(mPlayer, mLevel2->GetGroundTexture())) {

				mPlayer->SetIsGrounded(false);
			}
		}
		if (mInput->KeyDown(SDL_SCANCODE_RSHIFT)) {
			mPlayer->SetIsPushing(true);
			if (CheckCollision(mPlayer, mLevel2->GetBlock1Texture()) && !HorizontallyAligned(mPlayer, mLevel2->GetBlock1Texture())) {
				ResolveBlockCollision(mPlayer, mLevel2->GetBlock1Texture());
			}
			else if (CheckCollision(mPlayer, mLevel2->GetColliderBlock2Texture()) && !HorizontallyAligned(mPlayer, mLevel2->GetBlock1Texture())) {
				ResolveBlockCollision(mPlayer, mLevel2->GetColliderBlock2Texture());
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
			else if (CheckCollision(mPlayer, mLevel2->GetBlock1Texture())) {
				ResolvePlatformCollision(mPlayer, mLevel2->GetBlock1Texture());
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
			else if (CheckCollision(mPlayer, mLevel2->GetBlackBlock1Texture())) {
				ResolvePlatformCollision(mPlayer, mLevel2->GetBlackBlock1Texture());
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
	if (mPlayer->Position().x > 1900 && mPlayer->Position().y <= 520) {
		level += 1;
		mPlayer->Position(0.0f, mPlayer->Position().y);
	}
	if (mPlayer->Position().x < -50 && mPlayer->Position().y <= 520) {
		level -= 1;
		mPlayer->Position(1900.0f, mPlayer->Position().y);
	}
}