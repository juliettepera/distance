#include "downSamplingGui.h"

downSamplingGui::downSamplingGui(QWidget * parent , Qt::WFlags f  ): QMainWindow(parent, f)
{
    setupUi(this);

    m_NumberOfMesh = 0;
    m_MeshSelected = -1;

    QObject::connect( pushButtonQuit , SIGNAL( clicked() ) , this , SLOT( pushButtonQuitClicked() ) );
    QObject::connect( horizontalSliderDecimate , SIGNAL( sliderReleased() ), this, SLOT( ChangeValueDecimate() ) );
    QObject::connect( listWidgetLoadedMesh , SIGNAL( itemClicked( QListWidgetItem* ) ) , this , SLOT( ChangeMeshSelected() ) );
    QObject::connect( pushButtonRun , SIGNAL( clicked() ) , this , SLOT( applyDownSampling() ) );

    pushButtonRun -> setEnabled( false );
    horizontalSliderDecimate -> setEnabled( false );
}

//***********************************************************************************
void downSamplingGui::setWindow( meshQtDisplay WindowMesh )
{
   m_MyWindowMesh = WindowMesh;
}


//***********************************************************************************
void downSamplingGui::reset()
{
    m_DecimateList.clear();
    listWidgetLoadedMesh->clear();
}

void downSamplingGui::addOne( std::string Name )
{
    m_NumberOfMesh++;
    m_DecimateList.push_back( 0 );
    listWidgetLoadedMesh -> addItem( Name.c_str() );
}

void downSamplingGui::deleteOne( int IndiceOfMesh )
{
    m_DecimateList.erase( m_DecimateList.begin() + IndiceOfMesh );
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
        m_MeshSelected = listWidgetLoadedMesh -> currentRow();

        if( m_MeshSelected != -1 )
        {
            horizontalSliderDecimate -> setValue( m_DecimateList[ m_MeshSelected ] );
            lcdNumberDecimate -> display( m_DecimateList[ m_MeshSelected ] );

            m_ActivTool = m_MyWindowMesh.getTool( m_MeshSelected );

            pushButtonRun -> setEnabled( true );
            horizontalSliderDecimate -> setEnabled( true );
        }
    }
}
//***************************************************************************************

void downSamplingGui::ChangeValueDecimate()
{
    if( m_MeshSelected != -1 )
    {
        m_DecimateList[ m_MeshSelected ] = horizontalSliderDecimate -> value();
        lcdNumberDecimate -> display( m_DecimateList[ m_MeshSelected ] );
        m_ActivTool.setDecimate( m_DecimateList[ m_MeshSelected ]/100. );
        pushButtonRun -> setEnabled( true );
    }
}

void downSamplingGui::applyDownSampling()
{
    if( m_MeshSelected != -1 )
    {
        m_ActivTool.changeDataDecimer();

        m_ActivTool.changeMapperInputPort( 3 );

        m_MyWindowMesh.windowUpdate();
    }
}
