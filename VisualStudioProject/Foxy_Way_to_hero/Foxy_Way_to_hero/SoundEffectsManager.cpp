#include "SoundEffectsManager.h"


//godot::SoundEffectsManager* godot::SoundEffectsManager::_instance = nullptr;



//void godot::SoundEffectsManager::_register_methods()
//{
//	register_method("_process", &SoundEffectsManager::_process);
//	register_method("_init", &SoundEffectsManager::_init);
//	register_method("_ready", &SoundEffectsManager::_ready);
//}
//
//void godot::SoundEffectsManager::_init()
//{
//	_instance = this;
//}
//
//void godot::SoundEffectsManager::_process(float delta)
//{
//	Godot::print("SOUND_MANAGER");
//}
//void godot::SoundEffectsManager::_ready()
//{
//	_resource_loader = ResourceLoader::get_singleton();
//}

void godot::SoundEffectsManager::_play_sound_effect(String _name, Node* _node)
{
	_resource_loader = ResourceLoader::get_singleton();

	Ref<PackedScene> _sound_effect = _resource_loader->load("res://Scenes/SoundEffects/"+_name+".tscn");
	
	auto _se_audio_player = Node::cast_to<AudioStreamPlayer2D>(_sound_effect->instance());

	_node->Node::add_child(_se_audio_player);


}
