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

#include "guideletebadaspecttris.h"

void GuiDeleteBadAspectTris::operate()
{
  double threshold = ui.doubleSpinBox->value();
  QList<vtkIdType> new_cells;
  for (vtkIdType id_cell = 0; id_cell < grid->GetNumberOfCells(); ++id_cell) {
    if (isVolume(id_cell,grid)) EG_ERR_RETURN("The grid contains volume cells");
    vtkIdType type_cell = grid->GetCellType(id_cell);
    if (type_cell == VTK_TRIANGLE) {
      vtkIdType *pts, N_pts;
      grid->GetCellPoints(id_cell, N_pts, pts);
      vec3_t x[3];
      for (int i = 0; i < 3; ++i) {
        grid->GetPoint(pts[i], x[i].data());
      };
      double l1 = (x[1]-x[0]).abs();
      double l2 = (x[2]-x[1]).abs();
      double l3 = (x[0]-x[2]).abs();
      double l_min = min(l1,min(l2,l3));
      double l_max = max(l1,max(l2,l3));
      double ratio = l_max/l_min;
      if (ratio <= threshold) {
        new_cells.append(id_cell);
      };
    } else {
      new_cells.append(id_cell);
    };
  };
  EG_VTKSP(vtkUnstructuredGrid, new_grid);
  allocateGrid(new_grid, new_cells.size(), grid->GetNumberOfPoints());
  for (vtkIdType id_node = 0; id_node < grid->GetNumberOfPoints(); ++id_node) {
    vec3_t x;
    grid->GetPoints()->GetPoint(id_node, x.data());
    new_grid->GetPoints()->SetPoint(id_node, x.data());
    copyNodeData(grid, id_node, new_grid, id_node);
  };
  foreach (vtkIdType id_cell, new_cells) {
    vtkIdType *pts, N_pts;
    grid->GetCellPoints(id_cell, N_pts, pts);
    vtkIdType type_cell = grid->GetCellType(id_cell);
    vtkIdType id_new_cell = new_grid->InsertNextCell(type_cell, N_pts, pts);
    copyCellData(grid, id_cell, new_grid, id_new_cell);
  };
  makeCopy(new_grid,grid);
};
