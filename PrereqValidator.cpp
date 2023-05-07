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

    if (rc) {
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }

    const char* sql = "SELECT c1.name, c2.name FROM courses c1, courses c2, prerequisites p WHERE c1.id = p.prereq_id AND c2.id = p.course_id;";

    rc = sqlite3_exec(db, sql, callback, 0, NULL);

    if (rc != SQLITE_OK) {
        std::cout << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    } else {
        std::cout << "Operation done successfully" << std::endl;
    }

    sqlite3_close(db);

    return 0;
}
