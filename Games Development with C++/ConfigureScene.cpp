#include "ConfigureScene.h"
#include"WhiteScene.h"

#include"SceneManager.h"
#define SceneManager  SceneManager::Instance_()

#include"SoundManager.h"
#define SoundManager  SoundManager::Instance_()

#include<SFML/Graphics.hpp>

//init the static flags for AI and P2
bool ConfigureScene::P2_On_{ false };
bool ConfigureScene::AI_On_{ false };


ConfigureScene::ConfigureScene()
//init list for widget setup
	:menu_button_({ 1040, 930 }, "Menu", { 1123, 945 }, 60, sf::Color::White, { 330, 100 }),
	headding_text_("Configure Menu", { 700, 100 }, 0, 0, 35, sf::Color::White),

	BG_Slidebar(sf::Vector2f(510, 230), sf::Vector2f(900, 60), sf::Color::White),
	BG_Slide_Bar_Label_("BG Music :", {220, 260}, 0, 0, 30, sf::Color::White),

	UI_Slidebar(sf::Vector2f(510, 430), sf::Vector2f(900, 60), sf::Color::White),
	UI_Slide_Bar_Label_("UI Sounds :", { 190, 460 }, 0, 0, 30, sf::Color::White),
	UI_Slise_Bar_Test_Sound_Button_({ 1430, 430 }, "Play", { 1470, 430 }, 50, sf::Color::White, {200, 60}),


	SoundEffects_Slidebar(sf::Vector2f(510, 630), sf::Vector2f(900, 60), sf::Color::White),
	SoundEffects_Slide_Bar_Label_("Sound fx :", { 213, 660 }, 0, 0, 30, sf::Color::White),
	SoundEffects_Slise_Bar_Test_Sound_Button_({ 1430, 630 }, "Play", { 1470, 630 }, 50, sf::Color::White, { 200, 60 }),

	narrator_Slidebar(sf::Vector2f(510, 830), sf::Vector2f(900, 60), sf::Color::White),
	narrator_Slide_Bar_Label_("Narrator :", { 188, 860 }, 0, 0, 30, sf::Color::White),
	narrator_Slise_Bar_Test_Sound_Button_({ 1430, 830 }, "Play", { 1470, 830 }, 50, sf::Color::White, { 200, 60 }),

	AI_CheckBox_({ 685, 965 }, {40, 40}),
	AI_CheckBox_Text_("AI :", {600, 985}, 0, 0, 30U, sf::Color::White),

	P2_CheckBox_({ 955, 965 }, { 40, 40 }),
	P2_CheckBox_Text_("P2 :", { 870, 985 }, 0, 0, 30U, sf::Color::White)


{
}

