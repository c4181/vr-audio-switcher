#include "setupdialog.h"
#include "ui_setupdialog.h"

SetupDialog::SetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupDialog) {
    ui->setupUi(this);
    ListAudioDevices();
    ui->vr_playback_combo_box->addItems(playback_device_list_);
    ui->desktop_playback_combo_box->addItems(playback_device_list_);
    ui->vr_recording_combo_box->addItems(recording_device_list_);
    ui->desktop_recording_combo_box->addItems(recording_device_list_);
}

SetupDialog::~SetupDialog() {
    delete ui;
}

// Gets all active playback and recording devices and adds them to a QString List
// to populate the Ui comboboxes
void SetupDialog::ListAudioDevices() {
    AudioManager audio_devices;

    playback_devices_ = audio_devices.GetPlaybackDevices();
    recording_devices_ = audio_devices.GetRecordingDevices();

    for(ulong i = 0; i < playback_devices_.size(); ++i) {
        QString new_device = ConvertString(playback_devices_.at(i).deviceName);
        playback_device_list_.append(new_device);
    }

    for(ulong i = 0; i < recording_devices_.size(); ++i) {
        QString new_device = ConvertString(recording_devices_.at(i).deviceName);
        recording_device_list_.append(new_device);
    }

}

// Converts the PKEY_Device_Friendly_Name from a std::wstring
// to a std::string and then returns a QString
QString SetupDialog::ConvertString(wstring wdevice_name) {

    string sdevice_name;
    sdevice_name = string(wdevice_name.begin(), wdevice_name.end());

    QString ret_qstring = QString::fromStdString(sdevice_name);

    return ret_qstring;
}

AudioDevice SetupDialog::GetVrPlaybackDevice() {
   QString quser_selection = ui->vr_playback_combo_box->currentText();
   string suser_selection = quser_selection.toStdString();
   wstring wuser_selection = wstring(suser_selection.begin(), suser_selection.end());

   for(uint i = 0; i < playback_devices_.size(); ++i) {
       if (playback_devices_.at(i).deviceName == wuser_selection) {
           return playback_devices_.at(i);
       }
   }
   ErrorFindingDevice(quser_selection);
}

AudioDevice SetupDialog::GetVrRecordingDevice() {
    QString quser_selection = ui->vr_recording_combo_box->currentText();
    string suser_selection = quser_selection.toStdString();
    wstring wuser_selection = wstring(suser_selection.begin(), suser_selection.end());

    for(uint i = 0; i < recording_devices_.size(); ++i) {
        if (recording_devices_.at(i).deviceName == wuser_selection) {
            return recording_devices_.at(i);
        }
    }
    ErrorFindingDevice(quser_selection);
}

AudioDevice SetupDialog::GetDesktopPlaybackDevice() {
    QString quser_selection = ui->desktop_playback_combo_box->currentText();
    string suser_selection = quser_selection.toStdString();
    wstring wuser_selection = wstring(suser_selection.begin(), suser_selection.end());

    for(uint i = 0; i < playback_devices_.size(); ++i) {
        if (playback_devices_.at(i).deviceName == wuser_selection) {
            return playback_devices_.at(i);
        }
    }
    ErrorFindingDevice(quser_selection);
}

AudioDevice SetupDialog::GetDesktopRecordingDevice() {
    QString quser_selection = ui->desktop_recording_combo_box->currentText();
    string suser_selection = quser_selection.toStdString();
    wstring wuser_selection = wstring(suser_selection.begin(), suser_selection.end());

    for(uint i = 0; i < recording_devices_.size(); ++i) {
        if (recording_devices_.at(i).deviceName == wuser_selection) {
            return recording_devices_.at(i);
        }
    }
    ErrorFindingDevice(quser_selection);
}

void SetupDialog::ErrorFindingDevice(QString device) {
    QMessageBox::critical(this, "Error Finding Device", "Error: Could not find" + device, QMessageBox::Ok, QMessageBox::Ok);
    QCoreApplication::exit(1);
}
