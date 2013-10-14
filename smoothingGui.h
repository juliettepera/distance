#ifndef SMOOTHINGGUI_H
#define SMOOTHINGGUI_H

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
#include "ui_smoothingGui.h"

class smoothingGui: public QMainWindow, public Ui::SmoothingWindow
{
    Q_OBJECT

    public:
        smoothingGui( QWidget * parent = 0, Qt::WFlags f = 0 );

        void setWindow( display WindowMesh );
        void setProcess( processing Process );
        void setIcon( QIcon Visible , QIcon Unvisible );
        void setData( std::vector <data::data> DataList );

        void reset();
        void addOne( std::string Name );
        void deleteOne( int IndiceOfMesh );

    public slots:
        void pushButtonQuitClicked();
        void ChangeMeshSelected();

        void ChangeValueSmoothing();
        void ChangeDisplaySmoothing();
        void applySmoothing();

    private:
        std::vector <bool> m_SmoothList;

        int m_NumberOfMesh;
        int m_MeshSelected;

        QIcon m_Visible;
        QIcon m_Unvisible;

        display m_MyWindowMesh;
        processing m_MyProcess;
        std::vector <data::data> m_DataList;
};

#endif
