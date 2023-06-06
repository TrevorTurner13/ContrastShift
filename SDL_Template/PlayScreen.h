#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Timer.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "Player.h"
#include "Level1.h"
#include "Level2.h"

class PlayScreen : public GameEntity {
private:
	Timer * mTimer;
	AudioManager * mAudio;
	InputManager* mInput;

	Level1* mLevel1;
	Level2* mLevel2;
	Player * mPlayer;

	Vector2 mMoveBoundsLeft;

	bool mIsWhite;
	
	int level;

public:
	PlayScreen();
	~PlayScreen();

	bool GetIsWhite() { return mIsWhite; }
	void SetIsWhite(bool shift);

	bool CheckCollision(Player* player, GLTexture* object);
	void ResolvePlatformCollision(Player* player, GLTexture* object);
	void ResolveBlockCollision(Player* player, GLTexture* block);
	bool VerticallyAligned(Player* player, GLTexture* object);
	bool HorizontallyAligned(Player* player, GLTexture* object);

	void Update() override;
	void Render() override;

	void level1Update();
	void level2Update();
};
#endif