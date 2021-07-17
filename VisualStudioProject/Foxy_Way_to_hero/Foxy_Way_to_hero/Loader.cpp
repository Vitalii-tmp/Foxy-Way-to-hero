#include "Headers.h"

namespace godot
{

	void Loader::_register_methods()
	{
		register_method("_ready", &Loader::_ready);
		register_method("_process", &Loader::_process);
		register_method("load_coins_data", &Loader::load_coins_data);
		register_method("save_coins_data", &Loader::save_coins_data);
		register_method("load_acorns_data", &Loader::load_acorns_data);
		register_method("save_acorns_data", &Loader::save_acorns_data);
		register_method("load_start_position_data", &Loader::load_start_position_data);
		register_method("load_is_first_time", &Loader::load_is_first_time);
		//register_method("save_start_position_data", &Loader::save_start_position_data);
	}

	void Loader::_init()
	{
		_instance = this;

		Ref<File> _file = File::_new();
		if (_file->file_exists(_dataFile))
		{
			load_start_position_data();
			load_coins_data();
			load_acorns_data();
			load_backpack_data();
			load_is_first_time();
		}
		else
		{
			save_all_fields();
		}
	}

	void Loader::_ready()
	{
	}

	void Loader::_process(float delta)
	{

	}

	Loader* Loader::get_singleton()
	{
		return _instance;
	}

	void Loader::load_coins_data()
	{
		Ref<File> _file = File::_new();
		if (_file->file_exists(_dataFile))
		{
			_file->open(_dataFile, _file->READ);

			const Dictionary rez = JSON::get_singleton()->parse(_file->get_as_text())->get_result();

			_coins = rez["Number of coins"];
			//Godot::print(_player_start_position);
			//Godot::print(String::num(_acorns));
			Godot::print(String::num(_coins));
			_file->close();
		}
	}

	void Loader::save_coins_data() const
	{
		Ref<File> _file = File::_new();
		_file->open(_dataFile, _file->WRITE);

		Dictionary dict;
		dict["Number of coins"] = this->_coins;

		_file->store_string(dict.to_json());
		_file->close();

		Godot::print("Save coins");
	}

	void Loader::load_acorns_data()
	{
		Ref<File> _file = File::_new();
		if (_file->file_exists(_dataFile))
		{
			_file->open(_dataFile, _file->READ);

			const Dictionary rez = JSON::get_singleton()->parse(_file->get_as_text())->get_result();

			_acorns = rez["Number of acorns"];
			//Godot::print(_player_start_position);
			Godot::print(String::num(_acorns));
			//Godot::print(String::num(_coins));
			_file->close();
		}
	}

	void Loader::save_acorns_data() const
	{
		Ref<File> _file = File::_new();
		_file->open(_dataFile, _file->WRITE);

		Dictionary dict;
		dict["Number of acorns"] = this->_acorns;

		_file->store_string(dict.to_json());
		_file->close();
	}

	void Loader::save_all_fields()
	{
		Ref<File> _file = File::_new();
		_file->open(_dataFile, _file->WRITE);

		Dictionary dict;
		dict["Number of acorns"] = this->_acorns;
		dict["Number of coins"] = this->_coins;
		dict["Start position x"] = this->_player_start_position.x;
		dict["Start position y"] = this->_player_start_position.y;
		dict["Number of meat"] = this->_numMeat;
		dict["Number of cheese"] = this->_numCheese;
		dict["Number of fish"] = this->_numFish;
		dict["Number of speed item"] = this->_numSpeedItem;
		dict["Number of bat wings"] = this->_numBatWings;
		dict["Number of boar furs"] = this->_numBoarFurs;
		dict["Number of snake fangs"] = this->_numSnakeFangs;
		dict["Number of damage item"] = this->_numDamageItem;
		dict["Is first time"] = this->_isFirstTime;
		dict["Hunger"] = this->_hunger;
		dict["Hp"] = this->_hp;

		_file->store_string(dict.to_json());
		_file->close();

		/*Godot::print("save all "+_player_start_position);
		Godot::print("save all " + String::num(_acorns));
		Godot::print("save all " + String::num(_coins));*/
	}

	void Loader::set_coins(int coins)
	{
		this->_coins += coins;
	}

	void Loader::set_acorns(int acorns)
	{
		this->_acorns += acorns;
	}

	int Loader::get_coins() const
	{
		return this->_coins;
	}

	int Loader::get_acorns() const
	{
		return this->_acorns;
	}

	int Loader::get_num_meat()
	{
		return this->_numMeat;
	}

	int Loader::get_num_cheese()
	{
		return this->_numCheese;
	}

	int Loader::get_num_fish()
	{
		return this->_numFish;
	}

	int Loader::get_num_speed_item()
	{
		return this->_numSpeedItem;
	}

