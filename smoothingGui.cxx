#include "smoothingGui.h"

smoothingGui::smoothingGui(QWidget * parent , Qt::WFlags f ): QMainWindow( parent, f)
{
    setupUi(this);

    m_NumberOfMesh = 0;
    m_MeshSelected = -1;

    QObject::connect( pushButtonQuit , SIGNAL( clicked() ) , this , SLOT( pushButtonQuitClicked() ) );
    QObject::connect( pushButtonRun , SIGNAL( clicked() ) , this , SLOT( applySmoothing() ) );
    QObject::connect( spinBoxIteration , SIGNAL( valueChanged( int ) ) , this , SLOT( ChangeValueSmoothing() ) );
    QObject::connect( checkBoxDisplay , SIGNAL( toggled( bool ) ) , this , SLOT( ChangeDisplaySmoothing() ) );
    QObject::connect( listWidgetLoadedMesh , SIGNAL( itemClicked( QListWidgetItem* ) ) , this , SLOT( ChangeMeshSelected() ) );

    checkBoxDisplay -> setEnabled( false );
    pushButtonRun -> setEnabled( false );
    spinBoxIteration -> setEnabled( false );
}

//***********************************************************************************
void smoothingGui::setWindow( display WindowMesh )
{
   m_MyWindowMesh = WindowMesh;
}

void smoothingGui::setIcon( QIcon Visible , QIcon Unvisible )
{
   m_Visible = Visible;
   m_Unvisible = Unvisible;
}

void smoothingGui::setData( std::vector <data::data> DataList )
{
    m_DataList = DataList;
}

void smoothingGui::setProcess( processing Process )
{
    m_MyProcess = Process;
}

//***********************************************************************************
void smoothingGui::reset()
{
    m_SmoothList.clear();
    listWidgetLoadedMesh->clear();
}

void smoothingGui::addOne( std::string Name )
{
    m_NumberOfMesh++;
    m_SmoothList.push_back( false );
    listWidgetLoadedMesh -> addItem( Name.c_str() );
}

void smoothingGui::deleteOne( int IndiceOfMesh )
{
    m_DataList.erase( m_DataList.begin() + IndiceOfMesh );
    m_SmoothList.erase( m_SmoothList.begin() + IndiceOfMesh );
    delete listWidgetLoadedMesh -> item( IndiceOfMesh );
    m_NumberOfMesh--;
}


//***********************************************************************************
void smoothingGui::pushButtonQuitClicked()
{
    close();
}

void smoothingGui::ChangeMeshSelected()
{
    if( m_NumberOfMesh != 0 )
    {
        m_MeshSelected = listWidgetLoadedMesh -> currentRow();

        if( m_MeshSelected != -1 )
        {
            spinBoxIteration -> setValue( m_DataList[ m_MeshSelected ].getNumberOfIterationSmooth() );
            spinBoxIteration -> setEnabled( true );

            checkBoxDisplay -> setChecked( m_DataList[ m_MeshSelected ].getDisplaySmoothing() );
            checkBoxDisplay -> setEnabled( m_SmoothList[ m_MeshSelected ] );

            pushButtonRun -> setEnabled( ! m_DataList[ m_MeshSelected ].getDisplaySmoothing() );
        }
    }
}

//***********************************************************************************
void smoothingGui::ChangeValueSmoothing()
{
    if( m_MeshSelected != -1 )
    {
        m_DataList[ m_MeshSelected ].setNumberOfIterationSmooth( spinBoxIteration -> value() );
        
        pushButtonRun -> setEnabled( true );
        checkBoxDisplay -> setEnabled( false );
    }
}

void smoothingGui::ChangeDisplaySmoothing()
{
    if( m_MeshSelected != -1 )
    {
        m_DataList.[ m_MeshSelected ].setDisplaySmoothing( checkBoxDisplay -> isChecked() );

        if( checkBoxDisplay -> isChecked() )
        {
            m_DataList[ m_MeshSelected ].changeMapperInputPort( 2 );
        }
        else if( ! checkBoxDisplay -> isChecked() )
        {
            m_DataList[ m_MeshSelected ].changeMapperInputPort( 1 );
        }
        m_MyWindowMesh.updateWindow();
    }
}

void smoothingGui::applySmoothing()
{
    if( m_MeshSelected != -1 )
    {
        m_DataList[ m_MeshSelected ].setDisplaySmoothing( true );
        m_SmoothList[ m_MeshSelected ] = true;

        m_MyProcess.processSmoothing( m_DataList[ m_MeshSelected ] );
        m_MyWindowMesh.updateWindow();

        checkBoxDisplay -> setChecked( true );
        checkBoxDisplay -> setEnabled( true );
        pushButtonRun -> setEnabled( false );
    }
}
