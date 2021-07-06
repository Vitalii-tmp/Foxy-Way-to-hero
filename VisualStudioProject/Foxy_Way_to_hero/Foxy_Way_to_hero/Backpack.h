#pragma once
#include "Headers.h"

namespace godot
{
	class Backpack : public Node2D
	{
		GODOT_CLASS(Backpack, Node2D);
		
		//const int _SIZE = 12;
		Meat* _items[8];

	public:
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();

		void _add_element(Meat* el);
		bool _can_add_element();
		void _remove_by_name(String name);
		
		Backpack();
		~Backpack();

	private:
		ResourceLoader* _resource_loader = nullptr;
	};
}
