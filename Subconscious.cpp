#define OLC_PGE_APPLICATION
#define USE_OPEN_AL
#include <olcPixelGameEngine.h>
#include <olcPGEX_Graphics2D.h>
#include <olcPGEX_PopUpMenu.h>
#include <olcPGEX_TransformedView.h>

#define _CRT_SECURE_NO_WARNINGS
#include <SDL2/SDL.h>

#define CUTE_SOUND_FORCE_SDL
#define CUTE_SOUND_IMPLEMENTATION
#include <cute_sound.h>


class Subconscious : public olc::PixelGameEngine
{
public:
	Subconscious()
	{
		sAppName = "Subconscious";
	}

public:

  cs_context_t* ctx;
  cs_loaded_sound_t ambFile;
  cs_playing_sound_t ambSound;

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

    //olc::ResourcePack* pack = new olc::ResourcePack();

    //pack->SavePack("respak.dat", "#");

    ctx = cs_make_context(NULL, 44100, 2056, 0, NULL);

    ambFile = cs_load_wav("assets/whale-background-sounds_16bitDepth.wav");
    ambSound = cs_make_playing_sound(&ambFile);

    cs_spawn_mix_thread(ctx);

    cs_insert_sound(ctx, &ambSound);

    cs_loop_sound(&ambSound, 1);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand()% 255));
		return true;
	}
};


int main(int argc, char **argv)
{
	Subconscious game;
	if (game.Construct(256, 240, 4, 4, false, true, false))
		game.Start();

  cs_free_sound(&(game.ambFile));
	return 0;
}
