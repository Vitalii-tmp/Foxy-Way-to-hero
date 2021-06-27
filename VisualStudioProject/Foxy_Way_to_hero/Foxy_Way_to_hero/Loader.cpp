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
	}

	void Loader::_init()
	{
		_instance = this;

		Ref<File> _file = File::_new();
		if (_file->file_exists(_dataFile))
		{
			load_coins_data();
			load_acorns_data();
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

		_file->store_string(dict.to_json());
		_file->close();
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
}
