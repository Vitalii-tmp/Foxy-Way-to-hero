#pragma once
#include"Headers.h"
namespace godot
{
	class CameraController : public Camera2D
	{
		GODOT_CLASS(CameraController, Camera2D)

	public:
		CameraController();
		~CameraController();

		static void _register_methods();
		
		void _init();
		void _process(float delta);
		void _ready();

		//Gameplay variables
	private:

		Position2D* _top_left_limit;
		Position2D* _bottom_right_limit;
	    
	};

}


