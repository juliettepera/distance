#ifndef MESHQTDISPLAY_H
#define MESHQTDISPLAY_H

// VTK libraries
#include <QVTKWidget.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkPolyDataWriter.h>

// Other Libraries
#include <string>
#include <iostream>
#include <vector>

// Qt libraries
#include <qwidget.h>

// My Libraries
#include "displayTools.h"

class meshQtDisplay
{
    public:
        meshQtDisplay(); // constructor

        void setCameraX( int x ); // accessor x value of the camera position
        void setCameraY( int y ); // accessor y value of the camera position
        void setCameraZ( int z ); // accessor z value of the camera position
        void setSizeH( int Height ); // accessor to the height value of the window's size
        void setSizeW( int Width ); // accessor to the width value of the window's size
        void setOpacity( int IndiceOfMesh , double Opacity ); // accessor to the opacity value of one mesh
        void setColor(int IndiceOfMesh , double Red , double Green, double Blue); // accessor to the red value of one mesh
        void setMeshWidget( QVTKWidget *MeshWidget ); // set the widget

        void createTools( int NumberOfMesh , std::vector <std::string> MeshList );
        void windowInit(); // itinialize the window
        void windowUpdate(); // update the window with the new camera position or parameters
        void windowClear();

        void updateOpacity(); // update the opacity of mesh
        void updateColor(); // update the color of the mesh
        void updatePositionCamera(); // set the new position of the camera

    private:
        QVTKWidget *m_MeshWidget;

        int m_NumberOfMesh; // nb of mesh loaded
        std::vector <std::string> m_MeshList; // list of the mesh

        std::vector <displayTools::displayTools> m_ToolList;

        vtkSmartPointer <vtkRenderer> m_Renderer; // renderer
        vtkSmartPointer <vtkRenderWindow> m_RenderWindow; // renderWindow
        vtkSmartPointer <vtkCamera> m_Camera; // camera
        vtkSmartPointer <vtkSmoothPolyDataFilter> m_SmoothFilter;
        vtkSmartPointer <vtkPolyDataWriter> m_Writer;


        int m_SizeH; // height size of the window
        int m_SizeW; // width size of the window
        int m_CameraX; // x position of the camera
        int m_CameraY; // y position of the camera
        int m_CameraZ; // z position of the camera

};

#endif
