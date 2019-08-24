#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QString>
#include <string>

#include <map>

#include "audiohandler.h"
#include "DevicesManager.h"

using std::map;
using std::string;

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
    Ui::SetupDialog *ui;
    map<string, string> audio_device_map_;
    QStringList audio_device_list_;
};

#endif // SETUPDIALOG_H
