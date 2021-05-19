#include "App/MainWindow.hpp"
#include <iostream>

using namespace App;

static constexpr uint32_t SAMPLE_FREQ = 44100;


MainWindow::MainWindow()
{
}

MainWindow::~MainWindow()
{
	// ウィンドウ破棄
	if (mWindow) {
		SDL_DestroyWindow(mWindow);
	}
}
bool MainWindow::initialize()
{
	constexpr int SCREEN_WIDTH = 600;
	constexpr int SCREEN_HEIGHT = 400;

	// ウィンドウ生成
	auto window = SDL_CreateWindow(
		"Sample App",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_OPENGL
	);
	if(!window) {
		std::cerr << "Main : could not create window :" << SDL_GetError();
		return false;
	}
	auto fail_act_destroy = finally([&]{SDL_DestroyWindow(window);});

	// OK
	mWindow = window;
	fail_act_destroy.reset();
	return true;
}
