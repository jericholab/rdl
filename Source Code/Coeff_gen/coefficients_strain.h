#ifndef COEFFICIENTS_H
#define COEFFICIENTS_H

const int m_lines = 8;                 // Number of rows
const int m_col = 2;                   // Number of columns

float strain_matrix[m_lines][m_col] = {
  {4147.05, 23713.0},
  {4111.59, -171611.0},
  {0.0, 0.0},
  {0.0, 0.0},
  {0.0, 0.0},
  {0.0, 0.0},
  {0.0, 0.0},
  {0.0, 0.0},
};

#endif // COEFFICIENTS_H