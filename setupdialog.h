#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <map>
#include <QDialog>
#include <QStringList>

using std::map;

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
    map<char[], char[]> audio_device_map_;
    QStringList audio_device_list_;
};

#endif // SETUPDIALOG_H
