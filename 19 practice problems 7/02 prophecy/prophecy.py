import csv
from cs50 import SQL


def create_house(house, head, houses):
    count = 0
    for h in houses:
        if h["house"] == house:
            count += 1
    if count == 0:
        houses.append({"house": house, "head": head})


def create_student(name, students):
    students.append({"student_name": name})


def create_relationship(name, house, relationships):
    relationships.append({"student_name": name, "house": house})


db = SQL("sqlite:///roster.db")


students = []
houses = []
relationships = []


with open("students.csv", "r") as f:
    reader = csv.DictReader(f)
    for row in reader:
        create_house(row["house"], row["head"], houses)
        create_student(row["student_name"], students)
        create_relationship(row["student_name"], row["house"], relationships)

for s in students:
    db.execute("INSERT INTO student (student_name) VALUES (?)", s["student_name"])

for h in houses:
    db.execute("INSERT INTO house (house, head) VALUES (?,?)", h["house"], h["head"])

for r in relationships:
    db.execute("INSERT INTO relationship (student_name, house) VALUES (?,?)", r["student_name"], r["house"])
