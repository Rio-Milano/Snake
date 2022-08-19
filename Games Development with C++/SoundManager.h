#ifndef SoundManager_H
#define SoundManager_H
#include <SFML/Audio.hpp>
#include <unordered_map>
#include<utility>
#include<string>
#include<iostream>
	class SoundManager
	{
	public:

		//get instance of sound manager 
		static SoundManager& Instance_();

		//takes the name of a sound and plays it
		void Play_Sound_(const std::string& sound_);

		//add a sound with some params to the hash map
		void Add_Sound(std::string file_name_, std::string file_type_, bool set_loop_, std::string sound_name_, int volume_ =100 );

		//sets the volume level for a sound object by name
		void Set_Volume_Level_For_Sound_Instance_In_Map_(const std::string& sound_, const float& level_);

	private:
		//ctors and dtors
		SoundManager();
		~SoundManager();

		//a hash map mapping the name of a sound file to a pair of buffer and sound obj
		std::unordered_map<std::string, std::pair<std::shared_ptr<sf::Sound>, std::shared_ptr<sf::SoundBuffer>>> sounds_;
	};

#endif

