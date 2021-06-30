#pragma once
#include "Headers.h"

namespace godot
{
	class Countryman : public Node2D
	{
		GODOT_CLASS(Countryman, Node2D);
	public:
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();

		void _on_detection_area_entered(Node* node);
		
	private:

		Area2D* _detection_area = nullptr;
		Sprite* _dialog_window = nullptr;
		Label* _task = nullptr;
	};
}

