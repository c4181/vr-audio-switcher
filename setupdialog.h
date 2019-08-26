#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QStringList>
#include <QString>
#include <string>

#include "audiomanager.h"

using std::string;
using std::wstring;
using std::vector;

namespace Ui {
class SetupDialog;
}

class SetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetupDialog(QWidget *parent = nullptr);
    ~SetupDialog();
    AudioDevice GetVrPlaybackDevice();
    AudioDevice GetVrRecordingDevice();
    AudioDevice GetDesktopPlaybackDevice();
    AudioDevice GetDesktopRecordingDevice();

private:
    Ui::SetupDialog *ui;
    void ListAudioDevices();
    void ErrorFindingDevice(QString);
    vector<AudioDevice> playback_devices_;
    vector<AudioDevice> recording_devices_;
    QStringList playback_device_list_;
    QStringList recording_device_list_;
    QString ConvertString(wstring);
};

#endif // SETUPDIALOG_H
