#include "meshDisplay.h"

/* This is the constructor of the class, it first initialise the vtkSmartPointer used for the reader, mapper...
 * then set the size of the window and finally load the files passed by the user
 */
meshDisplay::meshDisplay(int NumberOfMesh , std::vector <std::string> MeshList )
{
    // initialisation of vtk
    m_Renderer = vtkSmartPointer <vtkRenderer>::New();
    m_RenderWindow = vtkSmartPointer <vtkRenderWindow>::New();
    m_Interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    m_Camera = vtkSmartPointer <vtkCamera>::New();

    // initialisation of variables
    m_SizeH = 700 ; m_SizeW = 700;
    m_CameraX = -1 ; m_CameraY = 0; m_CameraZ = 0;
    m_NumberOfMesh = NumberOfMesh;

    // link all the files to the window
    int i;

    std::cout << "number of mesh : " << m_NumberOfMesh << std::endl;

    for( i=0 ; i < m_NumberOfMesh ; i++)
    {
        m_MeshList.push_back( MeshList[ i ] );
        std::cout << "name mesh " << i << " : " << m_MeshList[ i ] << std::endl;
        createLinks( i );
    }
}


/* Accessor to the differents values x, y and z of the camera position
 */
void meshDisplay::setCameraX( int x )
{
    m_CameraX = x;
}

void meshDisplay::setCameraY( int y )
{
    m_CameraY = y;
}

void meshDisplay::setCameraZ( int z )
{
    m_CameraZ = z;
}


/* Accessor to the differents values height and width of the size of the window
 */
void meshDisplay::setSizeH( int Height )
{
    m_SizeH = Height;
}

void meshDisplay::setSizeW( int Width )
{
    m_SizeW = Width;
}


/* This function create all the links between the file and the Reader, then between the Reader and the Mapper,
 * finally between the Mapper and the Actor.
 * All the Data (polydata output of the Reader), the Mapper and the Actor are accessible by the creation of vector.
 */
void meshDisplay::createLinks( int IndiceOfMesh )
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


/* This function do the display of the window by adding all the Actor created previously to the renderer,
 * reseting the camera, linking the renderer to the render window and then do the render.
 * The probleme is that the window is not refresh and so disapear immediatly...
 * so I use an interActor, but We won't need it with Qt later...
 */
void meshDisplay::windowInit()
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

    // reset the camera
    m_Renderer -> ResetCamera();
    positionCamera( m_CameraX , m_CameraY , m_CameraZ );

    // init interActor
    m_Interactor -> SetRenderWindow( m_RenderWindow );

    // display
    m_RenderWindow -> Render();
    m_Interactor -> Start();
}

/* This function update the window with the new position
 * and display the window
 */
void meshDisplay::windowUpdate()
{
    // reset camera
    m_Renderer -> ResetCamera();

    // set the new position
    positionCamera( m_CameraX , m_CameraY , m_CameraZ );

    // display
    m_RenderWindow -> Render();
    m_Interactor -> Start();
}


/* This function permit to access to the propreties of one mesh and to change it.
 * The parameters accessible are the opacity and the color of the mesh.
 */
void meshDisplay::setParameters( int IndiceOfMesh , double Opacity )
{
    // select the Actor of the good mesh
    vtkActor* Actor = vtkActor::New();
    Actor = m_ActorList[ IndiceOfMesh ];

    // set the opacity of the mesh
    Actor -> GetProperty() -> SetOpacity( Opacity );
}

void meshDisplay::setParameters( int IndiceOfMesh , double Red , double Green , double Blue )
{
    // select the Actor of the good mesh
    vtkActor* Actor = vtkActor::New();
    Actor = m_ActorList[ IndiceOfMesh ];

    // set the color of the mesh
    Actor -> GetProperty() -> SetColor( Red , Green , Blue );
}

void meshDisplay::setParameters( int IndiceOfMesh , double Opacity , double Red , double Green , double Blue )
{
    // select the Actor of the good mesh
    vtkActor* Actor = vtkActor::New();
    Actor = m_ActorList[ IndiceOfMesh ];

    // set the opacity of the mesh
    Actor -> GetProperty() -> SetOpacity( Opacity );

    // set the color of the mesh
    Actor -> GetProperty() -> SetColor( Red , Green , Blue );
}


/* This function permit to calculate the new position of the camera in function of what view we want to see
 * ( from the program of Alexis )
 *  left : 1 0 0    | right : -1 0 0
 *  front : 0 1 0   | back : 0 -1 0 // doesn't work...
 *  up : 0 0 1      | down : 0 0 -1
 */
void meshDisplay::positionCamera( int PositionX , int PositionY , int PositionZ )
{

    double *focalPoint  = m_Camera -> GetFocalPoint();
    double distance = m_Camera -> GetDistance();

    m_Camera -> SetPosition( focalPoint[0] + PositionX*distance , focalPoint[1] + PositionY*distance , focalPoint[2]+ PositionZ*distance );
    m_Camera -> SetRoll(.001);
}

