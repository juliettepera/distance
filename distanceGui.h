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
#include <QCheckBox>
#include <QFileInfo>

// vtk Libraries
#include <vtkSmartPointer.h>
#include <vtkActor.h>

// Other Libraries
#include <string>
#include <iostream>

// My libraries
#include "meshQtDisplay.h"
#include "smoothingGui.h"
#include "testMeshValmet.h"
#include "ui_distanceGui.h"

// My class
class distanceGui : public QMainWindow, public Ui::MainWindow
{
   Q_OBJECT

   public:

    distanceGui ( QWidget * parent = 0 , Qt::WFlags f = 0 , std::string WorkDirectory = "" );

        void ChangeAccessFile();
        void InitIcon();
        void ChangeIcon( QIcon Icon );
        void ChangeIcon( QIcon Icon , int IndiceOfMesh );

        void DisplayUpdateCamera();

        void AvailableMesh();

        void DisplayError();

   public slots:

       void OpenBrowseWindowFile();
       void OpenBrowseWindowRepository();
       void DeleteOneFile();

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
       void ChangeSignedDistance();

       void ApplyDistance();
       void SelectMeshB();
       void ChangeDisplayError();
            
   private:

       int m_NumberOfMesh;
       int m_MeshSelected;
       int m_CameraX;
       int m_CameraY;
       int m_CameraZ;
       int m_NumberOfDisplay;
       int m_SelectedItemA;
       int m_SelectedItemB;
       std::string m_WorkDirectory;

       QIcon m_VisibleIcon;
       QIcon m_UnvisibleIcon;
       QIcon m_OkIcon;
       QIcon m_NotOkIcon;
       QIcon m_PlusIcon;
       QIcon m_MinusIcon;
       QIcon m_DeleteIcon;
       QIcon m_DisplayIcon;

       QString m_Visible;
       QString m_Unvisible;
       QString m_Ok;
       QString m_NotOk;
       QString m_Plus;
       QString m_Minus;
       QString m_Delete;
       QString m_Display;

       QColor m_Color;

       std::vector <std::string> m_MeshList;
       std::vector <double> m_OpacityList;
       std::vector <double> m_MinSampleFrequencyList;
       std::vector <double> m_SamplingStepList;
       std::vector <bool> m_SignedDistanceList;
       std::vector <int> m_DisplayErrorList;

       vtkSmartPointer <vtkPolyData> m_ComputedData;
       vtkSmartPointer <vtkColorTransferFunction> m_Lut;

       QString m_FileName1;
       QString m_FileName2;

       QVTKWidget *m_WidgetMesh;
       meshQtDisplay m_MyWindowMesh;
       smoothingGui m_MySmoothing;
       testMeshValmet m_MyTestMeshValmet;

};

#endif
