#include "chunkpropertieswidget.h"

#include "navigator_globalvalue.h"


#include <QGridLayout>

#include <QLabel>


ChunkPropertiesWidget::ChunkPropertiesWidget(QWidget *parent) :
    QWidget(parent)
{


    QGridLayout*    pLayout = new QGridLayout(this);

    const char*   titles[] = {
        "octaves",
        "frequency",
        "seed",
        "chunkSize",
        "chunkRange",
        /**
        "light",
        "perturbation",
        "poly",
        "line",
        //*/
        NULL
    };

    for (int i = 0; titles[i]; ++i)
        pLayout->addWidget( new QLabel( titles[i] ), i,0 );


    const char*   titles2[] = {
        /**
        "octaves",
        "frequency",
        "seed",
        "chunkSize",
        "chunkRange",
        //*/
        "light",
        // "perturbation",
        "poly",
        "line",
        NULL
    };

    for (int i = 0; titles2[i]; ++i)
        pLayout->addWidget( new QLabel( titles2[i] ), i,2 );


    _QSpinBox_octave = new QSpinBox;
    _QSpinBox_octave->setValue(Navigator_GlobalValue::pTest->_octaves);
    _QSpinBox_octave->setRange(1, 50);
    _QSpinBox_octave->setSingleStep(1);
//    pLayout->addWidget( _QSpinBox_octave, 0,1 );
    connect(_QSpinBox_octave, SIGNAL(valueChanged(int)), this, SLOT(valueChanged_octave(int)));

    _QDoubleSpinBox_frequency = new QDoubleSpinBox;
    _QDoubleSpinBox_frequency->setValue(Navigator_GlobalValue::pTest->_frequency);
    _QDoubleSpinBox_frequency->setRange(0.01, 10.0);
    _QDoubleSpinBox_frequency->setSingleStep(0.1);
//    pLayout->addWidget( _QDoubleSpinBox_frequency, 1,1 );
    connect(_QDoubleSpinBox_frequency, SIGNAL(valueChanged(double)), this, SLOT(valueChanged_frequency(double)));

    _QSpinBox_seed = new QSpinBox;
    _QSpinBox_seed->setValue(Navigator_GlobalValue::pTest->_seed);
//    pLayout->addWidget( _QSpinBox_seed, 2,1 );
    connect(_QSpinBox_seed, SIGNAL(valueChanged(int)), this, SLOT(valueChanged_seed(int)));


    _QSpinBox_chunkSize = new QSpinBox;
    _QSpinBox_chunkSize->setValue(Navigator_GlobalValue::pTest->_chunkSize);
    _QSpinBox_chunkSize->setRange(5, 100);
//    pLayout->addWidget( _QSpinBox_chunkSize, 3,1 );
    connect(_QSpinBox_chunkSize, SIGNAL(valueChanged(int)), this, SLOT(valueChanged_chunkSize(int)));

    _QSpinBox_chunkRange = new QSpinBox;
    _QSpinBox_chunkRange->setValue(Navigator_GlobalValue::pTest->_chunkRange);
    _QSpinBox_chunkRange->setRange(1, 5);
//    pLayout->addWidget( _QSpinBox_chunkRange, 4,1 );
    connect(_QSpinBox_chunkRange, SIGNAL(valueChanged(int)), this, SLOT(valueChanged_chunkRange(int)));

    _pQPushButton_light = new QPushButton();
    _pQPushButton_light->setCheckable(true);
    _pQPushButton_light->setChecked( Navigator_GlobalValue::pTest->_lightEnabled );
    valueChanged_light( _pQPushButton_light->isChecked() );
//    pLayout->addWidget( _pQPushButton_light, 5,1 );
    connect(_pQPushButton_light, SIGNAL(clicked(bool)), this, SLOT(valueChanged_light(bool)));

//     _pQPushButton_perturbation = new QPushButton();
//     _pQPushButton_perturbation->setCheckable(true);
//     _pQPushButton_perturbation->setChecked( Navigator_GlobalValue::pTest->_perturbationEnabled );
//     valueChanged_perturbation( _pQPushButton_perturbation->isChecked() );
// //    pLayout->addWidget( _pQPushButton_perturbation, 6,1 );
//     connect(_pQPushButton_perturbation, SIGNAL(clicked(bool)), this, SLOT(valueChanged_perturbation(bool)));



    _pQPushButton_poly = new QPushButton();
    _pQPushButton_poly->setCheckable(true);
    _pQPushButton_poly->setChecked( Navigator_GlobalValue::pTest->_polyEnabled );
    valueChanged_poly( _pQPushButton_poly->isChecked() );
//    pLayout->addWidget( _pQPushButton_poly, 7,1 );
    connect(_pQPushButton_poly, SIGNAL(clicked(bool)), this, SLOT(valueChanged_poly(bool)));

    _pQPushButton_line = new QPushButton();
    _pQPushButton_line->setCheckable(true);
    _pQPushButton_line->setChecked( Navigator_GlobalValue::pTest->_lineEnabled );
    valueChanged_line( _pQPushButton_line->isChecked() );
//    pLayout->addWidget( _pQPushButton_line, 8,1 );
    connect(_pQPushButton_line, SIGNAL(clicked(bool)), this, SLOT(valueChanged_line(bool)));


    QWidget*    column1[] = {
        _QSpinBox_octave,
        _QDoubleSpinBox_frequency,
        _QSpinBox_seed,
        _QSpinBox_chunkSize,
        _QSpinBox_chunkRange,
        /**
        _pQPushButton_light,
        _pQPushButton_perturbation,
        _pQPushButton_poly,
        _pQPushButton_line,
        //*/
        NULL
    };

    QWidget*    column2[] = {
        /**
        _QSpinBox_octave,
        _QDoubleSpinBox_frequency,
        _QSpinBox_seed,
        _QSpinBox_chunkSize,
        _QSpinBox_chunkRange,
        //*/
        _pQPushButton_light,
        // _pQPushButton_perturbation,
        _pQPushButton_poly,
        _pQPushButton_line,

        //_QSpinBox_chunkRange,

        NULL
    };

    for (int i = 0; column1[i]; ++i)
        pLayout->addWidget( column1[i], i,1 );

    for (int i = 0; column2[i]; ++i)
        pLayout->addWidget( column2[i], i,3 );

}


