#include "meshQtDisplay.h"

meshQtDisplay::meshQtDisplay( QWidget *MeshWidget , int NumberOfMesh , std::vector <std::string> MeshList)
{
    // initialisation of the Widget
    m_MeshWidget = new QVTKWidget( MeshWidget );

    int IndiceOfMesh;
    double Color;

    // initialisation of vtk
    m_Renderer = vtkSmartPointer <vtkRenderer>::New();
    m_RenderWindow = vtkSmartPointer <vtkRenderWindow>::New();
    m_Interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    m_Camera = vtkSmartPointer <vtkCamera>::New();

    // initialisation of variables
    m_SizeH = 700 ; m_SizeW = 700;
    m_CameraX = -1 ; m_CameraY = 0; m_CameraZ = 0;
    m_NumberOfMesh = NumberOfMesh;
    std::cout << "number of mesh : " << m_NumberOfMesh << std::endl;

    // initialisation of the parameters of each mesh
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++)
    {
        m_OpacityList.push_back( 1.0 );

        Color =  double( IndiceOfMesh + 1 ) / double( m_NumberOfMesh ) ;
        m_RedList.push_back( 0.0 ); m_GreenList.push_back( Color ); m_BlueList.push_back( Color );
    }

    // initialisation of the list of files
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++)
    {
        m_MeshList.push_back( MeshList[ IndiceOfMesh ] );
        std::cout << "name mesh " << IndiceOfMesh << " : " << m_MeshList[ IndiceOfMesh ] << std::endl;
    }
}


/* Accessor to the differents values x, y and z of the camera position
 */
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


/* Accessor to the differents values height and width of the size of the window
 */
void meshQtDisplay::setSizeH( int Height )
{
    m_SizeH = Height;
}

void meshQtDisplay::setSizeW( int Width )
{
    m_SizeW = Width;
}

/* Accessor to the value of opacity for one mesh
 */
void meshQtDisplay::setOpacity( int IndiceOfMesh , double Opacity )
{
    m_OpacityList[ IndiceOfMesh ] = Opacity;
}

/* Accessor to the values red, green and blue of the color parameter for one mesh
 */
void meshQtDisplay::setRed( int IndiceOfMesh , double Red )
{
    m_RedList[ IndiceOfMesh ] = Red;
}

void meshQtDisplay::setGreen( int IndiceOfMesh , double Green )
{
    m_GreenList[ IndiceOfMesh ] = Green;
}

void meshQtDisplay::setBlue( int IndiceOfMesh , double Blue )
{
    m_BlueList[ IndiceOfMesh ] = Blue;
}

/* This function create all the links between the file and the Reader, then between the Reader and the Mapper,
 * finally between the Mapper and the Actor.
 * All the Data (polydata output of the Reader), the Mapper and the Actor are accessible by the creation of vector.
 */
void meshQtDisplay::createLinks()
{
    int IndiceOfMesh;

    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++)
    {
        // init of the PolyData Reader
        vtkPolyDataReader* Reader = vtkPolyDataReader::New();
        m_ReaderList.push_back( Reader );
        m_ReaderList[ IndiceOfMesh ] -> SetFileName( m_MeshList[ IndiceOfMesh ].c_str() );
        m_ReaderList[ IndiceOfMesh ] -> Update();

        // add PolyData to the list
        m_PolyDataList.push_back( m_ReaderList[ IndiceOfMesh ] -> GetOutput() );

        // init Mapper
        vtkPolyDataMapper* Mapper = vtkPolyDataMapper::New();
        m_MapperList.push_back( Mapper );
        m_MapperList[ IndiceOfMesh ] -> SetInputData( m_PolyDataList[ IndiceOfMesh ] );

        // add Actor to the list
        vtkActor* Actor = vtkActor::New();
        m_ActorList.push_back( Actor );
        m_ActorList[ IndiceOfMesh ] -> SetMapper( m_MapperList[ IndiceOfMesh ] );
    }
}


/* This function do the display of the window by adding all the Actor created previously to the renderer,
 * reseting the camera, linking the renderer to the render window and then do the render.
 * The probleme is that the window is not refresh and so disapear immediatly...
 * so I use an interActor, but We won't need it with Qt later...
 */
void meshQtDisplay::windowInit()
{
    // init renderer
    m_Renderer -> SetBackground( .6 , .5 , .4 );
    m_Renderer -> SetActiveCamera( m_Camera );


    int i;
    for( i = 0 ; i < m_NumberOfMesh ; i++ )
    {
        m_Renderer -> AddActor( m_ActorList[ i ] );
    }

    // init render window
    m_RenderWindow -> AddRenderer( m_Renderer );
    m_RenderWindow -> SetSize( m_SizeH , m_SizeW );

    // init the widget
    m_MeshWidget -> SetRenderWindow( m_RenderWindow );
}

/* This function update the window with the new position
 * and display the window
 */
void meshQtDisplay::windowUpdate()
{
    // reset camera
    m_Renderer -> ResetCamera();

    // set the new size
    m_RenderWindow -> SetSize( m_SizeH , m_SizeW );

    // set the new position
    positionCamera( m_CameraX , m_CameraY , m_CameraZ );

    // set the new parameters
    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++)
    {
        // select the Actor of the good mesh
        vtkActor* Actor = vtkActor::New();
        Actor = m_ActorList[ IndiceOfMesh ];

        Actor -> GetProperty() -> SetOpacity( m_OpacityList[ IndiceOfMesh ] );
        Actor -> GetProperty() -> SetColor( m_RedList[ IndiceOfMesh ] , m_GreenList[ IndiceOfMesh ] , m_BlueList[ IndiceOfMesh ] );
    }

    // display
    m_RenderWindow -> Render();
    m_MeshWidget -> show();

}


/* This function permit to calculate the new position of the camera in function of what view we want to see
 * ( from the program of Alexis )
 *  left : 1 0 0    | right : -1 0 0
 *  front : 0 1 0   | back : 0 -1 0 // doesn't work...
 *  up : 0 0 1      | down : 0 0 -1
 */
void meshQtDisplay::positionCamera( int PositionX , int PositionY , int PositionZ )
{

    double *focalPoint  = m_Camera -> GetFocalPoint();
    double distance = m_Camera -> GetDistance();

    m_Camera -> SetPosition( focalPoint[0] + PositionX*distance , focalPoint[1] + PositionY*distance , focalPoint[2]+ PositionZ*distance );
    m_Camera -> SetRoll(.001);
}

