#include <QPainter>
#include <iostream>
#include "alphablending.h"

alphaBlending::alphaBlending(QWidget *parent)
    : QWidget{parent}
{
    int p_height = 1000;
    int p_width = 1000;
    im = QImage(p_width, p_height, QImage::Format_RGB32);

    //Obrazy + ustawienia początkowe
    Layer layer1;
    layer1.im = new QImage();
    layer1.im->load("C:/Users/rosia/OneDrive/Pulpit/Studia/Grafika Komputerowa/AlphaBlending/AlphaBlending/red.jpg");
    layer1.alpha = 0;
    layer1.mode = 1;
    layers.push_back(layer1);

    Layer layer2;
    layer2.im = new QImage();
    layer2.im->load("/Users/rosia/OneDrive/Pulpit/Studia/Grafika Komputerowa/AlphaBlending/AlphaBlending/green.jpg");
    layer2.alpha = 0;
    layer2.mode = 1;
    layers.push_back(layer2);

    Layer layer3;
    layer3.im = new QImage();
    layer3.im->load("/Users/rosia/OneDrive/Pulpit/Studia/Grafika Komputerowa/AlphaBlending/AlphaBlending/blue.jpg");
    layer3.alpha = 0;
    layer3.mode = 1;
    layers.push_back(layer3);
}

void alphaBlending::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::white);
    p.drawImage(0, 0, im);
    blend();
}

//Funkcja Alpha Blending
void alphaBlending::blend()
{
    im.fill(Qt::white);
    for (int i = (int)layers.size(); i>=0; i--)
    {
        if (layers[i].alpha == 0) continue;
        /*
         * Opis:
           Przy użyciu trybu normalnego tło jest całkowicie pokryte przez warstwę mieszania,
           więc powinieneś mieć pewną przezroczystość, jeśli używasz tego trybu.
            kolorR = αR ∗ kolor_pierwszoplanowyR + (1 − αR) ∗ kolor_tłaR
            kolorG = αG ∗ kolor_pierwszoplanowyG + (1 − αG ) ∗ kolor_tłaG
            kolorB = αB ∗ kolor_pierwszoplanowyB + (1 − αB ) ∗ kolor_tłaB

        */
        if (layers[i].mode == 1) //NORMAL
        {
            float alpha = layers[i].alpha / 100.0f; //zamaiana do przedziału [0:1]
            for (int y = 0; y < 500; y++)
            {
                for (int x = 0; x < 500; x++)
                {
                    uchar *pix1 = im.scanLine(y)+4*x;//pix1 kolor tla
                    uchar *pix2 = layers[i].im->scanLine(y)+4*x;//pix2 kolor pierwszoplanowy

                    pix1[0] = (int)(alpha * pix2[0] + (1 - alpha) * pix1[0]);
                    pix1[1] = (int)(alpha * pix2[1] + (1 - alpha) * pix1[1]);
                    pix1[2] = (int)(alpha * pix2[2] + (1 - alpha) * pix1[2]);
                }
            }
            update();
        }
        /*
            Opis:
            Oba parametry są po prostu mnożone przez siebie.
            W większości przypadków zwraca to wynik ciemniejszy niż oba parametry wejściowe
            (za wyjątkiem sytuacji, gdy jeden z nich jest równy 1). Całkowicie białe warstwy
            nie zmieniają tła wcale (i odwrotnie) - całkowicie czarne warstwy dają wynik czarny.
            f (a, b) = (a ∗ b) >> 8,
            a - kolor tła
            b - kolor obrazu
        */
        else if (layers[i].mode == 2) //MULTIPLY
        {
            float alpha = layers[i].alpha / 100.0f;
            for (int y = 0; y < 500; y++)
            {
                for (int x = 0; x < 500; x++)
                {
                    uchar *pix1 = im.scanLine(y)+4*x;
                    uchar *pix2 = layers[i].im->scanLine(y)+4*x;

                    int b=(pix1[0] * pix2[0]) >> 8;
                    int g=(pix1[1] * pix2[1]) >> 8;
                    int r=(pix1[2] * pix2[2]) >> 8;

                    pix1[0] = (int)(alpha * b + (1 - alpha) * pix1[0]);
                    pix1[1] = (int)(alpha * g + (1 - alpha) * pix1[1]);
                    pix1[2] = (int)(alpha * r + (1 - alpha) * pix1[2]);
                }
            }
            update();
        }
        /*
            Opis:
            "Przeciwność" dla trybu mnożenia. Oba parametry są odwrócone, pomnożone przez siebie,
            a następnie wynik jest ponownie odwracany. W większości przypadków daje to jaśniejszy
            wynik niż oba parametry wejściowe (za wyjątkiem sytuacji, gdy jeden z nich równa się 0).
            Całkowicie czarne warstwy nie zmieniają tła w ogóle (i odwrotnie) - całkowicie białe warstwy dają biały wynik.
            Średnia z trybu mnożenia i trybu screen to dokładnie tryb średniej.
            f (a, b) = 255 − ((255 − a) ∗ (255 − b) >> 8),
        */
        else if (layers[i].mode == 3) //SCREEN
        {
            float alpha = layers[i].alpha / 100.0f;
            for (int y = 0; y < 500; y++)
            {
                for (int x = 0; x < 500; x++)
                {
                    uchar *pix1 = im.scanLine(y)+4*x;
                    uchar *pix2 = layers[i].im->scanLine(y)+4*x;

                    int b= 255 - ((255- pix1[0]) * (255 - pix2[0]) >> 8);
                    int g= 255 - ((255- pix1[1]) * (255 - pix2[1]) >> 8);
                    int r= 255 - ((255- pix1[2]) * (255 - pix2[2]) >> 8);

                    pix1[0] = (int)(alpha * b + (1 - alpha) * pix1[0]);
                    pix1[1] = (int)(alpha * g + (1 - alpha) * pix1[1]);
                    pix1[2] = (int)(alpha * r + (1 - alpha) * pix1[2]);
                }
            }
            update();
        }
        /*
            Opis:
            Oba parametry są porównywane ze sobą, bierze się mniejszą wartość.
            Całkowicie białe warstwy nie zmieniają tła wcale (i vice versa) - całkowicie czarne warstwy dają czarny rezultat.
            f (a, b) =
            a dla a < b
            b dla a >= b
,
        */
        else if (layers[i].mode == 4) //DARKEN
        {
            float alpha = layers[i].alpha / 100.0f;
            for (int y = 0; y < 500; y++)
            {
                for (int x = 0; x < 500; x++)
                {
                    uchar *pix1 = im.scanLine(y)+4*x;
                    uchar *pix2 = layers[i].im->scanLine(y)+4*x;

                    int b = (pix1[0] < pix2[0]) ? pix1[0] : pix2[0];
                    int g = (pix1[1] < pix2[1]) ? pix1[1] : pix2[1];
                    int r = (pix1[2] < pix2[2]) ? pix1[2] : pix2[2];

                    pix1[0] = (int)(alpha * b + (1 - alpha) * pix1[0]);
                    pix1[1] = (int)(alpha * g + (1 - alpha) * pix1[1]);
                    pix1[2] = (int)(alpha * r + (1 - alpha) * pix1[2]);
                }
            }
            update();
        }
        /*
            Opis:
            Oba parametry są porównywane między sobą, bierze się większy z nich (jak się spodziewasz,
            ten jest przeciwny do trybu przyciemniania). Całkowicie czarne warstwy w ogóle nie zmieniają
            tła (i odwrotnie) - całkowicie białe warstwy dają biały rezultat.
            f (a, b) =
            a dla a > b
            b dla a <= b
        */
        else if (layers[i].mode == 5) //LIGHTEN
        {
            float alpha = layers[i].alpha / 100.0f;
            for (int y = 0; y < 500; y++)
            {
                for (int x = 0; x < 500; x++)
                {
                    uchar *pix1 = im.scanLine(y)+4*x;
                    uchar *pix2 = layers[i].im->scanLine(y)+4*x;

                    int b = (pix1[0] > pix2[0]) ? pix1[0] : pix2[0];
                    int g = (pix1[1] > pix2[1]) ? pix1[1] : pix2[1];
                    int r = (pix1[2] > pix2[2]) ? pix1[2] : pix2[2];

                    pix1[0] = (int)(alpha * b + (1 - alpha) * pix1[0]);
                    pix1[1] = (int)(alpha * g + (1 - alpha) * pix1[1]);
                    pix1[2] = (int)(alpha * r + (1 - alpha) * pix1[2]);
                }
            }
            update();
        }
    }
}
//Do Trybów
void alphaBlending::buttonNormal()
{
    layers[photo-1].mode=1;
    std::cout<<"Tryb:"<<layers[photo-1].mode<<", zdjecie:"<< photo << std::endl;
    blend();
}

