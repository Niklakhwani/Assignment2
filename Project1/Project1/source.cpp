// Assignment #2 - Debugging vs. Release Coding Practice
// Reads student data from a text file, stores it in a vector, and prints it
// depending on compiler directives (_DEBUG, PRE_RELEASE).

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Holds one student's information.
struct STUDENT_DATA
{
    std::string firstName;
    std::string lastName;
#ifdef PRE_RELEASE
    std::string email;      // Only exists in pre-release builds
#endif
};

// Removes leading/trailing whitespace from a string.
static std::string Trim(const std::string& str)
{
    const char* whitespace = " \t\r\n";
    size_t start = str.find_first_not_of(whitespace);
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(whitespace);
    return str.substr(start, end - start + 1);
}

int main()
{
    // Report which flavour of the source is running.
#ifdef PRE_RELEASE
    std::cout << "Running PRE-RELEASE source code\n";
    const char* fileName = "StudentData_Emails.txt";
#else
    std::cout << "Running STANDARD source code\n";
    const char* fileName = "StudentData.txt";
#endif

    std::vector<STUDENT_DATA> students;
    std::ifstream inFile(fileName);

    if (!inFile.is_open())
    {
        std::cerr << "Could not open " << fileName << "\n";
        return 1;
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        if (line.empty()) continue;

        std::stringstream ss(line);
        STUDENT_DATA s;

        // Each line is "Last, First" (or "Last, First,email" in pre-release).
        std::getline(ss, s.lastName, ',');
        std::getline(ss, s.firstName, ',');
        s.lastName = Trim(s.lastName);
        s.firstName = Trim(s.firstName);
#ifdef PRE_RELEASE
        std::getline(ss, s.email, ',');
        s.email = Trim(s.email);
#endif
        students.push_back(s);
    }
    inFile.close();

    // Debug-only: print every student that was loaded.
#ifdef _DEBUG
    for (const STUDENT_DATA& s : students)
    {
        std::cout << s.firstName << " " << s.lastName;
#ifdef PRE_RELEASE
        std::cout << " <" << s.email << ">";
#endif
        std::cout << "\n";
    }
#endif

    return 0;
}
