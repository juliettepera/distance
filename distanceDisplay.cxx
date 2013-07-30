#include "distanceDisplay.h"
#include "distanceGui.h"


// update the window with one mesh
/*void windowUpdate( QVTKWidget* widgetMesh , std::string mesh , QSize size , QColor color , double opacity , QVector3D positionCam )
{
    //READER
    vtkSmartPointer <vtkGenericDataObjectReader> readerMesh = vtkSmartPointer <vtkGenericDataObjectReader>::New();
    readerMesh -> SetFileName( mesh.c_str() );
    readerMesh -> Update();

    //MAPPER
    vtkSmartPointer <vtkPolyDataMapper> mapperMesh = vtkSmartPointer <vtkPolyDataMapper>::New();
    mapperMesh -> SetInputConnection( readerMesh -> GetOutputPort() );

    //ACTOR
    vtkSmartPointer <vtkActor> actorMesh = vtkSmartPointer <vtkActor>::New();
    actorMesh -> SetMapper( mapperMesh );
    actorMesh -> GetProperty() -> SetColor( color.red() , color.green() , color.blue() );
    actorMesh -> GetProperty() -> SetOpacity( opacity );

    //CAMERA
    vtkSmartPointer <vtkCamera> cameraMesh = vtkSmartPointer <vtkCamera>::New();

    //RENDERER
    vtkSmartPointer<vtkRenderer> rendererMesh = vtkSmartPointer<vtkRenderer>::New();
    rendererMesh -> SetBackground( .6 , .5 , .4 );
    rendererMesh -> AddActor( actorMesh );
    rendererMesh -> SetActiveCamera( cameraMesh );
    rendererMesh -> ResetCamera();

    positionCamera( cameraMesh , positionCam.x() , positionCam.y() , positionCam.z() );

    //RENDER WINDOW
    vtkSmartPointer <vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow-> AddRenderer( rendererMesh );

    //Display
    widgetMesh -> SetRenderWindow( renderWindow );
    widgetMesh -> resize( size );
    renderWindow -> Render();
    widgetMesh -> show();
}*/

// update the window with both mesh
void windowUpdate( QVTKWidget* widgetMesh , std::string meshA , std::string meshB , QSize size , QColor colorA, QColor colorB , double opacityA, double opacityB , QVector3D positionCam )
{
    //READERS
    vtkSmartPointer <vtkGenericDataObjectReader> readerMeshA = vtkSmartPointer <vtkGenericDataObjectReader>::New();
    readerMeshA -> SetFileName( meshA.c_str() );
    readerMeshA -> Update();

    vtkSmartPointer <vtkGenericDataObjectReader> readerMeshB = vtkSmartPointer <vtkGenericDataObjectReader>::New();
    readerMeshB -> SetFileName( meshB.c_str() );
    readerMeshB -> Update();

    //MAPPERS
    vtkSmartPointer <vtkPolyDataMapper> mapperMeshA = vtkSmartPointer <vtkPolyDataMapper>::New();
    mapperMeshA -> SetInputConnection( readerMeshA -> GetOutputPort() );

    vtkSmartPointer <vtkPolyDataMapper> mapperMeshB = vtkSmartPointer <vtkPolyDataMapper>::New();
    mapperMeshB -> SetInputConnection( readerMeshB -> GetOutputPort() );

    //ACTORS
    vtkSmartPointer <vtkActor> actorMeshA = vtkSmartPointer <vtkActor>::New();
    actorMeshA -> SetMapper( mapperMeshA );
    actorMeshA -> GetProperty() -> SetColor( colorA.red() , colorA.green() , colorA.blue() );
    actorMeshA -> GetProperty() -> SetOpacity( opacityA );

    vtkSmartPointer <vtkActor> actorMeshB = vtkSmartPointer <vtkActor>::New();
    actorMeshB -> SetMapper( mapperMeshB );
    actorMeshB -> GetProperty() -> SetColor( colorB.red() , colorB.green() , colorB.blue() );
    actorMeshB -> GetProperty() -> SetOpacity( opacityB );

    //CAMERA
    vtkSmartPointer <vtkCamera> cameraMesh = vtkSmartPointer <vtkCamera>::New();

    //RENDERER
    vtkSmartPointer<vtkRenderer> rendererMesh = vtkSmartPointer<vtkRenderer>::New();
    rendererMesh -> SetBackground( .6 , .5 , .4 );
    rendererMesh -> AddActor( actorMeshA );
    rendererMesh -> AddActor( actorMeshB );
    rendererMesh -> SetActiveCamera( cameraMesh );
    rendererMesh -> ResetCamera();

     positionCamera( cameraMesh , positionCam.x() , positionCam.y() , positionCam.z() );

    //RENDER WINDOW
    vtkSmartPointer <vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow-> AddRenderer( rendererMesh );

    //Display
    widgetMesh -> SetRenderWindow( renderWindow );
    widgetMesh -> resize( size );
    renderWindow -> Render();
    widgetMesh -> show();
}

// change the position of the camera
void positionCamera( vtkSmartPointer <vtkCamera> camera , int x ,int y , int z )
{

    double *focalPoint  = camera -> GetFocalPoint();
    double distance = camera -> GetDistance();

    camera -> SetPosition( focalPoint[0] + x*distance , focalPoint[1] + y*distance , focalPoint[2]+ z*distance );
    camera -> SetRoll(.001);
}
