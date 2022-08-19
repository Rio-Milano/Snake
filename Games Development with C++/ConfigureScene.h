#ifndef CONFIGURESCENE_H
#define CONFIGURESCENE_H

#include"Scene.h"
#include"Button.h"
#include"SlideBar.h"
#include"Text.h"
#include"Button.h"
#include"CheckBoxWidget.h"

/*
this is a child of scene and implements the functionality found in the configure scene that allows you to change game settings 
*/
class ConfigureScene : public  Scene
{
public:
	//ctors and dtors
	ConfigureScene();
	~ConfigureScene() = default;

	//update the scene
	void Update_() override final;
	
	//draw scene widgets to scene
	void Render_() override final;

	//load the scene
	void Init_() override final;

	//unload the scene
	void De_Init_() override final;

	//enable AI
	static bool AI_On_;

	//enable a seccond player
	static bool P2_On_;


private:
	//button that takes you to the menu
	 Button menu_button_;

	 //AI checkbox group
	 Text AI_CheckBox_Text_;
	 CheckBoxWidget AI_CheckBox_;

	 //Player 2 checkbox group
	 Text P2_CheckBox_Text_;
	 CheckBoxWidget P2_CheckBox_;

	//bg sound group
	SlideBar BG_Slidebar;
	Text BG_Slide_Bar_Label_;

	//UI sound group
	SlideBar UI_Slidebar;
	Text UI_Slide_Bar_Label_;
	Button UI_Slise_Bar_Test_Sound_Button_;

	//sound effects slidebar group
	SlideBar SoundEffects_Slidebar;
	Text SoundEffects_Slide_Bar_Label_;
	Button SoundEffects_Slise_Bar_Test_Sound_Button_;

	//narrator sound group
	SlideBar narrator_Slidebar;
	Text narrator_Slide_Bar_Label_;
	Button narrator_Slise_Bar_Test_Sound_Button_;

	//title for scene text
	Text headding_text_;


};

#endif