void  ChunkPropertiesWidget::valueChanged_octave(int)
{
    Navigator_GlobalValue::pTest->_octaves = _QSpinBox_octave->value();
    Navigator_GlobalValue::pTest->_update_needed = true;
}

void  ChunkPropertiesWidget::valueChanged_frequency(double)
{
    Navigator_GlobalValue::pTest->_frequency = _QDoubleSpinBox_frequency->value();
    Navigator_GlobalValue::pTest->_update_needed = true;
}


void  ChunkPropertiesWidget::valueChanged_seed(int)
{
    Navigator_GlobalValue::pTest->_seed = _QSpinBox_seed->value();
    Navigator_GlobalValue::pTest->_update_needed = true;
}

void    ChunkPropertiesWidget::valueChanged_chunkSize(int)
{
    Navigator_GlobalValue::pTest->_chunkSize = _QSpinBox_chunkSize->value();
    Navigator_GlobalValue::pTest->_update_needed = true;
}

void    ChunkPropertiesWidget::valueChanged_chunkRange(int)
{
    Navigator_GlobalValue::pTest->_chunkRange = _QSpinBox_chunkRange->value();
    Navigator_GlobalValue::pTest->_update_needed = true;
}

void    ChunkPropertiesWidget::valueChanged_light(bool value)
{
    Navigator_GlobalValue::pTest->_lightEnabled = value;

    _pQPushButton_light->setText( value ? "On" : "Off" );
}

// void    ChunkPropertiesWidget::valueChanged_perturbation(bool value)
// {
//     Navigator_GlobalValue::pTest->_perturbationEnabled = value;

//     _pQPushButton_perturbation->setText( value ? "On" : "Off" );
// }


void    ChunkPropertiesWidget::valueChanged_poly(bool value)
{
    Navigator_GlobalValue::pTest->_polyEnabled = value;

    _pQPushButton_poly->setText( value ? "On" : "Off" );
}

void    ChunkPropertiesWidget::valueChanged_line(bool value)
{
    Navigator_GlobalValue::pTest->_lineEnabled = value;

    _pQPushButton_line->setText( value ? "On" : "Off" );
}
