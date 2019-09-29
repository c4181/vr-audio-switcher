#include "setupdialog.h"
#include "ui_setupdialog.h"

#define SETTINGS_FILE_NAME "audio_settings.ini"

SetupDialog::SetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupDialog) {
    ui->setupUi(this);
    ListAudioDevices();
    ui->vr_playback_combo_box->addItems(playback_device_list_);
    ui->desktop_playback_combo_box->addItems(playback_device_list_);
    ui->vr_recording_combo_box->addItems(recording_device_list_);
    ui->desktop_recording_combo_box->addItems(recording_device_list_);
    SelectSavedDevices();
}

SetupDialog::~SetupDialog() {
    delete ui;
}

// Gets all active playback and recording devices and adds them to a QString List
// to populate the Ui comboboxes
void SetupDialog::ListAudioDevices() {
    AudioManager audio_devices;
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
    QMessageBox::critical(this, "Error Finding Device", "Error: Could not find " + device, QMessageBox::Ok, QMessageBox::Ok);
    QCoreApplication::exit(1);
}

void SetupDialog::SelectSavedDevices() {
    if (!saved_vr_record_selection.empty())
    {
        int index = ui->vr_recording_combo_box->findText(QString::fromStdString(saved_vr_record_selection));
        if(index != -1)
        {
            ui->vr_recording_combo_box->setCurrentIndex(index);
        }
    }
    if (!saved_vr_playback_selection.empty())
    {
        int index = ui->vr_playback_combo_box->findText(QString::fromStdString(saved_vr_playback_selection));
        if(index != -1)
        {
            ui->vr_playback_combo_box->setCurrentIndex(index);
        }
    }
    if (!saved_desktop_record_selection.empty())
    {
        int index = ui->desktop_recording_combo_box->findText(QString::fromStdString(saved_desktop_record_selection));
        if(index != -1)
        {
            ui->desktop_recording_combo_box->setCurrentIndex(index);
        }
    }
    if (!saved_desktop_playback_selection.empty())
    {
        int index = ui->desktop_playback_combo_box->findText(QString::fromStdString(saved_desktop_playback_selection));
        if(index != -1)
        {
            ui->desktop_playback_combo_box->setCurrentIndex(index);
        }
    }
}

void SetupDialog::save_on_dialog_accept() {
    string svr_record_selection = ui->vr_recording_combo_box->currentText().toStdString();
    string svr_playback_selection = ui->vr_playback_combo_box->currentText().toStdString();
    string sdesktop_record_selection = ui->desktop_recording_combo_box->currentText().toStdString();
    string sdesktop_playback_selection = ui->desktop_playback_combo_box->currentText().toStdString();
    ofstream settings_file(SETTINGS_FILE_NAME, std::ios::out | std::ios::trunc);

    if(settings_file.is_open())
    {
        settings_file << "[vr_record]\n";
        settings_file << svr_record_selection << "\n";
        settings_file << "[vr_playback]\n";
        settings_file << svr_playback_selection << "\n";
        settings_file << "[desktop_record]\n";
        settings_file << sdesktop_record_selection << "\n";
        settings_file << "[desktop_playback]\n";
        settings_file << sdesktop_playback_selection << "\n";
        settings_file.close();
    } else
    {
        QMessageBox::information(this, "Unable to Save Settings", "Unable to save settings to settings file.\nYour devices will reset to default on next launch.");
    }
}
