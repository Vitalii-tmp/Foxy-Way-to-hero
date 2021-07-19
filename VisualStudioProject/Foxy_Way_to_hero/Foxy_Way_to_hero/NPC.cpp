#include "NPC.h"

void godot::NPC::_register_methods()
{
	register_method("_process", &NPC::_process);
	register_method("_ready", &NPC::_ready);
	register_method("_on_detection_area_entered", &NPC::_on_detection_area_entered);
	register_method("_from_detection_area_exit", &NPC::_from_detection_area_exit);
}

void godot::NPC::_init()
{
}

void godot::NPC::_process(float delta)
{
	String progress_str;

	_count_of_boars = Player::_get_singleton()->_get_killed_boars();

	if (_task == HUNTER)
		progress_str = String::num(_count_of_boars) + "/5 boars to\n get a prize";
	else if (_task == ACORNS)
		progress_str = "";

	_progress_label->set_text(progress_str);

	if (_is_in_area)
	{
		_progress_check();
		/*if (GameManager::_get_singleton()->_get_help_npc())
		{
			_dialog_window->set_visible(true);
			Player::_get_singleton()->_set_is_received_task_hunter(true);
			_question_window->set_visible(false);
		}
		else
		{
			_question_window->set_visible(true);
		}*/
	}
}

void godot::NPC::_ready()
{
	if (rand() % 2 == 0) {
		_task = HUNTER;
	}
	else
		_task = ACORNS;
	//_task = HUNTER;

	String str, question;

	_question_window = cast_to<TextureRect>(get_child(2)->get_child(0)->get_node("QuestionWindow"));
	_question_label = cast_to<Label>(_question_window->get_child(0));
	_yes_button = cast_to<TextureButton>(_question_window->get_child(1));
	_no_button = cast_to<TextureButton>(_question_window->get_child(2));

	if (_task == HUNTER)
	{
		question = "Can you help me?";
		str = "You need to find and \nkill 5 boars";
		_yes_button->set_name("HunterYes");
		_no_button->set_name("HunterNo");
	}
	else if(_task == ACORNS)
	{
		question = "Can you give me 15 acorns?\nI don`t have any weapon...";
		str = "";
		_yes_button->set_name("AcornsYes");
		_no_button->set_name("AcornsNo");
	}

	_detection_area = cast_to<Area2D>(get_child(1));
	_detection_area->connect("body_entered", this, "_on_detection_area_entered");
	_detection_area->connect("body_exited", this, "_from_detection_area_exit");

	_dialog_window = cast_to<TextureRect>(get_child(2)->get_child(0)->get_node("DialogNPC"));
	_progress_menu = cast_to<TextureRect>(get_child(2)->get_child(0)->get_node("DialogNPC2"));
	_result_menu = cast_to<TextureRect>(get_child(2)->get_child(0)->get_node("DialogNPC3"));

	_task_label = cast_to<Label>(_dialog_window->get_child(0));
	_progress_label = cast_to<Label>(_progress_menu->get_child(0));

	_task_label->set_text(str);
	_question_label->set_text(question);
	
	_resource_loader = ResourceLoader::get_singleton();
}

void godot::NPC::_on_detection_area_entered(Node* node)
{

	if (node->get_name() == "Player")
	{
		if (GameManager::_get_singleton()->_get_help_npc() && _task == HUNTER 
			&& !cast_to<TextureRect>(get_child(2)->get_child(0)->get_node("NoAcornsWindow"))->is_visible())
		{
			_dialog_window->set_visible(true);
			Player::_get_singleton()->_set_is_received_task_hunter(true);
		}
		else
		{
			_question_window->set_visible(true);
		}
		_is_in_area = true;
	}
}

void godot::NPC::_from_detection_area_exit(Node* node)
{
	if (node->get_name() == "Player")
	{
		_dialog_window->set_visible(false);
		_progress_menu->set_visible(false);
		_question_window->set_visible(false);
		_result_menu->set_visible(false);
		_is_in_area = false;
	}
}

void godot::NPC::_progress_check()
{
	Input* i = Input::get_singleton();

	if (_task == HUNTER) {
		if (i->is_action_just_pressed("e_action") && !_progress_menu->is_visible()
			&& !_result_menu->is_visible() && _count_of_boars >= 5)
		{
			_progress_menu->set_visible(false);
			_dialog_window->set_visible(false);
			_result_menu->set_visible(true);
		}
		else if (i->is_action_just_pressed("e_action") && !_progress_menu->is_visible()
			&& !_result_menu->is_visible() && _count_of_boars <= 5)
		{
			Godot::print("In this");
			_progress_menu->set_visible(true);
			_dialog_window->set_visible(false);
			_result_menu->set_visible(false);
		}
	
		else if (i->is_action_just_pressed("e_action") && _progress_menu->is_visible()) {
			_progress_menu->set_visible(false);
			_dialog_window->set_visible(true);
			_result_menu->set_visible(false);
			//_not_enough_money->set_visible(false);
		}
	}
	if (i->is_action_just_pressed("e_action") && !_progress_menu->is_visible()
		&& _result_menu->is_visible() /*&& _count_of_boars >= 5*/)
	{
		_progress_menu->set_visible(false);
		_question_window->set_visible(true);
		_result_menu->set_visible(false);

		if (_task == HUNTER) {
			Player::_get_singleton()->_set_is_received_task_hunter(false);
			Player::_get_singleton()->_set_killed_boars(0);
			_count_of_boars = 0;

		}

		auto pos = this->get_global_position();

		for (int i = 0; i < 20 +rand() % 20; i++) {
			Ref<PackedScene> prefab = _resource_loader->load("res://Scenes/Items/Coin.tscn");

			auto item = cast_to<Area2D>(prefab->instance());

			get_node(NodePath("/root/World/YSort/Coins/"))->add_child(item);

			item->set_global_position(pos + Vector2(0, rand() % 10));
		}

	}
	if(cast_to<TextureRect>(get_child(2)->get_child(0)->get_node("NoAcornsWindow"))->is_visible())
	{
		_question_window->set_visible(true);
		cast_to<TextureRect>(get_child(2)->get_child(0)->get_node("NoAcornsWindow"))->set_visible(false);
	}
}
