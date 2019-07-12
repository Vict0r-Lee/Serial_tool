#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QString>
#include <QFileDialog>
#include <synchapi.h>
#include <QProcess>
#include <QDateTime>

#include "common.h"
#include "crc16.h"

void MainWindow::setup_ui_2ed_set(bool show)
{
    if(true == show)
    {
        ui->textEdit_send_cmp->show();
        ui->textEdit_recv_cmp->show();
        ui->textEdit_file_cmp->show();

        ui->checkBox_crc_cmp->show();
        ui->toolButton_file->show();
        ui->lineEdit_file_name->show();
        ui->btn_modbus_send->show();
        ui->clear_recv_cmp_btn->show();
        ui->lineEdit_time_modbus->show();

    }else
    {
        ui->textEdit_send_cmp->hide();
        ui->textEdit_recv_cmp->hide();
        ui->textEdit_file_cmp->hide();

        ui->checkBox_crc_cmp->hide();
        ui->toolButton_file->hide();
        ui->lineEdit_file_name->hide();
        ui->btn_modbus_send->hide();
        ui->clear_recv_cmp_btn->hide();
        ui->lineEdit_time_modbus->hide();

    }
}

void MainWindow::setup_ui_1st_set(bool show)
{
    if(true == show)
    {
        ui->btn_send_1->show();
        ui->btn_send_2->show();
        ui->btn_send_3->show();
        ui->btn_crc_1->show();
        ui->btn_crc_2->show();
        ui->btn_crc_3->show();


        ui->textEdit_recv->show();
        ui->textEdit_send_1->show();
        ui->textEdit_send_2->show();
        ui->textEdit_send_3->show();
        ui->lineEdit_time_1->show();
        ui->lineEdit_time_2->show();
        ui->lineEdit_time_3->show();
        ui->lineEdit_time_round->show();

        ui->label_7->show();
        ui->label_count_1->show();
        ui->label_count_2->show();
        ui->label_count_3->show();
        ui->label_count_4->show();
        ui->label_count_sb->show();
        ui->label_count_rb->show();
        ui->label_count_sfm->show();
        ui->label_count_rfm->show();

        ui->clear_recv_btn->show();
        ui->btn_clear_count->show();
        ui->checkBox_auto_send_1->show();
        ui->checkBox_auto_send_2->show();
        ui->checkBox_auto_send_3->show();
        ui->checkBox_auto_send_4->show();
        ui->checkBox_new_line->show();
        ui->checkBox_time_stamp->show();
    }else
    {
        ui->btn_send_1->hide();
        ui->btn_send_2->hide();
        ui->btn_send_3->hide();
        ui->btn_crc_1->hide();
        ui->btn_crc_2->hide();
        ui->btn_crc_3->hide();

        ui->textEdit_recv->hide();
        ui->textEdit_send_1->hide();
        ui->textEdit_send_2->hide();
        ui->textEdit_send_3->hide();
        ui->lineEdit_time_1->hide();
        ui->lineEdit_time_2->hide();
        ui->lineEdit_time_3->hide();
        ui->lineEdit_time_round->hide();

        ui->label_7->hide();
        ui->label_count_1->hide();
        ui->label_count_2->hide();
        ui->label_count_3->hide();
        ui->label_count_4->hide();
        ui->label_count_sb->hide();
        ui->label_count_rb->hide();
        ui->label_count_sfm->hide();
        ui->label_count_rfm->hide();


        ui->clear_recv_btn->hide();
        ui->btn_clear_count->hide();
        ui->checkBox_auto_send_1->hide();
        ui->checkBox_auto_send_2->hide();
        ui->checkBox_auto_send_3->hide();
        ui->checkBox_auto_send_4->hide();
        ui->checkBox_new_line->hide();
        ui->checkBox_time_stamp->hide();
    }
}

void MainWindow::enable_widget(bool enable)
{
    //发送按钮
    ui->btn_send_1->setEnabled(enable);
    ui->btn_send_2->setEnabled(enable);
    ui->btn_send_3->setEnabled(enable);
    ui->btn_modbus_send->setEnabled(enable);

    ui->checkBox_auto_send_1->setEnabled(enable);
    ui->checkBox_auto_send_2->setEnabled(enable);
    ui->checkBox_auto_send_3->setEnabled(enable);
    ui->checkBox_auto_send_4->setEnabled(enable);
}

