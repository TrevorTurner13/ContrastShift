#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

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
}

void Player::SetIsGrounded(bool isGrounded) {
	mIsGrounded = isGrounded;
}

void Player::SetIsJumping(bool isJumping) {
	mIsJumping = isJumping;
}

void Player::SetIsPushing(bool isPushing) {
	mIsPushing = isPushing;
}

void Player::SetVelocity(Vector2 velocity) {
	mVelocity = velocity;
}

void Player::SetMoveSpeed(float moveSpeed) {
	mMoveSpeed = moveSpeed;
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
	mIsPushing = false;

	mGravity = Vector2(0.0, 25);
	mJumpPower = Vector2(0.0, -16);

	mMoveSpeed = 400.0f;
	mMoveBoundsRight = Vector2(2260.0f, 720.0f);


	mScore = 0;
	mLives = 2;

	mGuy = new AnimatedGLTexture("Character Sprite.png", 0, 2560, 320, 320, 6, 1.0f, Animation::Layouts::Horizontal);
	mGuy->Parent(this);
	mGuy->Position(Vec2_Zero);
	mGuy->Scale(Vector2(0.5f, 0.5f));
	mGuy->SetWrapMode(Animation::WrapModes::Loop);

	mGuyDark = new AnimatedGLTexture("Character Sprite.png", 0, 640, 320, 320, 6, 1.0f, Animation::Layouts::Horizontal);
	mGuyDark->Parent(this);
	mGuyDark->Position(Vec2_Zero);
	mGuyDark->Scale(Vector2(0.5f, 0.5f));
	mGuyDark->SetWrapMode(Animation::WrapModes::Loop);

	mGuyRunning = new AnimatedGLTexture("Character Sprite.png", 0, 2240, 320, 320, 6, 0.5f, Animation::Layouts::Horizontal);
	mGuyRunning->Parent(this);
	mGuyRunning->Position(Vec2_Zero);
	mGuyRunning->Scale(Vector2(0.5f, 0.5f));
	mGuyRunning->SetWrapMode(Animation::WrapModes::Loop);

	mGuyRunningDark = new AnimatedGLTexture("Character Sprite.png", 0, 1280, 320, 320, 6, 0.5f, Animation::Layouts::Horizontal);
	mGuyRunningDark->Parent(this);
	mGuyRunningDark->Position(Vec2_Zero);
	mGuyRunningDark->Scale(Vector2(0.5f, 0.5f));
	mGuyRunningDark->SetWrapMode(Animation::WrapModes::Loop);

	mGuyJumping = new AnimatedGLTexture("Character Sprite.png", 0, 3200, 320, 320, 6, 1.0f, Animation::Layouts::Horizontal);
	mGuyJumping->Parent(this);
	mGuyJumping->Position(Vec2_Zero);
	mGuyJumping->Scale(Vector2(0.5f, 0.5f));
	mGuyJumping->SetWrapMode(Animation::WrapModes::Once);

	mGuyEnd = new AnimatedGLTexture("Character Sprite.png", 0, 2560, 320, 320, 6, 1.0f, Animation::Layouts::Horizontal);
	mGuyEnd->Parent(this);
	mGuyEnd->Position(Vec2_Zero);
	mGuyEnd->Scale(Vector2(0.5f, 0.5f));
	mGuyEnd->SetWrapMode(Animation::WrapModes::Loop);

	mGuyEndDark = new AnimatedGLTexture("Character Sprite.png", 0, 640, 320, 320, 6, 1.0f, Animation::Layouts::Horizontal);
	mGuyEndDark->Parent(this);
	mGuyEndDark->Position(Vec2_Zero);
	mGuyEndDark->Scale(Vector2(0.5f, 0.5f));
	mGuyEndDark->SetWrapMode(Animation::WrapModes::Loop);
	
	mGuyJumpingDark = new AnimatedGLTexture("Character Sprite.png", 0, 2880, 320, 320, 6, 1.0f, Animation::Layouts::Horizontal);
	mGuyJumpingDark->Parent(this);
	mGuyJumpingDark->Position(Vec2_Zero);
	mGuyJumpingDark->Scale(Vector2(0.5f, 0.5f));
	mGuyJumpingDark->SetWrapMode(Animation::WrapModes::Once);

	mCurrentTexture = mGuy;

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	Visible(true);
}

Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mGuy;
	mGuy = nullptr;

	delete mGuyDark;
	mGuyDark = nullptr;

	delete mGuyJumping;
	mGuyJumping = nullptr;

	delete mGuyEnd;
	mGuyEnd = nullptr;

	delete mGuyRunning;
	mGuyRunning = nullptr;

	delete mGuyRunningDark;
	mGuyRunningDark = nullptr;

	delete mGuyJumpingDark;
	mGuyJumpingDark = nullptr;

	delete mGuyEndDark;
	mGuyEndDark = nullptr;

	delete mCurrentTexture;
	mCurrentTexture = nullptr;

	delete mCurrentDarkTexture;
	mCurrentDarkTexture = nullptr;
}

void Player::Visible(bool visible) {
	mVisible = visible;
}

bool Player::IsAnimating() {
	return mAnimating;
}

void Player::Update() 
{
	mLastPosition = Vector2(Position().x, Position().y);

	if (mIsPushing) {
		mMoveSpeed = 100.0f; 
	}
	else {
		mMoveSpeed = 400.0f;
	}

	if (!mIsGrounded) {
		mVelocity.y += mGravity.y * mTimer->DeltaTime();
	}

	Position(Position() + mVelocity);

	//std::cout << mVelocity.y << std::endl;
	if (Active()) {
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
	}
	else {
		mCurrentTexture = mGuyEnd;
		mCurrentDarkTexture = mGuyEndDark;
	}

	//Check for lNDING ON GROUND

	if (!mAnimating) {
		if (Active()) {
			if (mIsGrounded) {
				mGuyJumping->ResetAnimation();
				mGuyJumpingDark->ResetAnimation();
				mIsJumping = false;
			}
			mCurrentTexture->Update();
			mCurrentDarkTexture->Update();

			HandleMovement();
			HandleJumping();
		}
		else {
			mCurrentTexture->Update();
			mCurrentDarkTexture->Update();
		}
	}
}

void Player::Render() {
	if (mVisible) {
		if (!mAnimating) {
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
		if (!mAnimating) {
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
		mIsJumping = true;
	}
}
