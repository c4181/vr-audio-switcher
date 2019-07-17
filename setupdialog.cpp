#include "SetupDialog.h"
#include "ui_SetupDialog.h"
#include "audiohandler.h"

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

void ListAudioDevice() {
    AudioHandler audio;

    map<char[], char[]> audio_device_map_ = audio.GetAudioDevices();
    QStringList audio_device_list_;

    for (map<char[], char[]>::iterator it=audio_device_map_.begin(); it!=audio_device_map_.end(); ++it) {
        string device_name(it->first);
        QString q_device_name = QString::fromStdString(device_name);
        audio_device_list_.append(q_device_name);
    }
}
