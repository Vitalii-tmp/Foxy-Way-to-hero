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

		TextureButton* _wing_item;
		TextureButton* _fur_item;
		TextureButton* _snake_item;

		Label* _label_wing;
		Label* _label_fur;
		Label* _label_spike;
	};
}

