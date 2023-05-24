#ifndef __SDLGRAPHICS_H 
#define __SDLGRAPHICS_H 
#include "Graphics.h" 

namespace SDLFramework { 
	class SDLGraphics : public Graphics { 
	public: 
		static SDLGraphics* Instance();

		SDLGraphics(); 
		~SDLGraphics(); 

		virtual void DrawTexture(SDL_Texture* tex, SDL_Rect* srcRect = nullptr, SDL_Rect* dstRect = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE) override; 
	
		virtual void Render() override; 
		virtual void ClearBackBuffer() override; 

	protected: 
		virtual bool Init() override;
	}; 

} 
#endif