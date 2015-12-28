#ifndef CHUNKPROPERTIESWIDGET_H
#define CHUNKPROPERTIESWIDGET_H

#include <QWidget>

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QPushButton>

class ChunkPropertiesWidget : public QWidget
{
private :
    Q_OBJECT
private :
    QSpinBox*       _QSpinBox_octave;
    QDoubleSpinBox* _QDoubleSpinBox_frequency;
    QSpinBox*       _QSpinBox_seed;

    QSpinBox*       _QSpinBox_chunkSize;
    QSpinBox*       _QSpinBox_chunkRange;

    QPushButton*    _pQPushButton_light;
    // QPushButton*    _pQPushButton_perturbation;

    QPushButton*    _pQPushButton_poly;
    QPushButton*    _pQPushButton_line;

public:
    explicit ChunkPropertiesWidget(QWidget *parent = 0);

signals:

public slots:
    void  valueChanged_octave(int);
    void  valueChanged_frequency(double);
    void  valueChanged_seed(int);

    void  valueChanged_chunkSize(int);
    void  valueChanged_chunkRange(int);

    void  valueChanged_light(bool);
    // void  valueChanged_perturbation(bool);

    void  valueChanged_poly(bool);
    void  valueChanged_line(bool);

};


#endif // CHUNKPROPERTIESWIDGET_H
