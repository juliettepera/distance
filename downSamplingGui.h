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
#include "meshQtDisplay.h"
#include "displayTools.h"
#include "ui_downSamplingGui.h"

class downSamplingGui: public QMainWindow, public Ui::downSamplingWindow
{
    Q_OBJECT

    public:

        downSamplingGui( QWidget * parent = 0, Qt::WFlags f = 0 );

        void setMeshList( std::vector <std::string> MeshList );
        void setWindow( meshQtDisplay WindowMesh );
        void initialization();
        void reset();
        void addOne( std::string Name );
        void deleteOne( int IndiceOfMesh );
        void setToolList();

    public slots:

        void pushButtonQuitClicked();
        void ChangeMeshSelected();
        void ChangeValueDensity();
        void applyDownSampling();

    private:
        std::vector <double> m_DensityList;
        std::vector <int> m_TypeList;

        int m_NumberOfMesh;
        int m_MeshSelected;

        meshQtDisplay m_MyWindowMesh;
        displayTools m_ActivTool;
};

#endif
