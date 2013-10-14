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
int processing::processSmoothing( dataM &Data )
{
    std::cout << " doing smoothing ... " << std::endl;

    vtkSmartPointer <vtkPolyData> SmoothedData = vtkSmartPointer<vtkPolyData>::New();
    Data.getPolyData( SmoothedData );
    Data.getSmoother() -> SetInputData( SmoothedData );

    int NumberOfPoints = SmoothedData -> GetNumberOfPoints();

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

    std::cout << " ... smoothing done " << std::endl;

    return 0;
}

/* process the downsampling of the choosen file
 * if the displayError == true ( means that the user want to display the error )
 * the input data is the polyDataError
 * else, it the original data
 * return 0 in case there is no error and 1 in case there is error
 */
int processing::processDownSampling(dataM &Data )
{
    vtkSmartPointer <vtkPolyData> DecimatedData = vtkSmartPointer<vtkPolyData>::New();
    Data.getPolyData( DecimatedData );
    Data.getDecimer() -> SetInputData( DecimatedData );

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

/* process the downsampling of the choosen file
 * if the displayError == true ( means that the user want to display the error )
 * the input data is the polyDataError
 * else, it the original data
 * return 0 in case there is no error and 1 in case there is error
 */
int processing::processError( dataM &Data1 , dataM &Data2 )
{
    /*vtkSmartPointer <vtkPolyData> DataCopy1 = vtkSmartPointer <vtkPolyData>::New();
    vtkSmartPointer <vtkPolyData> DataCopy2 = vtkSmartPointer <vtkPolyData>::New();
    Data1.getPolyData( DataCopy1 );
    Data2.getPolyData( DataCopy2);*/

    vtkSmartPointer <vtkPolyData> ErrorData = vtkSmartPointer<vtkPolyData>::New();
    vtkSmartPointer <vtkColorTransferFunction> ErrorLut = vtkSmartPointer <vtkColorTransferFunction>::New();

    m_MyMeshValmet.SetFileName1( Data1.getName() );
    m_MyMeshValmet.SetFileName2( Data2.getName() );
    //m_MyMeshValmet.SetData1( DataCopy1 );
    //m_MyMeshValmet.SetData2( DataCopy2 );

    m_MyMeshValmet.SetSignedDistance( Data1.getSignedDistance() );
    m_MyMeshValmet.SetSamplingStep( Data1.getSamplingStep() );
    m_MyMeshValmet.SetMinSampleFrequency( Data1.getMinSamplingFrequency() );

    m_MyMeshValmet.CalculateError();

    std::cout << " Error calculeted " << std::endl;

    ErrorData = m_MyMeshValmet.GetFinalData();
    ErrorLut = m_MyMeshValmet.GetLut();

    Data1.setPolyData( ErrorData );
    Data1.setLut( ErrorLut );

    std::cout << " Data and Lut recupered " << std::endl;

    Data1.changeMapperInput( 1 );

    return 0;
}

/*void processing::describePolyData( vtkSmartPointer <vtkPolyData> Data )
{
   int NumberOfPoints = Data->GetNumberOfPoints();
   int NumberOfCells = Data->GetNumberOfCells();

   vtkSmartPointer <vtkPoints> Points = vtkSmartPointer <vtkPoints> ::New();
   vtkSmartPointer <vtkCellArray> Polys = vtkSmartPointer <vtkCellArray> ::New();

   Points = Data -> GetPoints();
   Polys = Data -> GetPolys();

   vtkIdType Id = 0;
   vtkIdType Row = 0;
   vtkIdType *f;
   double v[3];


   std::cout << "********************************Points********************************************************************" << std::endl;
   std::cout << " Number of points : " << NumberOfPoints << std::endl;
   for( Id = 0 ; Id < NumberOfPoints ; Id++ )
   {
       Points-> GetPoint( Id , v );
       std::cout << v[ 0 ] << " | " << v[ 1 ] << " | " << v[ 2 ] << std::endl;
   }

   std::cout << "********************************Cells********************************************************************" << std::endl;
   std::cout << " Number of cells : " << NumberOfCells << std::endl;
   while( Polys -> GetNextCell( Row , f ) )
   {
        std::cout << f[ 0 ] << " | " << f[ 1 ] << " | " << f[ 2 ] << std::endl;
   }

}*/

