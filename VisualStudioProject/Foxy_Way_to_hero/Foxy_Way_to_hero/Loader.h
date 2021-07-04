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
		void set_start_position(Vector2 start_position);

		int get_coins() const;
		int get_acorns() const;

		
		Vector2 get_start_position();

		void load_start_position_data();
	private:
		static inline Loader* _instance;

		const String _dataFile = "data.save";

		int _coins ;
		int _acorns ;
		Vector2 _player_start_position;
	};
}

