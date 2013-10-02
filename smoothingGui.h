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
#include "meshQtDisplay.h"
#include "ui_smoothingGui.h"

class smoothingGui: public QMainWindow, public Ui::SmoothingWindow
{
    Q_OBJECT

    public:
        smoothingGui( QWidget * parent = 0, Qt::WFlags f = 0 );

        void setMeshList( std::vector <std::string> MeshList );
        void setWindow( meshQtDisplay WindowMesh );
        void setIcon( QIcon Visible , QIcon Unvisible );

        void initialization();

    public slots:

        void pushButtonQuitClicked();
        void applySmoothing();
        void ChangeMeshSelected();
        void ChangeValueSmoothing();
        void DisplaySmoothing();

    private:
        std::vector <std::string> m_MeshList;
        std::vector <double> m_NumberOfIterationList;
        std::vector <bool> m_DoSmoothList;
        std::vector <bool> m_DisplayList;

        int m_NumberOfMesh;
        int m_MeshSelected;

        QIcon m_Visible;
        QIcon m_Unvisible;

        meshQtDisplay m_MyWindowMesh;
};

#endif
