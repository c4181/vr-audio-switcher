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
    void ListAudioDevices();
    vector<AudioDevice> devices;
    Ui::SetupDialog *ui;
    map<string, string> audio_device_map_;
    QStringList audio_device_list_;
    QString ConvertString(wstring);
};

#endif // SETUPDIALOG_H
