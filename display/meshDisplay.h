#ifndef MESHDISPLAY_H
#define MESHDISPLAY_H

// VTK libraries
#include <vtkSmartPointer.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
//#include <QVTKWidget.h>
//#include <vtkImageViewer.h>
//#include <vtkCamera.h>

// Other Libraries
#include <string>
#include <iostream>
#include <vector>

class meshDisplay
{
    public:
        meshDisplay(int NumberOfMesh , char * mesh[] ); // constructor
        void createLinks( int IndiceOfMesh );
        void windowInit();
        void setParameters( int IndiceOfMesh , double Opacity , double Red , double Green , double Blue );

       // void windowUpdate( QVTKWidget* widgetMesh , double opacityA , double opacityB , QVector3D positionCam );
       // void positionCamera( vtkSmartPointer <vtkCamera> camera , int x ,int y , int z );

    private:
        int m_NumberOfMesh; // nb of mesh loaded
        char* m_MeshList[ 10 ]; // list of the mesh

        vtkSmartPointer <vtkPolyDataReader> m_Reader;
        vtkSmartPointer <vtkPolyDataMapper> m_Mapper;
        vtkSmartPointer <vtkActor> m_Actor;

        vtkSmartPointer <vtkRenderer> m_Renderer; // renderer
        vtkSmartPointer <vtkRenderWindow> m_RenderWindow; // renderWindow
        vtkSmartPointer<vtkRenderWindowInteractor> m_Interactor; // interactor

        std::vector <vtkPolyData *> m_PolyDataList; // list of the polyData, outputs of the reader
        std::vector <vtkActor *> m_ActorList; // list of the actor

        int m_SizeH; // height size of the window
        int m_SizeW; // width size of the window
};

#endif
