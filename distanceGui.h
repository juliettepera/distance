#ifndef DEF_distanceGui
#define DEF_distanceGui

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
#include <QVector3D>

// VTK libraries
#include "vtkSmartPointer.h"
#include "vtkGenericDataObjectReader.h"
#include "vtkGenericDataObjectWriter.h"
#include "vtkPolyData.h"
#include "vtkSmoothPolyDataFilter.h"
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataReader.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <QVTKWidget.h>

// Other Libraries
#include <string>
#include <iostream>

// My libraries
#include "ui_distanceGui.h"

// My class
class distanceGui : public QMainWindow, public Ui::MainWindow
{
   Q_OBJECT

   public:
        distanceGui ( std::string meshA , std::string meshB );

   public slots:
       void OpenMeshBrowseWindowA();
       void OpenMeshBrowseWindowB();
       void Display();
       void ChangeValue();
       void ChangeValueOpacityA();
       void ChangeValueOpacityB();
       void buttonFrontClicked();
       void buttonBackClicked();
       void buttonRightClicked();
       void buttonLeftClicked();
       void buttonUpClicked();
       void buttonDownClicked();
       void ApplyDistance();
            
   private:
       std::string m_meshA;
       std::string m_meshB;

       QColor m_colorA;
       QColor m_colorB;

       double m_opacityA;
       double m_opacityB;

       int m_distance;

       QVector3D m_positionCam;
};

#endif
