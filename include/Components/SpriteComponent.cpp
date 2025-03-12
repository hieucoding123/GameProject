#include "ECS/SpriteComponent.h"

SpriteComponent::SpriteComponent()
{
	texture = nullptr;
	srcRect = std::make_unique<SDL_Rect>();
	srcRect->x = 0;
	srcRect->y = 0;
	srcRect->h = 0;
	srcRect->w = 0;

	destRect = nullptr;
	scale = 2;
}

SpriteComponent::SpriteComponent(const char* path, std::unique_ptr<SDL_Rect>& rect)
{
	texture = TextureManager::LoadTexture(path);
	destRect = rect.get();
	srcRect = std::make_unique<SDL_Rect>();
	srcRect->x = 0;
	srcRect->y = 0;
	srcRect->h = 0;
	srcRect->w = 0;

	scale = 2;
}

// *srcRect
SDL_Rect* SpriteComponent::getSrcRect() { return srcRect.get(); }

// đặt tỉ lệ
void SpriteComponent::setScale(int s)
{
	scale = s;
}

void SpriteComponent::setFlip(SDL_RendererFlip f)
{
	spriteFlip = f;
}

SDL_RendererFlip SpriteComponent::getFlip() const
{
	return spriteFlip;
}

int SpriteComponent::getROL() const
{
	return ROL;
}

void SpriteComponent::update()
{
	ROL = ((int)spriteFlip * -2 + 1);

	destRect->w = srcRect->w * scale;
	destRect->h = srcRect->h * scale;
}

void SpriteComponent::draw()
{
	TextureManager::Draw(texture, srcRect.get(), destRect, spriteFlip);
}

SpriteComponent::~SpriteComponent()
{
	SDL_DestroyTexture(texture);
}