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
}

  std::string class_name;
    std::cout << "Enter class name: ";
    std::getline(std::cin, class_name);

    // Retrieve the class ID from the database
    std::string class_id_sql = "SELECT id FROM courses WHERE name = '" + class_name + "';";
    int class_id;
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, class_id_sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        class_id = sqlite3_column_int(stmt, 0);
    } else {
        std::cerr << "Error retrieving class ID from database" << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_finalize(stmt);

    // Retrieve prerequisite names from the database
    std::vector<std::string> prereq_names;
    std::string prereq_sql = "SELECT courses.name FROM prerequisites INNER JOIN courses ON prerequisites.prereq_id = courses.id WHERE prerequisites.course_id = " + std::to_string(class_id) + ";";
    rc = sqlite3_exec(db, "SELECT * from CSDP_Curriculum;", callback, &prereq_names, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Error retrieving prerequisite names from database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    // Output the prerequisite names
    std::cout << "Prerequisites for " << class_name << ":" << std::endl;
    if (prereq_names.empty()) {
        std::cout << "None" << std::endl;
    } else {
        for (const auto& prereq_name : prereq_names) {
            std::cout << "- " << prereq_name << std::endl;
        }
    }

    sqlite3_close(db);
    return 0;
}



 