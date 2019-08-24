#include "setupdialog.h"
#include "ui_setupdialog.h"

SetupDialog::SetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupDialog)
{
    ui->setupUi(this);
    ListAudioDevices();
    ui->vr_playback_combo_box->addItems(audio_device_list_);
}

SetupDialog::~SetupDialog()
{
    delete ui;
}

void SetupDialog::ListAudioDevices() {
    AudioManager audio_devices;

    devices = audio_devices.GetAudioDevices();

    QString test = ConvertString(devices.at(0).deviceName);

}

QString SetupDialog::ConvertString(wstring wdevice_name) {
    const wchar_t* wchar_name = wdevice_name.c_str();
    char buffer[32];
    int ret;

    ret = wcstombs(buffer, wchar_name, sizeof (buffer));
    if (ret==32) buffer[31] = '\0';

    QString ret_qstring;

    return ret_qstring;
}
