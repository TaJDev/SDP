std::string course_name;
    std::cout << "Enter a course name: ";
    std::getline(std::cin, course_name);

    // Retrieve the course ID from the database
    std::string course_id_sql = "SELECT id FROM courses WHERE name = '" + course_name + "';";
    int course_id;
    rc = sqlite3_exec(db, course_id_sql.c_str(), [](void* data, int argc, char** argv, char** azColName) -> int {
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
    rc = sqlite3_exec(db, prereq_sql.c_str(), callback, &prereq_names, NULL);

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

    // Check if the student has passed the course
    std::string pass_sql = "SELECT COUNT(*) FROM grades WHERE course_id = " + std::to_string(course_id) + " AND grade >= 60;";
    int pass_count;
    rc = sqlite3_exec(db, pass_sql.c_str(), [](void* data, int argc, char** argv, char** azCol
