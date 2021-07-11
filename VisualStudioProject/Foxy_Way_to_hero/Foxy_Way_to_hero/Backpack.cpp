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
	_resource_loader = ResourceLoader::get_singleton();
	_number_meat = Loader::get_singleton()->get_num_meat();
	_number_cheese = Loader::get_singleton()->get_num_cheese();
	_number_fish = Loader::get_singleton()->get_num_fish();
	_number_speed_item = Loader::get_singleton()->get_num_speed_item();
	_number_bat_wings = Loader::get_singleton()->get_num_bat_wings();
	_number_boar_fur = Loader::get_singleton()->get_num_boar_furs();
	_number_snake_fang = Loader::get_singleton()->get_num_snake_fangs();
	_number_damage_item = Loader::get_singleton()->get_num_damage_item();

	Godot::print(String::num(_number_meat));

	Ref<PackedScene> prefab, prefab2, prefab3, prefab4,
		prefab5, prefab6, prefab7, prefab8, backpack_item;

	String name;

	auto _b = cast_to<TextureButton>(get_child(1)->get_child(0));

	prefab = _resource_loader->load("res://Scenes/Items/Meat.tscn");
	name = "Meat";
	_b->set_normal_texture(cast_to<Sprite>(prefab->instance()->get_child(0))->get_texture());
	_b->set_stretch_mode(3);
	_b->set_expand(true);
	cast_to<Label>(get_node("GridContainer")->get_child(0)->get_child(0))->set_text(std::to_string(_number_meat).c_str());
	_items[0] = _b;

	auto _b2 = cast_to<TextureButton>(get_child(1)->get_child(1));
	prefab2 = _resource_loader->load("res://Scenes/Items/Cheese.tscn");
	name = "Cheese";
	_b2->set_normal_texture(cast_to<Sprite>(prefab2->instance()->get_child(0))->get_texture());
	_b2->set_stretch_mode(3);
	_b2->set_expand(true);
	Godot::print(_b2->get_name());
	cast_to<Label>(get_node("GridContainer")->get_child(1)->get_child(0))->set_text(std::to_string(_number_cheese).c_str());
	Godot::print("Number of cheese: " + String::num(_number_cheese));
	_items[1] = _b2;

	auto _b3 = cast_to<TextureButton>(get_child(1)->get_child(2));
	prefab3 = _resource_loader->load("res://Scenes/Items/Fish.tscn");
	name = "Fish";
	_b3->set_normal_texture(cast_to<Sprite>(prefab3->instance()->get_child(0))->get_texture());
	_b3->set_stretch_mode(3);
	_b3->set_expand(true);
	cast_to<Label>(get_node("GridContainer")->get_child(2)->get_child(0))->set_text(std::to_string(_number_fish).c_str());
	_items[2] = _b3;

	auto _b4 = cast_to<TextureButton>(get_child(1)->get_child(3));
	prefab4 = _resource_loader->load("res://Scenes/Items/SpeedItem.tscn");
	name = "SpeedItem";
	_b4->set_normal_texture(cast_to<Sprite>(prefab4->instance()->get_child(0))->get_texture());
	_b4->set_stretch_mode(3);
	_b4->set_expand(true);
	cast_to<Label>(get_node("GridContainer")->get_child(3)->get_child(0))->set_text(std::to_string(_number_speed_item).c_str());
	_items[3] = _b4;

	auto _b5 = cast_to<TextureButton>(get_child(1)->get_child(4));
	prefab5 = _resource_loader->load("res://Scenes/Items/BatWing.tscn");
	name = "BatWing";
	_b5->set_normal_texture(cast_to<Sprite>(prefab5->instance()->get_child(0))->get_texture());
	_b5->set_stretch_mode(3);
	_b5->set_expand(true);
	cast_to<Label>(get_node("GridContainer")->get_child(4)->get_child(0))->set_text(std::to_string(_number_bat_wings).c_str());
	_items[4] = _b5;

	auto _b6 = cast_to<TextureButton>(get_child(1)->get_child(5));
	prefab6 = _resource_loader->load("res://Scenes/Items/BoarFur.tscn");
	name = "BoarFur";
	_b6->set_normal_texture(cast_to<Sprite>(prefab6->instance()->get_child(0))->get_texture());
	_b6->set_stretch_mode(3);
	_b6->set_expand(true);
	cast_to<Label>(get_node("GridContainer")->get_child(5)->get_child(0))->set_text(std::to_string(_number_boar_fur).c_str());
	_items[5] = _b6;

	auto _b7 = cast_to<TextureButton>(get_child(1)->get_child(6));
	prefab7 = _resource_loader->load("res://Scenes/Items/SnakeSpike.tscn");
	name = "SnakeSpike";
	_b7->set_normal_texture(cast_to<Sprite>(prefab7->instance()->get_child(0))->get_texture());
	_b7->set_stretch_mode(3);
	_b7->set_expand(true);
	cast_to<Label>(get_node("GridContainer")->get_child(6)->get_child(0))->set_text(std::to_string(_number_snake_fang).c_str());
	_items[6] = _b7;

	auto _b8 = cast_to<TextureButton>(get_child(1)->get_child(7));
	prefab8 = _resource_loader->load("res://Scenes/Items/DamageItem.tscn");
	name = "DamageItem";
	_b8->set_normal_texture(cast_to<Sprite>(prefab8->instance()->get_child(0))->get_texture());
	_b8->set_stretch_mode(3);
	_b8->set_expand(true);
	cast_to<Label>(get_node("GridContainer")->get_child(7)->get_child(0))->set_text(std::to_string(_number_damage_item).c_str());
	_items[7] = _b8;
}

