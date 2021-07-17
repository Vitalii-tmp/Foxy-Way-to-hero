#include "SelectionButton.h"

void godot::SelectionButton::_register_methods()
{
	register_method("_process", &SelectionButton::_process);
	register_method("_ready", &SelectionButton::_ready);
	register_method("_on_button_pressed", &SelectionButton::_on_button_pressed);
}

void godot::SelectionButton::_init()
{
}

void godot::SelectionButton::_process(float delta)
{
}

void godot::SelectionButton::_ready()
{
	connect("pressed", this, "_on_button_pressed");
}

void godot::SelectionButton::_on_button_pressed()
{
	if(get_name() == "HunterYes")
	{
		Godot::print("HunterYES");
		GameManager::_get_singleton()->_set_help_npc(true);

		cast_to<TextureRect>(get_parent()->get_parent()->get_node("DialogNPC"))->set_visible(true);
		cast_to<TextureRect>(get_parent())->set_visible(false);
	}
	else if(get_name() == "HunterNo")
	{
		Godot::print("HunterNO");
		GameManager::_get_singleton()->_set_help_npc(false);
		cast_to<TextureRect>(get_parent())->set_visible(false);
	}
	else if (get_name() == "AcornsYes")
	{
		if (std::atoi(UI::get_singleton()->get_acorns_information().c_str()) >= 15)
		{
			Loader::get_singleton()->set_acorns(-15);
			UI::get_singleton()->change_acorns_information();
			cast_to<TextureRect>(get_parent()->get_parent()->get_node("DialogNPC3"))->set_visible(true);
			cast_to<TextureRect>(get_parent())->set_visible(false);
		}
	}
	else if (get_name() == "AcornsNo")
	{
		cast_to<TextureRect>(get_parent())->set_visible(false);
	}
}
