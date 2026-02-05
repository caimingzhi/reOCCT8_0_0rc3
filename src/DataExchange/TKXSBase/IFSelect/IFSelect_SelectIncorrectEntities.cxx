#include <IFSelect_SelectIncorrectEntities.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectIncorrectEntities, IFSelect_SelectFlag)

IFSelect_SelectIncorrectEntities::IFSelect_SelectIncorrectEntities()
    : IFSelect_SelectFlag("Incorrect")
{
}
