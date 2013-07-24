#include "distanceDisplay.h"



void initialisation(QTextBrowser* widgetText)
{
    // change text and background color
    // change font and size
    widgetText->setText("Choose Mesh A");
}

void windowInitialisation( QVTKWidget* widgetMesh , std::string mesh , QSize s )
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

    //RENDERER
    vtkSmartPointer<vtkRenderer> rendererMesh = vtkSmartPointer<vtkRenderer>::New();
    rendererMesh-> SetBackground( .6 , .5 , .4 );
    rendererMesh -> AddActor( actorMesh );
    rendererMesh->ResetCamera();

    //RENDER WINDOW
    vtkSmartPointer <vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow-> AddRenderer( rendererMesh );

    //Display
    widgetMesh -> SetRenderWindow( renderWindow );
    widgetMesh-> resize( s );
    renderWindow -> Render();
    widgetMesh -> show();
}


