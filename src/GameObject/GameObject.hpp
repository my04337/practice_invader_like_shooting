#pragma once

#include "Base/Base.hpp"

namespace App 
{
class GameEngine;

// ゲームオブジェクト 基底クラス
class GameObject : non_copy_move
{
public:
	GameObject(GameEngine& engine);

	virtual ~GameObject() = default;


	// オブジェクトのヒットボックスを取得します。
	virtual SDL_Rect hitBox()const = 0;

	// オブジェクトの状態を更新します
	virtual void update() = 0;

	// オブジェクトを描画します
	virtual void draw() = 0;

	// ---

	// オブジェクトが生存している場合はtrueを, そうで無い場合はfalseを返します
	bool alive()const noexcept;

	// オブジェクトをkillします。 killされたオブジェクトは次のサイクルまでに破棄されます。
	void kill()noexcept;

private:
	GameEngine& mEngine;
	tick_t mCreatedTick;
	bool mAlive = true;
};


}