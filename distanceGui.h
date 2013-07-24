#ifndef DEF_distanceGui
#define DEF_distanceGui

// Qt library
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

// VTK library
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

// Other Library
#include <string>

// My library
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
   
   //void FromAtoB();
   //void FromBtoA();
   //void CalculateBoth();
   void Display();
   void ChangeValue();
   void ApplyDistance();
            
   private:
   std::string m_meshA;
   std::string m_meshB;
   int m_distance;
};

#endif
