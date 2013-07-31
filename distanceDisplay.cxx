#include "distanceDisplay.h"
#include "distanceGui.h"

// globales variables
    vtkSmartPointer <vtkGenericDataObjectReader> readerMeshA = vtkSmartPointer <vtkGenericDataObjectReader>::New(); // reader A
    vtkSmartPointer <vtkGenericDataObjectReader> readerMeshB = vtkSmartPointer <vtkGenericDataObjectReader>::New(); // reader B

    vtkSmartPointer <vtkPolyDataMapper> mapperMeshA = vtkSmartPointer <vtkPolyDataMapper>::New(); // mapper A
    vtkSmartPointer <vtkPolyDataMapper> mapperMeshB = vtkSmartPointer <vtkPolyDataMapper>::New(); // mapper B

    vtkSmartPointer <vtkActor> actorMeshA = vtkSmartPointer <vtkActor>::New(); // actor A
    vtkSmartPointer <vtkActor> actorMeshB = vtkSmartPointer <vtkActor>::New(); // actor B

    QColor colorA; // color A
    QColor colorB; // color B

    vtkSmartPointer<vtkRenderer> rendererMesh = vtkSmartPointer<vtkRenderer>::New(); // renderer

    vtkSmartPointer <vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New(); // render window

    QSize size( 711 , 491 );// size


void windowInit( QVTKWidget* widgetMesh , std::string meshA , std::string meshB )
{
    // init reader A
    readerMeshA -> SetFileName( meshA.c_str() );
    readerMeshA -> Update();

    // init reader B
    readerMeshB -> SetFileName( meshB.c_str() );
    readerMeshB -> Update();

    // init mapper A
     mapperMeshA -> SetInputConnection( readerMeshA -> GetOutputPort() );

    // init mapper B
    mapperMeshB -> SetInputConnection( readerMeshB -> GetOutputPort() );

    // init color A
    colorA.setRed( 0.0 ) ; colorA.setGreen( 1.0 ) ; colorA.setBlue( 1.0 );

    // init color B
    colorB.setRed( 0.0 ) ; colorB.setGreen( 0.0 ) ; colorB.setBlue( 1.0 );

    // init actor A
    actorMeshA -> SetMapper( mapperMeshA );
    actorMeshA -> GetProperty() -> SetColor( colorA.red() , colorA.green() , colorA.blue() );

    // init actor B
    actorMeshB -> SetMapper( mapperMeshB );
    actorMeshB -> GetProperty() -> SetColor( colorB.red() , colorB.green() , colorB.blue() );

    // init renderer
    rendererMesh -> SetBackground( .6 , .5 , .4 );
    rendererMesh -> AddActor( actorMeshA );
    rendererMesh -> AddActor( actorMeshB );

    // reset camera
    rendererMesh -> ResetCamera();

    // init render window
    renderWindow-> AddRenderer( rendererMesh );

    // init widget
    widgetMesh -> SetRenderWindow( renderWindow );
    widgetMesh -> resize( size );

    // Display
    renderWindow -> Render();
    widgetMesh -> show();

}

// update the window with both mesh
void windowUpdate( QVTKWidget* widgetMesh , double opacityA, double opacityB , QVector3D positionCam )
{

    // set parameters
    actorMeshA -> GetProperty() -> SetOpacity( opacityA );
    actorMeshB -> GetProperty() -> SetOpacity( opacityB );
    positionCamera( rendererMesh->GetActiveCamera() , positionCam.x() , positionCam.y() , positionCam.z() );

    // display
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
