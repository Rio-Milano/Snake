#ifndef GAME_H
#define GAME_H

#include "SceneManager.h"
#define SceneManager  SceneManager::Instance_()

#include "Window.h"
#define Window  Window::Instance_()

#include"SoundManager.h"
#define SoundManager  SoundManager::Instance_()

#include<SFML/Graphics.hpp>

#include"ClockWidget.h"

#include<ctime>

/*

The game class represents the base logic of the game

*/
	class Game
	{
	public:
		//ctors amd dtors
		Game() {};
		~Game() {};

		//utility functions
		void Run_()
		{
			const float frame_rate{1.f/60.f};
			float time_passed_{0.0f};


			//start playing the background music
			SoundManager.Play_Sound_("BG_Music");

			//if the window is open
			while (Window.Get_Is_Window_Open())
			{
				while (time_passed_ >= frame_rate)
				{
					//update the window
					Window.Update_();

					//update all present scenes
					SceneManager.Update_Scenes_();
						
					//decrement time passed 
					time_passed_ -= frame_rate;
				}

				// all scenes
				SceneManager.Render_Scenes_();
				
				//render all drawn
				Window.Render_();


				//update delta time
				Window.Set_Elapsed_Time_();

				//update time passed
				time_passed_ += Window.Get_Elapsed_Time();

			}
		}
	};

#endif