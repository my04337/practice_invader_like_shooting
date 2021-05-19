﻿#include "Base/Text.hpp"


using namespace App;

Text::Text()noexcept
{
}
Text::Text(Text&& d)noexcept
{
	*this = std::move(d);
}
Text& Text::operator=(Text&& d)noexcept
{
	if(&d == this) return *this;

	dispose();
	mTexture = d.mTexture;
	mWidth = d.mWidth;
	mHeight = d.mHeight;
	d.mTexture = nullptr;
	d.mWidth = 0;
	d.mHeight = 0;
	return *this;
}
Text::~Text()
{
	dispose();
}

Text Text::make(SDL_Renderer* renderer, TTF_Font* font, const char* textU8, SDL_Color color)
{
	assert(renderer != nullptr);
	assert(font != nullptr);
	
	auto surface = TTF_RenderUTF8_Blended(font, textU8, color);
	if(!surface) return {};
	auto fin_act_free_surface = finally([&]{SDL_FreeSurface(surface);});

	Text text;
	text.mTexture = SDL_CreateTextureFromSurface(renderer, surface);
	text.mWidth = surface->w;
	text.mHeight = surface->h;
	return text; // NRVO
}
void Text::dispose()
{
	if (mTexture) {
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
	}
}