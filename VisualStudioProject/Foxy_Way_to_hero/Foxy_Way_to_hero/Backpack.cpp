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

	Ref<PackedScene> prefab;

	switch (el->_type)
	{
	case MEAT:
		{
		prefab = _resource_loader->load("res://Scenes/Items/Meat.tscn");
			break;
		}
	case CHEESE:
		prefab = _resource_loader->load("res://Scenes/Items/Cheese.tscn");
		break;
	case FISH:
		prefab = _resource_loader->load("res://Scenes/Items/Fish.tscn");
		break;
	case RED_FISH:
		prefab = _resource_loader->load("res://Scenes/Items/RedFish.tscn");
		break;
	}
	
	for(int i = 0; i<8; i++)
	{
		if(_items[i] == nullptr)
		{
			auto item = cast_to<KinematicBody2D>(prefab->instance());
			add_child(item);
			_items[i] = el;
			flag = true;
			Godot::print("add element");
			break;
		}
	}

	if (!flag)
		Godot::print("no empty place");
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

godot::Backpack::Backpack()
{
	
}

godot::Backpack::~Backpack()
{
}
