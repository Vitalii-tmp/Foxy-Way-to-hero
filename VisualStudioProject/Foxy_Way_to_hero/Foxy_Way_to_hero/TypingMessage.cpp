#include "TypingMessage.h"

void godot::TypingMessage::_register_methods()
{
	register_method("_ready", &TypingMessage::_ready);
	register_method("_process", &TypingMessage::_process);
	register_method("_add_char", &TypingMessage::_add_char);
	register_method("_delete_cut_scene", &TypingMessage::_delete_cut_scene);
}

void godot::TypingMessage::_init()
{
	
}

void godot::TypingMessage::_ready()
{
	_text = cast_to<Label>(get_child(1));
	_timer = Timer::_new();
	add_child(_timer);

	_message = "Hello, I`m Foxy and from\nmy childhood I have\ndreamed to become a\nhero. I think it`s time\nto do that. Let`s go\nwih me and do it together";
	_current_text = "";

	get_tree()->set_pause(true);
	
}

void godot::TypingMessage::_process(float delta)
{
	if (_current_text != _message && !_timer->is_connected("timeout", this, "_add_char"))
	{
		_timer->connect("timeout", this, "_add_char");
		//Godot::print(_current_text);
		_timer->start(0.1);
	}
	else if(_current_text == _message && !_timer->is_connected("timeout", this, "_delete_cut_scene")) {
		/*_timer->start(3);*/

		Godot::print("_current_text");
		_timer->connect("timeout", this, "_delete_cut_scene");
		_timer->start(1.5);
		
	}
}

void godot::TypingMessage::_add_char()
{
	Godot::print("_message[_pos]");
	_timer->disconnect("timeout", this, "_add_char");

	_current_text += _message[_pos];
	_text->set_text(_current_text);

	_pos++;
}

void godot::TypingMessage::_delete_cut_scene()
{
	Loader::get_singleton()->set_is_first_time(true);
	Loader::get_singleton()->save_all_fields();
	
	_timer->disconnect("timeout", this, "_delete_cut_scene");
	get_tree()->set_pause(false);
	queue_free();
}
