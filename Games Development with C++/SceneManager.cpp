#include "SceneManager.h"

#include "Background.h"
#include"GameScene.h"
#include "StartScreen.h"
#include"GameEndScene.h"
#include"WhiteScene.h"
#include"ConfigureScene.h"


//ctors and dtors
 SceneManager::SceneManager()
{
	 //load all of the scenes onto the heap and load the scenes for the start screen
	scenes_["Background"] = std::make_shared < Background>();
	Load_Scene_("Background");

	scenes_["StartScreen"] = std::make_shared < StartScreen>();
	Load_Scene_("StartScreen");

	scenes_["GameScene"] = std::make_shared < GameScene>();
	scenes_["GameEndScene"] = std::make_shared < GameEndScreen>();
	scenes_["WhiteScene"] = std::make_shared < WhiteScene>();
	Load_Scene_("WhiteScene");
	scenes_["ConfigureScene"] = std::make_shared<ConfigureScene>();



};

 SceneManager::~SceneManager()
{
}

//get the instance of the scene manager
 SceneManager&  SceneManager::Instance_()
{
	//one instanc of scene manager 
	static SceneManager scene_manager_;

	//return the one instance of the scene manager
	return scene_manager_;
}

//load a scene onto the stack
void  SceneManager::Load_Scene_(std::string scene_name_)
{
	//add the scene object to the stack
	list_of_visual_overlays_.emplace_back(scenes_[scene_name_]);

	//init the scene object
	list_of_visual_overlays_[list_of_visual_overlays_.size() - 1]->Init_();
}
const bool  SceneManager::Is_Scene_Active_(const std::string& scene_name_) 
{
	//get the scene from the heap to check
	std::shared_ptr<Scene> scene_ = scenes_[scene_name_];

	//loop through all of the scenes 
	for (const std::shared_ptr<Scene>& scene__ : list_of_visual_overlays_)
	{
		// if the scene is in the heap then return true for found scene
		if (scene__ == scene_)
			return true;
	}
	//return false for not found the scene
	return false;
}

//update the scene
void  SceneManager::Update_Scenes_()
{
	//loop through all the scenes
	for ( const std::shared_ptr<Scene> scene_ : list_of_visual_overlays_)
		//update the scene
		scene_->Update_();
}

void  SceneManager::Render_Scenes_()
{
	//loop through all the scenes
	for ( const std::shared_ptr<Scene> scene_ : list_of_visual_overlays_)
		//render the scene
		scene_->Render_();

}

void  SceneManager::Pop_Scene_()
{
	//take the scene from the top of the stack and unload it
	list_of_visual_overlays_[list_of_visual_overlays_.size() - 1]->De_Init_();

	//remove the scene from the top of the stack
	list_of_visual_overlays_.pop_back();

};
