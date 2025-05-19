import os

def find_txt_files_recursively(root_dir):
    txt_files = []
    for dirpath, _, filenames in os.walk(root_dir):
        for file in filenames:
            if file.endswith('.txt'):
                full_path = os.path.join(dirpath, file)
                txt_files.append(full_path)
    return sorted(txt_files)  # Sorts alphabetically, good if filenames contain datetime

def merge_txt_files(txt_files, output_file):
    with open(output_file, 'w') as outfile:
        for file_path in txt_files:
            with open(file_path, 'r') as infile:
                outfile.write(infile.read())
                outfile.write("\n")

def clean_txt_file(input_file, output_file):
    with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
        for line in infile:
            cleaned_line = line.strip()
            if cleaned_line and '*' in cleaned_line and 'date' not in cleaned_line.lower():
                outfile.write(line)

if __name__ == "__main__":
    script_directory = os.path.dirname(os.path.realpath(__file__))
    
    # Step 1: Find and sort all .txt files recursively
    txt_files = find_txt_files_recursively(script_directory)
    
    # Step 2: Merge into a single file
    merged_file = os.path.join(script_directory, 'merged_output.txt')
    merge_txt_files(txt_files, merged_file)
    print(f"Merged {len(txt_files)} .txt files into {merged_file}")
    
    # Step 3: Clean the merged file
    cleaned_file = os.path.join(script_directory, 'cleaned_output.txt')
    clean_txt_file(merged_file, cleaned_file)
    print(f"Cleaned data saved to {cleaned_file}")
