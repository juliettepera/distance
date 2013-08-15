#include "meshQtDisplay.h"

meshQtDisplay::meshQtDisplay() // constructor
{
    // initialisation of vtk
    m_Renderer = vtkSmartPointer <vtkRenderer>::New();
    m_RenderWindow = vtkSmartPointer <vtkRenderWindow>::New();
    m_Camera = vtkSmartPointer <vtkCamera>::New();
    m_SmoothFilter = vtkSmartPointer <vtkSmoothPolyDataFilter>::New();
    m_Writer = vtkSmartPointer <vtkPolyDataWriter>::New();

    // initialisation of variables
    m_SizeH = 700 ; m_SizeW = 700;
    m_CameraX = 0 ; m_CameraY = 1 ; m_CameraZ = 0;
}


void meshQtDisplay::setCameraX( int x )
{
    m_CameraX = x;
}

void meshQtDisplay::setCameraY( int y )
{
    m_CameraY = y;
}

void meshQtDisplay::setCameraZ( int z )
{
    m_CameraZ = z;
}

void meshQtDisplay::setSizeH( int Height )
{
    m_SizeH = Height;
}

void meshQtDisplay::setSizeW( int Width )
{
    m_SizeW = Width;
}

void meshQtDisplay::setOpacity( int IndiceOfMesh , double Opacity )
{
    std::cout << "in meshQtDisplay : setOpacity " << std::endl;
    m_ToolList[ IndiceOfMesh ].setOpacity( Opacity );
}

void meshQtDisplay::setColor( int IndiceOfMesh , double Red , double Green , double Blue )
{
    m_ToolList[ IndiceOfMesh ].setColor( Red , Green , Blue );
}

void meshQtDisplay::setMeshWidget( QVTKWidget *MeshWidget )
{
    std::cout << "in meshQtDisplay : setMeshWidget " << std::endl;

    m_MeshWidget = MeshWidget;
}


void meshQtDisplay::createTools( int NumberOfMesh , std::vector <std::string> MeshList )
{
    m_NumberOfMesh = NumberOfMesh;

    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++ )
    {
        m_ToolList.push_back( IndiceOfMesh );
        m_ToolList[ IndiceOfMesh ].setName( MeshList[ IndiceOfMesh ] );
    }
}

void meshQtDisplay::windowInit()
{
    std::cout << "in meshQtDisplay : windowInit " << std::endl;

    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++)
    {
        m_ToolList[ IndiceOfMesh ].initialization();
    }

    m_Renderer -> SetBackground( .6 , .5 , .4 ); // set background color
    m_Renderer -> SetActiveCamera( m_Camera ); // set active camera

    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++ ) // add all the actors for each mesh to one renderer
    {
        m_Renderer -> AddActor( m_ToolList[ IndiceOfMesh ].getActor() );
    }

    m_RenderWindow -> AddRenderer( m_Renderer ); // add the renderer to the renderWindow
    m_MeshWidget -> SetRenderWindow( m_RenderWindow ); // link the renderWindow with the widget

    m_RenderWindow -> SetSize( m_SizeH , m_SizeW ); // set the size of the renderWindow
    m_Renderer -> ResetCamera();

    updateOpacity();
    updateColor();

    m_RenderWindow -> Render();
    m_MeshWidget -> show();
}

void meshQtDisplay::windowUpdate()
{
    std::cout << "in meshQtDisplay : windowUpdate " << std::endl;

    m_RenderWindow -> Render();
    m_MeshWidget -> show();
}

void meshQtDisplay::windowClear()
{
    std::cout << "in meshQtDisplay : windowClear " << std::endl;

    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++ ) // add all the actors for each mesh to one renderer
    {
        m_Renderer -> RemoveActor( m_ToolList[ IndiceOfMesh ].getActor() );
    }

    m_ToolList.clear();
}


void meshQtDisplay::updateOpacity()
{
    std::cout << "in meshQtDisplay : updateOpacity " << std::endl;

    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++)
    {
        m_ToolList[ IndiceOfMesh ].getActor() -> GetProperty() -> SetOpacity( m_ToolList[ IndiceOfMesh ].getOpacity() );
    }
}

void meshQtDisplay::updateColor()
{
    std::cout << "in meshQtDisplay : updateColor " << std::endl;

    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++)
    {
        m_ToolList[ IndiceOfMesh ].getActor() -> GetProperty() -> SetColor( m_ToolList[ IndiceOfMesh ].getRed() , m_ToolList[ IndiceOfMesh ].getGreen() , m_ToolList[ IndiceOfMesh ].getBlue() );
    }
}

void meshQtDisplay::updatePositionCamera()
{
    std::cout << "in meshQtDisplay : updatePositionCamera " << std::endl;

    m_Renderer -> ResetCamera();

    double *focalPoint  = m_Camera -> GetFocalPoint();
    double distance = m_Camera -> GetDistance();

    m_Camera -> SetPosition( focalPoint[0] + m_CameraX*distance , focalPoint[1] + m_CameraY*distance , focalPoint[2]+ m_CameraZ*distance );
    m_Camera -> SetRoll(.001);
}


/*void meshQtDisplay::updateIteration()
{
    std::cout << "in meshQtDisplay : updateIteration " << std::endl;
    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++ )
    {
        m_SmoothFilter -> SetInputData( m_PolyDataList[ IndiceOfMesh ] );
        m_PolyDataList[ IndiceOfMesh ] = m_SmoothFilter ->GetOutput();
        m_SmoothFilter -> SetNumberOfIterations( m_IterationList[ IndiceOfMesh ] );
        m_SmoothFilter -> Update();

        m_MapperList[ IndiceOfMesh ] -> SetInputData( m_PolyDataList[ IndiceOfMesh ] );
        m_ActorList[ IndiceOfMesh ] -> SetMapper( m_MapperList[ IndiceOfMesh ] );
        m_Renderer -> AddActor( m_ActorList[ IndiceOfMesh ] );

    }
}*/
