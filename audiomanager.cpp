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

AudioManager::AudioManager() {
    Init();
}

void AudioManager::Init() {
    LoadAudioDevices();
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

HRESULT AudioManager::LoadAudioDevices() {
    devices.clear();
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
        AddDevice(device, pwszID);

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

void AudioManager::AddDevice (IMMDevice *device, LPCWSTR pwszID) {
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

    devices.push_back(audio_device);

    Exit:
        PropVariantClear(&varName);
        SAFE_RELEASE(pProps)

}

vector<AudioDevice> AudioManager::GetAudioDevices() {
    return devices;
}


