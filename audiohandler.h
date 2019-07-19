#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include <cstdlib>
#include <map>
#include <string>
#include <utility>

#include <mmdeviceapi.h>
#include <functiondiscoverykeys_devpkey.h>
#include <wchar.h>

using std::map;
using std::make_pair;
using std::pair;
using std::string;
using std::wcstombs;

class AudioHandler {
public:
    AudioHandler();
    virtual ~AudioHandler();
    map<string, string> GetAudioDevices();

private:
    map<string, string> audio_devices_;
    HRESULT CoCreateInstance(REFCLSID, LPUNKNOWN, DWORD, REFIID, LPVOID);
    void PropVariantClear(PROPVARIANT*);
    void CoTaskMemFree(wchar_t*);
};

#endif // AUDIOHANDLER_H
