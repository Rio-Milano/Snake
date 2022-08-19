#ifndef SCENE_H
#define SCENE_H

/*

this is a base class that all other scenes can implement and then they are handeled by the scene manager

*/

class Scene
{
public:
	//will draw any components to the window
	virtual void Render_() = 0;

	//will update any components on the window
	virtual void Update_() = 0;

	//loads any content the scene needs
	virtual void Init_() = 0;

	//unloads any content that the scene needs 
	virtual void De_Init_() = 0;
};


#endif

