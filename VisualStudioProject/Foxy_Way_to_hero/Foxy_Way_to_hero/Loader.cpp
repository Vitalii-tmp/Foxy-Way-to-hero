#include "Loader.h"

void Loader::_register_methods()
{
	godot::register_method("_ready", &Loader::_ready);
	godot::register_method("_process", &Loader::_process);
	godot::register_method("LoadCoinsData", &Loader::LoadCoinsData);
	godot::register_method("SaveCoinsData", &Loader::SaveCoinsData);
}

void Loader::_init()
{
	instance = this;

	godot::Ref<godot::File> _file = godot::File::_new();
	if (_file->file_exists(DataFile))
		LoadCoinsData();
	else
		SaveCoinsData();
}

void Loader::_ready()
{
}

void Loader::_process(float delta)
{
	
}

Loader* Loader::GetSingleton()
{
	return instance;
}

void Loader::LoadCoinsData()
{
	godot::Ref<godot::File> _file = godot::File::_new();
	if(_file->file_exists(DataFile))
	{
		_file->open(DataFile, _file->READ);

		const godot::Dictionary rez = godot::JSON::get_singleton()->parse(_file->get_as_text())->get_result();

		//auto variable = rez["Number of coins"];

		/*for (auto key : rez.keys())
			godot::Godot::print(key, " : ", rez[key]);*/

		_coins = rez["Number of coins"];

		if(_coins>10 && _coins<1000)
			godot::Godot::print("Rabotaye");
		else
			godot::Godot::print("AAAAAAAAAAAA");

		
		//godot::Godot::print("LOAD DATA" + rez.to_json()[0]);
	}
}

void Loader::SaveCoinsData()
{
	godot::Ref<godot::File> _file = godot::File::_new();
	_file->open(DataFile, _file->WRITE);

	godot::Dictionary dict;
	dict["Number of coins"] = this->_coins;

	_file->store_string(dict.to_json());
	_file->close();
	godot::Godot::print("SAVE SOME DATA");
}

void Loader::set_coins(int coins)
{
	this->_coins += coins;
	godot::Godot::print("Set coins");
}
