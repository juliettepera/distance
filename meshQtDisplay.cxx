#include "meshQtDisplay.h"

meshQtDisplay::meshQtDisplay() // constructor
{
    m_Renderer = vtkSmartPointer <vtkRenderer>::New();
    m_RenderWindow = vtkSmartPointer <vtkRenderWindow>::New();
    m_Camera = vtkSmartPointer <vtkCamera>::New();
    m_SmoothFilter = vtkSmartPointer <vtkSmoothPolyDataFilter>::New();
    m_Writer = vtkSmartPointer <vtkPolyDataWriter>::New();

    m_SizeH = 700 ; m_SizeW = 700;
    m_CameraX = 0 ; m_CameraY = 1 ; m_CameraZ = 0;
}

// **********************************************************************
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

void meshQtDisplay::setMeshWidget( QVTKWidget *MeshWidget )
{
    m_MeshWidget = MeshWidget;
}

// **********************************************************************
displayTools::displayTools meshQtDisplay::getTool( int IndiceOfMesh )
{
    return m_ToolList[ IndiceOfMesh ];
}

QVTKWidget* meshQtDisplay::getWidget()
{
    return m_MeshWidget;
}

// **********************************************************************
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
    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++)
    {
        m_ToolList[ IndiceOfMesh ].initialization();
    }

    m_Renderer -> SetBackground( .6 , .5 , .4 );
    m_Renderer -> SetActiveCamera( m_Camera );

    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++ )
    {
        m_Renderer -> AddActor( m_ToolList[ IndiceOfMesh ].getActor() );
    }

    m_RenderWindow -> AddRenderer( m_Renderer );
    m_MeshWidget -> SetRenderWindow( m_RenderWindow );

    m_RenderWindow -> SetSize( m_SizeH , m_SizeW );
    m_Renderer -> ResetCamera();

    updateOpacity();
    updateColor();

    m_RenderWindow -> Render();
    m_MeshWidget -> show();
}

void meshQtDisplay::windowUpdate()
{
    m_RenderWindow -> Render();
    m_MeshWidget -> show();
}

void meshQtDisplay::windowClear()
{
    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++ )
    {
        m_Renderer -> RemoveActor( m_ToolList[ IndiceOfMesh ].getActor() );
    }

    m_ToolList.clear();
    m_NumberOfMesh = 0;
}

void meshQtDisplay::hideOne( int IndiceOfMesh )
{
    m_Renderer -> RemoveActor( m_ToolList[ IndiceOfMesh ].getActor() );
}

void meshQtDisplay::updatePositionCamera()
{
    m_Renderer -> ResetCamera();

    double *focalPoint  = m_Camera -> GetFocalPoint();
    double distance = m_Camera -> GetDistance();

    m_Camera -> SetPosition( focalPoint[0] + m_CameraX*distance , focalPoint[1] + m_CameraY*distance , focalPoint[2]+ m_CameraZ*distance );
    m_Camera -> SetRoll(.001);
}

// **********************************************************************
void meshQtDisplay::setOpacity( int IndiceOfMesh , double Opacity )
{
    m_ToolList[ IndiceOfMesh ].setOpacity( Opacity );
}

void meshQtDisplay::setColor( int IndiceOfMesh , double Red , double Green , double Blue )
{
    m_ToolList[ IndiceOfMesh ].setColor( Red , Green , Blue );
}

void meshQtDisplay::setSmoothing( int IndiceOfMesh , bool Smooth )
{
    m_ToolList[ IndiceOfMesh ].setSmoothing( Smooth );
}

void meshQtDisplay::setNumberOfIteration( int IndiceOfMesh , int Number )
{
    m_ToolList[ IndiceOfMesh ].setNumberOfIterationSmooth( Number );
}

// **********************************************************************
void meshQtDisplay::updateOpacity()
{
    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++)
    {
        m_ToolList[ IndiceOfMesh ].getActor() -> GetProperty() -> SetOpacity( m_ToolList[ IndiceOfMesh ].getOpacity() );
    }
}

void meshQtDisplay::updateColor()
{
    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++)
    {
        m_ToolList[ IndiceOfMesh ].getActor() -> GetProperty() -> SetColor( m_ToolList[ IndiceOfMesh ].getRed() , m_ToolList[ IndiceOfMesh ].getGreen() , m_ToolList[ IndiceOfMesh ].getBlue() );
    }
}


void meshQtDisplay::updateSmoothing()
{
    int IndiceOfMesh;

    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++ )
    {
        m_Renderer -> RemoveActor( m_ToolList[ IndiceOfMesh ].getActor() );

        if( m_ToolList[ IndiceOfMesh ].getSmoothing() == true )
        {
            m_SmoothFilter -> SetInputConnection( m_ToolList[ IndiceOfMesh ].getReader() -> GetOutputPort() );
            m_SmoothFilter -> SetNumberOfIterations( m_ToolList[ IndiceOfMesh ].getNumberOfIterationSmooth() );
            m_SmoothFilter -> Update();

            m_ToolList[ IndiceOfMesh ].changeInputPort( m_SmoothFilter -> GetOutputPort() );
        }
        else
        {
            m_ToolList[ IndiceOfMesh ].changeInputPort( m_ToolList[ IndiceOfMesh ].getReader() -> GetOutputPort() );
        }

        m_Renderer -> AddActor( m_ToolList[ IndiceOfMesh ].getActor() );
    }
}


