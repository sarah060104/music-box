#ifndef BEATBOX_61601_AUDIOPLAYER_H
#define BEATBOX_61601_AUDIOPLAYER_H
#include <vector>

/**
 * Audio Player pour jouer sons d'un utilisteur
 * stocke le son,
 * gestion des frames, paramêtres
 */
class AudioPlayer {

public:

    void play();
    void stop();

    void setReverse(bool reversed);
    AudioPlayer ();


    void process(float* outputBuffer, int nbframes);
    void loadWav(const std::string& path);
    void trigger();

    bool isPlaying();
    int getChannels();

private:
    std::vector<float> buffer;

    int position = 0;
    bool playing = false;
    bool reverse = false;
    int channels = 1;

    float volume = 1.0f;

};


#endif //BEATBOX_61601_AUDIOPLAYER_H