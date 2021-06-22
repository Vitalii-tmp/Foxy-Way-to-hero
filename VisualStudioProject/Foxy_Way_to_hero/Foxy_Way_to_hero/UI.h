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

		void change_coins_information() const;
		void change_acorns_information() const;

		std::string get_coins_information() const;
		std::string get_acorns_information() const;
	private:
		static inline UI* _instance;
	};
}


