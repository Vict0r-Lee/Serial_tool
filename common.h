#ifndef COMMON_H
#define COMMON_H

#include "mainwindow.h"

int find_port(QStringList com_list,QString com_text);
QString ByteArrayToHexString(QByteArray data);
QByteArray HexStringToByteArray(QString HexString);
QString GetlLineString(QString str,int line);
bool hexStrCmp(QString lstring,QString sstring);
#endif // COMMON_H
