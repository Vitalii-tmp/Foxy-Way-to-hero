#include "Backpack.h"

void godot::Backpack::_register_methods()
{
	register_method("_process", &Backpack::_process);
	register_method("_ready", &Backpack::_ready);
}

void godot::Backpack::_init()
{

}

void godot::Backpack::_process(float delta)
{

}

void godot::Backpack::_ready()
{
	for (int i = 0; i < 8; i++)
	{
		_items[i] = nullptr;
		Godot::print("create backpack");
	}

	_resource_loader = ResourceLoader::get_singleton();
}

void godot::Backpack::_add_element(Meat* el)
{
	bool flag = false;
	String name; 

	Ref<PackedScene> prefab, backpack_item;

	switch (el->_type)
	{
	case MEAT:
		prefab = _resource_loader->load("res://Scenes/Items/Meat.tscn");
		name = "Meat";
		break;
	case CHEESE:
		prefab = _resource_loader->load("res://Scenes/Items/Cheese.tscn");
		name = "Cheese";
		break;
	case FISH:
		prefab = _resource_loader->load("res://Scenes/Items/Fish.tscn");
		name = "Fish";
		break;
	case RED_FISH:
		prefab = _resource_loader->load("res://Scenes/Items/RedFish.tscn");
		name = "RedFish";
		break;
	}

	backpack_item = _resource_loader->load("res://Scenes/Items/BackpackItem.tscn");
	auto item = cast_to<KinematicBody2D>(prefab->instance());
	auto _b = cast_to<TextureButton>(backpack_item->instance());
	//auto _cen = CenterContainer::_new();
	for (int i = 0; i < 8; i++)
	{

		if (_items[i]!= nullptr && get_child(1)->get_child(i)->get_name() == item->get_name())
		{
			auto text = cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text();
			cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->set_text(std::to_string((text.to_int()) + 1).c_str());
			break;
		}
		else{
			if (_items[i] == nullptr)
			{
				_b->set_normal_texture(cast_to<Sprite>(item->get_child(0))->get_texture());
				_b->set_custom_minimum_size(Vector2(13, 14));
				_b->set_stretch_mode(3);
				_b->set_expand(true);
				_b->set_name(name);
				/*_cen->add_child(_b);
				_cen->set_custom_minimum_size(Vector2(22, 22));*/
				get_child(1)->add_child(_b);
				_items[i] = el;
				flag = true;
				Godot::print("add element");
				break;
			}
		}
	}

}

bool godot::Backpack::_can_add_element()
{
	bool flag = false;

	for (int i = 0; i < 8; i++)
	{
		if (_items[i] == nullptr)
		{
			flag = true;
			break;
		}
	}

	return flag;
}

void godot::Backpack::_remove_by_name(String name)
{
	for(int i = 0; i<8; i++)
	{
		if(get_child(1)->get_child(i)->get_name() == name)
		{
			Godot::print("if name equals");
			_items[i] = nullptr;
		}
	}
}

godot::Backpack::Backpack()
{

}

godot::Backpack::~Backpack()
{
}
