#include "Acorn.h"

void godot::Acorn::_register_methods()
{
	register_method("_on_acorn_player_entered", &Acorn::_on_acorn_player_entered);
}

void godot::Acorn::_init()
{
	connect("body_entered", this, "_on_acorn_player_entered");
	//connect("animation_finished", this, "_acorn_animation_effect_finished");
}

void godot::Acorn::_process(float delta)
{
	
}

void godot::Acorn::_ready()
{
	//_animated_sprite = cast_to<AnimatedSprite>(get_parent()->get_parent()->get_child(0));
	//_sprite = cast_to<AnimatedSprite>(get_parent());

	//_animated_sprite->play("Anim1");
}

void godot::Acorn::_on_acorn_player_entered(Node* body)
{
	if (body->get_name() == "Player")
	{
		Loader::get_singleton()->set_acorns(1);
		//Loader::get_singleton()->save_acorns_data();

		Loader::get_singleton()->save_all_fields();

		UI::get_singleton()->change_acorns_information();
		
		this->get_parent()->queue_free();
	}
}

//void godot::Acorn::_acorn_animation_effect_finished()
//{
//	//_animated_sprite->queue_free();
//	_sprite->set_visible(true);
//}
