#include "setupdialog.h"
#include "ui_setupdialog.h"

#define SETTINGS_FILE_NAME "audio_settings.ini"

SetupDialog::SetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupDialog) {
    ui->setupUi(this);
}

SetupDialog::~SetupDialog() {
    delete ui;
}

// Converts the PKEY_Device_Friendly_Name from a std::wstring
// to a std::string and then returns a QString
QString SetupDialog::ConvertString(wstring wdevice_name) {

    string sdevice_name;
    sdevice_name = string(wdevice_name.begin(), wdevice_name.end());

    QString ret_qstring = QString::fromStdString(sdevice_name);

    return ret_qstring;
}

void SetupDialog::PopulateAudioDevices(vector<AudioDevice> playback_devices, vector<AudioDevice> recording_devices, string saved_vr_record, string saved_vr_playback, string saved_desktop_record, string saved_desktop_playback)
{
    //Turn the audio device vector's passed and turn them into QStringList's for the combo boxes
    playback_devices_ = playback_devices;
    recording_devices_ = recording_devices;

    for(ulong i = 0; i < playback_devices_.size(); ++i) {
        QString new_device = ConvertString(playback_devices_.at(i).deviceName);
        playback_device_list_.append(new_device);
    }

    for(ulong i = 0; i < recording_devices_.size(); ++i) {
        QString new_device = ConvertString(recording_devices_.at(i).deviceName);
        recording_device_list_.append(new_device);
    }

    //Populate the combo boxes with the devices
    ui->vr_playback_combo_box->addItems(playback_device_list_);
    ui->desktop_playback_combo_box->addItems(playback_device_list_);
    ui->vr_recording_combo_box->addItems(recording_device_list_);
    ui->desktop_recording_combo_box->addItems(recording_device_list_);

    //Select the saved devices if any were passed
    if (!saved_vr_record.empty())
    {
        int index = ui->vr_recording_combo_box->findText(QString::fromStdString(saved_vr_record));
        if(index != -1)
        {
            ui->vr_recording_combo_box->setCurrentIndex(index);
        }
    }
    if (!saved_vr_playback.empty())
    {
        int index = ui->vr_playback_combo_box->findText(QString::fromStdString(saved_vr_playback));
        if(index != -1)
        {
            ui->vr_playback_combo_box->setCurrentIndex(index);
        }
    }
    if (!saved_desktop_record.empty())
    {
        int index = ui->desktop_recording_combo_box->findText(QString::fromStdString(saved_desktop_record));
        if(index != -1)
        {
            ui->desktop_recording_combo_box->setCurrentIndex(index);
        }
    }
    if (!saved_desktop_playback.empty())
    {
        int index = ui->desktop_playback_combo_box->findText(QString::fromStdString(saved_desktop_playback));
        if(index != -1)
        {
            ui->desktop_playback_combo_box->setCurrentIndex(index);
        }
    }
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
