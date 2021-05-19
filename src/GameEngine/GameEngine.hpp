#pragma once

#include "Base/Base.hpp"
#include "Base/Text.hpp"
#include "Base/FontCache.hpp"
#include "GameObject/GameObject.hpp"

namespace App 
{
class Application;

// ゲームエンジン
class GameEngine : non_copy_move
{
public:
	GameEngine(SDL_Renderer* renderer);

	// ゲームエリアの幅を取得します
	int width()const noexcept;

	// ゲームエリアの高さを取得します
	int height()const noexcept;


	// 現在のゲーム内tickを取得します
	tick_t tick()const noexcept;

	// フォンとキャッシュを取得します
	FontCache& fontCache()const noexcept;

	// ゲームの出力先レンダラを取得します
	SDL_Renderer* renderer()const noexcept;

	// ゲームを1tick進めます
	void update();


public:
	// 指定領域と交差するオブジェクト一覧を返します
	std::vector<std::shared_ptr<GameObject>> hitTest(const SDL_Rect& rect)const;

private:
	SDL_Renderer* mRenderer;
	SDL_Rect mViewPort;

	tick_t mTick = 0;
	std::list<std::shared_ptr<GameObject>> mObjects;
};


}