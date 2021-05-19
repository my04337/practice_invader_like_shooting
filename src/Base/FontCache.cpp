#include "Base/FontCache.hpp"

using namespace App;


FontCache::FontCache()
	: mFontRWops(nullptr)
{
	auto font_path = std::filesystem::current_path();
	font_path.append("assets/font/ume-tgo4.ttf");

	mFontRWops = SDL_RWFromFile(font_path.string().c_str(), "rb");
	assert(mFontRWops != nullptr);
}
FontCache::~FontCache()
{
	for (auto[size, font] : mFontMap) {
		TTF_CloseFont(font);
	}
	mFontMap.clear();
}

TTF_Font* FontCache::get(int ptsize)
{
	std::lock_guard lock(mMutex);

	auto found = mFontMap.find(ptsize);
	if(found != mFontMap.end()) return found->second;

	auto font = TTF_OpenFontRW(mFontRWops, 0, ptsize);
	assert(font != nullptr);
	mFontMap.emplace(ptsize, font);
	return font;
}
TTF_Font* FontCache::defaultFont()
{
	return get(DEFAULT_FONT_SIZE);
}