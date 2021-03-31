#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    init();
    load();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_quitButton_clicked()
{
    QApplication::quit();
}

void Dialog::on_comboBox_currentIndexChanged(int index)
{
    ui->lineEdit->setText(QString::number(index) + " = " + ui->comboBox->currentText());

    qDebug() << "Index changed to" << metaEnum.value(index);
}

void Dialog::init()
{
    ui->comboBox->clear();

    int index = metaObject()->indexOfEnumerator("RSSElement");
    qDebug() << "index is" << index;

    metaEnum = metaObject()->enumerator(index);
    qDebug() << "metaEnum.keyCount is" << metaEnum.keyCount();

    for(int i=0; i<metaEnum.keyCount(); i++)
    {
        ui->comboBox->addItem(metaEnum.valueToKey(i));

        qDebug() << "metaEnum.key(" << i << ") = " << metaEnum.key(i);
    }
}

void Dialog::load()
{
    QCoreApplication::setOrganizationName("localQtBuiltApplications");
    QCoreApplication::setOrganizationDomain("MyCompany.com");
    QCoreApplication::setApplicationName("EnumClassOut");

    QSettings settings;
    settings.beginGroup("ComboBoxSettings");
    QVariant value = settings.value("settings", 0);
    settings.endGroup();
    qDebug() << "Loaded variant = " << value;

    bool ok;
    int index = value.toInt(&ok);
    qDebug() << "Loaded settings = " << index;

    if (!ok)
    {
        QMessageBox::critical(this, "Loading Error", "Error in loading selection!");
    }

    // The following warning message spit out by the following two lines
    // QPaintDevice::metrics: Device has no metric information
//    if (index >= ui->comboBox->colorCount())
//        index = 0;

    ui->comboBox->setCurrentIndex(index);
}

void Dialog::on_saveButton_clicked()
{
    QCoreApplication::setOrganizationName("localQtBuiltApplications");
    QCoreApplication::setOrganizationDomain("MyCompany.com");
    QCoreApplication::setApplicationName("EnumClassOut");

    int index = ui->comboBox->currentIndex();

    QSettings settings;
    settings.beginGroup("ComboBoxSettings");
    settings.setValue("settings", index);
    settings.endGroup();
    settings.sync();

    qDebug() << "Selected current index = " << index;

    QMessageBox::information(this, "Saved", "Selection saved. Please close and re-open the application.");
}
