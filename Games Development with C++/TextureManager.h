#ifndef Texture_Manager_H
#define TextureManager_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include<string>

/*
this class embraces the use of the flyweight pattern by managing textures needed in one place
*/

class TextureManager
{
public:
		

	//get the one instance of the texture manager
	static TextureManager& Instance_();

	//get a texture by name
	inline const sf::Texture& Get_Texture_ (const std::string& texture_name_) {return *textures_[texture_name_];};

	//get an animation by name
	inline const sf::Texture& Get_Texture_From_Animation_ (const std::string& animation_name_, const int& animation_index_){return *(animations_[animation_name_])[animation_index_];}

	//load a texture into memory
	void Load_Texture_Into_Memory_(const std::string& file_name_, const std::string& file_type_, const std::string& texture_name_);
	
	//load an animation into memory
	void Load_Animation_Into_Memory(const std::string& file_name_abbreviation_, const std::string& file_type_, const std::string& animation_name_, const size_t& total_animation_states_);
		
private:
	//Ctors & Dtors
	TextureManager();
	~TextureManager();

	//Texture Data

	//hash map to map names of texures to textures on the heap
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures_;

	//hash map to map names of animations to a vector of textures for the animation
	std::unordered_map<std::string, std::vector<std::shared_ptr<sf::Texture>>> animations_;
};

#endif