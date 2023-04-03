#include <iostream>
#include <sqlite3.h>
#include <cstdlib>

// C++ Leveling System
class Level {
  sqlite3* db;
  char* error_message = nullptr;

  // Level Constructor (Fixed Argument)
  Level(string file) {
    
    // Open the database
    int rc = sqlite3_open("database.db", &db);
    if (rc != SQLITE_OK) {
      std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
      sqlite3_close(db);
    }

    // Prepare the SQL statement
    const char* sql = "SELECT * FROM my_table"; 
      //^^^^^ Table Name Needs to Be Changed Iteratively at the moment, change later (feat)
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
      std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << std::endl;
      sqlite3_close(db);
    }

    // Variables
    string courseID = "", courseName = "", preReqOne = "", preReqTwo = "", preReqThree = "";
    int credits;
    bool passedPreReq[3] = {}
 

    // Database must follow specific format
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      // Grab all the items of first row
      courseID = sqlite_column_int(stmt, 0);
      courseName = sqlite_column_int(stmt, 1);
      preReqOne = sqlite_column_int(stmt, 2);
      preReqTwo = sqlite_column_int(stmt, 3);
      preReqThree = sqlite_column_int(stmt, 4);
      credits = sqlite_column_int(stmt, 5);

      
          // const char * string = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0))

      
    
        // Use the python code to generate a json file with information
        system("python coursecreator.py");
  }

  
}
