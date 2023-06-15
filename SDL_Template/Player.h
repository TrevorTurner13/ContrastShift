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
	bool mIsPushing;

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
	AnimatedGLTexture* mGuyEnd;

	AnimatedGLTexture* mGuyRunning;
	AnimatedGLTexture* mGuyRunningDark;
	AnimatedGLTexture* mGuyJumpingDark;
	AnimatedGLTexture* mGuyEndDark;

	AnimatedGLTexture* mCurrentTexture;
	AnimatedGLTexture* mCurrentDarkTexture;


	float mMoveSpeed;

	Vector2 mMoveBoundsRight;

private:
	void HandleMovement();
	void HandleJumping();

public:
	Player();
	~Player();

	void Visible(bool visible);
	bool IsAnimating();

	AnimatedGLTexture* GetCurrentTexture() { return mCurrentTexture; }
	AnimatedGLTexture* GetCurrentDarkTexture() { return mCurrentDarkTexture; }
	Vector2 GetLastPosition() { return mLastPosition; }
	bool GetIsGrounded() { return mIsGrounded; }
	bool GetIsJumping() { return mIsJumping; }
	bool GetIsPushing() { return mIsPushing; }

	float GetVelocityY() { return mVelocity.y; }
	float GetVelocityX() { return mVelocity.x; }
	float GetMovespeed() { return mMoveSpeed; }

	void SetIsGrounded(bool isGrounded);
	void SetIsJumping(bool isJumping);
	void SetIsPushing(bool isPushing);

	void SetVelocity(Vector2 velocity);
	void SetMoveSpeed(float moveSpeed);

	void Update() override;
	void Render() override;
	void RenderDark();
};
#endif