void MainWindow::set_checkbox_false()
{
    ui->checkBox_auto_send_1->setChecked(false);
    ui->checkBox_auto_send_2->setChecked(false);
    ui->checkBox_auto_send_3->setChecked(false);
    ui->checkBox_auto_send_4->setChecked(false);
}

void MainWindow::stop_timer()
{
    send_timer_1.stop();
    send_timer_2.stop();
    send_timer_3.stop();
    round_send_timer.stop();

    ui->lineEdit_time_1->setEnabled(true);
    ui->lineEdit_time_2->setEnabled(true);
    ui->lineEdit_time_3->setEnabled(true);
    ui->lineEdit_time_round->setEnabled(true);
}

void MainWindow::enable_serial_param(bool enable)
{
    ui->comboBox_baudRate->setEnabled(enable);
    ui->comboBox_dataBits->setEnabled(enable);
    ui->comboBox_flowBit->setEnabled(enable);
    ui->comboBox_parity->setEnabled(enable);
    ui->comboBox_serialPort->setEnabled(enable);
    ui->comboBox_stopBit->setEnabled(enable);
    ui->fresh_port_btn->setEnabled(enable);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->textEdit_recv->document()->setMaximumBlockCount(1024);
    /*ui->radioButton_stat->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:clicked {background-color:green;}"
                                   "QRadioButton::indicator:unclicked {background-color:red;}");*/
    setup_ui_2ed_set(false);
    check_timer.setInterval(5000);

    connect(&check_timer, SIGNAL(timeout()), this,  SLOT(check_open_port()));
    connect(&modbus_send_timer,SIGNAL(timeout()),this,SLOT(modbus_check_send()));
    connect(&send_timer_1,SIGNAL(timeout()),this,SLOT(on_btn_send_1_clicked()));
    connect(&send_timer_2,SIGNAL(timeout()),this,SLOT(on_btn_send_2_clicked()));
    connect(&send_timer_3,SIGNAL(timeout()),this,SLOT(on_btn_send_3_clicked()));
    connect(&round_send_timer,SIGNAL(timeout()),this,SLOT(round_buffer_send()));

    serial = new QSerialPort;
    scan_port();
     //设置波特率
     ui->comboBox_baudRate->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
     ui->comboBox_baudRate->addItem(QStringLiteral("4800"), QSerialPort::Baud4800);
     ui->comboBox_baudRate->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
     ui->comboBox_baudRate->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
     ui->comboBox_baudRate->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
     //ui->comboBox_baudRate->addItem(tr("Custom"));

     //设置数据位
     ui->comboBox_dataBits->addItem(QStringLiteral("5"), QSerialPort::Data5);
     ui->comboBox_dataBits->addItem(QStringLiteral("6"), QSerialPort::Data6);
     ui->comboBox_dataBits->addItem(QStringLiteral("7"), QSerialPort::Data7);
     ui->comboBox_dataBits->addItem(QStringLiteral("8"), QSerialPort::Data8);
     ui->comboBox_dataBits->setCurrentIndex(3);

     //设置奇偶校验位
     ui->comboBox_parity->addItem(tr("无"), QSerialPort::NoParity);
     ui->comboBox_parity->addItem(tr("偶校验"), QSerialPort::EvenParity);
     ui->comboBox_parity->addItem(tr("奇校验"), QSerialPort::OddParity);
     ui->comboBox_parity->addItem(tr("Mark"), QSerialPort::MarkParity);
     ui->comboBox_parity->addItem(tr("空格校验"), QSerialPort::SpaceParity);

     //设置停止位
     ui->comboBox_stopBit->addItem(QStringLiteral("1"), QSerialPort::OneStop);
     ui->comboBox_stopBit->addItem(QStringLiteral("1.5"), QSerialPort::OneAndHalfStop);
     ui->comboBox_stopBit->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

     //添加流控
     ui->comboBox_flowBit->addItem(tr("None"), QSerialPort::NoFlowControl);
     ui->comboBox_flowBit->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
     ui->comboBox_flowBit->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
}


void MainWindow::check_open_port()
{
    QString com_str = ui->comboBox_serialPort->currentText();

    QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &serialPortInfo : serialPortInfos)
    {
        if(com_str == serialPortInfo.portName())
        {
            return;
        }
    }

    ui->btn_openConsole->setText(tr("打开串口"));
    ui->comboBox_serialPort->clear();
    ui->stat_r_btn->setChecked(false);
    this->CloseSerialPort();
    disconnect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    this->scan_port();
    stop_timer();
    if(modbus_send_timer.isActive()){
        modbus_send_timer.stop();
        ui->btn_modbus_send->setText(tr("开始"));
        ui->btn_modbus_send->setEnabled(true);
    }

    enable_serial_param(true);
    enable_widget(false);
    QMessageBox::critical(this, tr("Error"), "串口连接中断，请检查是否正确连接！");
}

