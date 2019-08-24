#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#pragma comment(lib, "Ole32.lib")

#include <mmdeviceapi.h>
#include <functiondiscoverykeys_devpkey.h>
#include <combaseapi.h>
#include <objbase.h>
#include <string>
#include <winerror.h>
#include <vector>

using std::vector;

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
    vector<AudioDevice> GetAudioDevices();

private:
    IMMDeviceEnumerator *pEnum;
    vector<AudioDevice> devices;
    void AddDevice(IMMDevice *device, LPCWSTR pwszID);
    void Init();
};

#endif // AUDIOMANAGER_H
