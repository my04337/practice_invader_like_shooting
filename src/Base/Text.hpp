#pragma once

#include "Base/Base.hpp"

#include <sstream>
#include <iomanip>

#define FORMAT_STRING(...) dynamic_cast<std::ostringstream&>(std::ostringstream() << __VA_ARGS__).str()

namespace App
{
// 文字列描画ユーティリティクラス
class Text 
	: non_copy
{
public:
	static Text make(SDL_Renderer* renderer, TTF_Font* font, const char* textU8, SDL_Color color = SDL_Color{0,0,0,255});

	Text()noexcept;
	~Text();

	Text(Text&&)noexcept;
	Text& operator=(Text&&)noexcept;

	void dispose();

	operator SDL_Texture*()const noexcept { return mTexture; }
	
	int width()const noexcept { return mWidth; }
	int height()const noexcept { return mHeight; }

	SDL_Rect rect(int x, int y) { return {x, y, mWidth, mHeight}; }

private:
	SDL_Texture* mTexture = nullptr;
	int mWidth = 0;
	int mHeight = 0;
};

}