void MainWindow::scan_port()
{
    QString description;
    QString manufacturer;
    QString serialNumber;


    //获取可以用的串口
    QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();

    //输出当前系统可以使用的串口个数
    qDebug() << "Total numbers of ports: " << serialPortInfos.count();

    //将所有可以使用的串口设备添加到ComboBox中
    for (const QSerialPortInfo &serialPortInfo : serialPortInfos)
    {
        QStringList list;
        description = serialPortInfo.description();
        manufacturer = serialPortInfo.manufacturer();
        serialNumber = serialPortInfo.serialNumber();

        list << serialPortInfo.portName()
             << (!description.isEmpty() ? description : "")
             << (!manufacturer.isEmpty() ? manufacturer : "")
             << (!serialNumber.isEmpty() ? serialNumber : "")
             << serialPortInfo.systemLocation()
             << (serialPortInfo.vendorIdentifier() ? QString::number(serialPortInfo.vendorIdentifier(), 16) : "")
             << (serialPortInfo.productIdentifier() ? QString::number(serialPortInfo.productIdentifier(), 16) : "");
        ui->comboBox_serialPort->addItem(list.first(), list);
    }

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CloseSerialPort()
{
    serial->clear();
    serial->close();
    //serial->deleteLater();
}


void MainWindow::round_buffer_send()
{
    QByteArray send_bytes[3] = {get_send_buffer(ui->textEdit_send_1->toPlainText()),get_send_buffer(ui->textEdit_send_2->toPlainText()),get_send_buffer(ui->textEdit_send_3->toPlainText())};
    send_buffer(send_bytes[round_buffer_index%3]);
    round_buffer_index++;
}

void MainWindow::readData()
{
    QByteArray buf;
    QString read_str;
    QString line_str;
    bool cmp_result;
    QDateTime time = QDateTime::currentDateTime();
    QString time_str = " [" + time.toString("yyyy-MM-dd hh:mm:ss") + "]";

   /* while(1)
    {
        //因为ReadyRead的信号已经获取,所需要先读
        buf += serial->readAll();
        //超时10ms读取等待,防止一帧多次接收
        if(false == serial->waitForReadyRead(10)){
            qDebug() << "break" << buf << endl;
            break;
        }
    }*/

    buf = serial->readAll();
    if (!buf.isEmpty())
    {
        recv_bytes += buf.count();
        recv_frames++;
        if(true == this->recv_hex_switch){
            read_str = ByteArrayToHexString(buf);
            if(recv_with_time_stamp){
                read_str += time_str;
            }
            read_str += "\n";
        }else{
            read_str = tr(buf);
            if(recv_with_time_stamp){
                read_str.insert(read_str.indexOf('\n'),time_str);
            }
            //read_str = read_str.trimmed();
        }

        //ui->textEdit_recv->clear();

        if(false == modbus_test_switch)
        {
            ui->textEdit_recv->insertPlainText(read_str);
            ui->textEdit_recv->moveCursor(QTextCursor::End);
        }
        else{
            line_str = GetlLineString(cmp_str,cmp_send_index - 1);
            if(true == cmp_crc_switch){
                cmp_result = hexStrCmp(line_str,read_str.left(read_str.length() - 5));
            }else{
                cmp_result = hexStrCmp(line_str,read_str);
            }

            if(false == cmp_result){
                ui->textEdit_recv_cmp->setTextColor(Qt::red);
            }
            else{
                ui->textEdit_recv_cmp->setTextColor(Qt::black);
            }

            line_str.insert(0,QString::number(cmp_send_index) + ":");
            read_str.insert(0,QString::number(cmp_send_index) + ":");

            ui->textEdit_file_cmp->append(line_str);
            ui->textEdit_recv_cmp->append(read_str);
            ui->textEdit_recv_cmp->moveCursor(QTextCursor::End);
            ui->textEdit_file_cmp->moveCursor(QTextCursor::End);
        }
    }
}

void MainWindow::on_btn_openConsole_clicked()
{
    if (ui->btn_openConsole->text() == tr("打开串口"))
    {
        //设置串口名字
        serial->setPortName(ui->comboBox_serialPort->currentText());

        //设置波特率
        serial->setBaudRate(ui->comboBox_baudRate->currentData().toInt());

        //设置数据位
        serial->setDataBits((QSerialPort::DataBits)ui->comboBox_dataBits->currentData().toInt());

        //设置奇偶校验位
        serial->setParity((QSerialPort::Parity)ui->comboBox_parity->currentData().toInt());

        //设置停止位
        serial->setStopBits((QSerialPort::StopBits)ui->comboBox_stopBit->currentData().toInt());

        //设置流控
        serial->setFlowControl((QSerialPort::FlowControl)ui->comboBox_flowBit->currentData().toInt());

        //打开串口
        if (serial->open(QIODevice::ReadWrite))
        {
            ui->btn_openConsole->setText(tr("关闭串口"));
            ui->stat_r_btn->setChecked(true);

            enable_serial_param(false);
            enable_widget(true);

            //信号与槽函数关联
            connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
            check_timer.start();
        }else{
            QMessageBox::critical(this, tr("Error"), "╯﹏╰ 请检查串口是否被占用或者连接正确！╯﹏╰");
        }
    }
    else
    {
        //关闭串口
        ui->btn_openConsole->setText(tr("打开串口"));
        ui->stat_r_btn->setChecked(false);

        enable_serial_param(true);
        enable_widget(false);

        CloseSerialPort();
        //关闭信号槽连接
        stop_timer();
        set_checkbox_false();
        check_timer.stop();
        disconnect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
        if(modbus_send_timer.isActive()){
            modbus_send_timer.stop();
            ui->btn_modbus_send->setText(tr("开始"));
            ui->btn_modbus_send->setEnabled(true);
        }
    }
}

void MainWindow::send_buffer(QByteArray buffer)
{
    serial->write(buffer);
    serial->flush();

    qDebug() << "send_buffer"<<buffer<<endl;
    send_bytes += buffer.count();
    send_frames++;

    ui->label_count_sfm->setText(QString::number(send_frames));
    ui->label_count_sb->setText(QString::number(send_bytes));
}

void MainWindow::modbus_check_send()
{
    qDebug()<< "send start" << endl;
    if(!write_str.isEmpty())
    {
        QString send_str = GetlLineString(write_str,cmp_send_index);
        QByteArray send_bytes;
        if(send_str == "")
        {
            QMessageBox::information(this, tr("Info"), "全部发送完成!^ ^");
            modbus_send_timer.stop();
            ui->btn_modbus_send->setText(tr("开始"));
            ui->lineEdit_time_modbus->setEnabled(true);

        }else
        {
            send_bytes = get_send_buffer(send_str);
            send_buffer(send_bytes);
            cmp_send_index++;
            send_str.insert(0,QString::number(cmp_send_index) + ":");
            ui->textEdit_send_cmp->append(send_str);
            ui->textEdit_send_cmp->moveCursor(QTextCursor::End);
        }

    }else{
        QMessageBox::critical(this, tr("Error"), "请先打开文件再发送!^ ^");
    }
}

void MainWindow::on_clear_recv_btn_clicked()
{
    ui->textEdit_recv->clear();
}

void MainWindow::on_fresh_port_btn_clicked()
{
    ui->comboBox_serialPort->clear();
    this->scan_port();
}


void MainWindow::on_checkBox_recv_hex_clicked(bool checked)
{
    recv_hex_switch = checked;
}

void MainWindow::on_checkBox_send_hex_clicked(bool checked)
{
    send_hex_switch = checked;
}

void MainWindow::on_checkBox_crc_clicked(bool checked)
{
    crc16_check_switch = checked;
}


void MainWindow::on_checkBox_modbus_test_clicked(bool checked)
{
    modbus_test_switch = checked;
    setup_ui_1st_set(!checked);
    setup_ui_2ed_set(checked);
    if(true == checked)
    {
        cmp_send_index = 0;

        stop_timer();
        ui->checkBox_auto_send_1->setChecked(false);
        ui->checkBox_auto_send_2->setChecked(false);
        ui->checkBox_auto_send_3->setChecked(false);
        ui->checkBox_auto_send_4->setChecked(false);

        ui->checkBox_recv_hex->move(790,0);
    }else
    {
        modbus_send_timer.stop();
        enable_widget(true);

        ui->checkBox_recv_hex->move(190,230);
    }
}

void MainWindow::on_toolButton_file_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("文件对话框！"),"D:",tr("表格文件(*csv );;""所有文件(*)"));
    qDebug()<<"filename : "<<fileName;
    ui->lineEdit_file_name->setText(fileName);
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly  | QIODevice::Text))
    {
        QMessageBox::critical(this, tr("Error"), "打开文件失败");
        return ;
    }

    QTextStream txtInput(&file);
    QString lineStr;
    int n;
    write_str = "";
    cmp_str = "";
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        n = lineStr.indexOf(",");
        cmp_str += lineStr.right(lineStr.length() - n - 1);
        cmp_str += "\n";
        write_str += lineStr.left(n);
        write_str += "\n";
