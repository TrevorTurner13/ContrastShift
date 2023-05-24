#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

void Player::HandleMovement() {
	if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
		Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
	}
	else if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {
		Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
	}

	Vector2 pos = Position(Local);
	if (pos.x < mMoveBounds.x) {
		pos.x = mMoveBounds.x;
	}
	else if (pos.x > mMoveBounds.y) {
		pos.x = mMoveBounds.y;
	}

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

	mScore = 0;
	mLives = 2;

	mShip = new GLTexture("PlayerShips.png", 0, 0, 60, 64);
	mShip->Parent(this);
	mShip->Position(Vec2_Zero);

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

	delete mShip;
	mShip = nullptr;

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
	if (mAnimating) {

		if (mWasHit) {
			mWasHit = false;
		}

		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();
	}
	else {
		if (Active()) {
			HandleMovement();
			HandleFiring();
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
		else {
			mShip->Render();
		}
	}

	/*for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Render();
	}*/

	PhysEntity::Render();
}