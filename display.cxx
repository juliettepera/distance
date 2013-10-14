#include "display.h"

display::display()
{
    m_Renderer = vtkSmartPointer <vtkRenderer>::New();
    m_RenderWindow = vtkSmartPointer <vtkRenderWindow>::New();
    m_Camera = vtkSmartPointer <vtkCamera>::New();

    m_SizeH = 700 ; m_SizeW = 700;
    m_CameraX = 0 ; m_CameraY = 0 ; m_CameraZ = 0;

    m_NumberOfMesh = 0;
}

void display::initWindow()
{
    m_Renderer -> SetBackground( 1.0 , .898 , .8 );
    m_Renderer -> SetActiveCamera( m_Camera );

    int IndiceOfMesh;

    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++ )
    {
        m_Renderer -> AddActor( m_ActorList[ IndiceOfMesh ] );
    }

    m_RenderWindow -> AddRenderer( m_Renderer );
    m_MeshWidget -> SetRenderWindow( m_RenderWindow );

    m_RenderWindow -> SetSize( m_SizeH , m_SizeW );
    m_Renderer -> ResetCamera();
}

void display::updateWindow()
{
    m_RenderWindow -> Render();
    m_MeshWidget -> show();
}

void display::addData( vtkSmartPointer <vtkActor> Actor )
{
    m_ActorList.push_back( Actor );
    m_NumberOfMesh++;
}

void display::deleteData( int IndiceOfMesh )
{
    m_Renderer -> RemoveActor( m_ActorList[ IndiceOfMesh ] );
    m_ActorList.erase( m_ActorList.begin() + IndiceOfMesh );
    m_NumberOfMesh--;
    updateWindow();
}

void display::deleteAll()
{
    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++ )
    {
        m_Renderer -> RemoveActor( m_ActorList[ IndiceOfMesh ] );
    }

    m_ActorList.clear();
    m_NumberOfMesh = 0;
    updateWindow();
}

void display::updatePositionCamera()
{
    m_Renderer -> ResetCamera();

    double *focalPoint  = m_Camera -> GetFocalPoint();
    double distance = m_Camera -> GetDistance();

    m_Camera -> SetPosition( focalPoint[0] + m_CameraX*distance , focalPoint[1] + m_CameraY*distance , focalPoint[2] + m_CameraZ*distance );
    m_Camera -> SetRoll(.001);

}

void display::setCameraX( int x )
{
    m_CameraX = x;
}

void display::setCameraY( int y )
{
    m_CameraY = y;
}

void display::setCameraZ( int z )
{
    m_CameraZ = z;
}

void display::setSizeH( int Height )
{
    m_SizeH = Height;
}

void display::setSizeW( int Width )
{
    m_SizeW = Width;
}

void display::setMeshWidget( QVTKWidget *MeshWidget )
{
    m_MeshWidget = MeshWidget;
}
