void ConfigureScene::Update_()
{
	//update all widgets
	menu_button_.Update();
	BG_Slidebar.Update_();
	UI_Slidebar.Update_();
	SoundEffects_Slidebar.Update_();
	narrator_Slidebar.Update_();
	AI_CheckBox_.Update();
	P2_CheckBox_.Update();
	UI_Slise_Bar_Test_Sound_Button_.Update();
	SoundEffects_Slise_Bar_Test_Sound_Button_.Update();
	narrator_Slise_Bar_Test_Sound_Button_.Update();

	//check for AI checkbox click
	AI_CheckBox_.Get_Is_Clicked_();
	
	//if AI checkbox toggled
	if(AI_CheckBox_.Get_Is_Toggled_())
	{
		//enable AI flag
		AI_On_ = true;
	}
	else
	{
		//disable AI flag
		AI_On_ = false;
	}

	//check for P2 checkbox clicked 
	P2_CheckBox_.Get_Is_Clicked_();

	//if P2 checkbox toggled
	if(P2_CheckBox_.Get_Is_Toggled_())
	{
		//enable P2
		P2_On_ = true;
	}
	else
	{
		//disable P2
		P2_On_ = false;
	}

	//if menu button clicked
	if (menu_button_.Get_Is_Clicked_())
	{
		//cast top of scene stack to white scene
		Scene* is_click_animation_in_use_ = (dynamic_cast<WhiteScene*>(SceneManager.Peak_Scene_().get()));
		
		//if white scene is running
		if (is_click_animation_in_use_)
		{
			//take white scene from scene stack
			SceneManager.Pop_Scene_();
		}

		//pop the config scene
		SceneManager.Pop_Scene_();

		//load the start screen scene
		SceneManager.Load_Scene_("StartScreen");

		//load the white screen scene
		SceneManager.Load_Scene_("WhiteScene");

		//exit the runction
		return;
	}

	//set the volume for each sound object using the values found in the slide bar objects
	SoundManager.Set_Volume_Level_For_Sound_Instance_In_Map_("BG_Music", BG_Slidebar.Get_Percentage_()*100);
	SoundManager.Set_Volume_Level_For_Sound_Instance_In_Map_("ButtonClick", UI_Slidebar.Get_Percentage_() * 100);
	
	SoundManager.Set_Volume_Level_For_Sound_Instance_In_Map_("ElectricSoundEffect", SoundEffects_Slidebar.Get_Percentage_() * 100);
	SoundManager.Set_Volume_Level_For_Sound_Instance_In_Map_("FoodCollection", SoundEffects_Slidebar.Get_Percentage_() * 100);
	SoundManager.Set_Volume_Level_For_Sound_Instance_In_Map_("Killed_Snake_Sound", SoundEffects_Slidebar.Get_Percentage_() * 100);

	SoundManager.Set_Volume_Level_For_Sound_Instance_In_Map_("30_secconds", narrator_Slidebar.Get_Percentage_() * 100);
	SoundManager.Set_Volume_Level_For_Sound_Instance_In_Map_("60_secconds", narrator_Slidebar.Get_Percentage_() * 100);


	//check UI sound play button for clicks
	UI_Slise_Bar_Test_Sound_Button_.Get_Is_Clicked_(true);


	//if sound effects button is clicked
	if (SoundEffects_Slise_Bar_Test_Sound_Button_.Get_Is_Clicked_(false))
	{
		//have a static varible p used to cycle through different sound effects 
		static int p = 0;

		if (p == 0)
		{
			SoundManager.Play_Sound_("FoodCollection");
			p++;
		}
		else if (p == 1)
		{
			SoundManager.Play_Sound_("Killed_Snake_Sound");
			p++;
		}
		else
		{
			SoundManager.Play_Sound_("ElectricSoundEffect");
			p = 0;
		}

	}

	//if narrator button is clicked 
	if (narrator_Slise_Bar_Test_Sound_Button_.Get_Is_Clicked_(false))
	{
		//use the static variable j to cycle through different sounds 
		static int j = 0;
		if (j == 0)
		{
			SoundManager.Play_Sound_("30_secconds");
			j++;
		}
		else
		{
			SoundManager.Play_Sound_("60_secconds");
			j--;
		}

	}

}

void ConfigureScene::Render_()
{
	//draw all the widgets to the window
	menu_button_.Render();
	headding_text_.Render_();

	AI_CheckBox_.Render();
	AI_CheckBox_Text_.Render_();

	P2_CheckBox_.Render();
	P2_CheckBox_Text_.Render_();

	BG_Slidebar.Render_();
	BG_Slide_Bar_Label_.Render_();

	UI_Slidebar.Render_();
	UI_Slide_Bar_Label_.Render_();
	UI_Slise_Bar_Test_Sound_Button_.Render();

	SoundEffects_Slidebar.Render_();
	SoundEffects_Slide_Bar_Label_.Render_();
	SoundEffects_Slise_Bar_Test_Sound_Button_.Render();

	narrator_Slidebar.Render_();
	narrator_Slide_Bar_Label_.Render_();
	narrator_Slise_Bar_Test_Sound_Button_.Render();
}

void ConfigureScene::Init_()
{
}

void ConfigureScene::De_Init_()
{
	menu_button_.Reset_Button_();
}
