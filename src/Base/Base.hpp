#pragma once

// --- 基本的なヘッダ類 ---
#include <cassert>
#include <string>
#include <string_view>
#include <list>
#include <vector>
#include <tuple>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <any>
#include <variant>
#include <optional>
#include <chrono>
#include <limits>
#include <memory>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <memory_resource>
#include <algorithm>
#include <functional>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <filesystem>

#include <SDL.h>
#include <SDL_ttf.h>

// C++17 関連パッチ
#if _MSC_VER <= 1913 // 少なくともVisual Studio 2017 Update6以前はstd::filesystemは実験的実装
namespace std::filesystem {
	using namespace std::experimental::filesystem;
}
#endif

// --- 基本的なマクロ類 ---
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN 
#define STRICT 
#define NOMINMAX 
#endif

// マクロ展開遅延
#define DELAY_MACRO(...)  DELAY_MACRO_(__VA_ARGS__)
#define DELAY_MACRO_(...) __VA_ARGS__

// --- 基本的な型 ---
namespace App
{
// クロック類
using clock = std::chrono::steady_clock;

// tick : ゲーム内時間を示す。通常、tick=フレーム
using tick_t = std::uint64_t;

/// コピー禁止,ムーブ可能型
struct non_copy {
	constexpr non_copy() = default;
	non_copy(const non_copy&) = delete;
	non_copy(non_copy&&)noexcept = default;
	non_copy& operator=(const non_copy&) = delete;
	non_copy& operator=(non_copy&&)noexcept = default;
};

/// コピー,ムーブ禁止型
struct non_copy_move {
	constexpr non_copy_move() = default;
	non_copy_move(const non_copy_move&) = delete;
	non_copy_move(non_copy_move&&)noexcept = delete;
	non_copy_move& operator=(const non_copy_move&) = delete;
	non_copy_move& operator=(non_copy_move&&)noexcept = delete;
};

// テンプレート補助 : どのような値を受け取ってもfalseを表す値
template<typename ...>
constexpr bool false_v = false;

/// スコープ離脱時実行コード 補助クラス
template<typename F>
class [[nodiscard]] _finally_action
	: non_copy
{
public:
	_finally_action() : f(), valid(false) {}
	_finally_action(F f) : f(std::move(f)), valid(true) {}
	~_finally_action() { action(); }

	_finally_action(_finally_action&& d)noexcept : f(std::move(d.f)), valid(true) { d.valid=false; };
	_finally_action& operator=(_finally_action&& d)noexcept { reset(); f = std::move(d.f); valid=d.valid; d.valid=false; return *this;}

	void action()noexcept { if(valid) f(); reset(); }
	void reset()noexcept { valid = false; }

private:
	F f;
	bool valid;
};

/// スコープ離脱時実行コード 定義関数
template<typename F>
_finally_action<F> finally(F&& f) { return {std::forward<F>(f)}; }

/// 型名をデマングルした文字列に変換します
std::string demangle(const std::type_info& type);
std::string demangle(const std::type_index& type);
std::string demangle(const char* mangled_name);

// ファイルマクロ用 ファイル名
constexpr std::string_view file_macro_to_filename(const char* filepath)
{
	std::string_view path(filepath);
	auto sep = path.find_last_of("\\/");
	if (sep != std::string_view::npos) {
		return path.substr(sep+1);
	}else {
		return path;
	}
}

// std::pmr_memory_holder メモリ管理簡単化機構
template<class T>
class _memory_resource_deleter final
{
public:
	_memory_resource_deleter()
		: _mem(nullptr), _size(0), _align(0)
	{}
	_memory_resource_deleter(std::pmr::memory_resource* mem, size_t size, size_t align)
		: _mem(mem), _size(size), _align(align)
	{}

	void operator()(T* data) {
		if(data) _mem->deallocate(data, _size, _align);
	}

private:
	std::pmr::memory_resource* _mem;
	size_t _size;
	size_t _align;
};

template<class T>
std::unique_ptr<T[], _memory_resource_deleter<T>> 
allocate_memory(std::pmr::memory_resource* mem, size_t length, size_t align = alignof(T)) 
{
	size_t size = length * sizeof(T);
	auto data = reinterpret_cast<T*>(mem->allocate(size, align));
	return std::unique_ptr<T[], _memory_resource_deleter<T>>(data, _memory_resource_deleter<T>(mem, size, align));
}
}
