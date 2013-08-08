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
#include <vtkCamera.h>

// Other Libraries
#include <string>
#include <iostream>
#include <vector>

class meshDisplay
{
    public:
        meshDisplay(int NumberOfMesh , std::vector <std::string> MeshList ); // constructor
        void setCameraX( int x ); // accessor x value of the camera position
        void setCameraY( int y ); // accessor y value of the camera position
        void setCameraZ( int z ); // accessor z value of the camera position
        void setSizeH( int Height ); // accessor to the height value of the window's size
        void setSizeW( int Width ); // accessor to the width value of the window's size
        void setOpacity( int IndiceOfMesh , double Opacity ); // accessor to the opacity value of one mesh
        void setRed(int IndiceOfMesh , double Red ); // accessor to the red value of one mesh
        void setGreen(int IndiceOfMesh , double Green ); // accessor to the Green value of one mesh
        void setBlue(int IndiceOfMesh , double Blue ); // accessor to the Blue value of one mesh

        void createLinks(); // load the file and link it to the actor
        void windowInit(); // link all the actors to the same renderer and renderWindow and display the mesh
        void windowUpdate(); // update the window with the new camera position

        void positionCamera(int PositionX , int PositionY , int PositionZ ); // set the new position of the camera



    private:
        int m_NumberOfMesh; // nb of mesh loaded
        std::vector <std::string> m_MeshList; // list of the mesh

        vtkSmartPointer <vtkRenderer> m_Renderer; // renderer
        vtkSmartPointer <vtkRenderWindow> m_RenderWindow; // renderWindow
        vtkSmartPointer<vtkRenderWindowInteractor> m_Interactor; // interactor
        vtkSmartPointer <vtkCamera> m_Camera; // camera

        std::vector <vtkPolyData *> m_PolyDataList; // list of the polyData, outputs of the reader
        std::vector <vtkPolyDataReader*> m_ReaderList; // list of Readers
        std::vector <vtkPolyDataMapper*> m_MapperList; // list of the mappers
        std::vector <vtkActor *> m_ActorList; // list of the actors

        int m_SizeH; // height size of the window
        int m_SizeW; // width size of the window
        int m_CameraX; // x position of the camera
        int m_CameraY; // y position of the camera
        int m_CameraZ; // z position of the camera

        std::vector <double> m_RedList; // list of the color red parameters for each mesh
        std::vector <double> m_GreenList; // list of the color green parameters for each mesh
        std::vector <double> m_BlueList; // list of the color blue parameters for each mesh
        std::vector <double> m_OpacityList; // list of the opacity parameter for each mesh

};

#endif
