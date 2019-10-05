#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QStringList>
#include <QString>
#include <string>
#include <iostream>
#include <fstream>

#include "audiomanager.h"

using std::string;
using std::wstring;
using std::vector;
using std::ofstream;
using std::ifstream;

namespace Ui {
class SetupDialog;
}

class SetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetupDialog(QWidget *parent = nullptr);
    ~SetupDialog();
    void PopulateAudioDevices(vector<AudioDevice> playback_devices, vector<AudioDevice> recording_devices, string saved_vr_playback, string saved_vr_record, string saved_desktop_playback, string saved_desktop_record);
    AudioDevice GetVrPlaybackDevice();
    AudioDevice GetVrRecordingDevice();
    AudioDevice GetDesktopPlaybackDevice();
    AudioDevice GetDesktopRecordingDevice();

private:
    Ui::SetupDialog *ui;
    void ErrorFindingDevice(QString);
    vector<AudioDevice> playback_devices_;
    vector<AudioDevice> recording_devices_;
    QStringList playback_device_list_;
    QStringList recording_device_list_;
    QString ConvertString(wstring);

private slots:
    void save_on_dialog_accept();
};

#endif // SETUPDIALOG_H
