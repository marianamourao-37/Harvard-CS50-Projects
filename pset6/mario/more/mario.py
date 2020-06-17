from cs50 import get_int

while True:
    height = get_int("Enter the height of the half pyramid, between 1 and 8: ")

    if height <= 8 and height > 0:
        break

for n in range(height):  # loops over each row on the half pyramid
    # prints the ith row of the first pyramid:
    print(" " * (height - (n + 1)), end="")
    print("#" * (n + 1), end="")

    print("  ", end="")  # prints the spaces between the two pyramids
    print("#" * (n + 1))  # prints the ith row of the second pyramid

