import os

def check_word_in_file(file_path, word):
    word = word.lower()  # Make the word lowercase for case-insensitive comparison
    if os.path.isfile(file_path):
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read().lower()  # Read the file and convert the content to lowercase
            if word in content:
                return True
            else:
                return False
    else:
        return None  # File not found

# Path to the twi.c file (Master location)
twi_c_file_path1 = "/home/pi/.local/share/arduino-1.8.19/hardware/arduino/avr/libraries/Wire/src/utility/twi.c"
# Word to search for
word_to_search = "jericho"

# Check if the word exists in the file
word_found = check_word_in_file(twi_c_file_path1, word_to_search)

if word_found is None:
    print("<twi.c> file not found.")
elif word_found:
    print("A Jericho version of twi.c was found in the Master location")
else:
    print("A non-Jericho version of twi.c was found in the Master location.")



# Path to the twi.c file (Master location)
twi_c_file_path2 = "/tmp/arduino_build_5381/libraries/Wire/"
# Word to search for
word_to_search = "jericho"

# Check if the word exists in the file
word_found = check_word_in_file(twi_c_file_path2, word_to_search)

if word_found is None:
    print("<twi.c> file not found in tmp location.")
elif word_found:
    print("A Jericho version of twi.c was found in the tmp location")
else:
    print("A non-Jericho version of twi.c was found in the tmp location.")