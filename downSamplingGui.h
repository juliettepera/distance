#ifndef DOWNSAMPLINGGUI_H
#define DOWNSAMPLINGGUI_H

// Qt libraries
#include <QFont>
#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <QApplication>
#include <QLCDNumber>
#include <QSlider>
#include <QMessageBox>
#include <QMainWindow>
#include <QFileDialog>
#include <QTextBrowser>
#include <QListWidgetItem>
#include <QListWidget>
#include <QLineEdit>

// Other Libraries
#include <string>
#include <iostream>

// My Libraries
#include "display.h"
#include "data.h"
#include "processing.h"
#include "ui_downSamplingGui.h"

class downSamplingGui: public QMainWindow, public Ui::downSamplingWindow
{
    Q_OBJECT

    public:
        downSamplingGui( QWidget * parent = 0, Qt::WFlags f = 0 );

        void setWindow( display WindowMesh );
        void setProcess( processing Process );
        void setData( std::vector <data::data> DataList );

        void reset();
        void addOne( std::string Name );
        void deleteOne( int IndiceOfMesh );

    public slots:
        void pushButtonQuitClicked();
        void ChangeMeshSelected();

        void ChangeValueDecimate();
        void applyDownSampling();

    private:
        int m_NumberOfMesh;
        int m_MeshSelected;

        display m_MyWindowMesh;
        processing m_MyProcess;
        std::vector <data::data> m_DataList;
};

#endif
