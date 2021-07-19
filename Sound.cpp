#pragma once

class Sound
{
  private:
    cs_context_t* ctx;
    //TODO refactor to support more sounds flexibly. perhaps store in dict obj?
    cs_loaded_sound_t ambFile;
    cs_playing_sound_t ambSound;

  public:
    Sound();
    ~Sound();
};

//default constructor
Sound::Sound()
{
  //do not create more than one context or mix thread!
  ctx = cs_make_context(NULL, 44100, 2056, 0, NULL); //create sound context
  cs_spawn_mix_thread(ctx); //create mixing thread - required to schedule sounds

  ambFile = cs_load_wav("assets/whale-background-sounds_16bitDepth.wav"); //load sound file
  ambSound = cs_make_playing_sound(&ambFile); //prepare sound object

  //TODO move out to separate method. temporary for POC
  cs_insert_sound(ctx, &ambSound); //start sound object
  cs_loop_sound(&ambSound, 1); //make ambient track loop
}

//destructor
Sound::~Sound()
{
  //TODO refactor to support more sounds flexibly.
  cs_free_sound(&(ambFile)); //close sound file
}
