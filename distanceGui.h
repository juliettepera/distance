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

// Other Libraries
#include <string>
#include <iostream>

// My libraries
#include "meshQtDisplay.h"
#include "distanceCompute.h"
#include "ui_distanceGui.h"

// My class
class distanceGui : public QMainWindow, public Ui::MainWindow
{
   Q_OBJECT

   public:
        distanceGui (QWidget * parent = 0, Qt::WFlags f = 0 );

   public slots:
       void OpenBrowseWindow();

       void ChangeValueChoice();
       void ChangeMeshSelected();
       void ChangeValueOpacity();
       void ChangeValueColor();

       void DisplayInit();
       void DisplayReset();
       void DisplayUpdateCamera();

       void buttonFrontClicked();
       void buttonBackClicked();
       void buttonRightClicked();
       void buttonLeftClicked();
       void buttonUpClicked();
       void buttonDownClicked();

       void ApplyDistance();
       void ApplySmoothing();
            
   private:

       int m_NumberOfMesh; // nb of mesh loaded
       int m_MeshSelected; // indice of the mesh selected
       int m_ChoiceOfError; // choice of witch type of error is computed
       double m_Opacity; // list of the opacity parameter for each mesh
       double m_Color;

       int m_CameraX; // x position of the camera
       int m_CameraY; // y position of the camera
       int m_CameraZ; // z position of the camera

       int m_NumberOfDisplay; // number of time the display button is clicked
       bool m_Smoothing; // do or not the smoothing

       std::vector <std::string> m_MeshList; // list of the mesh
       QVTKWidget *m_WidgetMesh; // widget to display the files
       meshQtDisplay m_MyWindowMesh; // object of the class meshQtDisplay
};

#endif
