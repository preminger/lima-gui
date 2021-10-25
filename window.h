/****************************************************************************
**
** Copyright (C) 2021 Anders F Björklund
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef WINDOW_H
#define WINDOW_H

#include <QSystemTrayIcon>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QDialog>
#include <QProcess>

QT_BEGIN_NAMESPACE
class QAction;
class QComboBox;
class QFile;
class QGroupBox;
class QIcon;
class QLineEdit;
class QTableView;
class QMainWindow;
class QMenu;
class QPushButton;
class QStringList;
class QTemporaryDir;
class QTextEdit;
QT_END_NAMESPACE

#include "instance.h"

//! [0]
class Window : public QDialog
{
    Q_OBJECT

public:
    Window();

    void setVisible(bool visible) override;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void setIcon(int index);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void updateButtons();
    void startedCommand();
    void finishedCommand(int code, QProcess::ExitStatus status);

private:
    InstanceList getInstances();
    InstanceHash getInstanceHash();
    void createInstanceGroupBox();
    void createActions();
    void createTrayIcon();

    QString selectedInstance();
    void setSelectedInstance(QString instance);
    void updateInstances();
    void shellConsole();
    bool getProcessOutput(QStringList arguments, QString& text);
    void createEditor();
    void sendCommand(QString cmd);
    void sendCommand(QStringList cmds);
    void createInstance();
    void startInstance();
    void stopInstance();
    bool askConfirm(QString instance);
    void removeInstance();

    QComboBox *iconComboBox;

    QMainWindow *editWindow;
    QTemporaryDir *editDir;
    QFile *editFile;
    QLineEdit *createName;
    QTextEdit *createYAML;

    QGroupBox *instanceGroupBox;
    InstanceModel *instanceModel;
    QTableView *instanceListView;
    QPushButton *refreshButton;
    QPushButton *shellButton;
    QPushButton *createButton;
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *removeButton;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QProcess *process;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QIcon *trayIconIcon;
};
//! [0]

#endif // QT_NO_SYSTEMTRAYICON

#endif