;
    }
    file.close();
    ui->textEdit_send_cmp->clear();
    ui->textEdit_file_cmp->clear();

    //ui->textEdit_send_cmp->setText(write_str);
    //ui->textEdit_file_cmp->setText(cmp_str);
    ui->btn_modbus_send->setEnabled(true);
}


void MainWindow::on_clear_recv_cmp_btn_clicked()
{
    ui->textEdit_send_cmp->clear();
    ui->textEdit_file_cmp->clear();
    ui->textEdit_recv_cmp->clear();
}

void MainWindow::on_checkBox_crc_cmp_clicked(bool checked)
{
    cmp_crc_switch = checked;
}


void MainWindow::on_btn_modbus_send_clicked()
{
    if(ui->btn_modbus_send->text() == tr("开始"))
    {
        if(!write_str.isEmpty() && true == ui->stat_r_btn->isChecked())
        {
            cmp_send_index = 0;
            ui->btn_modbus_send->setText(tr("停止"));
            ui->lineEdit_time_modbus->setEnabled(false);
            modbus_send_timer.setInterval(ui->lineEdit_time_modbus->text().toInt());
            modbus_send_timer.start();
        }else
        {
            QMessageBox::critical(this, tr("Error"), "请先打开串口和文件后再发送!^ ^");
        }
    }
    else
    {
        ui->btn_modbus_send->setText(tr("开始"));
        ui->lineEdit_time_modbus->setEnabled(true);
        modbus_send_timer.stop();
    }
}

