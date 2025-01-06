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

def find_coordinates() -> set:
    """
    Yıldızların kooordinatlarını bulur.
    """
    coordinates = {}
    lines = read_file_lines(file_name)
    y_coor = 1
    for line in lines:
        x_coor = 0
        x_set = []
        for letter in line:
            x_coor += 1
            if letter == "*":
                x_set.append(x_coor)
        coordinates.update({y_coor : x_set})
        y_coor += 1
    return coordinates

coord = find_coordinates()

def find_the_star(y:int, start:int, end:int) -> str:
    if start > 1: start -= 1
    if end < 140: end += 1
    for border in coord[y]:
        if border >= start and border <= end:
            return f"{y}.{border}"
    return ""

def check_eligibility(y:int,x1:int,x2:int) -> str:
    sl = su = sd = ""
    sl = find_the_star(y, x1, x2)
    if y > 1:
        su = find_the_star((y-1), x1, x2)
    if y < 140:
        sd  = find_the_star((y+1), x1, x2)
    return f"{sl}{su}{sd}"

if __name__ == "__main__":
    star_container = {}
    for ey in coord:
        if coord[ey]:
            for bord in coord[ey]:
                star_container[f"{ey}.{bord}"] = []
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
                    ck = check_eligibility(y_coor,star_p,140)
                    if ck != "":
                        #print(f"{ck}->{part_no}")
                        star_container[ck].append(part_no)
                        part_no = ''
            elif part_no != '':
                end_p = x_coor-1
                ck = check_eligibility(y_coor,star_p,end_p)
                if ck != "":
                    #print(f"{ck}->{part_no}")
                    star_container[ck].append(part_no)
                part_no = ''
                star_p = end_p = 0
        y_coor += 1
    for star in star_container:
        if len(star_container[star])>1:
            pow = int(star_container[star][0])*int(star_container[star][1])
            total += pow
            
    print(f"{star_container[star]} = {total}")