#pragma once

#include "Base/Base.hpp"

namespace App
{
class GameEngine;

class MainWindow final
	: non_copy_move
{
public:
	MainWindow();
	~MainWindow();

	bool initialize();
	void onWindowShown();
	void onWindowHidden();

private:
	SDL_Window* mWindow = nullptr;
	SDL_Renderer* mRenderer = nullptr;

	std::unique_ptr<GameEngine> mEngine;
};

}