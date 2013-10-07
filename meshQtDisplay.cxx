#include "meshQtDisplay.h"

meshQtDisplay::meshQtDisplay() // constructor
{
    m_Renderer = vtkSmartPointer <vtkRenderer>::New();
    m_RenderWindow = vtkSmartPointer <vtkRenderWindow>::New();
    m_Camera = vtkSmartPointer <vtkCamera>::New();

    m_SizeH = 700 ; m_SizeW = 700;
    m_CameraX = 0 ; m_CameraY = 0 ; m_CameraZ = 0;

    m_NumberOfMesh = 0;
}

//********************************************* SET THE ATTRIBUTS  **********************************************
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
//********************************************* ACESS THE ATTRIBUTS  ********************************************
displayTools::displayTools meshQtDisplay::getTool( int IndiceOfMesh )
{
    std::cout << " getTool" << std::endl;
    return m_ToolList[ IndiceOfMesh ];
}

QVTKWidget* meshQtDisplay::getWidget()
{
    return m_MeshWidget;
}

//************************************************ ADD NEW TOOL  ************************************************
void meshQtDisplay::addTool( std::string Mesh )
{
   m_ToolList.push_back( m_NumberOfMesh );
   m_ToolList[ m_NumberOfMesh ].setName( Mesh );

   m_ErrorList.push_back( false );
   m_NumberOfMesh ++;
}

//******************************************** INIT / UPDATE WINDOW  ********************************************
void meshQtDisplay::windowInit()
{
    int IndiceOfMesh;

    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++)
    {
        m_ToolList[ IndiceOfMesh ].initialization();
    }

    m_Renderer -> SetBackground( 1.0 , .898 , .8 );
    m_Renderer -> SetActiveCamera( m_Camera );

    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++ )
    {
        m_Renderer -> AddActor( m_ToolList[ IndiceOfMesh ].getActor() );
    }

    m_RenderWindow -> AddRenderer( m_Renderer );
    m_MeshWidget -> SetRenderWindow( m_RenderWindow );

    m_RenderWindow -> SetSize( m_SizeH , m_SizeW );
    m_Renderer -> ResetCamera();
}

void meshQtDisplay::windowUpdate()
{
    m_RenderWindow -> Render();
    m_MeshWidget -> show();
}


//********************************************** CLEAR THE WINDOW  **********************************************
void meshQtDisplay::windowClear()
{
    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++ )
    {
        m_Renderer -> RemoveActor( m_ToolList[ IndiceOfMesh ].getActor() );
    }

    m_ToolList.clear();
    m_ErrorList.clear();

    m_NumberOfMesh = 0;
}

void meshQtDisplay::windowClearOne( int IndiceOfMesh )
{
    m_Renderer -> RemoveActor( m_ToolList[ IndiceOfMesh ].getActor() );
    m_ToolList.erase( m_ToolList.begin() + IndiceOfMesh );
    m_ErrorList.erase( m_ErrorList.begin() + IndiceOfMesh );

    m_NumberOfMesh--;
}


//******************************************** UPDATE THE CAMERA  ********************************************
void meshQtDisplay::updatePositionCamera()
{
    m_Renderer -> ResetCamera();

    double *focalPoint  = m_Camera -> GetFocalPoint();
    double distance = m_Camera -> GetDistance();

    m_Camera -> SetPosition( focalPoint[0] + m_CameraX*distance , focalPoint[1] + m_CameraY*distance , focalPoint[2] + m_CameraZ*distance );
    m_Camera -> SetRoll(.001);

}


//******************************************** COMPUTE THE ERROR  ********************************************
void meshQtDisplay::displayInitError( vtkSmartPointer <vtkPolyData> Data , vtkSmartPointer <vtkColorTransferFunction> Lut , int Indice )
{
    m_ToolList[ Indice ].setLut( Lut );
    m_ToolList[ Indice ].setPolyDataError( Data );
    m_ToolList[ Indice ].changeInputData( 1 );
    m_ErrorList[ Indice ] = true;

    m_Renderer -> AddActor( m_ToolList[ Indice ].getActor() );

    windowUpdate();
}

void meshQtDisplay::chooseDisplayError( int Indice , bool Choice )
{
    if( Choice == false )
    {
        m_ToolList[ Indice ].changeInputData( false );
    }
    if( Choice == true && m_ErrorList[ Indice ] == true )
    {
        m_ToolList[ Indice ].changeInputData( true );
    }

    m_Renderer -> AddActor( m_ToolList[ Indice ].getActor() );

    windowUpdate();
}

