#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QDateEdit>
#include <QDateTimeEdit>
#include <QListWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QTimer* oneSecondTimer;
    QLabel* currTimeLabel;
    QDateTimeEdit* dateTimeEdit;
    QDateEdit* dateEdit;
    QListWidget* listWidget;
    QLabel* restTillBirthday;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
};
#endif // MAINWINDOW_H
