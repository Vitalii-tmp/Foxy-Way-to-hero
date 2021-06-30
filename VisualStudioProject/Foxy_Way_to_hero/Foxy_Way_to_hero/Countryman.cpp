#include "Countryman.h"

void godot::Countryman::_register_methods()
{
	register_method("_process", &Countryman::_process);
	register_method("_ready", &Countryman::_ready);

	register_method("_on_detection_area_entered", &Countryman::_on_detection_area_entered);
	register_method("_from_detection_area_exit", &Countryman::_from_detection_area_exit);
}

void godot::Countryman::_init()
{
}

void godot::Countryman::_process(float delta)
{
	std::string str;
	if (_task == ACORNS) {
		str = std::to_string(Loader::get_singleton()->get_acorns()) + "/30 acorns\n to buy wheat";
	}
	else {
		str = std::to_string(Loader::get_singleton()->get_coins()) + "/150 coins\n to buy carrot";
	}

	_task_label->set("text", str.c_str());

	_buy_items();
}

void godot::Countryman::_ready()
{
	srand(time(NULL));
	_detection_area = cast_to<Area2D>(get_child(1));
	_detection_area->connect("body_entered", this, "_on_detection_area_entered");
	_detection_area->connect("body_exited", this, "_from_detection_area_exit");

	if (rand() % 3 != 1) _task = ACORNS;
	else _task = COINS;

	_dialog_window = cast_to<Sprite>(get_child(2));
	
	_task_label = cast_to<Label>(_dialog_window->get_child(0));
	

}

void godot::Countryman::_on_detection_area_entered(Node* node)
{
	if(node->get_name() == "Player")
		_dialog_window->set_visible(true);
}

void godot::Countryman::_from_detection_area_exit(Node* node)
{
	if (node->get_name() == "Player")
		_dialog_window->set_visible(false);
}

void godot::Countryman::_buy_items()
{
	Input* i = Input::get_singleton();

	if(i->is_action_pressed("e_action"))
	{
		if(_task == ACORNS && Loader::get_singleton()->get_acorns() >= 30)
		{
			Loader::get_singleton()->set_acorns(-30);
			UI::get_singleton()->change_acorns_information();
		}
		else if(_task == COINS && Loader::get_singleton()->get_coins() >= 150)
		{
			Loader::get_singleton()->set_coins(-150);
			UI::get_singleton()->change_coins_information();
		}
		
		Loader::get_singleton()->save_all_fields();

	}
}
