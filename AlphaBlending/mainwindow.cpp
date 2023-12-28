#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Przyciski
    connect(ui->normal, SIGNAL(clicked()), this, SLOT(buttonNormalClicked()));
    connect(ui->multiply, SIGNAL(clicked()), this, SLOT(buttonMultiplyClicked()));
    connect(ui->screen, SIGNAL(clicked()), this, SLOT(buttonScreenClicked()));
    connect(ui->darken, SIGNAL(clicked()), this, SLOT(buttonDarkenClicked()));
    connect(ui->lighten, SIGNAL(clicked()), this, SLOT(buttonLightenClicked()));

    connect(ui->normal, SIGNAL(clicked()), ui->widget, SLOT(buttonNormal()));
    connect(ui->multiply, SIGNAL(clicked()), ui->widget, SLOT(buttonMultiply()));
    connect(ui->screen, SIGNAL(clicked()), ui->widget, SLOT(buttonScreen()));
    connect(ui->darken, SIGNAL(clicked()), ui->widget, SLOT(buttonDarken()));
    connect(ui->lighten, SIGNAL(clicked()), ui->widget, SLOT(buttonLighten()));

    //Wybranie zdjecia
    connect(ui->Image1Button, SIGNAL(clicked()), this, SLOT(buttonImage1Clicked()));
    connect(ui->Image2Button, SIGNAL(clicked()), this, SLOT(buttonImage2Clicked()));
    connect(ui->Image3Button, SIGNAL(clicked()), this, SLOT(buttonImage3Clicked()));

    connect(ui->Image1Button, SIGNAL(clicked()), ui->widget, SLOT(image1()));
    connect(ui->Image2Button, SIGNAL(clicked()), ui->widget, SLOT(image2()));
    connect(ui->Image3Button, SIGNAL(clicked()), ui->widget, SLOT(image3()));

    //Suwaki

    /*Image1*/
    connect(ui->img1Slider, SIGNAL(valueChanged(int)), ui->widget, SLOT(Slider1(int)));
    connect(ui->img1SB, SIGNAL(valueChanged(int)), ui->widget, SLOT(Slider1(int)));
    connect(ui->img1Slider,  &QSlider::valueChanged, ui->img1SB, &QSpinBox::setValue);
    connect(ui->img1SB, QOverload<int>::of(&QSpinBox::valueChanged), ui->img1Slider, &QSlider::setValue);
    ui->img1Slider->setRange(0, 100);
    ui->img1SB->setRange(0, 100);
    ui->img1Slider->setValue(100);
    ui->img1Slider->setEnabled(false);
    ui->img1SB->setEnabled(false);
    /*Image2*/
    connect(ui->img2Slider, SIGNAL(valueChanged(int)), ui->widget, SLOT(Slider2(int)));
    connect(ui->img2SB, SIGNAL(valueChanged(int)), ui->widget, SLOT(Slider2(int)));
    connect(ui->img2Slider,  &QSlider::valueChanged, ui->img2SB, &QSpinBox::setValue);
    connect(ui->img2SB, QOverload<int>::of(&QSpinBox::valueChanged), ui->img2Slider, &QSlider::setValue);
    ui->img2Slider->setRange(0, 100);
    ui->img2SB->setRange(0, 100);
    ui->img2Slider->setValue(100);
    ui->img2Slider->setEnabled(false);
    ui->img2SB->setEnabled(false);
    /*Image3*/
    connect(ui->img3Slider, SIGNAL(valueChanged(int)), ui->widget, SLOT(Slider3(int)));
    connect(ui->img3SB, SIGNAL(valueChanged(int)), ui->widget, SLOT(Slider3(int)));
    connect(ui->img3Slider,  &QSlider::valueChanged, ui->img3SB, &QSpinBox::setValue);
    connect(ui->img3SB, QOverload<int>::of(&QSpinBox::valueChanged), ui->img3Slider, &QSlider::setValue);
    ui->img3Slider->setRange(0, 100);
    ui->img3SB->setRange(0, 100);
    ui->img3Slider->setValue(100);
    ui->img3Slider->setEnabled(false);
    ui->img3SB->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonNormalClicked()
{
    QString nazwa = ui->normal->text();  // Pobierz nazwę przycisku
    // Sprawdź, czy użytkownik wybrał zdjęcie
    if (ui->ImageLabel->text().isEmpty())
    {
        QMessageBox::warning(this, "Błąd", "Najpierw wybierz zdjęcie!\nNastępnie tryb aby odblokować suwaki!");
        return;
    }
    ui->nazwaLabel->setText(nazwa);  // Ustaw tekst w Labelu na pobraną nazwę
    ui->trybLabel->setText("1");
    ui->img1Slider->setEnabled(true);
    ui->img2Slider->setEnabled(true);
    ui->img3Slider->setEnabled(true);
    ui->img1SB->setEnabled(true);
    ui->img2SB->setEnabled(true);
    ui->img3SB->setEnabled(true);

}

