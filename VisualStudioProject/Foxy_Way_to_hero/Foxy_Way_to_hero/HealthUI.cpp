#include "HealthUI.h"

void godot::HealthUI::_register_methods()
{
	register_method("_ready", &HealthUI::_ready);
	register_method("_delete_next_full_heart", &HealthUI::_delete_next_full_heart);
	register_method("_turn_on_hit_anim", &HealthUI::_turn_on_hit_anim);
}

void godot::HealthUI::_init()
{
	_instance = this;
}

void godot::HealthUI::_ready()
{
	//connect("animation_finished", this, "_delete_next_full_heart");
}

godot::HealthUI* godot::HealthUI::_get_singleton()
{
	return _instance;
}

void godot::HealthUI::_turn_on_hit_anim()
{
	cast_to<AnimatedSprite>(this->get_child(0)->get_child(0))->set_visible(true);
	cast_to<AnimatedSprite>(this->get_child(0)->get_child(0))->play("hitAnim");
}

void godot::HealthUI::_delete_next_full_heart()
{
	this->get_child(0)->queue_free();
}
