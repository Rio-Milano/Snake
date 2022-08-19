#include "SoundManager.h"

//ctors and dtors
 SoundManager::SoundManager()
{
	 //add all sound assets to the game
	Add_Sound("Assets_/Sounds_/BG_Music", ".wav", 1, "BG_Music", 0);
	Add_Sound("Assets_/Sounds_/ButtonClick", ".wav", 0, "ButtonClick", 0);
	Add_Sound("Assets_/Sounds_/ElectricSoundEffect", ".wav", false, "ElectricSoundEffect", 0);
	Add_Sound("Assets_/Sounds_/FoodCollection", ".wav", 0, "FoodCollection", 0);
	Add_Sound("Assets_/Sounds_/30_secconds", ".wav", 0, "30_secconds", 0);
	Add_Sound("Assets_/Sounds_/60_secconds", ".wav", 0, "60_secconds", 0);
	Add_Sound("Assets_/Sounds_/Killed_Snake_Sound", ".wav", 0, "Killed_Snake_Sound", 0);
}


 SoundManager::~SoundManager()
{

}


 SoundManager&  SoundManager::Instance_()
{
	 //one instance of sound manager
	static SoundManager sound_manager_;
	return sound_manager_;
}

//setter functions
void  SoundManager::Play_Sound_(const std::string& sound_)
{
	//look the sound up in the hash map then play it
	sounds_[sound_].first->play();
}


void  SoundManager::Add_Sound(std::string file_name_, std::string file_type_, bool set_loop_, std::string sound_name_, int volume_)
{
	//variables used to create the objects for the sound to work
	std::shared_ptr<sf::Sound> sound_;
	std::shared_ptr<sf::SoundBuffer> sound_buffer_;
	std::pair<std::shared_ptr<sf::Sound>, std::shared_ptr<sf::SoundBuffer>> sound_pair_;

	//make a sound buffer
	sound_buffer_ = std::make_shared<sf::SoundBuffer>();

	//load some sound into the sound buffer
	sound_buffer_->loadFromFile(file_name_+file_type_);

	//make a sound object
	sound_ = std::make_shared<sf::Sound>();

	//set the buffer of the sound object
	sound_->setBuffer(*sound_buffer_);

	//if loop is set then enable loop
	set_loop_ ?  sound_->setLoop(1) : sound_->setLoop(0);
	
	//set volume level of sound
	sound_->setVolume(float(volume_));

	//coupple the sound and buffer into a pair
	sound_pair_ = { sound_, sound_buffer_ };

	//add the sound and buffer pair into the hash map
	sounds_[sound_name_] = sound_pair_;
}

void  SoundManager::Set_Volume_Level_For_Sound_Instance_In_Map_(const std::string& sound_, const float& level_)
{
	//look up sound in hash map and set its volume level
	sounds_[sound_].first->setVolume(level_);
}
