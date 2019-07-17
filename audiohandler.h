#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include <map>
#include <utility>

#include <mmdeviceapi.h>
#include <functiondiscoverykeys_devpkey.h>

using std::map;
using std::make_pair;
using std::pair;

class AudioHandler
{
public:
    AudioHandler();
    map<char[], char[]> GetAudioDevices();

private:
    map<char[], char[]> audio_devices_;
};

#endif // AUDIOHANDLER_H
