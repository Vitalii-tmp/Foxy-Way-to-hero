#pragma once
#include "Headers.h"
#include <Node.hpp>
#include <File.hpp>
#include <JSON.hpp>
#include <JSONParseResult.hpp>

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

	void set_coins(int coins);
	int get_coins();
private:
	static inline Loader* _instance;

	const godot::String _dataFile = "user://data.save";

	int _coins = 0;
};

