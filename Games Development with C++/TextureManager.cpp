#include "TextureManager.h"

//Ctors & Dtors
 TextureManager::TextureManager()
{
	//load in the snake textures
	Load_Texture_Into_Memory_("Assets_/Textures_/Snakes_/Snake_1_Texture/HEAD", ".png", "A_Default_Head_Texture");
	Load_Texture_Into_Memory_("Assets_/Textures_/Snakes_/Snake_1_Texture/CROSS_HEAD", ".png", "A_Default_Head_TextureDEAD");
	Load_Texture_Into_Memory_("Assets_/Textures_/Snakes_/Snake_1_Texture/BODY", ".png", "A_Default_Body_Texture");

	Load_Texture_Into_Memory_("Assets_/Textures_/Snakes_/Snake_2_Texture/HEAD", ".png", "B_Default_Head_Texture");
	Load_Texture_Into_Memory_("Assets_/Textures_/Snakes_/Snake_2_Texture/CROSS_HEAD", ".png", "B_Default_Head_TextureDEAD");
	Load_Texture_Into_Memory_("Assets_/Textures_/Snakes_/Snake_2_Texture/BODY", ".png", "B_Default_Body_Texture");

	Load_Texture_Into_Memory_("Assets_/Textures_/Snakes_/Snake_3_Texture/HEAD", ".png", "C_Default_Head_Texture");
	Load_Texture_Into_Memory_("Assets_/Textures_/Snakes_/Snake_3_Texture/CROSS_HEAD", ".png", "C_Default_Head_TextureDEAD");
	Load_Texture_Into_Memory_("Assets_/Textures_/Snakes_/Snake_3_Texture/BODY", ".png", "C_Default_Body_Texture");

	Load_Texture_Into_Memory_("Assets_/Textures_/Snakes_/Snake_4_Texture/HEAD", ".png", "D_Default_Head_Texture");
	Load_Texture_Into_Memory_("Assets_/Textures_/Snakes_/Snake_4_Texture/CROSS_HEAD", ".png", "D_Default_Head_TextureDEAD");
	Load_Texture_Into_Memory_("Assets_/Textures_/Snakes_/Snake_4_Texture/BODY", ".png", "D_Default_Body_Texture");

	Load_Texture_Into_Memory_("Assets_/Textures_/Snakes_/Snake_5_Texture/HEAD", ".png", "Player_Head_Texture");
	Load_Texture_Into_Memory_("Assets_/Textures_/Snakes_/Snake_5_Texture/HEAD", ".png", "Player_Head_TextureDEAD");
	Load_Texture_Into_Memory_("Assets_/Textures_/Snakes_/Snake_5_Texture/BODY", ".png", "Player_Body_Texture");

	Load_Texture_Into_Memory_("Assets_/Textures_/Snakes_/Snake_6_Texture/HEAD", ".png", "2Player_Head_Texture");
	Load_Texture_Into_Memory_("Assets_/Textures_/Snakes_/Snake_6_Texture/HEAD", ".png", "2Player_Head_TextureDEAD");
	Load_Texture_Into_Memory_("Assets_/Textures_/Snakes_/Snake_6_Texture/BODY", ".png", "2Player_Body_Texture");

	Load_Texture_Into_Memory_("Assets_/Textures_/Snakes_/dead_snake", ".png", "dead_snake");

	Load_Texture_Into_Memory_("Assets_/Textures_/Collectables_/Apple_/Apple_Texture", ".png", "Apple_Texture");
	Load_Texture_Into_Memory_("Assets_/Textures_/Collectables_/Apple_/Apple_Texture_Invert", ".png", "Apple_Texture_Invert");

	Load_Texture_Into_Memory_("Assets_/Textures_/Collectables_/Battery_/Battery_Texture", ".png", "Battery_Texture");
	Load_Texture_Into_Memory_("Assets_/Textures_/Collectables_/Battery_/Battery_Texture_Invert", ".png", "Battery_Texture_Invert");

	Load_Texture_Into_Memory_("Assets_/Textures_/Overlays_/Grid_Overlay_Texture_", ".png", "Grid_Overlay_Texture_");
	Load_Texture_Into_Memory_("Assets_/Textures_/Overlays_/Podium_Texture", ".png", "Podium_Texture");

}

 TextureManager::~TextureManager()
{

}

//Getter Functions
 TextureManager&  TextureManager::Instance_()
{
	static TextureManager texture_manager_;
	return texture_manager_;
}

//loads a texture into memory
void  TextureManager::Load_Texture_Into_Memory_(const std::string& file_name_, const std::string& file_type_, const std::string& texture_name_)
{
	//cretate a texture object to put on the heap
	std::shared_ptr<sf::Texture> texture_ = std::make_shared<sf::Texture>();
	
	//load a texture into that texture object
	texture_->loadFromFile(file_name_ + file_type_);

	//add the texture to the hash map
	textures_[texture_name_] = texture_;
}

//load an animation into memory
void  TextureManager::Load_Animation_Into_Memory(const std::string& file_name_abbreviation_, const std::string& file_type_, const std::string& animation_name_, const size_t& total_animation_states_)
{
	//used for a single pool texture
	std::shared_ptr<sf::Texture> texture_;

	//loop through the textures needed to load the animation
	for (size_t i = 0; i < total_animation_states_; i++)
	{
		//make a new texture and assign it to texture_
		texture_ = std::make_shared<sf::Texture>();

		//load a texture into the new texture
		texture_->loadFromFile(file_name_abbreviation_ + std::to_string(i) + file_type_);
		
		//append that texture to the vector assigned to the animation name in the hash map of animations 
		animations_[animation_name_].push_back(texture_);
	}
}
