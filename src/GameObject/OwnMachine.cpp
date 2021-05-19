#include "GameObject/OwnMachine.hpp"
#include "GameEngine/GameEngine.hpp"

using namespace App;

OwnMachine::OwnMachine(GameEngine& engine)
	: GameObject(engine)
	, mX(300)
	, mY(300)
	, mTexture(Text::make(engine.renderer(), engine.fontCache().get(Size), L"凸"))
{
	
}
SDL_Rect OwnMachine::hitBox()const
{

	SDL_Rect rect{
		mX - Size/2,
		mY - Size/2,
		Size,
		Size,
	};
	return rect;
}
void OwnMachine::update()
{
	// キー移動
	auto keys = SDL_GetKeyboardState(nullptr);

	//TODO 速度や当たり判定周りを整理する
	if(keys[SDL_SCANCODE_LEFT]) {
		mX -= 5;
	}
	if(keys[SDL_SCANCODE_RIGHT]) {
		mX += 5;
	}
}

void OwnMachine::draw()
{
	mTexture.draw(mX - mTexture.width()/2, mY - mTexture.height()/2);
}