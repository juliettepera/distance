#ifndef PROCESSING_H
#define PROCESSING_H

/* CLASS WHERE ALL THE PROCESS IS DONE THANK TO THE DATA STOCKED ON DATA
 *  -> DO THE SMOOTHING
 *  -> DO THE DOWNSAMPLING
 *  -> DO THE ERROR
 */

// My libraries
#include "data.h"

// QT libraries
#include <QMessageBox>

// VTK libraries
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>

// OTHER libraries
#include <string>
#include <iostream>
#include <vector>

class processing
{
    public:
        processing();
        int processSmoothing( data Data );
        int processDownSampling( data Data );
        int processError( data Data1 , data Data2 );
};

#endif
