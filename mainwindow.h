#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma comment(lib, "Ole32.lib")

#include <combaseapi.h>
#include <string>
#include <QMainWindow>
#include <vector>
#include <iostream>
#include <fstream>

#include "PolicyConfig.h"
#include "setupdialog.h"
#include "aboutdialog.h"

using std::wstring;
using std::vector;
using std::ifstream;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    HRESULT SetDevice(const wstring&);
    void SwitchToVrDevices();
    void SwtichToDesktopDevices();
    QString ConvertString(wstring);
    void GetAllAudioDevices();
    void GetSavedAudioDevices();
    vector<AudioDevice> playback_devices;
    vector<AudioDevice> recording_devices;
    AudioDevice vr_playback_device;
    AudioDevice vr_recording_device;
    AudioDevice desktop_playback_device;
    AudioDevice desktop_recording_device;
    QStringList playback_device_list;
    QStringList recording_device_list;
    string saved_vr_record_selection;
    string saved_vr_playback_selection;
    string saved_desktop_record_selection;
    string saved_desktop_playback_selection;


private slots:
    void on_setupMenu_triggered();
    void on_switch_to_vr_button_clicked();
    void on_switch_to_desktop_button_clicked();
    void on_switch_to_vr_menu_triggered();
    void on_switch_to_desktop_menu_triggered();
    void on_exit_menu_triggered();
    void on_about_menu_triggered();
};


#endif // MAINWINDOW_H
