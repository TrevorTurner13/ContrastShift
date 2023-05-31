#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Rect ledge1(400.0f, 945.0f, 520.0f, 45.5f);
Rect ledge2(1500.0f, 550.0f, 440.0f, 38.5f);
Rect block1(265.0f, 793.0f, 321.1f, 214.5f);

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
	mGuy->Position(-478.0f, -275.0f);
	mGuy->Scale(Vector2(0.5f, 0.5f));
	mGuy->SetWrapMode(Animation::WrapModes::Loop);

	mGuyDark = new AnimatedGLTexture("Character Sprite.png", 0, 640, 320, 320, 6, 1.0f, Animation::Layouts::Horizontal);
	mGuyDark->Parent(this);
	mGuyDark->Position(mGuy->Position().x, mGuy->Position().y);
	mGuyDark->Scale(Vector2(0.5f, 0.5f));
	mGuyDark->SetWrapMode(Animation::WrapModes::Loop);

	mGuyRunning = new AnimatedGLTexture("Character Sprite.png", 0, 2240, 320, 310, 6, 0.5f, Animation::Layouts::Horizontal);
	mGuyRunning->Parent(this);
	mGuyRunning->Position(Vector2(-478.0f, -280.0f));
	mGuyRunning->Scale(Vector2(0.5f, 0.5f));
	mGuyRunning->SetWrapMode(Animation::WrapModes::Loop);

	mGuyRunningDark = new AnimatedGLTexture("Character Sprite.png", 0, 1280, 320, 310, 6, 0.5f, Animation::Layouts::Horizontal);
	mGuyRunningDark->Parent(this);
	mGuyRunningDark->Position(Vector2(mGuyRunning->Position().x, mGuyRunning->Position().y));
	mGuyRunningDark->Scale(Vector2(0.5f, 0.5f));
	mGuyRunningDark->SetWrapMode(Animation::WrapModes::Loop);
	
	mGuyJumpingDark = new AnimatedGLTexture("Character Sprite.png", 0, 2880, 320, 310, 6, 2.0f, Animation::Layouts::Horizontal);
	mGuyJumpingDark->Parent(this);
	mGuyJumpingDark->Position(Vector2(mGuyRunning->Position().x, mGuyRunning->Position().y));
	mGuyJumpingDark->Scale(Vector2(0.5f, 0.5f));
	mGuyJumpingDark->SetWrapMode(Animation::WrapModes::Loop);

	mMoveSpeed = 300.0f;
	mMoveBounds = Vector2(0.0f, 800.0f);

	mDeathAnimation = new AnimatedGLTexture("PlayerExplosion.png", 0, 0, 128, 128, 4, 1.0f, Animation::Layouts::Horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(Animation::WrapModes::Once);

	/*for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i] = new Bullet(true);
	}*/

	//AddCollider(new BoxCollider(Vector2(16.0f, 67.0f)));
	//AddCollider(new BoxCollider(Vector2(20.0f, 37.0f)), Vector2(18.0f, 10.0f));
	//AddCollider(new BoxCollider(Vector2(20.0f, 37.0f)), Vector2(-18.0f, 10.0f));
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
			if (!mMovingLeft && !mMovingRight && mIsGrounded) {
				mGuy->Update();
				mGuyDark->Update();
			}
			else if (mMovingRight) {
				mGuyRunning->Update();
				mGuyRunningDark->Update();
			}
			else if (mMovingLeft) {
				mGuyRunning->Update();
				mGuyRunningDark->Update();
			}
			

			HandleMovement();   
			HandleFiring();
			HandleJumping();

		}
	}

	/*for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Update();
	}*/
	
	if (mIsGrounded &&
		!CheckCollision(ledge1.x, ledge1.y, ledge1.w, ledge1.h, Position().x - mGuy->ScaledDimensions().x / 2, Position().y - mGuy->ScaledDimensions().y / 2, 160, 160)) {
		mIsGrounded = false;
	}
	//ledge 1
	if (CheckCollision(ledge1.x, ledge1.y, ledge1.w, ledge1.h, Position().x - mGuy->ScaledDimensions().x / 2, Position().y - mGuy->ScaledDimensions().y / 2, 160, 160) && (!mInput->KeyDown(SDL_SCANCODE_SPACE))) {
		//Position(Position().x,(ledge1.x) - mGuy->ScaledDimensions().y / 2 + 1);
		mIsGrounded = true;
		mVelocity.y = 0;
	}
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

void Player::RenderDark() {
	if (mVisible) {
		if (mAnimating) {
			mDeathAnimation->Render();
		}
		else if (!mMovingLeft && !mMovingRight) {
			mGuyDark->Render();
		}
		else if (mMovingRight) {
			mGuyRunningDark->Render();
		}
		else if (mMovingLeft) {
			mGuyRunningDark->RenderFlip();

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
bool Player::CheckCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
	float obj1_left = x1;
	float obj1_right = x1 + w1;
	float obj1_top = y1;
	float obj1_bottom = y1 + h1;



	float obj2_left = x2;
	float obj2_right = x2 + w2;
	float obj2_top = y2;
	float obj2_bottom = y2 + h2;
	return obj1_right > obj2_left && obj1_left < obj2_right&& obj1_bottom > obj2_top && obj1_top < obj2_bottom;
}