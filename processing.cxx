#include "processing.h"

processing::processing()
{
}

/* process the smoothing of the choosen file
 * if the displayError == true ( means that the user want to display the error )
 * the input data is the polyDataError
 * else, it the original data
 * return 0 in case there is no error and 1 in case there is error
 */
int processing::processSmoothing( data Data )
{
    vtkSmartPointer <vtkPolyData> SmoothedData = vtkSmartPointer<vtkPolyData>::New();

    Data.getSmoother() -> SetInputData( Data.getPolyData() );

    int NumberOfPoints = Data.getPolyData() -> GetNumberOfPoints();

    Data.getSmoother() -> SetNumberOfIterations( Data.getNumberOfIterationSmooth() );
    Data.getSmoother() -> Update();
    SmoothedData =  Data.getSmoother() -> GetOutput();

    if( NumberOfPoints != SmoothedData -> GetNumberOfPoints() )
    {
        QMessageBox MsgBox;
        MsgBox.setText( " ERROR : PROCESSING SMOOTHING ");
        MsgBox.exec();
        return 1;
    }

    Data.setPolyData( SmoothedData );
    Data.changeMapperInput( 2 );

    return 0;
}

/* process the downsampling of the choosen file
 * if the displayError == true ( means that the user want to display the error )
 * the input data is the polyDataError
 * else, it the original data
 * return 0 in case there is no error and 1 in case there is error
 */
int processing::processDownSampling( data Data )
{
    vtkSmartPointer <vtkPolyData> DecimatedData = vtkSmartPointer<vtkPolyData>::New();

    Data.getDecimer() -> SetInputData( Data.getPolyData() );

    Data.getDecimer() -> SetTargetReduction( Data.getDecimate() );
    Data.getDecimer() -> Update();

    DecimatedData = Data.getDecimer() -> GetOutput();

    if( DecimatedData -> GetNumberOfPoints() == 0 )
    {
        QMessageBox MsgBox;
        MsgBox.setText( " ERROR : PROCESSING DOWN SAMPLING ");
        MsgBox.exec();
        return 1;
    }

    Data.setPolyData( DecimatedData );

    Data.changeMapperInput( 3 );

    return 0;
}

int processing::processError( data Data1 , data Data2 )
{

}

