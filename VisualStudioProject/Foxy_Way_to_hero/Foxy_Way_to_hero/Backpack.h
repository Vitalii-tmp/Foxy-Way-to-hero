#pragma once
#include "Headers.h"

namespace godot
{
	class Item;
	
	class Backpack : public Node2D
	{
		GODOT_CLASS(Backpack, Node2D);
		
		//const int _SIZE = 12;
		TextureButton* _items[8];

	public:
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();

		/*void _add_element(Item* el);
		bool _can_add_element(Item* el);*/

		void _add_item(Item* item);
		bool _can_add_item(Item* item);
		void _remove_by_name(String name);

		int _get_number_meat();
		int _get_number_fish();
		int _get_number_cheese();
		int _get_number_speed_item();
		int _get_number_bat_wins();
		
		Backpack();
		~Backpack();

	private:
		ResourceLoader* _resource_loader = nullptr;

		int _number_meat = 0;
		int _number_cheese = 0;
		int _number_fish = 0;
		int _number_speed_item = 0;
		int _number_bat_wings = 0;
	};
}
