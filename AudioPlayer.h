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
    void loadWav(const std::string& path);

    void play();
    void stop();

    void setVolume(float v);
    void setReverse(bool r);

    void getNextFrames(float* out, int numFrames);

private:
    std::vector<float> buffer;

    int position = 0;
    bool playing = false;
    bool reverse = false;

    float volume = 1.0f;

    float applyVolumeToSample(float sample) const;
};


#endif //BEATBOX_61601_AUDIOPLAYER_H