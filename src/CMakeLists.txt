cmake_minimum_required(VERSION 3.2)

add_executable(
	app WIN32 
	
	main.cpp

	Base/Base.cpp
	Base/Text.cpp
	Base/FontCache.cpp

	App/Application.cpp
	App/MainWindow.cpp
	
	GameEngine/GameEngine.cpp

	GameObject/GameObject.cpp
	GameObject/OwnMachine.cpp
	)
	
	
target_include_directories(
             app
             PRIVATE  .
            )

target_link_libraries(app SDL2main.lib SDL2.lib SDL2_ttf.lib)
add_dependencies(app SDL2_ttf UmeFont)

get_property(APP_BINARY_DIR TARGET app PROPERTY BINARY_DIR )
get_property(APP_SOURCEY_DIR TARGET app PROPERTY SOURCE_DIR )
add_custom_command(TARGET app POST_BUILD
    COMMAND robocopy /NFL /NDL /NJH /NJS /nc /ns /np  "${SDL2_LIB_DIRS}" "${APP_BINARY_DIR}" SDL2.dll 2> NUL & %COMSPEC% /C exit 0
    COMMAND robocopy /NFL /NDL /NJH /NJS /nc /ns /np  "${SDL2_ttf_LIB_DIRS}" "${APP_BINARY_DIR}" SDL2_ttf.dll libfreetype-6.dll zlib1.dll 2> NUL & %COMSPEC% /C exit 0
	COMMAND robocopy /NFL /NDL /NJH /NJS /nc /ns /np  "${UmeFont_ROOT_PATH}" "${APP_BINARY_DIR}/assets/font" license.html ume-tgo4.ttf 2> NUL & %COMSPEC% /C exit 0
)
 