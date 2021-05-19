#include "App/Application.hpp"
#include "App/MainWindow.hpp"
#include <iostream>

using namespace App;

Application::Application()
{
	// SDL 初期化
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cerr << "Main : could not initialize SDL :" << SDL_GetError();
		std::abort();
	}
	if (TTF_Init() < 0) {
		std::cerr << "Main : could not initialize SDL_ttf :" << TTF_GetError();
		std::abort();
	}

	// 各種サービス初期化
	mFontCache = std::make_unique<FontCache>();
}
Application::~Application()
{
	mFontCache.reset();
	TTF_Quit();
	SDL_Quit();
}

Application& Application::instance()
{
	static Application app;
	return app;
}

int Application::exec(int argc, char** argv)
{

	// ウィンドウ生成
	App::MainWindow main_window;
	if (!main_window.initialize()) {
		return 1;
	}

	// メッセージループ 開始
	bool done = false;
	SDL_Event ev;
	while (!done && SDL_WaitEvent(&ev))
	{
		switch (ev.type) {
		case SDL_QUIT:
			done = true;
			break;
		}
	}
	return 0;
}

FontCache& Application::fontCache()noexcept
{
	assert(mFontCache != nullptr);
	return *mFontCache;
}