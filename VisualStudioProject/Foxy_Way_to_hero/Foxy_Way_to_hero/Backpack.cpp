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
	int numMeat = Loader::get_singleton()->get_num_meat();
	int numCheese = Loader::get_singleton()->get_num_cheese();
	int numFish = Loader::get_singleton()->get_num_fish();
	int numRedFish = Loader::get_singleton()->get_num_red_fish();

	Godot::print(String::num(numMeat));

	Ref<PackedScene> prefab, prefab2, prefab3, prefab4, backpack_item;

	//Meat* el;
	String name;

	//backpack_item = _resource_loader->load("res://Scenes/Items/BackpackItem.tscn");
	auto _b = cast_to<TextureButton>(get_child(1)->get_child(0));

	prefab = _resource_loader->load("res://Scenes/Items/Meat.tscn");
	name = "Meat";
	//el = new Meat("name");
	_b->set_normal_texture(cast_to<Sprite>(prefab->instance()->get_child(0))->get_texture());
	//_b->set_custom_minimum_size(Vector2(13, 14));
	_b->set_stretch_mode(3);
	_b->set_expand(true);
	//_b->set_name(name);
	//get_node("GridContainer")->add_child(_b);
	cast_to<Label>(get_node("GridContainer")->get_child(0)->get_child(0))->set_text(std::to_string(numMeat).c_str());
	_items[0] = _b;

	////backpack_item = _resource_loader->load("res://Scenes/Items/BackpackItem.tscn");
	auto _b2 = cast_to<TextureButton>(get_child(1)->get_child(1));
	prefab2 = _resource_loader->load("res://Scenes/Items/Cheese.tscn");
	name = "Cheese";
	//el = new Meat("name");
	_b2->set_normal_texture(cast_to<Sprite>(prefab2->instance()->get_child(0))->get_texture());
	//_b2->set_custom_minimum_size(Vector2(13, 14));
	_b2->set_stretch_mode(3);
	_b2->set_expand(true);
	//_b2->set_name(name);
	Godot::print(_b2->get_name());
	//get_node("GridContainer")->add_child(_b2);
	cast_to<Label>(get_node("GridContainer")->get_child(1)->get_child(0))->set_text(std::to_string(numCheese).c_str());
	Godot::print("Number of cheese: " + String::num(numCheese));
	_items[1] = _b2;

	auto _b3 = cast_to<TextureButton>(get_child(1)->get_child(2));
	prefab3 = _resource_loader->load("res://Scenes/Items/Fish.tscn");
	name = "Fish";
	//el = new Meat("name");
	_b3->set_normal_texture(cast_to<Sprite>(prefab3->instance()->get_child(0))->get_texture());
	//_b3->set_custom_minimum_size(Vector2(13, 14));
	_b3->set_stretch_mode(3);
	_b3->set_expand(true);
	//_b3->set_name(name);
	//get_node("GridContainer")->add_child(_b3);
	cast_to<Label>(get_node("GridContainer")->get_child(2)->get_child(0))->set_text(std::to_string(numFish).c_str());
	_items[2] = _b3;

	auto _b4 = cast_to<TextureButton>(get_child(1)->get_child(3));
	prefab4 = _resource_loader->load("res://Scenes/Items/RedFish.tscn");
	name = "RedFish";
	//el = new Meat("name");
	_b4->set_normal_texture(cast_to<Sprite>(prefab4->instance()->get_child(0))->get_texture());
	//_b4->set_custom_minimum_size(Vector2(13, 14));
	_b4->set_stretch_mode(3);
	_b4->set_expand(true);
	//_b4->set_name(name);
	//get_node("GridContainer")->add_child(_b4);
	cast_to<Label>(get_node("GridContainer")->get_child(3)->get_child(0))->set_text(std::to_string(numRedFish).c_str());
	_items[3] = _b4;

	for(int i = 4; i<8; i++)
	{
		_items[i] = cast_to<TextureButton>(get_child(1)->get_child(i));
	}
	
	/*for (int i = 4; i < 8; i++)
	{
		_items[i] = nullptr;
		Godot::print("create backpack");
	}*/


}

void godot::Backpack::_add_element(Meat* el)
{
	bool flag = false;
	String name;

	Ref<PackedScene> /*prefab,*/ backpack_item;

	/*switch (el->_type)
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
	}*/

	Godot::print("bbbbbbbbbbbbbbbbbbbbbbb");
	backpack_item = _resource_loader->load("res://Scenes/Items/BackpackItem.tscn");
	Godot::print("ccccccccccccccccccccccccccc");

	auto item = cast_to<KinematicBody2D>(el->get_parent());
	Godot::print("dddddddddddddddddddddddddd");

	auto _b = cast_to<TextureButton>(backpack_item->instance());
	Godot::print("eeeeeeeeeeeeeeeeeeeeeeee");

	//auto _cen = CenterContainer::_new();
	for (int i = 0; i < 8; i++)
	{

		if (/*_items[i]!= nullptr &&*/ get_node("GridContainer")->get_child(i)->get_name() == item->get_name())
		{
			Godot::print(item->get_name());
			auto text = cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text();
			cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->set_text(std::to_string((text.to_int()) + 1).c_str());

			break;
		}
		//else{
		//	if (_items[i] == nullptr)
		//	{
		//		_b->set_normal_texture(cast_to<Sprite>(item->get_child(0))->get_texture());
		//		_b->set_custom_minimum_size(Vector2(13, 14));
		//		_b->set_stretch_mode(3);
		//		_b->set_expand(true);
		//		_b->set_name(name);
		//		/*_cen->add_child(_b);
		//		_cen->set_custom_minimum_size(Vector2(22, 22));*/
		//		get_child(1)->add_child(_b);
		//		_items[i] = el;
		//		flag = true;
		//		Godot::print("add element");
		//		break;
		//	}
		//}


	}
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			Loader::get_singleton()->set_num_meat(cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int());
			Godot::print("Set num meat");
		}
		else if (i == 1)
		{
			Loader::get_singleton()->set_num_cheese(cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int());
		}
		else if (i == 2)
		{
			Loader::get_singleton()->set_num_fish(cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int());
		}
		else if (i == 3)
		{
			Loader::get_singleton()->set_num_red_fish(cast_to<Label>(get_child(1)->get_child(i)->get_child(0))->get_text().to_int());
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
	for (int i = 0; i < 8; i++)
	{
		if (get_child(1)->get_child(i)->get_name() == name)
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
