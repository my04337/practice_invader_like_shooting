#include "App/Application.hpp"


int main(int argc, char** argv)
{
	return App::Application::instance().exec(argc, argv);
}