#include "setupdialog.h"
#include "ui_setupdialog.h"
#include "audiohandler.h"

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
    CDevicesManager devices;


}
