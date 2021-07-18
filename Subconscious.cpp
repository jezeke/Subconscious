#include "Subconscious.hpp"

class Subconscious : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "Subconscious";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

    olc::ResourcePack* pack = new olc::ResourcePack();
    pack->AddFile("./assets/whale-background-sounds.wav");

    //pack->SavePack("respak.dat", "#");

    int ambId = olc::SOUND::LoadAudioSample("assets/whale-background-sounds.wav");
    olc::SOUND::PlaySample(ambId, true); //loop ambient music
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


int main()
{
	Subconscious game;
	if (game.Construct(256, 240, 4, 4))
		game.Start();

	return 0;
}
