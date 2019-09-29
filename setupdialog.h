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
    AudioDevice GetVrPlaybackDevice();
    AudioDevice GetVrRecordingDevice();
    AudioDevice GetDesktopPlaybackDevice();
    AudioDevice GetDesktopRecordingDevice();

private:
    Ui::SetupDialog *ui;
    void ListAudioDevices();
    void ErrorFindingDevice(QString);
    void SelectSavedDevices();
    vector<AudioDevice> playback_devices_;
    vector<AudioDevice> recording_devices_;
    QStringList playback_device_list_;
    QStringList recording_device_list_;
    QString ConvertString(wstring);
    string saved_vr_record_selection;
    string saved_vr_playback_selection;
    string saved_desktop_record_selection;
    string saved_desktop_playback_selection;

private slots:
    void save_on_dialog_accept();
};

#endif // SETUPDIALOG_H
