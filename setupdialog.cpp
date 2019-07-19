#include "setupdialog.h"
#include "ui_setupdialog.h"
#include "audiohandler.h"
#include "audiohandler.cpp"

#include <map>

using std::map;


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
    AudioHandler audio;

    //audio_device_map_ = audio.GetAudioDevices();

    for (map<string, string>::iterator it=audio_device_map_.begin(); it!=audio_device_map_.end(); ++it) {
        string device_name(it->first);
        QString q_device_name = QString::fromStdString(device_name);
        audio_device_list_.append(q_device_name);
    }
}
