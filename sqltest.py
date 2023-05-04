import sqlite3

# connect to the database
conn = sqlite3.connect('SDP.db')

# create a cursor object
cur = conn.cursor()

# To display all the table names
cur.execute("SELECT name from sqlite_schema WHERE type='table';")
table_names = cur.fetchall()

for i in table_names:
    print(i[0])

# Grab all passed courses then assign levels to those that havent been taken/passed.
courseList = []

cur.execute("SELECT CourseID from gened;")
gened = cur.fetchall()
gened = [i[0] for i in gened] # Reformatting for grabbing


cur.execute("SELECT CourseID from CSDP_Curriculum;")
csdp = cur.fetchall()

cur.execute("Select CC.CourseID from CSDP_Curriculum as CC;")
allcourses = cur.fetchall()
cur.execute("Select GE.CourseID from gened as GE;")
allcourses += cur.fetchall()
for a in allcourses:
    print(a)

cur.execute("SELECT CourseID from testcase where Grade = 'A' OR Grade = 'B' OR Grade = 'C' OR Grade = 'P';")
passedCourses = cur.fetchall()
for b in passedCourses:
    print(b)
 ## Issue: Grab all testing requirements and add them to this list as passed courses



# Setting up dictionaries for each course in CSDP Curriculum
cur.execute("SELECT * from CSDP_Curriculum;")
course = cur.fetchall()
print(course)

# Recursive Leveling System

def Level(C, tracker):
    print(tracker)
    print(C)

    for i in range(2,4):
        print("Working with prerequisite " + str(i))
        if(tuple((C[i],)) in passedCourses):
            print("Course Passed-")
        else:
            print("\t\tFound Prerequisite: " + C[i])
            # SELECT * FROM table1 INNER JOIN table2 ON table1.primary_key = table2.primary_key WHERE table1.primary_key = 'specific_value';
            cur.execute("SELECT * from CSDP_Curriculum WHERE CourseID= ?", (C[i],))
            prereq = cur.fetchall()
            cur.execute("Select * from gened where CourseID= ?", (C[i],))
            prereq += cur.fetchall()

            tracker += 1

            if(prereq):
                print("\t\tSending to next level")
                Level(prereq[0], tracker)
            else:
                print("\t\tDONE with " + C[i])
                print("Tracker: " + str(tracker))
                break
    return tracker


for e in course:
    dictionary = {}
    prereqs = [e[2], e[3], e[4]]
    if (tuple((e[0],)) in passedCourses): # If we already passed the courses, make its level 0
        dictionary = {
            "course":e[0],
            "credits":e[5],
            "level":0,
            "prerequisite(s)":prereqs,
            "taken_passed": True,
            "major_req":True, # Will need a getMajorRequirementStatus()
            "minor_req":False, # Will need a getMinorRequirementStatus()
            "GenEd_req":False # Will need a getGenEdRequirementStatus()
            }
    else:
        dictionary = {
            "course":e[0],
            "credits":e[5],
            "level":Level(e, 0), #If the course is not passed already -> Figure out level,
            "prerequisite(s)":prereqs,
            "taken_passed": False,
            "major_req":True, # Will need a getMajorRequirementStatus()
            "minor_req":False, # Will need a getMinorRequirementStatus()
            "GenEd_req":False # Will need a getGenEdRequirementStatus()
            }

    courseList.append(dictionary)





# Setting up dictionaries for each course in General Education Curriculum
cur.execute("SELECT * from gened;")
course = cur.fetchall()

for j in course:
    prereqs = [j[2], j[3], j[4]]
    if tuple((j[0],)) in passedCourses:
        dictionary = {
            "course":j[0],
            "credits":j[5],
            "level":0,
            "prerequisite(s)":prereqs,
            "taken_passed": True,
            "major_req":False, # Will need a getMajorRequirementStatus()
            "minor_req":False, # Will need a getMinorRequirementStatus()
            "GenEd_req":True # Will need a getGenEdRequirementStatus()
            }
    else:
        dictionary = {
            "course":j[0],
            "credits":j[5],
            "level":Level(j, 0),
            "prerequisite(s)":prereqs,
            "taken_passed": False,
            "major_req":False, # Will need a getMajorRequirementStatus()
            "minor_req":False, # Will need a getMinorRequirementStatus()
            "GenEd_req":True # Will need a getGenEdRequirementStatus()
            }

        # Get a Level for Courses that havent been passed

    courseList.append(dictionary)

for i in courseList:
    print(i)



# close the database connection
conn.close()
