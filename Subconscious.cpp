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

#include "SubSystems.cpp"
#include "World.cpp"
#include "Sound.cpp"

#include "uiBlinker.cpp"
#include "uiGauges.cpp"
#include "uiPanels.cpp"
#include "uiRadar.cpp"



class Subconscious : public olc::PixelGameEngine
{
public:
	Subconscious()
	{
		sAppName = "Subconscious";
	}

public:

	Sound soundEngine;

	World world;
	SubSystems sub;

	uiRadar uiRadar;
	uiBlinker uiBlinker;
	uiGauges uiGauges;
	uiPanels uiPanels;

	double runtime = 0;

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

    //olc::ResourcePack* pack = new olc::ResourcePack();
    //pack->SavePack("respak.dat", "#");

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		runtime += fElapsedTime; //seconds since program started

		sub.simulate(runtime);
		world.simulate(runtime, sub);

		/*uiRadar.render(runtime, world, sub);
		uiBlinker.render(runtime, world, sub);
		uiGauges.render(runtime, world, sub);
		uiPanels.render(runtime, world, sub);*/

		int viewZ = (int)(runtime*8) % world.sizeZ; //view next frame every 8th of a second

		for(uint32_t x = 0; x < world.sizeX; x++)
		{
			for(uint32_t y = 0; y < world.sizeY; y++)
			{
				if(world.data[x][y][viewZ])
					Draw(x, y, olc::Pixel(255, 255, 255));
				else
					Draw(x, y, olc::Pixel(0,0,0));

				//int tint = world.data[x][y][viewZ];
				//Draw(x, y, olc::Pixel(tint, tint, tint));
			}
		}

		return true;
	}
};

int main(int argc, char **argv)
{
	Subconscious game;

	//if(game.Construct(1080/2, 720/2, 2, 2, false, false, false))
	if(game.Construct(game.world.sizeX, game.world.sizeY, 2, 2, false, false, false))
		game.Start();

	return 0;
}
