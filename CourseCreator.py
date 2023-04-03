import json

class CourseCreator:

    def __init__(self, courseList = [], courses= [None, None, None]):
        self.courseList = courseList
        self.courses = courses

    # No Arg Constructor
    def CourseCreator(self):
        dictionary = {
            "course":"template_course_name",
            "credits":0,
            "prerequisite(s)":courses,
            "taken_passed":False,
            "major_req":True,
            "minor_req":False,
            "GenEd_req":False
        }

        self.courseList.append(dictionary)

    # Generating specific courses:
    def CourseCreator(self, course, credits, prerequisite0 = None, prerequisite1 = None, prerequisite2 = None):

        # Making the dictionary for the course
        dictionary = {
            "course":course,
            "credits":credits,
            "prerequisite(s)":[prerequisite0, prerequisite1, prerequisite2],
            "taken_passed": False,
            "major_req":True, # Will need a getMajorRequirementStatus()
            "minor_req":False, # Will need a getMinorRequirementStatus()
            "GenEd_req":False # Will need a getGenEdRequirementStatus()
        }

        self.courseList.append(dictionary)

    # Serialize and Write to the json file
    def makejson(self):

        json_name ="courses.json"
        json_object = json.dumps(self.courseList, indent=4)

        # Write to
        with open(json_name, "w") as outfile:
            outfile.write(json_object)
