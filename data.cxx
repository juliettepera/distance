#include "data.h"

data::data( std::string Name )
{
    // init the basic data
    m_Name = Name;
    m_Mapper = vtkSmartPointer <vtkPolyDataMapper>::New();
    m_Actor = vtkSmartPointer <vtkActor>::New();
    m_PolyData = vtkSmartPointer <vtkPolyData>::New();

    // init the file properties
    m_Opacity = 1.0;
    m_Red = rand()/(double)RAND_MAX;
    m_Green = rand()/(double)RAND_MAX;
    m_Blue = rand()/(double)RAND_MAX;
    m_Type = 1;

    // init the smoothing parameters
    m_NumberOfIterationSmooth = 500;
    m_Smoother = vtkSmartPointer <vtkSmoothPolyDataFilter>::New();

    // init the downSampling parameters
    m_Decimate = 0.0;
    m_Decimer = vtkSmartPointer <vtkDecimatePro>::New();

    // init the error parameters
    m_MinSamplingFrequency = 2.0;
    m_SamplingStep = 0.5;
    m_SignedDistance = false;
    m_DisplayError = false;
    m_PolyDataError = vtkSmartPointer <vtkPolyData>::New();
    m_Lut = vtkSmartPointer <vtkColorTransferFunction>::New();
}

/* initialize the reading of the file, create the polydata, update the properties of the
*  file, the type of display, connect the mapper to the actor
*/
void data::initialization()
{
    vtkSmartPointer <vtkPolyDataReader> Reader = vtkSmartPointer <vtkPolyDataReader>::New();
    vtkSmartPointer <vtkTriangleFilter> Triangler = vtkSmartPointer <vtkTriangleFilter>::New();

    Reader -> SetFileName( m_Name.c_str() );
    Reader -> Update();

    Triangler -> SetInputData( Reader -> GetOutput() );
    Triangler -> Update();

    m_PolyData -> ShallowCopy( Triangler -> GetOutput() );

    m_Mapper -> SetInputData( m_PolyData );

    updateActorProperties();
    updateTypeOfDisplay();

    m_Actor -> SetMapper( m_Mapper );
}

/* update the properties of the file ( opacity and color )
 */
void data::updateActorProperties()
{
    m_Actor -> GetProperty() -> SetOpacity( m_Opacity );
    m_Actor -> GetProperty() -> SetColor( m_Red , m_Green , m_Blue );
}

/* update the type of display of the file
 * type = 1 : surface | 2 : points | 3 : wireframe
 * return 0 in case of success and 1 in case of error
 **/
int data::updateTypeOfDisplay()
{
    if( m_Type == 1 )
    {
        m_Actor -> GetProperty() -> SetRepresentationToSurface();
        return 0;
    }
    else if( m_Type == 2 )
    {
       m_Actor -> GetProperty() -> SetRepresentationToPoints();
       return 0;
    }
    else if( m_Type == 3 )
    {
       m_Actor -> GetProperty() -> SetRepresentationToWireframe();
       return 0;
    }
    else
    {
        QMessageBox MsgBox;
        MsgBox.setText( " ERROR : TYPE OF DISPLAY ");
        MsgBox.exec();
        return 1;
    }
}

/* change the input of the mapper in function of the choice
 * choice = 1 : data ( with or without error ) | 2 : data smoothed | 3 : data downsampled
 * return 0 in case of success and 1 in case of error
 */
int data::changeMapperInput( int Choice )
{
    m_Mapper = vtkSmartPointer <vtkPolyDataMapper>::New();

    if( Choice == 1 )
    {
       m_Mapper -> SetInputData( m_PolyData );
    }
    else if( Choice == 2 )
    {
       m_Mapper -> SetInputData( m_Smoother -> GetOutput() );
    }
    else if( Choice == 3 )
    {
       m_Mapper -> SetInputData( m_Decimer -> GetOutput() );
    }
    else
    {
        QMessageBox MsgBox;
        MsgBox.setText( " ERROR : CHANGE MAPPER INPUT ");
        MsgBox.exec();
        return 1;
    }

    m_Actor -> SetMapper( m_Mapper );
    return 0;
}


// Set the basic data
void data::setName( std::string Name )
{
    m_Name = Name;
}

void data::setPolyData( vtkSmartPointer<vtkPolyData> PolyData )
{
    m_PolyData -> ShallowCopy( PolyData );
}

// Get the basic data
std::string data::getName()
{
    return m_Name;
}

vtkSmartPointer<vtkPolyDataMapper> data::getMapper()
{
    return m_Mapper;
}

vtkSmartPointer <vtkActor> data::getActor()
{
    return m_Actor;
}

vtkSmartPointer<vtkPolyData> data::getPolyData()
{
    return m_PolyData;
}

// Set the File properties
void data::setOpacity( double Opacity )
{
    m_Opacity = Opacity;
}

void data::setColor( double Red , double Green , double Blue )
{
    m_Red = Red;
    m_Green = Green;
    m_Blue = Blue;
}

void data::setType( int Type )
{
    m_Type = Type;
}

// Get the file properties
double data::getOpacity()
{
    return m_Opacity;
}

double data::getRed()
{
    return m_Red;
}

double data::getGreen()
{
    return m_Green;
}

double data::getBlue()
{
    return m_Blue;
}

int data::getType()
{
    return m_Type;
}

// Set the smoothing parameters
void data::setNumberOfIterationSmooth( int Number )
{
    m_NumberOfIterationSmooth = Number;
}

// Get the smoothing parameters
int data::getNumberOfIterationSmooth()
{
    return m_NumberOfIterationSmooth;
}

vtkSmartPointer <vtkSmoothPolyDataFilter> data::getSmoother()
{
    return m_Smoother;
}

// Set the downSampling parameters
void data::setDecimate(double Decimate)
{
    m_Decimate = Decimate;
}

double data::getDecimate()
{
    return m_Decimate;
}

vtkSmartPointer <vtkDecimatePro> data::getDecimer()
{
    return m_Decimer;
}

// Set the error parameters
void data::setMinSamplingFrequency( double MinSamplingFrequency )
{
    m_MinSamplingFrequency = MinSamplingFrequency;
}

void data::setSamplingStep( double SamplingStep )
{
    m_SamplingStep = SamplingStep;
}

void data::setSignedDistance( bool SignedDistance )
{
    m_SignedDistance = SignedDistance;
}

void data::setDisplayError( bool DisplayError )
{
    m_DisplayError = DisplayError;
}

void data::setPolyDataError( vtkSmartPointer <vtkPolyData> PolyDataError )
{
    m_PolyDataError -> ShallowCopy( PolyDataError );
}

void data::setLut( vtkSmartPointer <vtkColorTransferFunction> Lut )
{
    m_Lut = Lut;
}

// Get the error parameters
double data::getMinSamplingFrequency()
{
    return m_MinSamplingFrequency;
}

double data::getSamplingStep()
{
    return m_SamplingStep;
}

bool data::getSignedDistance()
{
    return m_SignedDistance;
}

bool data::getDisplayError()
{
    return m_DisplayError;
}

vtkSmartPointer <vtkPolyData> data::getPolyDataError()
{
    return m_PolyDataError;
}

vtkSmartPointer <vtkColorTransferFunction> data::getLut()
{
    return m_Lut;
}

















