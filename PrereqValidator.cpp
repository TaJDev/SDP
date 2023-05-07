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

    return 0;
}
