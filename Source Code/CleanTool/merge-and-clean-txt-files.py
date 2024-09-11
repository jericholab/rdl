import os

def merge_txt_files(output_file):
    # Get the current directory where the script is running
    script_directory = os.path.dirname(os.path.realpath(__file__))
    
    # Create or overwrite the output file in the same directory
    with open(output_file, 'w') as outfile:
        # Iterate over all files in the script directory
        for filename in os.listdir(script_directory):
            # Check if the file is a .txt file
            if filename.endswith('.txt'):
                file_path = os.path.join(script_directory, filename)
                with open(file_path, 'r') as infile:
                    # Write the content of the current .txt file into the output file
                    outfile.write(infile.read())
                    # Add a newline character after each file's content to separate them
                    outfile.write("\n")

# Specify the name of the output file
output_file = 'merged_output.txt'  # The output file will be created in the script's directory

# Call the function to merge the files
merge_txt_files(output_file)

print(f"All .txt files in the script's directory have been merged into {output_file}")


def clean_txt_file(input_file, output_file):
    # Open the input file for reading
    with open(input_file, 'r') as infile:
        # Open the output file for writing the cleaned content
        with open(output_file, 'w') as outfile:
            # Iterate through each line in the input file
            for line in infile:
                # Strip the line of leading/trailing spaces (including newlines)
                cleaned_line = line.strip()
                # Check if the line is not empty, contains '*', and doesn't contain the word 'date'
                if cleaned_line and 'date' not in cleaned_line.lower() and '*' in cleaned_line:
                    # Write the cleaned line to the output file
                    outfile.write(line)

# Specify the input and output file names
input_file = 'merged_output.txt'  # Replace with your input file path
output_file = 'cleaned_output.txt'  # The output file will have cleaned content

# Call the function to clean the file
clean_txt_file(input_file, output_file)

print(f"The file {input_file} has been cleaned and saved as {output_file}")