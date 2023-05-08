
#include <iostream>
#include <sqlite3.h>

int callback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    return 0;
}

int main() {
    sqlite3* db;
    int rc = sqlite3_open("SDP.db", &db);


    rc = sqlite3_exec(db, "SELECT * from CSDP_Curriculum;", callback, 0, NULL);

    std::cout << rc << std::endl;

    sqlite3_close(db);


  std::string course_name;
    std::cout << "Enter a course name: ";
    std::getline(std::cin, course_name);

    std::string course_id_sql = "SELECT id FROM courses WHERE name = '" + course_name + "';";
int course_id;
rc = sqlite3_exec(db, "SELECT * from CSDP_Curriculum;", [](void* data, int argc, char** argv, char** azColName) -> int {
    if (argc > 0 && argv[0]) {
        *reinterpret_cast<int*>(data) = std::stoi(argv[0]);
    }
    return 0;
}, &course_id, NULL);

    if (rc != SQLITE_OK) {
        std::cout << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    if (course_id == 0) {
        std::cout << "Invalid course name" << std::endl;
        sqlite3_close(db);
        return 1;
    }

    // Retrieve the prerequisites for the course
    std::vector<std::string> prereq_names;
    std::string prereq_sql = "SELECT c2.name FROM courses c1, courses c2, prerequisites p WHERE c1.id = " + std::to_string(course_id) + " AND c1.id = p.course_id AND c2.id = p.prereq_id;";
    rc = sqlite3_exec(db, "SELECT * from CSDP_Curriculum;", callback, &prereq_names, NULL);

    if (rc != SQLITE_OK) {
        std::cout << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    if (prereq_names.empty()) {
        std::cout << "No prerequisites found for " << course_name << std::endl;
    } else {
        std::cout << "Prerequisites for " << course_name << ":" << std::endl;
        for (const auto& prereq_name : prereq_names) {
            std::cout << "- " << prereq_name << std::endl;
        }
    }

    sqlite3_close(db);
    return 0;
}