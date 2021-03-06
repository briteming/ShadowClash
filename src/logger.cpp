//
//  logger.cpp
//  ShadowClash
//
//  Created by TheWanderingCoel on 2019/11/7.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "paths.h"
#include "plog/Log.h"
#include "logger.h"

#include <QDir>
#include <QMessageBox>

QStringList Logger::logLevel = QStringList() << "silent" << "debug" << "info" << "warning" << "error";

void Logger::init()
{
    QDir dir(Paths::logsPath);
    if (!dir.exists()) {
        try {
            dir.mkpath(".");
        } catch (...) {
            showCreateLogDirFailAlert();
        }
    }
    plog::init(plog::verbose,Paths::logFilePath.toLocal8Bit().data());
}

void Logger::log(QString msg, QString level)
{
    switch(Logger::logLevel.indexOf(level)) {
        case 0 | 1:
            PLOG_DEBUG << msg;
            break;
        case 2:
            PLOG_INFO << msg;
            break;
        case 3:
            PLOG_WARNING << msg;
            break;
        case 4:
            PLOG_ERROR << msg;
            break;
    }
}

void Logger::showCreateLogDirFailAlert()
{
    QMessageBox alert;
    alert.setWindowTitle("ShadowClash");
    alert.setText(QString("ShadowClash fail to create %1 folder. Please check privileges or manually create folder and restart ShadowClash.").arg(Paths::logsPath));
    alert.addButton(tr("OK"), QMessageBox::YesRole);
    alert.exec();
}
