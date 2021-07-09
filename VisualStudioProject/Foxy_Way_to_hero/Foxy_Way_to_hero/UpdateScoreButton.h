#pragma once
#include "Headers.h"

namespace godot
{
	class UpdateScoreButton : public TextureButton
	{
		GODOT_CLASS(UpdateScoreButton, TextureButton);

	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _process(float delta);

		void _update_speed_player();

	private:
		ResourceLoader* _resource_loader;

		TextureButton* _meat_item;
		TextureButton* _cheese_item;
	};
}

