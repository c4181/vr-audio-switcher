#include "mainwindow.h"
#include "ui_mainwindow.h"

#define SETTINGS_FILE_NAME "audio_settings.ini"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GetAllAudioDevices();
    GetSavedAudioDevices();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_setupMenu_triggered() {
  SetupDialog dialog(this);
  dialog.PopulateAudioDevices(playback_devices, recording_devices, saved_vr_record_selection, saved_vr_playback_selection, saved_desktop_record_selection, saved_desktop_playback_selection);
  int dialog_code = dialog.exec();

  if (dialog_code == QDialog::Accepted) {
     vr_playback_device = dialog.GetVrPlaybackDevice();
     vr_recording_device = dialog.GetVrRecordingDevice();

     desktop_playback_device = dialog.GetDesktopPlaybackDevice();
     desktop_recording_device = dialog.GetDesktopRecordingDevice();
  }
  dialog.close();
}

HRESULT MainWindow::SetDevice(const wstring& id) {
    IPolicyConfig *pPolicyConfig;

    HRESULT hr = CoCreateInstance(__uuidof(CPolicyConfigClient), nullptr, CLSCTX_ALL,
                                  __uuidof(IPolicyConfig), reinterpret_cast<LPVOID*>(&pPolicyConfig));

    if (SUCCEEDED(hr)) {
        hr = pPolicyConfig->SetDefaultEndpoint(id.c_str(), eConsole);
        hr = pPolicyConfig->SetDefaultEndpoint(id.c_str(), eMultimedia);
        hr = pPolicyConfig->SetDefaultEndpoint(id.c_str(), eCommunications);
        pPolicyConfig->Release();
    }

    return hr;
}

// Converts the PKEY_Device_Friendly_Name from a std::wstring
// to a std::string and then returns a QString
QString MainWindow::ConvertString(wstring wdevice_name) {

    string sdevice_name;
    sdevice_name = string(wdevice_name.begin(), wdevice_name.end());

    QString ret_qstring = QString::fromStdString(sdevice_name);

    return ret_qstring;
}

void MainWindow::GetAllAudioDevices()
{
    AudioManager audio_devices;

    playback_devices = audio_devices.GetPlaybackDevices();
    recording_devices = audio_devices.GetRecordingDevices();

    for(ulong i = 0; i < playback_devices.size(); ++i) {
        QString new_device = ConvertString(playback_devices.at(i).deviceName);
        playback_device_list.append(new_device);
    }

    for(ulong i = 0; i < recording_devices.size(); ++i) {
        QString new_device = ConvertString(recording_devices.at(i).deviceName);
        recording_device_list.append(new_device);
    }
}

void MainWindow::GetSavedAudioDevices()
{
    ifstream settings_file (SETTINGS_FILE_NAME);
    string current_line;
    vector<string> settings_buffer;

    if(settings_file.is_open())
    {
        while (getline(settings_file, current_line))
        {
            settings_buffer.push_back(current_line);
        }
        settings_file.close();
        for(ulong i=0;i<settings_buffer.size();++i)
        {
            if(settings_buffer[i] == "[vr_record]")
            {
                saved_vr_record_selection = settings_buffer[i+1];
            }
            if(settings_buffer[i] == "[vr_playback]")
            {
                saved_vr_playback_selection = settings_buffer[i+1];
            }
            if(settings_buffer[i] == "[desktop_record]")
            {
                saved_desktop_record_selection = settings_buffer[i+1];
            }
            if(settings_buffer[i] == "[desktop_playback]")
            {
                saved_desktop_playback_selection = settings_buffer[i+1];
            }
        }
    }

    wstring wsaved_vr_record = wstring(saved_vr_record_selection.begin(), saved_vr_record_selection.end());
    wstring wsaved_vr_playback = wstring(saved_vr_playback_selection.begin(), saved_vr_playback_selection.end());
    wstring wsaved_desktop_record = wstring(saved_desktop_record_selection.begin(), saved_desktop_record_selection.end());
    wstring wsaved_desktop_playback = wstring(saved_desktop_playback_selection.begin(), saved_desktop_playback_selection.end());

    for(size_t i = 0; i < playback_devices.size(); ++i) {
        if (playback_devices.at(i).deviceName == wsaved_vr_playback) {
            vr_playback_device =  playback_devices.at(i);
        }
        if (playback_devices.at(i).deviceName == wsaved_desktop_playback) {
            desktop_playback_device =  playback_devices.at(i);
        }
    }

    for(size_t i = 0; i < recording_devices.size(); ++i) {
        if (recording_devices.at(i).deviceName == wsaved_vr_record) {
            vr_recording_device =  recording_devices.at(i);
        }
        if (recording_devices.at(i).deviceName == wsaved_desktop_record) {
            desktop_recording_device =  recording_devices.at(i);
        }
    }
}

void MainWindow::on_switch_to_vr_button_clicked() {
    SetDevice(vr_playback_device.deviceID);
    SetDevice(vr_recording_device.deviceID);
}

void MainWindow::on_switch_to_desktop_button_clicked() {
    SetDevice(desktop_playback_device.deviceID);
    SetDevice(desktop_recording_device.deviceID);
}

void MainWindow::on_switch_to_vr_menu_triggered() {
    SetDevice(vr_playback_device.deviceID);
    SetDevice(vr_recording_device.deviceID);
}

void MainWindow::on_switch_to_desktop_menu_triggered() {
    SetDevice(desktop_playback_device.deviceID);
    SetDevice(desktop_recording_device.deviceID);
}

void MainWindow::on_exit_menu_triggered() {
    QApplication::quit();
}

void MainWindow::on_about_menu_triggered() {
    AboutDialog dialog(this);
    dialog.exec();
}
