#pragma once

#include "Base/Base.hpp"
#include "Base/FontCache.hpp"

namespace App
{
class Application final
	: non_copy_move
{
public:
	static Application& instance();

	int exec(int argc, char** argv);

	FontCache& fontCache()noexcept;

private:
	Application();
	~Application();

	std::unique_ptr<FontCache> mFontCache;
};

}