#pragma once
#include <QMainWindow>
#include <cassert>
#include "../gpio-client.hpp"

namespace Ui {
class VPBreadboard;
}

struct Sevensegment
{
    QPoint offs;
    QPoint extent;
    uint8_t linewidth;
    uint8_t map;
    void draw(QPainter& p);
    Sevensegment() :
        offs(50,50), extent(100, 100), linewidth(10), map(0){};
    Sevensegment(QPoint offs, QPoint extent, uint8_t linewidth) :
        offs(offs), extent(extent), linewidth(linewidth), map(0){};
};

class VPBreadboard : public QWidget
{
    Q_OBJECT
    GpioClient gpio;
    Sevensegment sevensegment;
    uint64_t translateGpioToExtPin(Gpio::Reg& reg);
    uint8_t translatePinNumberToSevensegment(uint64_t pinmap);

public:
    VPBreadboard(QWidget *mparent = 0);
    ~VPBreadboard();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *e);

    void notifyChange(bool success);
};