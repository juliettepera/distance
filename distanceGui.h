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
#include <QLineEdit>
#include <QColorDialog>

// Other Libraries
#include <string>
#include <iostream>

// My libraries
#include "meshQtDisplay.h"
#include "smoothingGui.h"
#include "distanceCompute.h"
#include "ui_distanceGui.h"

// My class
class distanceGui : public QMainWindow, public Ui::MainWindow
{
   Q_OBJECT

   public:

        distanceGui ( QWidget * parent = 0, Qt::WFlags f = 0 );

        void ChangeIcon( QIcon Icon );
        void ChangeIcon( QIcon Icon , int IndiceOfMesh );

        void DisplayUpdateCamera();

   public slots:

       void OpenBrowseWindowFile();
       void OpenBrowseWindowRepository();

       void ChangeMeshSelected();

       void DisplayInit();
       void DisplayReset();

       void ChangeValueOpacity();
       void ChooseColor();

       void OpenSmoothingWindow();

       void buttonFrontClicked();
       void buttonBackClicked();
       void buttonRightClicked();
       void buttonLeftClicked();
       void buttonUpClicked();
       void buttonDownClicked();

       void ChangeMinSampleFrequency();
       void ChangeSamplingStep();
       void ChangeValueChoice();

       void ApplyDistance();

       void SelectMeshA();
       void SelectMeshB();
       void SetAvailableMesh( int call );
            
   private:

       int m_NumberOfMesh;
       int m_MeshSelected;
       int m_CameraX;
       int m_CameraY;
       int m_CameraZ;
       int m_NumberOfDisplay;
       int m_ChoiceOfError;
       int m_SelectedItemA;
       int m_SelectedItemB;
       double m_MinSampleFrequency;
       double m_SamplingStep;

       QIcon m_visible;
       QIcon m_unvisble;
       QColor m_Color;

       std::vector <std::string> m_MeshList;
       std::vector <std::string> m_MeshAvailableList;
       std::vector <double> m_OpacityList;

       QVTKWidget *m_WidgetMesh;
       meshQtDisplay m_MyWindowMesh;
       smoothingGui m_MySmoothing;
       distanceCompute m_MyCompute;

};

#endif
