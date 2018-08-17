#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QByteArray>
#include <QNetworkReply>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void replyFinished(QNetworkReply* reply);
    void on_readyRead();

    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void testFunction();

private:
    Ui::MainWindow *ui;
    QByteArray gb2312ToUtf8(std::string strGb2312);
QTimer *testTimer;
     void updateJiaGe();
};

#endif // MAINWINDOW_H
