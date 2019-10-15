#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma comment(lib, "Ole32.lib")

#include <combaseapi.h>
#include <string>
#include <QMainWindow>

#include "PolicyConfig.h"
#include "setupdialog.h"
#include "aboutdialog.h"

using std::wstring;

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
    AudioDevice vr_playback_device;
    AudioDevice vr_recording_device;
    AudioDevice desktop_playback_device;
    AudioDevice desktop_recording_device;


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