void alphaBlending::buttonMultiply()
{
    layers[photo-1].mode=2;
    std::cout<<"Tryb:"<<layers[photo-1].mode<<", zdjecie:"<< photo << std::endl;
    blend();
}

void alphaBlending::buttonScreen()
{
    layers[photo-1].mode=3;
    std::cout<<"Tryb:"<<layers[photo-1].mode<<", zdjecie:"<< photo << std::endl;
    blend();
}

void alphaBlending::buttonDarken()
{
    layers[photo-1].mode=4;
    std::cout<<"Tryb:"<<layers[photo-1].mode<<", zdjecie:"<< photo << std::endl;
    blend();
}

void alphaBlending::buttonLighten()
{
    layers[photo-1].mode=5;
    std::cout<<"Tryb:"<<layers[photo-1].mode<<", zdjecie:"<< photo << std::endl;
    blend();
}

void alphaBlending::image1()
{
    photo=1;
    std::cout<<"Zdjecie:"<<photo<<std::endl;
}

void alphaBlending::image2()
{
    photo=2;
    std::cout<<"Zdjecie:"<<photo<<std::endl;
}

void alphaBlending::image3()
{
    photo=3;
    std::cout<<"Zdjecie:"<<photo<<std::endl;
}

//Do suwaków od Wartości
void alphaBlending::Slider1(int value)
{
    layers[0].alpha = value;
    blend();
}

void alphaBlending::Slider2(int value)
{
    layers[1].alpha = value;
    blend();
}

void alphaBlending::Slider3(int value)
{
    layers[2].alpha = value;
    blend();
}



