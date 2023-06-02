#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

//Rect ledge1(400.0f, 945.0f, 520.0f, 6.0f);
//Rect ledge2(1500.0f, 550.0f, 440.0f, 5.f);
//Rect block1(265.0f, 793.0f, 321.1f, 214.5f);
//Rect ground(300, 1200, 4000, 400);

void Player::HandleMovement() {
	if (mInput->KeyDown(SDL_SCANCODE_D)) {
		Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
		mMovingLeft = false;
		mIsFacingLeft = false;
		mMovingRight = true;
		mIsFacingRight = true;
	}
	else if (mInput->KeyDown(SDL_SCANCODE_A)) {
		Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
		mMovingRight = false;
		mIsFacingRight = false;
		mMovingLeft = true;
		mIsFacingLeft = true;
	}
	else {
		mMovingLeft = false;
		mMovingRight = false;
	}

	Vector2 pos = Position(Local);
	
	/*if (pos.x < mMoveBoundsLeft.x) {
		pos.x = mMoveBoundsLeft.x;
	}
	else if (pos.x >= mMoveBoundsRight.x && pos.y > mMoveBoundsRight.y) {
		pos.x = mMoveBoundsRight.x;		
	}*/
	

	Position(pos);
	mLastPosition = Position(Local);
}

void Player::SetIsGrounded(bool isGrounded) {
	mIsGrounded = isGrounded;
}

void Player::SetVelocity(Vector2 velocity) {
	mVelocity = velocity;
}

void Player::HandleFiring() {
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
		/*for (int i = 0; i < MAX_BULLETS; ++i) {
			if (!mBullets[i]->Active()) {
				mBullets[i]->Fire(Position());
				mAudio->PlaySFX("SFX/Fire.wav");
				break;
			}
		}*/
	}
}

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;
	mWasHit = false;
	mMovingRight = false;
	mIsFacingRight = true;
	mIsFacingLeft = false;
	mMovingLeft = false;
	mIsJumping = false;
	mIsWhite = false;
	mIsGrounded = true;
	mGravity = Vector2(0.0, 25);
	mJumpPower = Vector2(0.0, -15);

	mScore = 0;
	mLives = 2;

	mGuy = new AnimatedGLTexture("Character Sprite.png", 0, 2560, 320, 320, 6, 1.0f, Animation::Layouts::Horizontal);
	mGuy->Parent(this);
	mGuy->Position(-478.0f, -275.0f);
	mGuy->Scale(Vector2(0.5f, 0.5f));
	mGuy->SetWrapMode(Animation::WrapModes::Loop);

	mGuyDark = new AnimatedGLTexture("Character Sprite.png", 0, 640, 320, 320, 6, 1.0f, Animation::Layouts::Horizontal);
	mGuyDark->Parent(this);
	mGuyDark->Position(mGuy->Position().x, mGuy->Position().y);
	mGuyDark->Scale(Vector2(0.5f, 0.5f));
	mGuyDark->SetWrapMode(Animation::WrapModes::Loop);

	mGuyRunning = new AnimatedGLTexture("Character Sprite.png", 0, 2240, 320, 320, 6, 0.5f, Animation::Layouts::Horizontal);
	mGuyRunning->Parent(this);
	mGuyRunning->Position(Vector2(-478.0f, -280.0f));
	mGuyRunning->Scale(Vector2(0.5f, 0.5f));
	mGuyRunning->SetWrapMode(Animation::WrapModes::Loop);

	mGuyRunningDark = new AnimatedGLTexture("Character Sprite.png", 0, 1280, 320, 320, 6, 0.5f, Animation::Layouts::Horizontal);
	mGuyRunningDark->Parent(this);
	mGuyRunningDark->Position(Vector2(mGuyRunning->Position().x, mGuyRunning->Position().y));
	mGuyRunningDark->Scale(Vector2(0.5f, 0.5f));
	mGuyRunningDark->SetWrapMode(Animation::WrapModes::Loop);

	mGuyJumping = new AnimatedGLTexture("Character Sprite.png", 0, 3200, 320, 320, 6, 1.0f, Animation::Layouts::Horizontal);
	mGuyJumping->Parent(this);
	mGuyJumping->Position(Vector2(mGuyRunning->Position().x, mGuyRunning->Position().y));
	mGuyJumping->Scale(Vector2(0.5f, 0.5f));
	mGuyJumping->SetWrapMode(Animation::WrapModes::Once);
	
	mGuyJumpingDark = new AnimatedGLTexture("Character Sprite.png", 0, 2880, 320, 320, 6, 1.0f, Animation::Layouts::Horizontal);
	mGuyJumpingDark->Parent(this);
	mGuyJumpingDark->Position(Vector2(mGuyRunning->Position().x, mGuyRunning->Position().y));
	mGuyJumpingDark->Scale(Vector2(0.5f, 0.5f));
	mGuyJumpingDark->SetWrapMode(Animation::WrapModes::Once);

	mMoveSpeed = 400.0f;
	mMoveBoundsLeft = Vector2(600.0f, 1100.0f);
	mMoveBoundsRight = Vector2(2260.0f, 720.0f);

	mDeathAnimation = new AnimatedGLTexture("PlayerExplosion.png", 0, 0, 128, 128, 4, 1.0f, Animation::Layouts::Horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(Animation::WrapModes::Once);

	mCurrentTexture = mGuy;
	AddCollider(new BoxCollider(mGuy->Position()), mGuy->Scale());

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	Visible(true);
}

Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mGuy;
	mGuy = nullptr;

	delete mDeathAnimation;
	mDeathAnimation = nullptr;

	/*for (auto b : mBullets) {
		delete b;
	}*/
}

