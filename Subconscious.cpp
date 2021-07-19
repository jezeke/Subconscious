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

		world.simulate(fElapsedTime);
		sub.simulate(fElapsedTime);

		uiRadar.render(fElapsedTime, world, sub);
		uiBlinker.render(fElapsedTime, world, sub);
		uiGauges.render(fElapsedTime, world, sub);
		uiPanels.render(fElapsedTime, world, sub);

		return true;
	}
};

int main(int argc, char **argv)
{
	Subconscious game;
	if (game.Construct(1080/2, 720/2, 2, 2, false, false, false))
		game.Start();

	return 0;
}
