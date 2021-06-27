#pragma once
#include "Headers.h"

namespace godot
{
	class Loader : public godot::Node
	{
	private:
		GODOT_CLASS(Loader, Node);

	public:
		static void _register_methods();
		void _init();

		void _ready();
		void _process(float delta);
		static Loader* get_singleton();

		void load_coins_data();
		void save_coins_data() const;

		void load_acorns_data();
		void save_acorns_data() const;

		void save_all_fields();

		void set_coins(int coins);
		void set_acorns(int acorns);

		int get_coins() const;
		int get_acorns() const;
	private:
		static inline Loader* _instance;

		const String _dataFile = "user://data.save";

		int _coins = 0;
		int _acorns = 0;
	};
}