void Player::Visible(bool visible) {
	mVisible = visible;
}

bool Player::IsAnimating() {
	return mAnimating;
}

int Player::Score() {
	return mScore;
}

int Player::Lives() {
	return mLives;
}

void Player::AddScore(int change) {
	mScore += change;
}

bool Player::IgnoreCollisions()
{
	return !mVisible || mAnimating;
}

void Player::Hit(PhysEntity* other) {
	mLives -= 1;
	mAnimating = true;
	mDeathAnimation->ResetAnimation();
	mAudio->PlaySFX("SFX/PlayerExplosion.wav");
	mWasHit = true;
}

bool Player::WasHit() {
	return mWasHit;
}

void Player::Update() {
	if (!mIsGrounded) {
		mVelocity.y += mGravity.y * mTimer->DeltaTime();
	}

	Position(Position() + mVelocity);

	std::cout << mVelocity.y << std::endl;

	if (!mMovingLeft && !mMovingRight && mIsGrounded && mIsFacingRight || !mMovingLeft && !mMovingRight && mIsGrounded && mIsFacingLeft) {
		mCurrentTexture = mGuy;
		mCurrentDarkTexture = mGuyDark;
	}
	else if (mMovingRight && mIsGrounded || mMovingLeft && mIsGrounded) {
		mCurrentTexture = mGuyRunning;
		mCurrentDarkTexture = mGuyRunningDark;
	}
	else if (!mIsGrounded && mIsFacingLeft || !mIsGrounded && mIsFacingRight) {
		mCurrentTexture = mGuyJumping;
		mCurrentDarkTexture = mGuyJumpingDark;
	}

	//Check for lNDING ON GROUND

	if (mAnimating) {

		if (mWasHit) {
			mWasHit = false;
		}

		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();
	}
	else {
		if (Active()) {
			if (mIsGrounded) {
				mGuyJumping->ResetAnimation();
				mGuyJumpingDark->ResetAnimation();
			}
			mCurrentTexture->Update();
			mCurrentDarkTexture->Update();


			HandleMovement();
			HandleFiring();
			HandleJumping();

		}
	}

	/*for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Update();
	}*/

	//if (mIsGrounded &&
	//	!CheckCollision(ledge1.x, ledge1.y, ledge1.w, ledge1.h, Position().x - mGuy->ScaledDimensions().x / 2, Position().y - mGuy->ScaledDimensions().y / 2, 160, 160)&& 
	//	!CheckCollision(ground.x, ground.y, ground.w, ground.h, Position().x - mGuy->ScaledDimensions().x / 2, Position().y - mGuy->ScaledDimensions().y / 2, 160, 160)) {
	//	mIsGrounded = false;
	//}
	////ledge 1
	//if (CheckCollision(ledge1.x, ledge1.y, ledge1.w, ledge1.h, Position().x - mGuy->ScaledDimensions().x / 2, Position().y - mGuy->ScaledDimensions().y / 2, 160, 160) && (!mInput->KeyDown(SDL_SCANCODE_SPACE))) {
	//	//Position(Position().x,(ledge1.x) - mGuy->ScaledDimensions().y / 2 + 1);
	//	mIsGrounded = true;
	//	mVelocity.y = 0;
	//}
	////ground
	//if (CheckCollision(ground.x, ground.y, ground.w, ground.h, Position().x - mGuy->ScaledDimensions().x / 2, Position().y - mGuy->ScaledDimensions().y / 2, 160, 160) && (!mInput->KeyDown(SDL_SCANCODE_SPACE))) {
	//	//Position(Position().x,(ledge1.x) - mGuy->ScaledDimensions().y / 2 + 1);
	//	mIsGrounded = true;
	//	mVelocity.y = 0;
	//}
}

void Player::Render() {
	if (mVisible) {
		if (mAnimating) {
			mDeathAnimation->Render();
		}
		else {
			if (mIsFacingRight) {
				mCurrentTexture->Render();
			}
			else {
				mCurrentTexture->RenderFlip();
			}
		}

		
	}

	PhysEntity::Render();
}

void Player::RenderDark() {
	if (mVisible) {
		if (mAnimating) {
			mDeathAnimation->Render();
		}
		else {
			if (mIsFacingRight) {
				mCurrentDarkTexture->Render();
			}
			else {
				mCurrentDarkTexture->RenderFlip();
			}
		}


	}

	PhysEntity::Render();
}

void Player::HandleJumping() {
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE) && (mIsGrounded)) { 
		mAudio->PlaySFX("SFX/Jump.wav", 0);
		mVelocity.y = mJumpPower.y;
		mIsGrounded = false;
	}
}
