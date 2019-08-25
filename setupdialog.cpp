#include "setupdialog.h"
#include "ui_setupdialog.h"

SetupDialog::SetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupDialog)
{
    ui->setupUi(this);
    ListAudioDevices();
    ui->vr_playback_combo_box->addItems(playback_device_list_);
    ui->desktop_playback_combo_box->addItems(playback_device_list_);
}

SetupDialog::~SetupDialog()
{
    delete ui;
}

void SetupDialog::ListAudioDevices() {
    AudioManager audio_devices;

    devices = audio_devices.GetAudioDevices();

    for(ulong i = 0; i < devices.size(); ++i) {
        QString new_device = ConvertString(devices.at(i).deviceName);
        playback_device_list_.append(new_device);
    }

}

QString SetupDialog::ConvertString(wstring wdevice_name) {

    string sdevice_name;
    sdevice_name = string(wdevice_name.begin(), wdevice_name.end());

    QString ret_qstring = QString::fromStdString(sdevice_name);

    return ret_qstring;
}