	int Loader::get_num_bat_wings()
	{
		return this->_numBatWings;
	}

	int Loader::get_num_boar_furs()
	{
		return this->_numBoarFurs;
	}

	int Loader::get_num_snake_fangs()
	{
		return this->_numSnakeFangs;
	}

	int Loader::get_num_damage_item()
	{
		return this->_numDamageItem;
	}

	bool Loader::get_is_first_time()
	{
		return this->_isFirstTime;
	}

	float Loader::get_hunger()
	{
		return this->_hunger;
	}

	float Loader::get_hp()
	{
		return this->_hp;
	}

	void Loader::set_start_position(Vector2 start_position)
	{
		_player_start_position = start_position;
	}

	void Loader::set_num_meat(int numMeat)
	{
		_numMeat = numMeat;
	}

	void Loader::set_num_cheese(int numCheese)
	{
		_numCheese = numCheese;
	}

	void Loader::set_num_fish(int numFish)
	{
		_numFish = numFish;
	}

	void Loader::set_num_speed_item(int numSpeedItem)
	{
		_numSpeedItem = numSpeedItem;
	}

	void Loader::set_num_bat_wings(int numBatWings)
	{
		_numBatWings = numBatWings;
	}

	void Loader::set_num_boar_furs(int numBoarFurs)
	{
		_numBoarFurs = numBoarFurs;
	}

	void Loader::set_num_snake_fangs(int numSnakeFangs)
	{
		_numSnakeFangs = numSnakeFangs;
	}

	void Loader::set_num_damage_item(int numDamageItem)
	{
		_numDamageItem = numDamageItem;
	}

	void Loader::set_is_first_time(bool isFirstTime)
	{
		_isFirstTime = isFirstTime;
	}

	void Loader::set_hunger(float hunger)
	{
		_hunger = hunger;
	}

	void Loader::set_hp(float hp)
	{
		_hp = hp;
	}

	Vector2 Loader::get_start_position()
	{
		return _player_start_position;
	}


	void Loader::load_start_position_data()
	{
		Godot::print("load_start_position_data");
		Ref<File> _file = File::_new();
		if (_file->file_exists(_dataFile))
		{
			_file->open(_dataFile, _file->READ);

			const Dictionary rez = JSON::get_singleton()->parse(_file->get_as_text())->get_result();

			_player_start_position.x = rez["Start position x"];
			_player_start_position.y = rez["Start position y"];

			Godot::print(_player_start_position);
			_file->close();
		}
	}

	void Loader::load_backpack_data()
	{
		Ref<File> _file = File::_new();
		if (_file->file_exists(_dataFile))
		{
			_file->open(_dataFile, _file->READ);

			const Dictionary rez = JSON::get_singleton()->parse(_file->get_as_text())->get_result();

			_numMeat = rez["Number of meat"];
			_numCheese = rez["Number of cheese"];
			_numFish = rez["Number of fish"];
			_numSpeedItem = rez["Number of speed item"];
			_numBatWings = rez["Number of bat wings"];
			_numBoarFurs = rez["Number of boar furs"];
			_numSnakeFangs = rez["Number of snake fangs"];
			_numDamageItem = rez["Number of damage item"];

			//Godot::print(_player_start_position);
			_file->close();
		}
	}
	void Loader::load_is_first_time()
	{
		Ref<File> _file = File::_new();
		if (_file->file_exists(_dataFile))
		{
			_file->open(_dataFile, _file->READ);

			const Dictionary rez = JSON::get_singleton()->parse(_file->get_as_text())->get_result();

			_isFirstTime = rez["Is first time"];

			_file->close();
		}
	}
	void Loader::load_hunger()
	{
		Ref<File> _file = File::_new();
		if (_file->file_exists(_dataFile))
		{
			_file->open(_dataFile, _file->READ);

			const Dictionary rez = JSON::get_singleton()->parse(_file->get_as_text())->get_result();

			_hunger = rez["Hunger"];

			_file->close();
		}
	}
	void Loader::load_hp()
	{
		Ref<File> _file = File::_new();
		if (_file->file_exists(_dataFile))
		{
			_file->open(_dataFile, _file->READ);

			const Dictionary rez = JSON::get_singleton()->parse(_file->get_as_text())->get_result();

			_hp = rez["Hp"];

			_file->close();
		}
	}
	void Loader::set_to_start_values()
	{
		_coins = 0;
		_acorns = 0;
		_player_start_position = Vector2(0, 0);
		_numMeat = 0;
		_numCheese = 0;
		_numFish = 0;
		_numSpeedItem = 0;
		_numBatWings = 0;
		_numBoarFurs = 0;
		_numSnakeFangs = 0;
		_numDamageItem = 0;

		_isFirstTime = false;

		_hunger = 360.f;
		_hp = 100.f;

		save_all_fields();
	}
}
