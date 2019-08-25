#include "audiomanager.h"

#ifndef RETURN_ON_ERROR
#define RETURN_ON_ERROR(hres) \
    if(FAILED(hres)) {goto Exit;}
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(punk)  \
    if ((punk) != nullptr) \
    { (punk) -> Release(); (punk) = nullptr; }
#endif

AudioManager::AudioManager() :pEnum(nullptr) {
    Init();
}
/*
AudioManager::~AudioManager() {
    ReleaseDeviceEnumerator();
    delete client;
}
*/
void AudioManager::Init() {
    InitializeDeviceEnumerator();
    LoadPlaybackDevices();
    LoadRecordingDevices();
}

HRESULT AudioManager::InitializeDeviceEnumerator()
{
    HRESULT hr = S_OK;
    if(!pEnum)
    {
        hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL,
            CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnum);
    }
    return hr;
}

HRESULT AudioManager::LoadPlaybackDevices() {
    playback_devices_.clear();
    IMMDeviceCollection *devicesCollection = NULL;
    IMMDevice *device = NULL;
    LPWSTR pwszID = NULL;
    HRESULT hr = pEnum -> EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, &devicesCollection);
    RETURN_ON_ERROR(hr)
    UINT count;
    hr = devicesCollection -> GetCount(&count);
    RETURN_ON_ERROR(hr)

    for (UINT i = 0; i < count; ++i) {
        hr = devicesCollection -> Item(i, &device);
        RETURN_ON_ERROR(hr)

        hr = device -> GetId(&pwszID);
        RETURN_ON_ERROR(hr)
        AddPlaybackDevice(device, pwszID);

        CoTaskMemFree(pwszID);
        pwszID = NULL;
        SAFE_RELEASE(device);
    }

    Exit:
        CoTaskMemFree(pwszID);
        SAFE_RELEASE(devicesCollection)
        SAFE_RELEASE(device)
        return hr;
}

HRESULT AudioManager::LoadRecordingDevices() {
    recording_devices_.clear();
    IMMDeviceCollection *devicesCollection = NULL;
    IMMDevice *device = NULL;
    LPWSTR pwszID = NULL;
    HRESULT hr = pEnum -> EnumAudioEndpoints(eCapture, DEVICE_STATE_ACTIVE, &devicesCollection);
    RETURN_ON_ERROR(hr)
    UINT count;
    hr = devicesCollection -> GetCount(&count);
    RETURN_ON_ERROR(hr)

    for (UINT i = 0; i < count; ++i) {
        hr = devicesCollection -> Item(i, &device);
        RETURN_ON_ERROR(hr)

        hr = device -> GetId(&pwszID);
        RETURN_ON_ERROR(hr)
        AddRecordingDevice(device, pwszID);

        CoTaskMemFree(pwszID);
        pwszID = NULL;
        SAFE_RELEASE(device);
    }

    Exit:
        CoTaskMemFree(pwszID);
        SAFE_RELEASE(devicesCollection)
        SAFE_RELEASE(device)
        return hr;
}

void AudioManager::AddPlaybackDevice (IMMDevice *device, LPCWSTR pwszID) {
    IPropertyStore *pProps = NULL;
    AudioDevice audio_device;
    HRESULT hr = device -> OpenPropertyStore(STGM_READ, &pProps);
    RETURN_ON_ERROR(hr)

    PROPVARIANT varName;
    PropVariantInit(&varName);
    hr = pProps -> GetValue(PKEY_Device_FriendlyName, &varName);
    RETURN_ON_ERROR(hr)

    audio_device.deviceID.assign(pwszID);
    audio_device.deviceName.assign(varName.pwszVal);

    playback_devices_.push_back(audio_device);

    Exit:
        PropVariantClear(&varName);
        SAFE_RELEASE(pProps)

}

void AudioManager::AddRecordingDevice (IMMDevice *device, LPCWSTR pwszID) {
    IPropertyStore *pProps = NULL;
    AudioDevice audio_device;
    HRESULT hr = device -> OpenPropertyStore(STGM_READ, &pProps);
    RETURN_ON_ERROR(hr)

    PROPVARIANT varName;
    PropVariantInit(&varName);
    hr = pProps -> GetValue(PKEY_Device_FriendlyName, &varName);
    RETURN_ON_ERROR(hr)

    audio_device.deviceID.assign(pwszID);
    audio_device.deviceName.assign(varName.pwszVal);

    recording_devices_.push_back(audio_device);

    Exit:
        PropVariantClear(&varName);
        SAFE_RELEASE(pProps)

}

vector<AudioDevice> AudioManager::GetPlaybackDevices() {
    return playback_devices_;
}

vector<AudioDevice> AudioManager::GetRecordingDevices() {
    return recording_devices_;
}

