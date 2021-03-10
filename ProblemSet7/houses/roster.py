import cs50
import sys

#correct command line arguments
if len(sys.argv) != 2:
    print("error USAGE: python roster.py [HOUSE NAME]")
    exit(1)

#USE SQL QUERIES IN PYTHON

#open database
db = cs50.SQL("sqlite:///students.db")

#query
rows = db.execute ("SELECT * FROM students WHERE house = ? ORDER BY last, first", sys.argv[1])

#printing the output
for row in rows:
    if row['middle'] != None:
        print(row ['first'] + ' ' + row ['middle'] + ' ' + row ['last'] + ', born ' + str(row['birth']))
    else:
        print(row ['first'] + ' ' + row ['last'] + ', born ' + str(row['birth']))