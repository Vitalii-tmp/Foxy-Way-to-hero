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
		str = "HI! You can buy some\n food in my store";
	}
	else {
		str = "Are you hungry? Welcome\n to my store";
	}

	_task_label->set("text", str.c_str());

	if(_is_in_area)
		_buy_items();
}

void godot::Countryman::_ready()
{
	//srand(time(NULL));
	_detection_area = cast_to<Area2D>(get_child(1));
	_detection_area->connect("body_entered", this, "_on_detection_area_entered");
	_detection_area->connect("body_exited", this, "_from_detection_area_exit");

	if (rand() % 3 != 1) _task = ACORNS;
	else _task = COINS;

	_dialog_window = cast_to<TextureRect>(UI::get_singleton()->get_node("DialogCountryMan"));
	
	_task_label = cast_to<Label>(_dialog_window->get_child(0));
	
	_store_menu = cast_to<Sprite>(get_child(2));
}

void godot::Countryman::_on_detection_area_entered(Node* node)
{
	if (node->get_name() == "Player") {
		_dialog_window->set_visible(true);
		_is_in_area = true;
	}
}

void godot::Countryman::_from_detection_area_exit(Node* node)
{
	if (node->get_name() == "Player") {
		_dialog_window->set_visible(false);
		_store_menu->set_visible(false);
		_is_in_area = false;
		//_buy_items();
	}
}

void godot::Countryman::_buy_items()
{
	Input* i = Input::get_singleton();

	if(i->is_action_just_pressed("e_action") && !_store_menu->is_visible())
	{
		_store_menu->set_visible(true);
		/*if(_task == ACORNS && Loader::get_singleton()->get_acorns() >= 30)
		{
			Loader::get_singleton()->set_acorns(-30);
			UI::get_singleton()->change_acorns_information();
		}
		else if(_task == COINS && Loader::get_singleton()->get_coins() >= 150)
		{
			Loader::get_singleton()->set_coins(-150);
			UI::get_singleton()->change_coins_information();
		}
		
		Loader::get_singleton()->save_all_fields();*/

	}
	else if(i->is_action_just_pressed("e_action") && _store_menu->is_visible())
		_store_menu->set_visible(false);
}
