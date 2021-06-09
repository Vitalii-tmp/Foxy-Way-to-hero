#pragma once
#include "Headers.h"


namespace godot
{
	class UI:public CanvasLayer
	{
	private:
		GODOT_CLASS(UI, CanvasLayer);

	public:
		static void _register_methods();
		void _init();

		void _ready();
		void _process(float delta);

		static UI* get_singleton();

		void change_coins_information();

		std::string get_coins_information();
	private:
		static inline UI* _instance;
	};
}


