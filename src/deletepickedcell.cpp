//
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +                                                                      +
// + This file is part of enGrid.                                         +
// +                                                                      +
// + Copyright 2008,2009 Oliver Gloth                                     +
// +                                                                      +
// + enGrid is free software: you can redistribute it and/or modify       +
// + it under the terms of the GNU General Public License as published by +
// + the Free Software Foundation, either version 3 of the License, or    +
// + (at your option) any later version.                                  +
// +                                                                      +
// + enGrid is distributed in the hope that it will be useful,            +
// + but WITHOUT ANY WARRANTY; without even the implied warranty of       +
// + MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        +
// + GNU General Public License for more details.                         +
// +                                                                      +
// + You should have received a copy of the GNU General Public License    +
// + along with enGrid. If not, see <http://www.gnu.org/licenses/>.       +
// +                                                                      +
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//

#include "deletepickedcell.h"
#include "guimainwindow.h"
#include "deletepickedpoint.h"

#include <vtkCell.h>
#include <vtkGenericCell.h>

void DeletePickedCell::operate()
{
  vtkIdType cellId = GuiMainWindow::pointer()->getPickedCell();
  cout<<"You picked "<<cellId<<endl;
  vtkIdType N_pts, *pts;
  grid->GetCellPoints(cellId, N_pts, pts);
//   quad2triangle(grid,cellId,pts[3]);
  int N_newpoints;
  int N_newcells;
  for(int i=0;i<N_pts;i++) DeletePoint(grid,pts[i], N_newpoints, N_newcells);
//   quad2triangle(vtkUnstructuredGrid* src,vtkIdType quadcell,vtkIdType MovingPoint)
};