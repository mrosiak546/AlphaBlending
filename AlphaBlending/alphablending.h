
#ifndef ALPHABLENDING_H
#define ALPHABLENDING_H


#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QString>
#include <vector>

class Layer
{
public:
    QImage *im;
    float alpha;
    int mode;
    Layer() {};
};


class alphaBlending : public QWidget
{
    Q_OBJECT
public:
    explicit alphaBlending(QWidget *parent = nullptr);
private:
    //zmienne
    QImage im;
    std::vector<Layer> layers;
    int tryb;
    int photo;
    //funkcje
    void paintEvent(QPaintEvent *);
    void blend();
public slots:
    //DO WARTOŚCI
    void Slider1(int value);
    void Slider2(int value);
    void Slider3(int value);
    void image1();
    void image2();
    void image3();
    //DO TRYBY
    void buttonNormal();
    void buttonMultiply();
    void buttonScreen();
    void buttonDarken();
    void buttonLighten();

signals:

};

#endif // ALPHABLENDING_H
