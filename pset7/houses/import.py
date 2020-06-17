# import libraries:
import csv
import cs50
from sys import argv, exit

# check incorrect usage
if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit(1)

# opens database for interative manipulation within python
db = cs50.SQL("sqlite:///students.db")

# csv file name
name_csv = argv[1]

# opens for reading the csv file
with open(name_csv) as csv_file:
    csv_reader = csv.DictReader(csv_file) # creates DictReader

    # iterates over the csv file converted to a dictionary (DictReader)
    for student in csv_reader:
        stu_house = student["house"]
        stu_birth = student["birth"]
        st_index = student["name"].find(" ")  # finds the index of the " " character within the student's name

        if student["name"].count(" ") == 1:  # if the student's name only has 2 separated names (first and last)
            st_name = student["name"][:st_index]  # first name
            mid_name = None  # doesn't have a middle name
            lst_name = student["name"][st_index + 1:]  # last name

        else:  # if the student's name has 3 separated names (first, middle, last)
            nd_index = student["name"].find(" ", st_index + 1)  # index of the second " " character within the name

            st_name = student["name"][:st_index]  # first name
            mid_name = student["name"][st_index + 1:nd_index]  # middle name
            lst_name = student["name"][nd_index + 1:]  # last name

        # Inserts into the student's table on the database their full name, house and birth
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", st_name, mid_name, lst_name, stu_house,
                   stu_birth)
