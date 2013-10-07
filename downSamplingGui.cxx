#include "downSamplingGui.h"

downSamplingGui::downSamplingGui(QWidget * parent , Qt::WFlags f  ): QMainWindow(parent, f)
{
    setupUi(this);

    m_NumberOfMesh = 0;
    m_MeshSelected = -1;

    QObject::connect( pushButtonQuit , SIGNAL( clicked() ) , this , SLOT( pushButtonQuitClicked() ) );
    QObject::connect( horizontalSliderDensity , SIGNAL( sliderReleased() ), this, SLOT( ChangeValueDensity() ) );
    QObject::connect( listWidgetLoadedMesh , SIGNAL( itemClicked( QListWidgetItem* ) ) , this , SLOT( ChangeMeshSelected() ) );
    QObject::connect( pushButtonRun , SIGNAL( clicked() ) , this , SLOT( applyDownSampling() ) );

    pushButtonRun -> setEnabled( false );
    horizontalSliderDensity -> setEnabled( false );
}

//***********************************************************************************
void downSamplingGui::setWindow( meshQtDisplay WindowMesh )
{
   m_MyWindowMesh = WindowMesh;
}


//***********************************************************************************
void downSamplingGui::reset()
{
    m_TypeList.clear();
    m_DensityList.clear();
    listWidgetLoadedMesh->clear();
}

void downSamplingGui::addOne( std::string Name )
{
    m_NumberOfMesh++;
    m_TypeList.push_back( 1 );
    m_DensityList.push_back( 0.05 );
    listWidgetLoadedMesh -> addItem( Name.c_str() );
}

void downSamplingGui::deleteOne( int IndiceOfMesh )
{
    m_TypeList.erase( m_TypeList.begin() + IndiceOfMesh );
    m_DensityList.erase( m_DensityList.begin() + IndiceOfMesh );
    delete listWidgetLoadedMesh -> item( IndiceOfMesh );
    m_NumberOfMesh--;
}


//***********************************************************************************
void downSamplingGui::pushButtonQuitClicked()
{
    close();
}

void downSamplingGui::ChangeMeshSelected()
{
    if( m_NumberOfMesh != 0 )
    {
        m_MeshSelected = listWidgetLoadedMesh -> currentRow();\
        horizontalSliderDensity -> setValue( m_DensityList[ m_MeshSelected ]*100 );
        lcdNumberDensity -> display( m_DensityList[ m_MeshSelected ] );

        if( m_MeshSelected != -1 )
        {
            m_ActivTool = m_MyWindowMesh.getTool( m_MeshSelected );
            m_TypeList[ m_MeshSelected ] = m_ActivTool.getType();

            pushButtonRun -> setEnabled( true );
            horizontalSliderDensity -> setEnabled( true );
        }
    }
}
//***************************************************************************************

void downSamplingGui::ChangeValueDensity()
{
    if( m_MeshSelected != -1 )
    {
        m_DensityList[ m_MeshSelected ] = horizontalSliderDensity -> value()/100.;
        lcdNumberDensity -> display( m_DensityList[ m_MeshSelected ] );
        m_ActivTool.setDensity( m_DensityList[ m_MeshSelected ] );
        pushButtonRun -> setEnabled( true );
    }
}

void downSamplingGui::applyDownSampling()
{
    if( m_MeshSelected != 1 )
    {
        m_ActivTool.changeDataSampler();

        if( m_TypeList[ m_MeshSelected ] == 1 )
        {
            //m_ActivTool.changeMapperInputPort( m_ActivTool.getReader() -> GetOutputPort() );
        }
        else if( m_TypeList[ m_MeshSelected ] == 2 )
        {
            m_ActivTool.changeMapperInputPort( 3 );
        }
        else if( m_TypeList[ m_MeshSelected ] == 3 )
        {
            //m_ActivTool.changeMapperInputPort( m_ActivTool.getReader() -> GetOutputPort() );
        }

        m_MyWindowMesh.windowUpdate();
    }
}
