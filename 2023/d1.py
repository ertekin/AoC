import re
def read_file_lines(file_name):
    try:
        # Open the file in read mode
        with open(file_name, 'r') as file:
            # Read all lines into a list
            lines = file.readlines()
            # Remove trailing newline characters from each line
            lines = [line.strip() for line in lines]
        return lines
    except FileNotFoundError:
        print(f"Error: The file '{file_name}' was not found.")
        return []
    except Exception as e:
        print(f"An unexpected error occurred: {e}")
        return []

snumbers = ("one", "two", "three", "four", "five", "six", "seven", "eight", "nine")
anumbers = ("o1e", "t2o", "t3ree", "f4ur", "f5ve", "s6x", "s7ven", "e8ght", "n9ne")
# Example usage
if __name__ == "__main__":
    file_name = 'inputs/d1_1.txt'
    lines = read_file_lines(file_name)
    st = 0
    for line in lines:
        # convert string numbers into integer
        aa = 0
        for findText in snumbers:
            line = re.sub(findText, anumbers[aa], line)
            aa+=1
        fi = li = 0
        for l in line:
            if l.isdigit():
                li = int(l)
                if fi == 0: fi = li
        st += (fi*10 + li)
        print(f"{fi}-{li} : {line}")
    print(f"Total: {st}")
