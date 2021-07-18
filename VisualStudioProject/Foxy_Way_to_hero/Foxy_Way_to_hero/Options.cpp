#include "Options.h"


godot::Options::Options()
{
	is_full_screen = false;
}

void godot::Options::_register_methods()
{
	register_method("_ready", &Options::_ready);
	register_method("_init", &Options::_init);
	register_method("_on_full_screen_button_up", &Options::_on_full_screen_button_up);
	register_method("_on_sound_effects_slider_value_changed", &Options::_on_sound_effects_slider_value_changed);
	register_method("_on_music_slider_value_changed", &Options::_on_music_slider_value_changed);
}


void godot::Options::_init()
{
}

void godot::Options::_ready()
{
	_full_screen_check_box = cast_to<CheckBox>(get_node("FullScreenCB"));
	_sound_effects_hslider = cast_to<HSlider>(get_node("SoundEffectsSlider"));
	_music_hslider= cast_to<HSlider>(get_node("MusicSlider"));
	_os = OS::get_singleton();
}

void godot::Options::_on_full_screen_button_up()
{
	Godot::print("CheckBox");

	is_full_screen = !is_full_screen;
	_os->set_window_fullscreen(is_full_screen);

}

void godot::Options::_on_sound_effects_slider_value_changed()
{
	Godot::print("changed");
	Godot::print(String::num(_sound_effects_hslider->get_value()));
	auto _value = _sound_effects_hslider->get_value();

	AudioController::_get_singleton()->_set_sound_effects_volume(_value);
	
}

void godot::Options::_on_music_slider_value_changed()
{
	auto _value = _music_hslider->get_value();
	AudioController::_get_singleton()->_set_music_volume(_value);
	AudioController::_get_singleton()->_set_max_sound_value(_value);
}
