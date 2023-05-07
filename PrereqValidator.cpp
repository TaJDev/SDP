#include <iostream>
#include <sqlite3.h>


int main() {
    sqlite3* db;
    int rc = sqlite3_open("SDP.db", &db);

    const char* sql = "SELECT c1.name, c2.name FROM courses c1, courses c2, prerequisites p WHERE c1.id = p.prereq_id AND c2.id = p.course_id;";

    rc = sqlite3_exec(db, sql, 0, 0, NULL);

    sqlite3_close(db);

    return 0;
}
