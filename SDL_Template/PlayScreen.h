#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Timer.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "Player.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "LevelEnd.h"

class PlayScreen : public GameEntity {
private:
	Timer * mTimer;
	AudioManager * mAudio;
	InputManager* mInput;

	bool mEnding;

	Level1* mLevel1;
	Level2* mLevel2;
	Level3* mLevel3;
	LevelEnd* mLevelEnd;

	AnimatedGLTexture* mFade;
	GLTexture* mFade1;

	Player * mPlayer;

	Vector2 mMoveBoundsLeft;

	bool mIsWhite;
	
	int level;

public:
	PlayScreen();
	~PlayScreen();

	bool GetIsWhite() { return mIsWhite; }
	void SetIsWhite(bool shift);
	// player/object collision
	bool CheckCollision(Player* player, GLTexture* object);
	void ResolvePlatformCollision(Player* player, GLTexture* object);
	void ResolvePushCollision(Player* player, GLTexture* block);
	bool VerticallyAligned(Player* player, GLTexture* object);
	bool HorizontallyAligned(Player* player, GLTexture* object);

	// object/object collision
	bool CheckBlockCollision(GLTexture* block1, GLTexture* block2);
	void ResolveBlockCollision(GLTexture* block1, GLTexture* block2);
	bool VerticallyAlignedBlocks(GLTexture* object1, GLTexture* object2);

	void Update() override;
	void Render() override;

	void Level1Update();
	void Level2Update();
	void Level3Update();
	void LevelEndUpdate();
};
#endif