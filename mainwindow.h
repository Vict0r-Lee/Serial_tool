#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QList>
#include <QDebug>
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

    void CloseSerialPort();
    void scan_port();
    void setup_ui_1st_set(bool show);
    void setup_ui_2ed_set(bool show);
    void enable_widget(bool enable);
    void enable_serial_param(bool serial_param);
    void set_checkbox_false();
    void stop_timer();
    void send_buffer(QByteArray buffer);
    QByteArray get_send_buffer(QString send_text);

private slots:
    void on_btn_openConsole_clicked();

    void on_clear_recv_btn_clicked();

    void check_open_port();

    void readData();

    void round_buffer_send();

    void on_fresh_port_btn_clicked();

    void on_checkBox_recv_hex_clicked(bool checked);

    void on_checkBox_send_hex_clicked(bool checked);

    void on_checkBox_crc_clicked(bool checked);



    void on_toolButton_file_clicked();

    void on_checkBox_modbus_test_clicked(bool checked);

    void on_clear_recv_cmp_btn_clicked();

    void modbus_check_send();

    void on_checkBox_crc_cmp_clicked(bool checked);

    void on_btn_send_1_clicked();

    void on_btn_send_2_clicked();

    void on_btn_send_3_clicked();

    void on_btn_crc_1_clicked();

    void on_btn_crc_2_clicked();

    void on_btn_crc_3_clicked();

    void on_btn_modbus_send_clicked();

   void on_checkBox_auto_send_1_clicked(bool checked);
    void on_checkBox_auto_send_2_clicked(bool checked);

    void on_checkBox_auto_send_3_clicked(bool checked);

    void on_checkBox_auto_send_4_clicked(bool checked);

    void on_checkBox_new_line_clicked(bool checked);

    void on_pushButton_new_thread_clicked();

    void on_checkBox_time_stamp_clicked(bool checked);

    void on_btn_clear_count_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QTimer check_timer;
    QTimer send_timer_1;
    QTimer send_timer_2;
    QTimer send_timer_3;
    QTimer round_send_timer;

    QTimer modbus_send_timer;
    QString write_str;
    QString cmp_str;
    bool modbus_test_switch= false;     //modbus测试开关
    bool recv_hex_switch = false;       //十六进制显示接收开关
    bool send_hex_switch = false;       //十六进制发送开关
    bool crc16_check_switch = false;    //补CRC16开关
    bool cmp_crc_switch = false;        //CRC16比较开关
    bool send_str_with_line = false;            //发送加换行符判断
    bool recv_with_time_stamp = false;          //时间戳显示开关

    int cmp_send_index;                 //modbus测试发送行
    int round_buffer_index;             //轮发进度

    int send_bytes = 0;                     //发字节数
    int recv_bytes = 0;                     //收字节数
    int send_frames = 0;                    //发帧数
    int recv_frames = 0;                    //收帧数
};

#endif // MAINWINDOW_H
