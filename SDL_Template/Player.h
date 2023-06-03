#ifndef __PLAYER_H
#define __PLAYER_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "Bullet.h"

using namespace SDLFramework;

class Player : public PhysEntity {
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;
	bool mWasHit;
	bool mMovingRight;
	bool mIsFacingRight;
	bool mMovingLeft;
	bool mIsFacingLeft;
	bool mIsJumping;
	bool mIsWhite;
	bool mIsGrounded;

	//mAcceleration;
	Vector2 mVelocity;
	Vector2 mGravity;
	Vector2 mJumpPower;
	Vector2 mLastPosition;

	int mScore;
	int mLives;

	AnimatedGLTexture* mGuy;
	AnimatedGLTexture* mGuyDark;
	AnimatedGLTexture* mGuyJumping;

	AnimatedGLTexture* mGuyRunning;
	AnimatedGLTexture* mGuyRunningDark;
	AnimatedGLTexture* mGuyJumpingDark;

	AnimatedGLTexture* mCurrentTexture;
	AnimatedGLTexture* mCurrentDarkTexture;

	AnimatedGLTexture* mDeathAnimation;

	float mMoveSpeed;
	Vector2 mMoveBoundsLeft;
	Vector2 mMoveBoundsRight;

	static const int MAX_BULLETS = 2;
	//Bullet* mBullets[MAX_BULLETS];

private:
	void HandleMovement();
	void HandleFiring();
	void HandleJumping();

public:
	Player();
	~Player();

	void Visible(bool visible);
	bool IsAnimating();

	int Score();
	int Lives();

	void AddScore(int change);

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;
	void Hit(PhysEntity* other) override;

	bool WasHit();

	AnimatedGLTexture* GetCurrentTexture() { return mCurrentTexture; }
	AnimatedGLTexture* GetCurrentDarkTexture() { return mCurrentDarkTexture; }
	Vector2 GetLastPosition() { return mLastPosition; }
	bool GetIsGrounded() { return mIsGrounded; }
	bool GetIsJumping() { return mIsJumping; }
	bool GetVelocity();

	void SetIsGrounded(bool isGrounded);
	void SetIsJumping(bool isJumping);
	void SetVelocity(Vector2 velocity);
	void SetMoveSpeed(float moveSpeed);

	void Update() override;
	void Render() override;
	void RenderDark();
};
#endif