# import libraries:
from sys import argv, exit
import cs50

# check incorrect usage
if len(argv) != 2:
    print("Usage: python roster.py house_name")
    exit(1)

# name of the desired house to be search in the database
house_name = argv[1]

# opens database for interative manipulation within python
db = cs50.SQL("sqlite:///students.db")

# performs a query
list_dict_students = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", house_name)

# for every dictionary on a list
for dict_student in list_dict_students:
    if dict_student["middle"] != None:  # student doesn't have a middle name registered on the database
        print(dict_student["first"] + " " + dict_student["middle"] + " " +
              dict_student["last"] + ", born " + str(dict_student["birth"]))
    else:
        print(dict_student["first"] + " " + dict_student["last"] + ", born " + str(dict_student["birth"]))