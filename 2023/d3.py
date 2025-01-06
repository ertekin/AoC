import re
file_name = 'inputs/d3.txt'

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

def find_symbols() -> str:
    symbols = ""
    lines = read_file_lines(file_name)
    for line in lines:
        line = re.sub("[.\\d]", "", line)
        for letter in line:
            match = re.search(f"[{letter}]", symbols)
            if not match:
                symbols = symbols + letter
    return symbols


def find_coordinates() -> set:
    coordinates = {}
    lines = read_file_lines(file_name)
    y_coor = 1
    for line in lines:
        x_coor = 1
        x_set = []
        for letter in line:
            if letter == ".":
                x_coor += 1
                continue
            if not letter.isdigit():
                x_set.append(x_coor)
            x_coor += 1
        coordinates.update({y_coor : x_set})
        y_coor += 1
    return coordinates

coord = find_coordinates()

def is_in_the_box(y:int, start:int, end:int) -> bool:
    if start > 1: start -= 1
    if end < 140: end += 1
    for border in coord[y]:
        if border >= start and border <= end:
            return True
    return False

def check_eligibility(y:int,x1:int,x2:int) -> bool:
    if is_in_the_box(y, x1, x2):
        return True
    if y > 1 and is_in_the_box((y-1), x1, x2):
        return True
    if y < 140 and is_in_the_box((y+1), x1, x2):
        return True

if __name__ == "__main__":
    coor = find_coordinates()
    lines = read_file_lines(file_name)
    y_coor = 1
    total = 0
    for line in lines:
        x_coor = 0
        part_no = ''
        star_p = 0
        end_p = 0
        for letter in line:
            x_coor += 1
            if letter.isdigit():
                if part_no == '':
                    part_no = str(letter)
                    star_p = x_coor
                else:
                    part_no = str(part_no) + str(letter)
                if x_coor == 140:
                    if check_eligibility(y_coor,star_p,140):
                        print(f"{y_coor}-{star_p}-{140}-->{part_no}")
                        total += int(part_no)
                        part_no = ''
            elif part_no != '':
                end_p = x_coor-1
                if check_eligibility(y_coor,star_p,end_p):
                    print(f"{y_coor}-{star_p}-{end_p}-->{part_no}")
                    total += int(part_no)
                part_no = ''
                star_p = end_p = 0
        y_coor += 1
    print(total)