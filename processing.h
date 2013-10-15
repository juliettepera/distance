#ifndef PROCESSING_H
#define PROCESSING_H

/* CLASS WHERE ALL THE PROCESS IS DONE THANK TO THE DATA STOCKED ON DATA
 *  -> DO THE SMOOTHING
 *  -> DO THE DOWNSAMPLING
 *  -> DO THE ERROR
 */

// My libraries
#include "dataM.h"
#include "testMeshValmet.h"

// QT libraries
#include <QMessageBox>

// VTK libraries
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkColorTransferFunction.h>

// OTHER libraries
#include <string>
#include <iostream>
#include <vector>

class processing
{
    public:
        processing();
        int processSmoothing(dataM &Data );
        int processDownSampling( dataM &Data );
        int processError(dataM &Data1 , dataM &Data2 );
        int testPolyData( vtkSmartPointer <vtkPolyData> inData , vtkSmartPointer <vtkPolyData> outData );

    private:
        testMeshValmet m_MyMeshValmet;
};

#endif
