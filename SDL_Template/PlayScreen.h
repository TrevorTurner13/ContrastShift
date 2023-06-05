#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Timer.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "Player.h"
#include "Level1.h"

class PlayScreen : public GameEntity {
private:
	Timer * mTimer;
	AudioManager * mAudio;
	InputManager* mInput;

	Level1* mLevel1;
	Player * mPlayer;

	bool mIsWhite;
	
	int level;

public:
	PlayScreen();
	~PlayScreen();

	bool GetIsWhite() { return mIsWhite; }
	void SetIsWhite(bool shift);

	bool CheckCollision(Player* player, GLTexture* object);
	void ResolveCollision(Player* player, GLTexture* object);
	bool VerticallyAligned(Player* player, GLTexture* object);
	bool HorizontallyAligned(Player* player, GLTexture* object);

	void Update() override;
	void Render() override;

	void level1Update();
};
#endif