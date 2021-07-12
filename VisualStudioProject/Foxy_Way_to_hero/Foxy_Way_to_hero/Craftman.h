#pragma once
#include "Headers.h"

namespace godot
{
	
	class Craftman : public Node2D
	{
		GODOT_CLASS(Craftman, Node2D);

	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _process(float delta);

		void _on_detection_area_entered(Node* node);
		void _from_detection_area_exit(Node* node);

		void _craft();

	private:
		Area2D* _detection_area = nullptr;
		Sprite* _recipe_menu = nullptr;
		TextureRect* _dialog_window = nullptr;

		bool _is_in_area = false;

	};
}

