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
void meshQtDisplay::addTool( std::string Mesh )
{
   std::cout << "    meshQtDisplay : addTool " << std::endl;
   m_ToolList.push_back( m_NumberOfMesh );
   m_ToolList[ m_NumberOfMesh ].setName( Mesh );

   m_ErrorList.push_back( false );

   m_NumberOfMesh ++;
}

void meshQtDisplay::windowInit()
{
    std::cout << "    meshQtDisplay : windowInit " << std::endl;
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

    updateOpacity();
    updateColor();
}

void meshQtDisplay::windowUpdate()
{
    std::cout << "    meshQtDisplay : windowUpdate " << std::endl;
    m_RenderWindow -> Render();
    m_MeshWidget -> show();
}

void meshQtDisplay::windowClear()
{
    std::cout << "    meshQtDisplay : windowClear " << std::endl;
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
    std::cout << "    meshQtDisplay : windowClearOne " << std::endl;
    m_Renderer -> RemoveActor( m_ToolList[ IndiceOfMesh ].getActor() );
    m_ToolList.erase( m_ToolList.begin() + IndiceOfMesh );
    m_ErrorList.erase( m_ErrorList.begin() + IndiceOfMesh );

    m_NumberOfMesh--;
}

void meshQtDisplay::updatePositionCamera()
{
    m_Renderer -> ResetCamera();

    double *focalPoint  = m_Camera -> GetFocalPoint();
    double distance = m_Camera -> GetDistance();

    m_Camera -> SetPosition( focalPoint[0] + m_CameraX*distance , focalPoint[1] + m_CameraY*distance , focalPoint[2] + m_CameraZ*distance );
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
    std::cout << " meshQtDisplay : updateSmoothing " << std::endl;

    int IndiceOfMesh;

    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++ )
    {
        m_Renderer -> RemoveActor( m_ToolList[ IndiceOfMesh ].getActor() );

        if( m_ToolList[ IndiceOfMesh ].getSmoothing() == true )
        {
            m_ToolList[ IndiceOfMesh ].getFilter() -> SetInputConnection( m_ToolList[ IndiceOfMesh ].getReader() -> GetOutputPort() );
            m_ToolList[ IndiceOfMesh ].getFilter() -> SetNumberOfIterations( m_ToolList[ IndiceOfMesh ].getNumberOfIterationSmooth() );
            m_ToolList[ IndiceOfMesh ].getFilter() -> Update();

            m_ToolList[ IndiceOfMesh ].changeInputPort( m_ToolList[ IndiceOfMesh ].getFilter() -> GetOutputPort() );

            if( m_ToolList[ IndiceOfMesh ].getFilter() -> GetOutput() -> GetNumberOfPoints() != m_ToolList[ IndiceOfMesh ].getReader() -> GetOutput() -> GetNumberOfPoints() )
            {
                QMessageBox MsgBox;
                MsgBox.setText( " problem occur during the smoothing");
                MsgBox.exec();
                m_ToolList[ IndiceOfMesh ].changeInputPort( m_ToolList[ IndiceOfMesh ].getReader() -> GetOutputPort() );
            }
        }
        else
        {
            m_ToolList[ IndiceOfMesh ].changeInputPort( m_ToolList[ IndiceOfMesh ].getReader() -> GetOutputPort() );
        }

        m_Renderer -> AddActor( m_ToolList[ IndiceOfMesh ].getActor() );
    }
}

//*************************************************************************
void meshQtDisplay::displayInitError( vtkSmartPointer <vtkPolyData> Data , vtkSmartPointer <vtkColorTransferFunction> Lut , int Indice )
{
    m_ToolList[ Indice ].setLut( Lut );
    m_ToolList[ Indice ].setPolyDataError( Data );
    m_ToolList[ Indice ].changeInputData( 1 );
    m_ErrorList[ Indice ] = true;

    m_Renderer -> AddActor( m_ToolList[ Indice ].getActor() );

    m_RenderWindow -> Render();
    m_MeshWidget -> show();
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
    m_RenderWindow -> Render();
    m_MeshWidget -> show();
}

void meshQtDisplay::typeOfDisplay( int IndiceOfMesh , int Type )
{

    vtkSmartPointer <vtkActor> Actor = m_ToolList[ IndiceOfMesh ].getActor();
    vtkSmartPointer <vtkProperty> Property =  Actor->GetProperty();

    if( Type == 1 )
    {
        Property -> SetRepresentationToSurface();
    }
    else if( Type == 2 )
    {
        Property -> SetRepresentationToPoints();
    }
    else if( Type == 3 )
    {
        Property -> SetRepresentationToWireframe();
    }

    m_RenderWindow -> Render();
    m_MeshWidget -> show();
}

