#include "App/MainWindow.hpp"
#include "App/Application.hpp"
#include "GameEngine/GameEngine.hpp"
#include <iostream>

using namespace App;

static constexpr uint32_t SAMPLE_FREQ = 44100;


MainWindow::MainWindow()
{
}

MainWindow::~MainWindow()
{
	// レンダラ破棄
	if (mRenderer) {
		SDL_DestroyRenderer(mRenderer);
	}
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
	auto fail_act_destroy_window = finally([&]{SDL_DestroyWindow(window);});

	// OK
	mWindow = window;
	fail_act_destroy_window.reset();
	return true;
}
void MainWindow::onWindowShown()
{
	// レンダラ生成
	mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
	assert(mRenderer != nullptr);

	// ゲームエンジン生成
	mEngine = std::make_unique<GameEngine>(mRenderer);



	// 定期的コールバックタイマ起動
	SDL_TimerID my_timer_id = SDL_AddTimer(20, [](Uint32 interval, void *param)->Uint32{
		// タイマースレッドからメインスレッドに振替

		void (*cb)(void*) = [](void* this_)
		{ 
			reinterpret_cast<MainWindow*>(this_)->mEngine->update(); 
		};

		SDL_Event event;
		SDL_UserEvent userevent;
		userevent.type = SDL_USEREVENT;
		userevent.code = 0;
		userevent.data1 = (void*)cb;
		userevent.data2 = param;

		event.type = SDL_USEREVENT;
		event.user = userevent;

		SDL_PushEvent(&event);

		return interval;
	}, this);

}
void MainWindow::onWindowHidden()
{
}