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

max_numbers = {
    "red" : 12,
    "green" : 13,
    "blue" : 14
}

def check_color_number(set: str) -> bool:
    """
    Her sette çekilen küp sayısı örnek olarak şöyle
        12 blue, 15 red, 2 green
    """
    for color in max_numbers:
        pattern = f"(\\d+) {color}"
        match = re.search(pattern, set)
        color_no = 0
        if match:
            color_no = int(match.group(1))
        if color_no > 0 and color_no > max_numbers[color]:
            max_numbers[color] = color_no
    return True

if __name__ == "__main__":
    file_name = 'inputs/d2.txt'
    lines = read_file_lines(file_name)
    game = 1
    total = 0
    for line in lines:
        max_numbers = {
        "red" : 0,
        "green" : 0,
        "blue" : 0
        }
        x = re.split(r":", line)
        sets = re.split(r";",x[1])
        set_no = 1
        for set in sets:
            check_color_number(set)
        power = max_numbers["red"]*max_numbers["green"]*max_numbers["blue"]
        print(f"Game {game}: {power} {max_numbers}")
        total += power
        game += 1
    print(f"Power total: {total}")
