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
#include <QListWidgetItem>
#include <QListWidget>

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
       void ChangeValueSmoothing();

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

       void DisableDisplay( bool EnableOrNot );
       void DisableParameters( bool EnableOrNot );
       void DisableCamera( bool EnableOrNot );
       void DisableDistance( bool EnableOrNot );
            
   private:

       int m_NumberOfMesh;
       int m_MeshSelected;
       std::vector <std::string> m_MeshList;

       std::vector <double> m_OpacityList;
       std::vector <double> m_ColorList;
       std::vector <double> m_NumberOfIterationList;
       std::vector <bool> m_DoSmoothList;

       QVTKWidget *m_WidgetMesh;
       meshQtDisplay m_MyWindowMesh;

       int m_CameraX;
       int m_CameraY;
       int m_CameraZ;

       double m_Opacity;
       double m_Color;

       int m_NumberOfDisplay;
       int m_ChoiceOfError;


};

#endif
