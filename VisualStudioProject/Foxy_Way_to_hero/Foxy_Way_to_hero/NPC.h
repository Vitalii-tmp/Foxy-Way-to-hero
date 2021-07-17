#pragma once
#include "Headers.h"

namespace godot {
	enum task;
	
	class NPC : public Node2D
	{
		GODOT_CLASS(NPC, Node2D);

	public:
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();

		void _on_detection_area_entered(Node* node);
		void _from_detection_area_exit(Node* node);

		void _progress_check();

	private:
		task _task;

		bool _is_in_area = false;

		int _count_of_boars = 0;
		int _count_of_acorns = 0;

		Area2D* _detection_area = nullptr;
		TextureRect* _dialog_window = nullptr;
		TextureRect* _progress_menu = nullptr;
		TextureRect* _result_menu = nullptr;
		TextureRect* _question_window = nullptr;
		Label* _task_label = nullptr;
		Label* _progress_label = nullptr;
		TextureButton* _yes_button = nullptr;
		TextureButton* _no_button = nullptr;

		ResourceLoader* _resource_loader;
	};
}
