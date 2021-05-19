#pragma once

#include "Base/Base.hpp"

namespace App
{
class FontCache final
	: non_copy_move
{
public:
	static constexpr int DEFAULT_FONT_SIZE = 12;
public:
	FontCache();
	~FontCache();

	TTF_Font* get(int ptsize);

	TTF_Font* defaultFont();

private:
	std::mutex mMutex;
	SDL_RWops* mFontRWops;
	std::unordered_map<int, TTF_Font*> mFontMap;
};

}