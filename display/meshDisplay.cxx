#include "meshDisplay.h"

/* This is the constructor of the class, it first initialise the vtkSmartPointer used for the reader, mapper...
 * then set the size of the window and finally load the files passed by the user
 */
meshDisplay::meshDisplay( int NumberOfMesh , char* mesh[] )
{
    // initialisation of vtk
    m_Reader = vtkSmartPointer <vtkPolyDataReader>::New();
    m_Mapper = vtkSmartPointer <vtkPolyDataMapper>::New();
    m_Actor = vtkSmartPointer <vtkActor>::New();

    m_Renderer = vtkSmartPointer <vtkRenderer>::New();
    m_RenderWindow = vtkSmartPointer <vtkRenderWindow>::New();
    m_Interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    // initialisation of window size
    m_SizeH = 700 ; m_SizeW = 700;

    int i;

    m_NumberOfMesh = NumberOfMesh; // get the number of mesh loaded

    std::cout << "number of mesh : " << NumberOfMesh << std::endl;

    // link all the files to the window
    for( i=0 ; i < m_NumberOfMesh ; i++)
    {
        m_MeshList[ i ] = mesh[ i ];
        std::cout << "name mesh " << i << " : " << m_MeshList[ i ] << std::endl;
        createLinks( i );
    }
}


/* This function create all the links between the file and the Reader, then between the Reader and the Mapper,
 * finally between the Mapper and the Actor.
 * All the Data (polydata output of the Reader), the Mapper and the Actor are accessible by the creation of vector.
 */
void meshDisplay::createLinks( int IndiceOfMesh )
{
    // init of the PolyData Reader
    m_Reader -> SetFileName( m_MeshList[ IndiceOfMesh ] );
    m_Reader -> Update();

    // add PolyData to the list
    m_PolyDataList.push_back( m_Reader -> GetOutput() );

    // init Mapper
    m_Mapper -> SetInputData( m_PolyDataList[ IndiceOfMesh ] );

    // add Actor to the list
    m_Actor -> SetMapper( m_Mapper );
    m_ActorList.push_back( m_Actor );
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

    int i;
    for( i = 0 ; i < m_NumberOfMesh ; i++ )
    {
        m_Renderer -> AddActor( m_ActorList[ i ] );
        std::cout << " Actor " << i << " added " << std::endl;
    }

    // reset camera
    m_Renderer -> ResetCamera();

    // init render window
    m_RenderWindow -> AddRenderer( m_Renderer );
    m_RenderWindow -> SetSize( m_SizeH , m_SizeW );

    // init interActor
    m_Interactor -> SetRenderWindow( m_RenderWindow );

    // Display
    m_RenderWindow -> Render();
    m_Interactor -> Start();
}


/* This function permit to access to the propreties of one mesh and to change it.
 * The parameters accessible are the opacity and the color of the mesh.
 */
void meshDisplay::setParameters( int IndiceOfMesh , double Opacity , double Red , double Green , double Blue )
{
    // select the Actor of the good mesh
    m_Actor = m_ActorList[ IndiceOfMesh ]; // use at or value? need to protect the access???????

    // set the opacity of the mesh
    m_Actor -> GetProperty() -> SetOpacity( Opacity );

    // set the color of the mesh
    m_Actor -> GetProperty() -> SetColor( Red , Green , Blue );
}


/*
// update the window
void meshDisplay::windowUpdate( QVector3D positionCam )
{

    // set parameters

    positionCamera( m_Renderer->GetActiveCamera() , positionCam.x() , positionCam.y() , positionCam.z() );

    // display
    m_RenderWindow -> Render();
}
*/

/*
// change the position of the camera
void meshDisplay::positionCamera( vtkSmartPointer <vtkCamera> camera , int x ,int y , int z )
{

    double *focalPoint  = camera -> GetFocalPoint();
    double distance = camera -> GetDistance();

    camera -> SetPosition( focalPoint[0] + x*distance , focalPoint[1] + y*distance , focalPoint[2]+ z*distance );
    camera -> SetRoll(.001);
}
*/
