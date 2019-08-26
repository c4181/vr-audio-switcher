#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_setupMenu_triggered() {
  SetupDialog dialog(this);
  int dialog_code = dialog.exec();

  if (dialog_code == QDialog::Accepted) {
     vr_playback_device = dialog.GetVrPlaybackDevice();
     vr_recording_device = dialog.GetVrRecordingDevice();

     desktop_playback_device = dialog.GetDesktopPlaybackDevice();
     desktop_recording_device = dialog.GetDesktopRecordingDevice();
  }
  dialog.close();
}

HRESULT MainWindow::SetDevice(const wstring& id) {
    IPolicyConfig *pPolicyConfig;

    HRESULT hr = CoCreateInstance(__uuidof(CPolicyConfigClient), NULL, CLSCTX_ALL,
                                  __uuidof(IPolicyConfig), (LPVOID*)&pPolicyConfig);

    if (SUCCEEDED(hr)) {
        hr = pPolicyConfig->SetDefaultEndpoint(id.c_str(), eConsole);
        hr = pPolicyConfig->SetDefaultEndpoint(id.c_str(), eMultimedia);
        hr = pPolicyConfig->SetDefaultEndpoint(id.c_str(), eCommunications);
        pPolicyConfig->Release();
    }

    return hr;
}

void MainWindow::on_switch_to_vr_button_clicked() {
    SetDevice(vr_playback_device.deviceID);
    SetDevice(vr_recording_device.deviceID);
}

void MainWindow::on_switch_to_desktop_button_clicked() {
    SetDevice(desktop_playback_device.deviceID);
    SetDevice(desktop_recording_device.deviceID);
}

void MainWindow::on_switch_to_vr_menu_triggered() {
    SetDevice(vr_playback_device.deviceID);
    SetDevice(vr_recording_device.deviceID);
}

void MainWindow::on_switch_to_desktop_menu_triggered() {
    SetDevice(desktop_playback_device.deviceID);
    SetDevice(desktop_recording_device.deviceID);
}

void MainWindow::on_exit_menu_triggered() {
    QApplication::quit();
}
