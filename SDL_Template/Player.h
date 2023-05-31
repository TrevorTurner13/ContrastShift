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
	bool mMovingLeft;
	bool mIsJumping;
	bool mIsWhite;
	bool mIsGrounded;

	//mAcceleration;
	Vector2 mVelocity;
	Vector2 mGravity;
	Vector2 mJumpPower;

	int mScore;
	int mLives;

	AnimatedGLTexture* mGuy;
	AnimatedGLTexture* mGuyDark;

	AnimatedGLTexture* mGuyRunning;
	AnimatedGLTexture* mGuyRunningDark;

	AnimatedGLTexture* mDeathAnimation;

	float mMoveSpeed;
	Vector2 mMoveBounds;

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

	bool CheckCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);

	void Update() override;
	void Render() override;
	void RenderDark();
};
#endif