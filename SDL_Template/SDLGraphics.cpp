#include "SDLGraphics.h" 

namespace SDLFramework { 
	
	SDLGraphics::SDLGraphics() : Graphics() { 
		sInitialized = Init();
	} 
	
	SDLGraphics::~SDLGraphics() { } 

	SDLGraphics* SDLGraphics::Instance() { 
		if (sInstance == nullptr) { 
			Graphics::Instance(); 
		} 
		return static_cast<SDLGraphics*>(sInstance); 
	}

	void SDLGraphics::DrawTexture(SDL_Texture* tex, SDL_Rect* srcRect, SDL_Rect* dstRect,
		float angle, SDL_RendererFlip flip) {
		SDL_RenderCopyEx(mRenderer, tex, srcRect, dstRect, angle, nullptr, flip);
	} 
	
	void SDLGraphics::Render() { 
		SDL_RenderPresent(mRenderer); 
	} 
	
	void SDLGraphics::ClearBackBuffer() { 
		SDL_RenderClear(mRenderer); 
	} 
	
	bool SDLGraphics::Init() { 
		return Graphics::Init(); 
	}
}