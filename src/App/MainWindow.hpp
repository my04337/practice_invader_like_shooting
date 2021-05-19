#pragma once

#include "Base/Base.hpp"

namespace App
{

class MainWindow final
	: non_copy_move
{
public:
	MainWindow();
	~MainWindow();

	bool initialize();

private:
	SDL_Window* mWindow = nullptr;

};

}