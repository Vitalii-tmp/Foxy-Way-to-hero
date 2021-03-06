#include "Headers.h"

using namespace godot;

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options * o) {
	Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options * o) {
	Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void* handle) {
	Godot::nativescript_init(handle);

	register_class<Player>();
	register_class<Coin>();
	register_class<Loader>();
	register_class<Grass>();
	register_class<BatAI>();
	register_class<CameraController>();
	register_class<UI>();
	register_class<Bullet>();
	register_class<Acorn>();
	register_class<PauseButton>();
	register_class<ContinueButton>();
	register_class<HealthUI>();
	register_class<RestartButton>();
	register_class<QuitButton>();
	register_class<LoadSceneButton>();
	register_class<Tomb>();
	register_class<CheckPoint>();
	register_class<Countryman>();
	register_class<StoreButton>();
	register_class<Backpack>();
	register_class<BoarAI>();
	register_class<SnakeAI>();
	register_class<BackpackItemButton>();
	register_class<Craftman>();
	register_class<UpdateScoreButton>();
	register_class<Item>();
	register_class<HungerUI>();
	register_class<TypingMessage>();
	register_class<MainMenuCamera>();
	register_class<Preloader>();
	register_class<NPC>();
	register_class<GameManager>();
	register_class<Mushrooms>();

	register_class<SoundEffect>();
	//register_class<SoundEffectsManager>();

	register_class<SelectionButton>();
	register_class<Options>();
}