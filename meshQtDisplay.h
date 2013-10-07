#ifndef MESHQTDISPLAY_H
#define MESHQTDISPLAY_H

// VTK libraries
#include <QVTKWidget.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>

// Qt Libraries
//#include <QMessageBox>
//#include <qwidget.h>

// My Libraries
#include "displayTools.h"

class meshQtDisplay
{
    public:

        meshQtDisplay();

        void setCameraX( int x );
        void setCameraY( int y );
        void setCameraZ( int z );
        void setSizeH( int Height );
        void setSizeW( int Width );
        void setMeshWidget( QVTKWidget *MeshWidget );

        displayTools::displayTools getTool( int IndiceOfMesh );
        QVTKWidget* getWidget();

        void addTool( std::string Mesh );

        void windowInit();
        void windowUpdate();

        void windowClear();
        void windowClearOne( int IndiceOfMesh );

        void updatePositionCamera();

        void displayInitError(vtkSmartPointer<vtkPolyData> Data , vtkSmartPointer<vtkColorTransferFunction> Lut , int Indice);
        void chooseDisplayError(int Indice , bool Choice );

    private:

        QVTKWidget *m_MeshWidget;

        vtkSmartPointer <vtkRenderer> m_Renderer;
        vtkSmartPointer <vtkRenderWindow> m_RenderWindow;
        vtkSmartPointer <vtkCamera> m_Camera;

        int m_SizeH;
        int m_SizeW;
        int m_CameraX;
        int m_CameraY;
        int m_CameraZ;

        int m_NumberOfMesh;

        std::vector <displayTools::displayTools> m_ToolList;
        std::vector <bool> m_ErrorList;
};

#endif