void MainWindow::buttonMultiplyClicked()
{
    QString nazwa = ui->multiply->text();  // Pobierz nazwę przycisku
    if (ui->ImageLabel->text().isEmpty())
    {
        QMessageBox::warning(this, "Błąd", "Najpierw wybierz zdjęcie!\nNastępnie tryb aby odblokować suwaki!");
        return;
    }
    ui->nazwaLabel->setText(nazwa);  // Ustaw tekst w Labelu na pobraną nazwę
    ui->trybLabel->setText("2");
    ui->img1Slider->setEnabled(true);
    ui->img2Slider->setEnabled(true);
    ui->img3Slider->setEnabled(true);
    ui->img1SB->setEnabled(true);
    ui->img2SB->setEnabled(true);
    ui->img3SB->setEnabled(true);
}

void MainWindow::buttonScreenClicked()
{
    QString nazwa = ui->screen->text();  // Pobierz nazwę przycisku
    if (ui->ImageLabel->text().isEmpty())
    {
        QMessageBox::warning(this, "Błąd", "Najpierw wybierz zdjęcie!\nNastępnie tryb aby odblokować suwaki!");
        return;
    }
    ui->nazwaLabel->setText(nazwa);  // Ustaw tekst w Labelu na pobraną nazwę
    ui->trybLabel->setText("3");
    ui->img1Slider->setEnabled(true);
    ui->img2Slider->setEnabled(true);
    ui->img3Slider->setEnabled(true);
    ui->img1SB->setEnabled(true);
    ui->img2SB->setEnabled(true);
    ui->img3SB->setEnabled(true);
}

void MainWindow::buttonDarkenClicked()
{
    QString nazwa = ui->darken->text();  // Pobierz nazwę przycisku
    if (ui->ImageLabel->text().isEmpty())
    {
        QMessageBox::warning(this, "Błąd", "Najpierw wybierz zdjęcie!\nNastępnie tryb aby odblokować suwaki!");
        return;
    }
    ui->nazwaLabel->setText(nazwa);  // Ustaw tekst w Labelu na pobraną nazwę
    ui->trybLabel->setText("4");
    ui->img1Slider->setEnabled(true);
    ui->img2Slider->setEnabled(true);
    ui->img3Slider->setEnabled(true);
    ui->img1SB->setEnabled(true);
    ui->img2SB->setEnabled(true);
    ui->img3SB->setEnabled(true);
}

void MainWindow::buttonLightenClicked()
{
    QString nazwa = ui->lighten->text();  // Pobierz nazwę przycisku
    if (ui->ImageLabel->text().isEmpty())
    {
        QMessageBox::warning(this, "Błąd", "Najpierw wybierz zdjęcie!\nNastępnie tryb aby odblokować suwaki!");
        return;
    }
    ui->nazwaLabel->setText(nazwa);  // Ustaw tekst w Labelu na pobraną nazwę
    ui->trybLabel->setText("5");
    ui->img1Slider->setEnabled(true);
    ui->img2Slider->setEnabled(true);
    ui->img3Slider->setEnabled(true);
    ui->img1SB->setEnabled(true);
    ui->img2SB->setEnabled(true);
    ui->img3SB->setEnabled(true);
}

void MainWindow::buttonImage1Clicked()
{
    QString nazwa = ui->Image1Button->text();  // Pobierz nazwę przycisku
    ui->ImageLabel->setText(nazwa);  // Ustaw tekst w Labelu na pobraną nazwę
}

void MainWindow::buttonImage2Clicked()
{
    QString nazwa = ui->Image2Button->text();  // Pobierz nazwę przycisku
    ui->ImageLabel->setText(nazwa);  // Ustaw tekst w Labelu na pobraną nazwę
}

void MainWindow::buttonImage3Clicked()
{
    QString nazwa = ui->Image3Button->text();  // Pobierz nazwę przycisku
    ui->ImageLabel->setText(nazwa);  // Ustaw tekst w Labelu na pobraną nazwę
}

