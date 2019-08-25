#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QString>
#include <string>

#include <map>

#include "audiomanager.h"

using std::map;
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

private:
    Ui::SetupDialog *ui;
    void ListAudioDevices();
    vector<AudioDevice> playback_devices_;
    vector<AudioDevice> recording_devices_;
    QStringList playback_device_list_;
    QStringList recording_device_list_;
    QString ConvertString(wstring);
};

#endif // SETUPDIALOG_H
