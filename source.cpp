// Assignment #2 - Initial version: read student names into a vector.

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
    std::vector<STUDENT_DATA> students;
    std::ifstream inFile("StudentData.txt");

    if (!inFile.is_open())
    {
        std::cerr << "Could not open StudentData.txt\n";
        return 1;
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        if (line.empty()) continue;

        std::stringstream ss(line);
        STUDENT_DATA s;

        // Each line is "Last, First".
        std::getline(ss, s.lastName, ',');
        std::getline(ss, s.firstName, ',');
        s.lastName = Trim(s.lastName);
        s.firstName = Trim(s.firstName);
        students.push_back(s);
    }
    inFile.close();

    // Debug-only: print every student that was loaded.
#ifdef _DEBUG
    for (const STUDENT_DATA& s : students)
    {
        std::cout << s.firstName << " " << s.lastName << "\n";
    }
#endif

    return 0;
}
