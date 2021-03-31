#pragma once

#include <QDebug>
#include <QDialog>
#include <QMessageBox>
#include <QMetaEnum>
#include <QPushButton>
#include <QSettings>
#include <QVariant>
#include "definition.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT
    Q_ENUMS(RSSElement)

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_quitButton_clicked();
    void on_saveButton_clicked();
    void on_comboBox_currentIndexChanged(int index);

private:
    void init();
    void load();

private:
    Ui::Dialog *ui;
    QMetaEnum metaEnum;
};