QByteArray MainWindow::get_send_buffer(QString send_text)
{
    unsigned char crc[2];
    QByteArray byte_arr;
    if(true == send_hex_switch)
    {
        byte_arr = HexStringToByteArray(send_text);
    }else
    {
        byte_arr = send_text.toUtf8();
    }
    if(true == crc16_check_switch){
        crc16(byte_arr,crc);
        byte_arr.append(crc[0]);
        byte_arr.append(crc[1]);
    }

    return byte_arr;
}

void MainWindow::on_btn_send_1_clicked()
{

    if(false == ui->stat_r_btn->isChecked()){
        QMessageBox::critical(this, tr("Error"), "请先打开串口！");
    }else
    {
        QString send_str = ui->textEdit_send_1->toPlainText();
        if(true == send_str_with_line){
            send_str += "\n";
        }
        QByteArray send_bytes = get_send_buffer(send_str);
        send_buffer(send_bytes);
    }


}

void MainWindow::on_btn_send_2_clicked()
{

    if(false == ui->stat_r_btn->isChecked()){
        QMessageBox::critical(this, tr("Error"), "请先打开串口！");
    }else
    {
        QString send_str = ui->textEdit_send_2->toPlainText();
        if(true == send_str_with_line){
            send_str += "\n";
        }
        QByteArray send_bytes = get_send_buffer(send_str);
        send_buffer(send_bytes);
    }


}

void MainWindow::on_btn_send_3_clicked()
{
    if(false == ui->stat_r_btn->isChecked()){
        QMessageBox::critical(this, tr("Error"), "请先打开串口！");
    }else
    {
        QString send_str = ui->textEdit_send_3->toPlainText();
        if(true == send_str_with_line){
            send_str += "\n";
        }
        QByteArray send_bytes = get_send_buffer(send_str);
        send_buffer(send_bytes);
    }
}

void MainWindow::on_btn_crc_1_clicked()
{
    QByteArray text_bytes = HexStringToByteArray(ui->textEdit_send_1->toPlainText());
    unsigned char crc_str[2];
    crc16(text_bytes,crc_str);
    text_bytes.append(crc_str[0]);
    text_bytes.append(crc_str[1]);
    QString text_string = ByteArrayToHexString(text_bytes);
    ui->textEdit_send_1->setText(text_string);
}

