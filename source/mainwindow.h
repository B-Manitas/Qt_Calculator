#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    double computeOperation(QString const &operatorValue,
                            double const& x, double const& y);

public slots:
    void digitPressed();
    void operatorPressed();
    void resetOperation();
    void negativeNb();

private:
    Ui::MainWindow *ui;
    QString *m_xStr, *m_yStr, *m_operator, *m_nan;
    double *m_xValue, *m_yValue;
    int *m_nbMax;
};
#endif // MAINWINDOW_H
