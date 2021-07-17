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
		void set_num_meat(int numMeat);
		void set_num_cheese(int numCheese);
		void set_num_fish(int numFish);
		void set_num_speed_item(int numSpeedItem);
		void set_num_bat_wings(int numBatWings);
		void set_num_boar_furs(int numBoarFurs);
		void set_num_snake_fangs(int numSnakeFangs);
		void set_num_damage_item(int numDamageItem);
		void set_is_first_time(bool isFirstTime);
		void set_hunger(float hunger);
		void set_hp(float hp);

		int get_coins() const;
		int get_acorns() const;
		int get_num_meat();
		int get_num_cheese();
		int get_num_fish();
		int get_num_speed_item();
		int get_num_bat_wings();
		int get_num_boar_furs();
		int get_num_snake_fangs();
		int get_num_damage_item();
		bool get_is_first_time();
		float get_hunger();
		float get_hp();
		
		Vector2 get_start_position();

		void load_start_position_data();
		void load_backpack_data();
		void load_is_first_time();
		void load_hunger();
		void load_hp();

		void set_to_start_values();
	private:
		static inline Loader* _instance;

		const String _dataFile = "data.save";

		int _coins ;
		int _acorns ;
		Vector2 _player_start_position;

		int _numMeat = 0;
		int _numCheese = 0;
		int _numFish = 0;
		int _numSpeedItem = 0;
		int _numBatWings = 0;
		int _numBoarFurs = 0;
		int _numSnakeFangs = 0;
		int _numDamageItem = 0;

		bool _isFirstTime = true;

		float _hunger = 360.f;
		float _hp = 100.f;
	};
}

