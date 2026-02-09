

#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <Vrml_MatrixTransform.hpp>

Vrml_MatrixTransform::Vrml_MatrixTransform()
{

  gp_Trsf T;
  T.SetValues(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0);
  T.SetScaleFactor(1);

  myMatrix = T;
}

Vrml_MatrixTransform::Vrml_MatrixTransform(const gp_Trsf& aMatrix)
{
  myMatrix = aMatrix;
}

void Vrml_MatrixTransform::SetMatrix(const gp_Trsf& aMatrix)
{
  myMatrix = aMatrix;
}

gp_Trsf Vrml_MatrixTransform::Matrix() const
{
  return myMatrix;
}

Standard_OStream& Vrml_MatrixTransform::Print(Standard_OStream& anOStream) const
{
  int i, j;
  anOStream << "MatrixTransform {\n";

  if (std::abs(myMatrix.Value(1, 1) - 1) > 0.0000001
      || std::abs(myMatrix.Value(2, 1) - 0) > 0.0000001
      || std::abs(myMatrix.Value(3, 1) - 0) > 0.0000001
      || std::abs(myMatrix.Value(1, 2) - 0) > 0.0000001
      || std::abs(myMatrix.Value(2, 2) - 1) > 0.0000001
      || std::abs(myMatrix.Value(3, 2) - 0) > 0.0000001
      || std::abs(myMatrix.Value(1, 3) - 0) > 0.0000001
      || std::abs(myMatrix.Value(2, 3) - 0) > 0.0000001
      || std::abs(myMatrix.Value(3, 3) - 1) > 0.0000001
      || std::abs(myMatrix.Value(1, 4) - 0) > 0.0000001
      || std::abs(myMatrix.Value(2, 4) - 0) > 0.0000001
      || std::abs(myMatrix.Value(3, 4) - 0) > 0.0000001)
  {
    anOStream << "    matrix\t";

    for (j = 1; j <= 4; j++)
    {
      for (i = 1; i <= 3; i++)
      {

        anOStream << myMatrix.Value(i, j) << ' ';
      }
      if (j != 4)
      {
        anOStream << "0\n";
        anOStream << "\t\t";
      }
      else
      {
        anOStream << myMatrix.ScaleFactor() << "\n";
      }
    }
  }
  anOStream << "}\n";
  return anOStream;
}