void MainWindow::on_btn_crc_2_clicked()
{
    QByteArray text_bytes = get_send_buffer(ui->textEdit_send_2->toPlainText());
    unsigned char crc_str[2];
    crc16(text_bytes,crc_str);
    text_bytes.append(crc_str[0]);
    text_bytes.append(crc_str[1]);
    QString text_string = ByteArrayToHexString(text_bytes);
    ui->textEdit_send_2->setText(text_string);
}

void MainWindow::on_btn_crc_3_clicked()
{
    QByteArray text_bytes = get_send_buffer(ui->textEdit_send_3->toPlainText());
    unsigned char crc_str[2];
    crc16(text_bytes,crc_str);
    text_bytes.append(crc_str[0]);
    text_bytes.append(crc_str[1]);
    QString text_string = ByteArrayToHexString(text_bytes);
    ui->textEdit_send_3->setText(text_string);
}

void MainWindow::on_checkBox_auto_send_1_clicked(bool checked)
{
    if(true == checked)
    {
        if(false == ui->stat_r_btn->isChecked()){
            QMessageBox::critical(this, tr("Error"), "请先打开串口！");
            ui->checkBox_auto_send_1->setChecked(false);
        }else
        {
            //send_timer_1.setInterval(ui->lineEdit_time_1->text().toInt());
            send_timer_1.start(ui->lineEdit_time_1->text().toInt());
            ui->lineEdit_time_1->setEnabled(!checked);
        }

    }else {
        send_timer_1.stop();
        ui->lineEdit_time_1->setEnabled(!checked);
    }

}

void MainWindow::on_checkBox_auto_send_2_clicked(bool checked)
{
    if(true == checked)
    {
        if(false == ui->stat_r_btn->isChecked()){
            QMessageBox::critical(this, tr("Error"), "请先打开串口！");
            ui->checkBox_auto_send_2->setChecked(false);
        }else
        {
            //send_timer_1.setInterval(ui->lineEdit_time_1->text().toInt());
            send_timer_2.start(ui->lineEdit_time_2->text().toInt());
            ui->lineEdit_time_2->setEnabled(!checked);
        }

    }else {
        send_timer_2.stop();
        ui->lineEdit_time_2->setEnabled(!checked);
    }
}

void MainWindow::on_checkBox_auto_send_3_clicked(bool checked)
{
    if(true == checked)
    {
        if(false == ui->stat_r_btn->isChecked()){
            QMessageBox::critical(this, tr("Error"), "请先打开串口！");
            ui->checkBox_auto_send_3->setChecked(false);
        }else
        {
            //send_timer_1.setInterval(ui->lineEdit_time_1->text().toInt());
            send_timer_3.start(ui->lineEdit_time_3->text().toInt());
            ui->lineEdit_time_3->setEnabled(!checked);
        }

    }else {
        send_timer_3.stop();
        ui->lineEdit_time_3->setEnabled(!checked);
    }
}

void MainWindow::on_checkBox_auto_send_4_clicked(bool checked)
{
    if(true == checked)
    {
        if(false == ui->stat_r_btn->isChecked()){
            QMessageBox::critical(this, tr("Error"), "请先打开串口！");
            ui->checkBox_auto_send_4->setChecked(false);
        }else {
            round_buffer_index = 0;
            stop_timer();
            enable_widget(false);
            round_send_timer.start(ui->lineEdit_time_round->text().toInt());
            ui->lineEdit_time_round->setEnabled(false);
            ui->checkBox_auto_send_4->setEnabled(true);
        }

    }else{
        round_send_timer.stop();
        ui->lineEdit_time_round->setEnabled(true);
        enable_widget(true);
    }
}


void MainWindow::on_checkBox_new_line_clicked(bool checked)
{
    send_str_with_line = checked;
}

void MainWindow::on_pushButton_new_thread_clicked()
{
    QString exe_path = QCoreApplication::applicationFilePath();
    QProcess new_Process;
    qDebug() << exe_path << endl;
    new_Process.startDetached(exe_path);
}

void MainWindow::on_checkBox_time_stamp_clicked(bool checked)
{
    recv_with_time_stamp = checked;
}

void MainWindow::on_btn_clear_count_clicked()
{
    send_bytes = 0;
    recv_bytes = 0;
    send_frames = 0;
    recv_frames = 0;

    ui->label_count_sb->setText("0");
    ui->label_count_rb->setText("0");
    ui->label_count_sfm->setText("0");
    ui->label_count_rfm->setText("0");

}
