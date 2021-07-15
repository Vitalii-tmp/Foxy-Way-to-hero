#pragma once
#include "Headers.h"

namespace godot
{

	class Preloader :public Control
	{

		GODOT_CLASS(Preloader, Control)


	public:

		static void _register_methods();
		void _init();
		void _ready();
		void _process(float delta);

		void _on_video_player_finished();

	private:

		ResourceLoader* _resource_loader = nullptr;
	};

}

