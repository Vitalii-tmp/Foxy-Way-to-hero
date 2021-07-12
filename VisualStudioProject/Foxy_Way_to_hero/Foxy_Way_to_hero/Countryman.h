#pragma once
#include "Headers.h"

namespace godot
{
	enum task
	{
		ACORNS,
		COINS
	};
	
	class Countryman : public Node2D
	{
		GODOT_CLASS(Countryman, Node2D);
	public:
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();

		void _on_detection_area_entered(Node* node);
		void _from_detection_area_exit(Node* node);

		void _buy_items();
	private:

		Area2D* _detection_area = nullptr;
		TextureRect* _dialog_window = nullptr;
		Sprite* _store_menu = nullptr;
		Label* _task_label = nullptr;

		task _task;
		bool _is_in_area = false;
	};
}

