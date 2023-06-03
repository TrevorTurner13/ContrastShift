#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Timer.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "Player.h"
#include "Foreground.h"

class PlayScreen : public GameEntity {
private:
	Timer * mTimer;
	AudioManager * mAudio;
	InputManager* mInput;

	Foreground* mForeground;
	Player * mPlayer;

	bool mIsWhite;

public:
	PlayScreen();
	~PlayScreen();

	bool GetIsWhite() { return mIsWhite; }
	void SetIsWhite(bool shift);

	bool CheckCollision(AnimatedGLTexture* player, GLTexture* object);
	void ResolveCollision(Player* player, GLTexture* object);
	bool VerticallyAligned(AnimatedGLTexture* player, GLTexture* object);
	bool HorizontallyAligned(AnimatedGLTexture* player, GLTexture* object);

	void Update() override;
	void Render() override;
};
#endif