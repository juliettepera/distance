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
#include "displayTools.h"
#include "ui_smoothingGui.h"

class smoothingGui: public QMainWindow, public Ui::SmoothingWindow
{
    Q_OBJECT

    public:
        smoothingGui( QWidget * parent = 0, Qt::WFlags f = 0 );

        void setWindow( meshQtDisplay WindowMesh );
        void setIcon( QIcon Visible , QIcon Unvisible );
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
        std::vector <double> m_NumberOfIterationList;
        std::vector <bool> m_DisplayList;
        std::vector <bool> m_SmoothList;

        int m_NumberOfMesh;
        int m_MeshSelected;

        QIcon m_Visible;
        QIcon m_Unvisible;

        meshQtDisplay m_MyWindowMesh;
        displayTools m_ActivTool;
};

#endif
