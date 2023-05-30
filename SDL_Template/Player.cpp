#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"


void Player::HandleMovement() {
	if (mInput->KeyDown(SDL_SCANCODE_D)) {
		Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
		mMovingLeft = false;
		mMovingRight = true;
	}
	else if (mInput->KeyDown(SDL_SCANCODE_A)) {
		Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
		mMovingLeft = true; 
		mMovingRight = false;
	}
	else {
		mMovingLeft = false;
		mMovingRight = false;
	}
	if (mInput->KeyPressed(SDL_SCANCODE_LSHIFT)) {
		if (mIsWhite == true) {
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			mIsWhite = false;
		}
		else {
			glClearColor(250.0f, 250.0f, 250.0f, 1.0f);
			mIsWhite = true;
		}

	}

	Vector2 pos = Position(Local);
	/*if (pos.x < mMoveBounds.x) {
		pos.x = mMoveBounds.x;
	}
	else if (pos.x > mMoveBounds.y) {
		pos.x = mMoveBounds.y;
	}*/

	Position(pos);
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
	mMovingLeft = false;
	mIsJumping = false;
	mIsWhite = false;
	mIsGrounded = true;
	mGravity = Vector2(0.0, 20);
	mJumpPower = Vector2(0.0, -6);

	mScore = 0;
	mLives = 2;

	mGuy = new AnimatedGLTexture("Character Sprite.png", 0, 2560, 320, 320, 6, 1.0f, Animation::Layouts::Horizontal);
	mGuy->Parent(this);
	mGuy->Position(-478.0f, -268.0f);
	mGuy->Scale(Vector2(0.5f, 0.5f));
	mGuy->SetWrapMode(Animation::WrapModes::Loop);

	mGuyRunning = new AnimatedGLTexture("Character Sprite.png", 0, 2240, 320, 310, 6, 0.5f, Animation::Layouts::Horizontal);
	mGuyRunning->Parent(this);
	mGuyRunning->Position(Vector2(-478.0f, -280.0f));
	mGuyRunning->Scale(Vector2(0.5f, 0.5f));
	mGuyRunning->SetWrapMode(Animation::WrapModes::Loop);

	mMoveSpeed = 300.0f;
	mMoveBounds = Vector2(0.0f, 800.0f);

	mDeathAnimation = new AnimatedGLTexture("PlayerExplosion.png", 0, 0, 128, 128, 4, 1.0f, Animation::Layouts::Horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(Animation::WrapModes::Once);

	/*for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i] = new Bullet(true);
	}*/

	AddCollider(new BoxCollider(Vector2(16.0f, 67.0f)));
	AddCollider(new BoxCollider(Vector2(20.0f, 37.0f)), Vector2(18.0f, 10.0f));
	AddCollider(new BoxCollider(Vector2(20.0f, 37.0f)), Vector2(-18.0f, 10.0f));

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
			if (!mMovingLeft && !mMovingRight) {
				mGuy->Update();
			}
			else if (mMovingRight) {
				mGuyRunning->Update();
			}
			else if (mMovingLeft) {
				mGuyRunning->Update();
			}
			HandleMovement();
			HandleFiring();
			HandleJumping();

		}
	}

	/*for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Update();
	}*/
}

void Player::Render() {
	if (mVisible) {
		if (mAnimating) {
			mDeathAnimation->Render();
		}
		else if (!mMovingLeft && !mMovingRight) {
			mGuy->Render();
		}
		else if (mMovingRight) {
			mGuyRunning->Render();
		}
		else if (mMovingLeft) {
			mGuyRunning->RenderFlip();

		}
	}

	/*for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Render();
	}*/

	PhysEntity::Render();
}

void Player::HandleJumping() {
	if (mInput->KeyDown(SDL_SCANCODE_SPACE)) {
		mVelocity.y = mJumpPower.y;
		mIsGrounded = false;
	}
}
