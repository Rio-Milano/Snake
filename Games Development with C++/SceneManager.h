#ifndef  SceneManager_H
#define SceneManager_H

#include <vector>
#include <unordered_map>
#include<string>
#include<memory>
#include"Scene.h"






class SceneManager
{
public:

	//get the instance of the sound manager
	static SceneManager& Instance_();
	
	//get if a scene is on the stack display
	const bool Is_Scene_Active_(const std::string& scene_name_) ;

	//load a scene onto the stack
	void Load_Scene_(std::string scene_name_);

	/*
	Utility Functions
	*/

	//update the scene
	void Update_Scenes_();

	//draw scene components onto the window
	void Render_Scenes_();

	//take the top scene from the stack and discard it
	void Pop_Scene_();
	
	//peak what scene is on top of the stack
	inline std::shared_ptr<Scene> Peak_Scene_()const { return this->list_of_visual_overlays_[list_of_visual_overlays_.size() - 1]; };


private:
	//ctors and dtors
	SceneManager();
	~SceneManager();

	//a stack of all scenes (not used std::stack as was unaware tit existed at the time)
	std::vector< std::shared_ptr<Scene>> list_of_visual_overlays_;

	//a hash map mapping names of scenes to the location they are on the heap
	std::unordered_map<std::string,  std::shared_ptr<Scene>> scenes_;

};

#endif 

