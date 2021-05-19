#include "GameObject/GameObject.hpp"

using namespace App;

GameObject::GameObject(GameEngine& engine)
	: mEngine(engine)
{
}

bool GameObject::alive()const noexcept
{
	return mAlive;
}

void GameObject::kill()noexcept
{
	mAlive = false;
}