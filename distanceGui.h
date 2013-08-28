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

        void DisplayUpdateCamera();

        void DisableDisplay( bool EnableOrNot );
        void DisableParameters( bool EnableOrNot );
        void DisableCamera( bool EnableOrNot );
        void DisableDistance( bool EnableOrNot );
        void DisableAll();

        void ChangeIcon( QIcon Icon );
        void ChangeIcon( QIcon Icon , int IndiceOfMesh );

   public slots:
       void OpenBrowseWindowFile();
       void OpenBrowseWindowRepository();
       void OpenSmoothingWindow();

       void ChangeValueChoice();
       void ChangeMeshSelected();
       void ChangeValueOpacity();
       void ChangeValueColor();

       void DisplayInit();
       void DisplayReset();

       void buttonFrontClicked();
       void buttonBackClicked();
       void buttonRightClicked();
       void buttonLeftClicked();
       void buttonUpClicked();
       void buttonDownClicked();

       void ApplyDistance();


            
   private:

       int m_NumberOfMesh;
       int m_MeshSelected;
       std::vector <std::string> m_MeshList;

       std::vector <double> m_OpacityList;
       std::vector <double> m_ColorList;

       QVTKWidget *m_WidgetMesh;
       meshQtDisplay m_MyWindowMesh;

       int m_CameraX;
       int m_CameraY;
       int m_CameraZ;

       int m_NumberOfDisplay;

       distanceCompute m_MyCompute;
       int m_ChoiceOfError;

       smoothingGui m_MySmoothing;

       // icones
       QIcon m_visible;
       QIcon m_unvisble;
};

#endif
