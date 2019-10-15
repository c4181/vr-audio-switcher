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
    vector<AudioDevice> GetPlaybackDevices();
    vector<AudioDevice> GetRecordingDevices();

private:
    IMMDeviceEnumerator *pEnum;
    vector<AudioDevice> playback_devices_;
    vector<AudioDevice> recording_devices_;
    void AddPlaybackDevice(IMMDevice *device, LPCWSTR pwszID);
    void AddRecordingDevice(IMMDevice *device, LPCWSTR pwszID);
    HRESULT InitializeDeviceEnumerator();
    HRESULT LoadPlaybackDevices();
    HRESULT LoadRecordingDevices();
    void Init();
};

#endif // AUDIOMANAGER_H
