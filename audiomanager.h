#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <mmdeviceapi.h>
#include <functiondiscoverykeys_devpkey.h>
#include <combaseapi.h>
#include <string>
#include <winerror.h>
#include <vector>

struct Device;

struct AudioDevice {
    std::wstring deviceID;
    std::wstring deviceName;
    bool missing;
    AudioDevice() :deviceID(L""), deviceName(L""), missing(false) {}
};

class AudioManager
{
public:
    AudioManager();
    HRESULT InitializeDeviceEnumerator();
    HRESULT LoadAudioDevices();

private:
    IMMDeviceEnumerator *pEnum;
    std::vector<AudioDevice> devices;
    void AddDevice(IMMDevice *device, LPCWSTR pwszID);
};

#endif // AUDIOMANAGER_H
