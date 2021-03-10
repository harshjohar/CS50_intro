import csv
import sys
import cs50

#correct command line arguments
if len(sys.argv) != 2:
    print("error USAGE: python import.py [NAME OF CSV].csv")
    exit(1)

#use python as a script(to change one data type to other){here csv to db}

#open database
db = cs50.SQL("sqlite:///students.db")

#open csv file
with open(sys.argv[1]) as csvfile:
    #open dictreader
    csvreader = csv.DictReader(csvfile)

    for row in csvreader:
        #split function is used to list the elments in a list... the objects which are separated by spaces
        name = row["name"].split()
        if len(name) == 3:
            first = name[0]
            middle = name[1]
            last = name[2]
        else:
            first = name[0]
            middle = None
            last = name[1]

        house = row["house"]
        birth = row["birth"]

        #insert into database
        db.execute ("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, house, birth)