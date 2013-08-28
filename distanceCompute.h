#ifndef DISTANCECOMPUTE_H
#define DISTANCECOMPUTE_H

// MeshValmet Libraries

// vtk Libraries
#include "vtkSmartPointer.h"
#include "vtkPolyData.h"

// Other Libraries
#include <string>
#include <iostream>

class distanceCompute
{
    public:
        distanceCompute();

        void computeDistanceAtoB();
        void computeDistanceBtoA();
        void computeDistanceBoth();

    private:
        vtkSmartPointer <vtkPolyData> m_DataMeshA;
        vtkSmartPointer <vtkPolyData> m_DataMeshB;
        vtkSmartPointer <vtkPolyData> m_DataCompute;
};

#endif
