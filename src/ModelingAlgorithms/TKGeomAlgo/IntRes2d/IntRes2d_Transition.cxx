#include <IntRes2d_Transition.hpp>
#include <Standard_DomainError.hpp>

IntRes2d_Transition::IntRes2d_Transition()
    : tangent(true),
      posit(IntRes2d_Middle),
      typetra(IntRes2d_Undecided),
      situat(IntRes2d_Unknown),
      oppos(false)
{
}

std::ostream& operator<<(std::ostream& os, IntRes2d_Transition& Trans)
{

  os << "   Position : ";
  if (Trans.PositionOnCurve() == IntRes2d_Head)
  {
    os << "Debut\n";
  }
  else if (Trans.PositionOnCurve() == IntRes2d_Middle)
  {
    os << "Milieu\n";
  }
  else
  {
    os << "Fin\n";
  }

  os << "   Type de transition : ";
  if (Trans.TransitionType() == IntRes2d_Undecided)
  {
    os << "Indeterminee\n";
  }
  else
  {
    if (Trans.TransitionType() == IntRes2d_In)
    {
      os << "Entrante\n";
    }
    else if (Trans.TransitionType() == IntRes2d_Out)
    {
      os << "Sortante\n";
    }
    else
    {
      os << "Touch\n";
      os << "     Position par rapport a l'autre courbe : ";
      if (Trans.Situation() == IntRes2d_Inside)
      {
        os << "Interieure\n";
      }
      else if (Trans.Situation() == IntRes2d_Outside)
      {
        os << "Exterieure\n";
      }
      else if (Trans.Situation() == IntRes2d_Unknown)
      {
        os << "Indeterminee\n";
      }
      os << "   Position matiere : ";
      if (Trans.IsOpposite())
      {
        os << "Opposee\n";
      }
      else
      {
        os << "Idem\n";
      }
    }
    os << "   Cas de tangence : ";
    if (Trans.IsTangent())
    {
      os << "Oui\n";
    }
    else
    {
      os << "Non\n";
    }
  }
  os << "\n";
  return os;
}
