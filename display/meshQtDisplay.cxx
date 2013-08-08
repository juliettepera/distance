#include "meshQtDisplay.h"

meshQtDisplay::meshQtDisplay( QWidget *MeshWidget , int NumberOfMesh , std::vector <std::string> MeshList)
{
    setupUi(this);

    // initialisation of the Widget
    m_MeshWidget = new QVTKWidget( this -> MeshWidget );

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


    // link all the files to the window
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++)
    {
        m_MeshList.push_back( MeshList[ IndiceOfMesh ] );
        std::cout << "name mesh " << IndiceOfMesh << " : " << m_MeshList[ IndiceOfMesh ] << std::endl;
        createLinks( IndiceOfMesh );
    }
}


/* This function create all the links between the file and the Reader, then between the Reader and the Mapper,
 * finally between the Mapper and the Actor.
 * All the Data (polydata output of the Reader), the Mapper and the Actor are accessible by the creation of vector.
 */
void meshQtDisplay::createLinks( int IndiceOfMesh )
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

    // init the Widget
    m_MeshWidget -> SetRenderWindow( m_RenderWindow );
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
    m_MeshWidget -> show();
}

// change the parameters