//void godot::Backpack::_add_element(Item* el)
//{
//	bool flag = false;
//	String name;
//
//	Ref<PackedScene> backpack_item;
//
//	backpack_item = _resource_loader->load("res://Scenes/Items/BackpackItem.tscn");
//
//	auto item = cast_to<KinematicBody2D>(el->get_parent());
//
//	auto _b = cast_to<TextureButton>(backpack_item->instance());
//
//	for (int i = 0; i < 8; i++)
//	{
//
//		if (get_node("GridContainer")->get_child(i)->get_name() == item->get_parent()->get_name())
//		{
//			Godot::print(item->get_name());
//			auto text = cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text();
//			cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->set_text(std::to_string((text.to_int()) + 1).c_str());
//
//			break;
//		}
//	}
//	for (int i = 0; i < 4; i++)
//	{
//		if (i == 0)
//		{
//			Loader::get_singleton()->set_num_meat(cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int());
//			_number_meat = cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int();
//		}
//		else if (i == 1)
//		{
//			Loader::get_singleton()->set_num_cheese(cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int());
//			_number_cheese = cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int();
//		}
//		else if (i == 2)
//		{
//			Loader::get_singleton()->set_num_fish(cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int());
//			_number_fish = cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int();
//		}
//		else if (i == 3)
//		{
//			Loader::get_singleton()->set_num_speed_item(cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int());
//			_number_speed_item = cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int();
//		}
//	}
//}

//bool godot::Backpack::_can_add_element(Item* el)
//{
//	bool flag = false;
//
//	for (int i = 0; i < 8; i++)
//	{
//		if (_items[i]->get_name() == el->get_parent()->get_parent()->get_name() 
//			&& cast_to<Label>(_items[i]->get_child(0))->get_text().to_int()<20)
//		{
//			flag = true;
//			break;
//		}
//	}
//
//	return flag;
//}

void godot::Backpack::_add_item(Item* item)
{
	bool flag = false;
	String name;

	Ref<PackedScene> backpack_item;

	backpack_item = _resource_loader->load("res://Scenes/Items/BackpackItem.tscn");

	auto _item = cast_to<KinematicBody2D>(item->get_parent());

	auto _b = cast_to<TextureButton>(backpack_item->instance());

	for (int i = 0; i < 8; i++)
	{

		if (get_node("GridContainer")->get_child(i)->get_name() == _item->get_parent()->get_name())
		{
			Godot::print(_item->get_name());
			auto text = cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text();
			cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->set_text(std::to_string((text.to_int()) + 1).c_str());

			break;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (i == 0)
		{
			Loader::get_singleton()->set_num_meat(cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int());
			_number_meat = cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int();
		}
		else if (i == 1)
		{
			Loader::get_singleton()->set_num_cheese(cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int());
			_number_cheese = cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int();
		}
		else if (i == 2)
		{
			Loader::get_singleton()->set_num_fish(cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int());
			_number_fish = cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int();
		}
		else if (i == 3)
		{
			Loader::get_singleton()->set_num_speed_item(cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int());
			_number_speed_item = cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int();
		}
		else if (i == 4)
		{
			Loader::get_singleton()->set_num_bat_wings(cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int());
			_number_bat_wings = cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int();
		}
		else if (i == 5)
		{
			Loader::get_singleton()->set_num_boar_furs(cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int());
			_number_boar_fur = cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int();
		}
		else if (i == 6)
		{
			Loader::get_singleton()->set_num_snake_fangs(cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int());
			_number_snake_fang = cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int();
		}
		else if (i == 7)
		{
			Loader::get_singleton()->set_num_damage_item(cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int());
			_number_damage_item = cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int();
		}
	}
}

bool godot::Backpack::_can_add_item(Item* item)
{
	bool flag = false;

	for (int i = 0; i < 8; i++)
	{
		if (_items[i]->get_name() == item->get_parent()->get_parent()->get_name()
			&& cast_to<Label>(_items[i]->get_child(0))->get_text().to_int() < 20)
		{
			flag = true;
			break;
		}
	}

	return flag;
}

void godot::Backpack::_remove_by_name(String name)
{
	for (int i = 0; i < 8; i++)
	{
		if (get_child(1)->get_child(i)->get_name() == name)
		{
			Godot::print("if name equals");
			_items[i] = nullptr;
		}
	}
}

int godot::Backpack::_get_number_meat()
{
	return _number_meat;
}

int godot::Backpack::_get_number_fish()
{
	return _number_fish;
}

int godot::Backpack::_get_number_cheese()
{
	return _number_cheese;
}

int godot::Backpack::_get_number_speed_item()
{
	return _number_speed_item;
}

int godot::Backpack::_get_number_bat_wins()
{
	return _number_bat_wings;
}

int godot::Backpack::_get_number_boar_fur()
{
	return _number_boar_fur;
}

int godot::Backpack::_get_number_snake_fang()
{
	return _number_snake_fang;
}

int godot::Backpack::_get_number_damage_item()
{
	return _number_damage_item;
}

godot::Backpack::Backpack()
{

}

godot::Backpack::~Backpack()
{
}
