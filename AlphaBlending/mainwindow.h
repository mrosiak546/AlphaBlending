
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void buttonNormalClicked();
    void buttonMultiplyClicked();
    void buttonScreenClicked();
    void buttonDarkenClicked();
    void buttonLightenClicked();
    void buttonImage1Clicked();
    void buttonImage2Clicked();
    void buttonImage3Clicked();
};

#endif // MAINWINDOW_H
