#include "Headers.h"

using namespace godot;

void SplashScreen::_register_methods()
{
	register_method((char*)"_process", &SplashScreen::_process);
	register_method((char*)"_init", &SplashScreen::_init);

}

void SplashScreen::_init() {}

SplashScreen::SplashScreen() {}

SplashScreen::~SplashScreen() {}

void SplashScreen::_process(float delta)
{
	
}