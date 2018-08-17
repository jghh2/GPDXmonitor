#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextCodec>

static bool monitor_status = true;

static bool buy_fall = true;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    ui->radioButton->setChecked(buy_fall);

    on_checkBox_stateChanged(ui->checkBox->checkState());
}

MainWindow::~MainWindow()
{
    delete ui;
}

QByteArray MainWindow::gb2312ToUtf8(std::string strGb2312)
{

QTextCodec* utf8Codec= QTextCodec::codecForName("utf-8");
QTextCodec* gb2312Codec = QTextCodec::codecForName("gb2312");

QString strUnicode= gb2312Codec->toUnicode(strGb2312.c_str());
QByteArray ByteUtf8= utf8Codec->fromUnicode(strUnicode);

return  ByteUtf8;
}

void MainWindow::updateJiaGe()
{


    float fuDongJia;
    float fuDongBi;
    float linrui;
    float xiaDan = ui->doubleSpinBox->value();
    float price = ui->doubleSpinBox_2->value();

    if(buy_fall)
    {
        fuDongJia = xiaDan - price;
        fuDongBi = fuDongJia*100/xiaDan;
    }else{
        fuDongJia = price - xiaDan;
        fuDongBi = fuDongJia*100/xiaDan;

    }

    ui->label_7->setText(QString::number((fuDongJia),'f',2));

    ui->label_4->setText(QString("%1%").arg(QString::number(fuDongBi,'f',2)));


    float xiaDanChenBen = xiaDan * ui->spinBox->value();
    float priceChenBen = price * ui->spinBox->value();

    if(buy_fall)
        linrui = (xiaDanChenBen - priceChenBen) - xiaDanChenBen * 0.00025 - priceChenBen * 0.00025 - priceChenBen * 0.001;
    else
        linrui = (priceChenBen - xiaDanChenBen)  - xiaDanChenBen * 0.00025 - priceChenBen * 0.00025 - priceChenBen * 0.001;


    ui->label_12->setText(QString::number((linrui),'f',2));

    ui->label_14->setText(QString::number((xiaDanChenBen),'f',2));

}

void MainWindow::replyFinished(QNetworkReply* reply)
{

    QByteArray data = reply->readAll();



    QString name  = QString(data).section('~',1,1);

//    qDebug()<<QString(gb2312ToUtf8(name.toStdString()));
//    ui->label_2->setText(name.toLocal8Bit());

      float  price = QString(data).section('~',3,3).toFloat();

    ui->doubleSpinBox_2->setValue(price);
    reply->deleteLater();
    updateJiaGe();



}

void MainWindow::on_readyRead()
{

}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
//    return;
    hide();
    if(arg1)
        setWindowFlags(Qt::WindowStaysOnTopHint);
    else
        setWindowFlags(Qt::Widget);
    show();
}
void MainWindow::testFunction()
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://qt.gtimg.cn/q=" + ui->lineEdit->text()));
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(request);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

}
void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    monitor_status  = arg1;

if(arg1)
{
    testTimer = new QTimer(this);
    connect( testTimer, SIGNAL(timeout()), this, SLOT(testFunction()) );
    testTimer->start(1000);
} else {
    if (testTimer->isActive() )
    testTimer->stop();
    delete  testTimer;
}
  //  connect(reply,SIGNAL(readyRead()),this,SLOT(on_readyRead()));

}


void MainWindow::on_pushButton_clicked()
{

//    if(ui->checkBox_2->checkState())
   if(1)
    {
    QNetworkRequest request;
    request.setUrl(QUrl("http://qt.gtimg.cn/q=" + ui->lineEdit->text()));
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(request);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}else{
        updateJiaGe();
    }



  // update();
//   ui->label_14->setText("aaa");
}

void MainWindow::on_radioButton_clicked()
{
    //跌
    buy_fall = true;

}

void MainWindow::on_radioButton_2_clicked()
{
    //涨
    buy_fall = false;
}
