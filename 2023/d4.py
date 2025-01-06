import re
file_name = 'inputs/d4.txt'

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

if __name__ == "__main__":

    lines = read_file_lines(file_name)
    y_coor = 0
    total = 0
    copies = []
    founds = []
    while y_coor < 218:
        copies.append(1)
        y_coor += 1
    y_coor = 0
    for line in lines:
        numb_list = re.split(r":",line)
        numbers_str = re.split(r"\|", numb_list[1])
        winning_numbers = re.split(r"\s",numbers_str[0])
        played_numbers = numbers_str[1] + ' '
        found = 0
        for num in winning_numbers:
            if num:
                patern = r"\s{1}" + num + r"\s{1}"
                match = re.search(patern, played_numbers)
                if match:
                    found += 1
        founds.append(found)
    copy_index = 0
    for cp in copies:
        if founds[copy_index] > 0:
            x = 0
            while x < founds[copy_index]:
                index = copy_index+1+x
                copies[index] += copies[copy_index]
                x += 1
                if x==217: break
        copy_index += 1
    for cp in copies:
        total += cp
    print(total)