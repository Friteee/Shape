#include <SDl_mixer.h>
#include <string>
#include <memory>

namespace audio
{

/** \brief Sound class to play small audio files
 *
 */


class Sound
{

public:
    void init(std::string init_sound);
    void play();
    ~Sound();
    static void set_volume(unsigned int volume);
    static void change_volume(int amount);
private:
    std::shared_ptr<Mix_Chunk *> sound_;
    static unsigned int volume_;

};

}
