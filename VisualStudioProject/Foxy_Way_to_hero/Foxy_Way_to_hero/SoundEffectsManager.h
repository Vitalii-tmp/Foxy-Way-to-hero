#pragma once
#include "Headers.h"

namespace godot 
{
	class SoundEffectsManager 
	{

	
			// Gameplay methods
	public:
		
		static SoundEffectsManager* _get_singleton()
		{
			if (_instance == nullptr)
				_instance = new SoundEffectsManager;

			return _instance;
		}

		/*static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();*/

		void _play_sound_effect(String _name, Node* _node);

	private:

		static inline SoundEffectsManager* _instance = nullptr;
		ResourceLoader* _resource_loader = nullptr;
	};
}


