#include "common.h"
#include<QMessageBox>

int find_port(QStringList com_list,QString com_text)
{
    for(int i = 0;i < com_list.count();i++)
    {
        if(com_list.at(i) == com_text){
            return 1;
        }
    }
    return 0;
}
QString ByteArrayToHexString(QByteArray data){
    QString ret(data.toHex().toUpper());
    int len = ret.length()/2;
    for(int i=1;i<len;i++)
    {
        ret.insert(2*i+i-1," ");
    }

    return ret;
}

QByteArray HexStringToByteArray(QString HexString)
{
    bool ok;
    QByteArray ret;
    HexString = HexString.trimmed();
    HexString = HexString.simplified();
    QStringList sl = HexString.split(" ");

    foreach (QString s, sl)
    {
        if(!s.isEmpty())
        {
            char c = s.toInt(&ok,16)&0xFF;
            if(ok){
                ret.append(c);
            }else{
                qDebug()<<"非法的16进制字符："<<s;
                //QMessageBox::warning(0,"错误：",QString("非法的16进制字符: \"%1\"").arg(s));
            }
        }
    }
    return ret;
}

QString GetlLineString(QString str,int line)
{
    QStringList sl = str.split("\n");
    QString s;
    int i = 0;
    foreach (s, sl)
    {
        if(i == line){
            return s;
        }
        i++;
    }
    return "";
}


bool hexStrCmp(QString lstring,QString sstring)
{
    QByteArray arr1 = HexStringToByteArray(lstring);
    QByteArray arr2 = HexStringToByteArray(sstring);

    qDebug() << "lineStrCmp "<< lstring << endl << sstring << endl;
    return arr1 == arr2;
}
