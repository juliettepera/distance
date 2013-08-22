#ifndef MESHQTDISPLAY_H
#define MESHQTDISPLAY_H

// VTK libraries
#include <QVTKWidget.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkPolyDataWriter.h>

// Qt libraries
#include <qwidget.h>

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

        void createTools( int NumberOfMesh , std::vector <std::string> MeshList );
        void windowInit();
        void windowUpdate();
        void windowClear();
        void hideOne( int IndiceOfMesh );
        void updatePositionCamera();

        void setOpacity( int IndiceOfMesh , double Opacity );
        void setColor(int IndiceOfMesh , double Red , double Green, double Blue);
        void setSmoothing( int IndiceOfMesh , bool Smooth );
        void setNumberOfIteration( int IndiceOfMesh , int Number );

        void updateOpacity();
        void updateColor();
        void updateSmoothing();

    private:
        QVTKWidget *m_MeshWidget;

        int m_NumberOfMesh;
        std::vector <displayTools::displayTools> m_ToolList;

        vtkSmartPointer <vtkRenderer> m_Renderer;
        vtkSmartPointer <vtkRenderWindow> m_RenderWindow;
        vtkSmartPointer <vtkCamera> m_Camera;

        int m_SizeH;
        int m_SizeW;
        int m_CameraX;
        int m_CameraY;
        int m_CameraZ;

        vtkSmartPointer <vtkSmoothPolyDataFilter> m_SmoothFilter;
        vtkSmartPointer <vtkPolyDataWriter> m_Writer;
};

#endif
