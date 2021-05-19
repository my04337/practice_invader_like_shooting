#pragma once

#include "Base/Base.hpp"
#include "GameObject/GameObject.hpp"
#include "Base/Text.hpp"

namespace App 
{

// 自機
class OwnMachine : public GameObject
{
public:
	static constexpr int Size = 32;

public:
	OwnMachine(GameEngine& engine);

	// オブジェクトのヒットボックスを取得します。
	SDL_Rect hitBox()const override;

	// オブジェクトの状態を更新します
	void update() override;

	// オブジェクトを描画します
	void draw() override;


private:
	int mX;
	int mY;
	Text mTexture;
};


}