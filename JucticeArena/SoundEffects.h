#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_audio.h>

struct SoundEffect
{
	ALLEGRO_SAMPLE* sound;
	SoundEffect(const char* soundname)
	{
		sound = al_load_sample(soundname);
		
		al_reserve_samples(1);
	}

	void play()
	{
		if (sound != nullptr)
		{
			al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
		}
	}
    void long_play()
    {
        if (sound != nullptr)
        {
            al_play_sample(sound, 3.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        }
    }
};