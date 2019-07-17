#include "SetupDialog.h"
#include "ui_SetupDialog.h"
#include "audiohandler.h"

SetupDialog::SetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupDialog)
{
    ui->setupUi(this);
}

SetupDialog::~SetupDialog()
{
    delete ui;
}

void ListAudioDevice() {
    AudioHandler audio;

    audio_device_map_ = audio.GetAudioDevices();


}
