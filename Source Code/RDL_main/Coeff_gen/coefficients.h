#ifndef COEFFICIENTS_H
#define COEFFICIENTS_H

const int m_lines = 8;                 // Number of rows
const int m_col = 2;                   // Number of columns

float strain_matrix[m_lines][m_col] = {
  {1352.93917770982, 549.0},
  {5090.553856608902, 555.0},
  {6789.568467550119, 549.0},
  {0.0, 0.0},
  {0.0, 0.0},
  {0.0, 0.0},
  {0.0, 0.0},
  {0.0, 0.0},
};

#endif // COEFFICIENTS_H