#include "mainwindow.h"
#include <QTime>
#include <QDate>
#include <QString>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(800, 450);
    setWindowTitle("Дата и время");

    // настройка и запуск таймера
    oneSecondTimer = new QTimer(this);
    oneSecondTimer->setInterval(1000);
    oneSecondTimer->start();

    // настройка надписи для вывода текущего времени
    currTimeLabel = new QLabel(QTime::currentTime().toString("hh:mm:ss"), this);
    currTimeLabel->setGeometry(10, 10, 780, 100);
    currTimeLabel->setAlignment(Qt::AlignCenter);
    QFont lblFont = currTimeLabel->font();
    lblFont.setPointSize(36);
    currTimeLabel->setFont(lblFont);

    // связь надписи с таймером
    connect(oneSecondTimer, &QTimer::timeout, this, [this]() {
        currTimeLabel->setText(QTime::currentTime().toString("hh:mm:ss"));
    });

    // поле ввода даты и времени
    dateTimeEdit = new QDateTimeEdit(this);
    dateTimeEdit->setGeometry(100, 130, 600, 30);
    dateTimeEdit->setDisplayFormat("dd.MM.yyyy hh:mm:ss");
    dateTimeEdit->setAlignment(Qt::AlignCenter);

    // дата и время в различных форматах
    listWidget = new QListWidget(this);
    listWidget->setGeometry(100, 180, 600, 100);

    // установка связи между полем ввода даты/времени с полями вывода
    connect(dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, [this]() {
        QString format1 = "dd.MM.yyyy hh:mm:ss";
        QString format2 = "yyyy-MM-dd hh-mm-ss";
        QString format3 = "ddd d MMM yyyy h:mm";
        listWidget->clear();
        listWidget->addItem(dateTimeEdit->dateTime().toString(format1) + "\t\t\t" + format1);
        listWidget->addItem(dateTimeEdit->dateTime().toString(format2) + "\t\t\t" + format2);
        listWidget->addItem(dateTimeEdit->dateTime().toString(format3) + "\t\t\t" + format3);
    });
    dateTimeEdit->setDateTime(QDateTime::currentDateTime());

    // поле ввода даты
    QLabel* birthDateLbl = new QLabel("Введите дату рождения:", this);
    birthDateLbl->setGeometry(100, 300, 600, 30);
    dateEdit = new QDateEdit(this);
    dateEdit->setGeometry(100, 340, 600, 30);
    dateEdit->setAlignment(Qt::AlignCenter);

    // поле для вывода оставшихся дней до дня рождения
    restTillBirthday = new QLabel("Дней до ближайшего дня рождения: ", this);
    restTillBirthday->setGeometry(100, 370, 600, 30);
    restTillBirthday->setAlignment(Qt::AlignCenter);

    // установка связи между полем ввода даты и надписью
    connect(dateEdit, &QDateEdit::dateChanged, this, [this]() {
        QDate currDate = QDate::currentDate();
        QDate birthDayDate(currDate.year(), dateEdit->date().month(), dateEdit->date().day());
        int daysTillBirthday = currDate.daysTo(birthDayDate);
        if (daysTillBirthday < 0) {
            birthDayDate.setDate(birthDayDate.year() + 1, birthDayDate.month(), birthDayDate.day());
            daysTillBirthday = currDate.daysTo(birthDayDate);
        }
        restTillBirthday->setText("Дней до ближайшего дня рождения: " + QString::number(daysTillBirthday));
    });
    dateEdit->setDate(QDate::currentDate());
}

MainWindow::~MainWindow() = default;

