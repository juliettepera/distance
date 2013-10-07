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
void smoothingGui::setWindow( meshQtDisplay WindowMesh )
{
   m_MyWindowMesh = WindowMesh;
}

void smoothingGui::setIcon( QIcon Visible , QIcon Unvisible )
{
   m_Visible = Visible;
   m_Unvisible = Unvisible;
}

//***********************************************************************************
void smoothingGui::reset()
{
    m_DisplayList.clear();
    m_NumberOfIterationList.clear();
    m_SmoothList.clear();
    listWidgetLoadedMesh->clear();
}

void smoothingGui::addOne( std::string Name )
{
    m_NumberOfMesh++;
    m_NumberOfIterationList.push_back( 500 );
    m_DisplayList.push_back( false );
    m_SmoothList.push_back( false );
    listWidgetLoadedMesh -> addItem( Name.c_str() );
}

void smoothingGui::deleteOne( int IndiceOfMesh )
{
    m_NumberOfIterationList.erase( m_NumberOfIterationList.begin() + IndiceOfMesh );
    m_DisplayList.erase( m_DisplayList.begin() + IndiceOfMesh );
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
            spinBoxIteration -> setValue( m_NumberOfIterationList[ m_MeshSelected ] );
            spinBoxIteration -> setEnabled( true );

            checkBoxDisplay -> setChecked( m_DisplayList[ m_MeshSelected ] );
            checkBoxDisplay -> setEnabled( m_SmoothList[ m_MeshSelected ] );

            pushButtonRun -> setEnabled( ! m_DisplayList[ m_MeshSelected ] );

            m_ActivTool = m_MyWindowMesh.getTool( m_MeshSelected );          
        }
    }
}

//***********************************************************************************
void smoothingGui::ChangeValueSmoothing()
{
    if( m_MeshSelected != -1 )
    {
        m_NumberOfIterationList[ m_MeshSelected ] = spinBoxIteration -> value();
        m_ActivTool.setNumberOfIterationSmooth( m_NumberOfIterationList[ m_MeshSelected ] );

        pushButtonRun -> setEnabled( true );
        checkBoxDisplay -> setEnabled( false );
    }
}

void smoothingGui::ChangeDisplaySmoothing()
{
    if( m_MeshSelected != -1 )
    {
        m_DisplayList[ m_MeshSelected ] = checkBoxDisplay -> isChecked();
        m_ActivTool.setSmoothing( m_DisplayList[ m_MeshSelected ] );

        if( checkBoxDisplay -> isChecked() )
        {
            m_ActivTool.changeMapperInputPort( 2 );
        }
        else if( ! checkBoxDisplay -> isChecked() )
        {
            m_ActivTool.changeMapperInputPort( 1 );
        }
        m_MyWindowMesh.windowUpdate();
    }
}

void smoothingGui::applySmoothing()
{
    if( m_MeshSelected != -1 )
    {
        m_DisplayList[ m_MeshSelected ] = true;
        m_SmoothList[ m_MeshSelected ] = true;

        m_ActivTool.changeDataFilter();
        m_MyWindowMesh.windowUpdate();

        checkBoxDisplay -> setChecked( true );
        checkBoxDisplay -> setEnabled( true );
        pushButtonRun -> setEnabled( false );
    }
}
