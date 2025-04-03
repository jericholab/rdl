import pandas as pd

# Input and output file names (adjust these if needed)
excel_file = 'coefficients_source.xlsx'
header_file = 'coefficients.h'

# Read the matrix from the Excel file.
# The matrix of interest is in the range C7:D14.
# - usecols="C:D" selects columns C and D.
# - skiprows=6 skips the first 6 rows so that row 7 becomes the first row of data.
# - nrows=8 reads 8 rows (rows 7 to 14).
# - header=None ensures that no row is treated as column headers.
df = pd.read_excel(excel_file, usecols="C:D", skiprows=6, nrows=8, header=None)

# Determine the dimensions of the matrix
m_lines = df.shape[0]  # number of rows
m_col = df.shape[1]    # number of columns

# Prepare the lines for the header file
lines = []
lines.append("#ifndef COEFFICIENTS_H")
lines.append("#define COEFFICIENTS_H")
lines.append("")
lines.append(f"const int m_lines = {m_lines};                 // Number of rows")
lines.append(f"const int m_col = {m_col};                   // Number of columns")
lines.append("")
lines.append("float strain_matrix[m_lines][m_col] = {")    

# Iterate over each row of the DataFrame and create a corresponding row in the header file.
for index, row in df.iterrows():
    # Convert each element to string.
    # You can format numbers as needed. Here, we simply use the default string representation.
    row_values = ", ".join(str(x) for x in row)
    lines.append(f"  {{{row_values}}},")

lines.append("};")
lines.append("")
lines.append("#endif // COEFFICIENTS_H")

# Write the header file with the constructed lines
with open(header_file, "w") as f:
    f.write("\n".join(lines))

print(f"Header file '{header_file}' generated successfully.")
