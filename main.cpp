#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Subject {
public:
    std::string name;
    int marks;
};

class Student {
public:
    std::string name;
    std::vector<Subject> subjects;
    int schoolRank;  

    int calculateTotalMarks() const {
        int totalMarks = 0;
        for (const auto& subject : subjects) {
            totalMarks += subject.marks;
        }
        return totalMarks;
    }
};

class Class {
public:
    std::vector<Student> students;

    void calculateRanks() {
      
        std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.calculateTotalMarks() > b.calculateTotalMarks();
        });


        for (size_t i = 0; i < students.size(); ++i) {
            students[i].schoolRank = i + 1;
        }
    }
};

class Stream {
public:
    std::string name;
    std::vector<Class> classes;
};

int main() {

    Stream bioStream;
    bioStream.name = "Bioscience";

    for (int i = 0; i < 3; ++i) {
        Class bioClass;
        for (int j = 0; j < 40; ++j) {
            Student student;
            std::cout << "Enter Bio student name for Class " << i + 1 << ", Student " << j + 1 << ": ";
            std::cin >> student.name;

            for (const std::string& subject : {"Biology", "Physics", "Chemistry"}) {
                Subject sub;
                sub.name = subject;
                std::cout << "Enter marks for " << subject << ": ";
                std::cin >> sub.marks;
                student.subjects.push_back(sub);
            }

            bioClass.students.push_back(student);
        }
        bioStream.classes.push_back(bioClass);
    }


    Stream mathStream;
    mathStream.name = "Math";

    for (int i = 0; i < 5; ++i) {
        Class mathClass;
        for (int j = 0; j < 40; ++j) {
            Student student;
            std::cout << "Enter Math student name for Class " << i + 1 << ", Student " << j + 1 << ": ";
            std::cin >> student.name;

            for (const std::string& subject : {"Combined Maths", "Physics", "Chemistry"}) {
                Subject sub;
                sub.name = subject;
                std::cout << "Enter marks for " << subject << ": ";
                std::cin >> sub.marks;
                student.subjects.push_back(sub);
            }

            mathClass.students.push_back(student);
        }
        mathStream.classes.push_back(mathClass);
    }


    for (auto& bioClass : bioStream.classes) {
        bioClass.calculateRanks();
    }

    for (auto& mathClass : mathStream.classes) {
        mathClass.calculateRanks();
    }


    std::ofstream outputFile("rank_results.txt");
    if (outputFile.is_open()) {
        for (const auto& bioClass : bioStream.classes) {
            for (const auto& student : bioClass.students) {
                std::cout << "Bio Class " << &bioClass - &bioStream.classes[0] + 1 << " - "
                          << "Student: " << student.name << ", Total Marks: " << student.calculateTotalMarks()
                          << ", School Rank: " << student.schoolRank << std::endl;

                outputFile << "Bio Class " << &bioClass - &bioStream.classes[0] + 1 << " - "
                           << "Student: " << student.name << ", Total Marks: " << student.calculateTotalMarks()
                           << ", School Rank: " << student.schoolRank << std::endl;
            }
        }

        for (const auto& mathClass : mathStream.classes) {
            for (const auto& student : mathClass.students) {
                std::cout << "Math Class " << &mathClass - &mathStream.classes[0] + 1 << " - "
                          << "Student: " << student.name << ", Total Marks: " << student.calculateTotalMarks()
                          << ", School Rank: " << student.schoolRank << std::endl;

                outputFile << "Math Class " << &mathClass - &mathStream.classes[0] + 1 << " - "
                           << "Student: " << student.name << ", Total Marks: " << student.calculateTotalMarks()
                           << ", School Rank: " << student.schoolRank << std::endl;
            }
        }

        outputFile.close();
    } else {
        std::cerr << "Unable to open output file." << std::endl;
    }

    return 0;
}