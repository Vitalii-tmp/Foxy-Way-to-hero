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
	static Loader* GetSingleton();

	void LoadCoinsData();
	void SaveCoinsData();

	void set_coins(int coins);
private:
	static inline Loader* instance;

	const godot::String DataFile = "user://data.save";

	int _coins = 0;
};

