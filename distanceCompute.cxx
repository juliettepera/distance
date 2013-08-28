#include "distanceCompute.h"

distanceCompute::distanceCompute()
{
    m_DataMeshA = vtkSmartPointer <vtkPolyData>::New();
    m_DataMeshB = vtkSmartPointer <vtkPolyData>::New();
    m_DataCompute = vtkSmartPointer <vtkPolyData>::New();
}

void distanceCompute::computeDistanceAtoB()
{
    std::cout << std::endl << "you want to compute the A to B distances " << std::endl;
}

void distanceCompute::computeDistanceBtoA()
{
    std::cout << std::endl << "you want to compute the B to A distances " << std::endl;
}

void distanceCompute::computeDistanceBoth()
{
    std::cout << std::endl << "you want to compute both distances " << std::endl;
}
