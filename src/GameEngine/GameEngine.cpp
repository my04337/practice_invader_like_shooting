#include "GameEngine/GameEngine.hpp"
#include "GameObject/OwnMachine.hpp"
#include "App/Application.hpp"

// デバッグフラグ : ヒットボックスを描画します
#define DEBUG_SHOW_HITBOX

using namespace App;

GameEngine::GameEngine(SDL_Renderer* renderer)
	: mRenderer(renderer)
{
	assert(mRenderer != nullptr);

	SDL_RenderGetViewport(mRenderer, &mViewPort);


	// 自機の配置
	mObjects.emplace_back(std::make_shared<OwnMachine>(*this));
}

SDL_Renderer* GameEngine::renderer()const noexcept
{
	return mRenderer;
}
FontCache& GameEngine::fontCache()const noexcept
{
	return Application::instance().fontCache();
}

int GameEngine::width()const noexcept
{
	return mViewPort.w;
}
int GameEngine::height()const noexcept
{
	return mViewPort.h;
}
tick_t GameEngine::tick()const noexcept
{
	return mTick;
}

void GameEngine::update()
{
	// 画面クリア
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(mRenderer, nullptr);

	// 各オブジェクトの状態を更新
	for(auto iter = mObjects.begin(); iter != mObjects.end(); ++iter) {
		auto& obj = *iter;
		obj->update();
	}

	// 描画
	for(auto iter = mObjects.begin(); iter != mObjects.end(); ++iter) {
		auto& obj = *iter;
		obj->draw();

#ifdef DEBUG_SHOW_HITBOX
		auto hitBox = obj->hitBox();
		SDL_SetRenderDrawColor(mRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(mRenderer, &hitBox);
#endif
	}

	// killされたオブジェクトの廃棄
	for(auto iter = mObjects.begin(); iter != mObjects.end();) {
		auto& obj = *iter;
		if(!obj->alive()) {
			iter = mObjects.erase(iter);
		} else {
			++iter;
		}
	}

	// ディスプレイ更新
	SDL_RenderPresent(mRenderer);

}
std::vector<std::shared_ptr<GameObject>> GameEngine::hitTest(const SDL_Rect& rect)const
{
	// TODO この実装だと検索が非常に遅い。 いずれ高速化する

	std::vector<std::shared_ptr<GameObject>> ret;
	for(auto& obj : mObjects) {
		auto objRect = obj->hitBox();
		if(SDL_HasIntersection(&rect, &objRect)) {
			ret.emplace_back(obj);
		}
	}
	return ret; // NRVO
}