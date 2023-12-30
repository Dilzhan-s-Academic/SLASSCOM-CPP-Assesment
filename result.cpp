#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Student {
    std::string name;
    int rollNumber;
    int marksBiology;
    int marksPhysics;
    int marksChemistry;
    int totalMarks;
    int stream; // 0 for Bio, 1 for Math
    int classNumber;

    bool operator<(const Student& other) const {
        return totalMarks > other.totalMarks; // Sort in descending order of total marks
    }
};

class School {
private:
    std::vector<Student> students;

public:
    void addStudent(const Student& student) {
        students.push_back(student);
    }

    void calculateRanks() {
        // Calculate total marks and sort students
        for (auto& student : students) {
            student.totalMarks = student.marksBiology + student.marksPhysics + student.marksChemistry;
        }
        std::sort(students.begin(), students.end());

        // Assign school rank
        for (size_t i = 0; i < students.size(); ++i) {
            students[i].rollNumber = i + 1;
        }

        // Assign class rank
        for (int stream = 0; stream <= 1; ++stream) {
            for (int classNumber = 1; classNumber <= (stream == 0 ? 3 : 5); ++classNumber) {
                std::vector<Student> classStudents;
                for (const auto& student : students) {
                    if (student.stream == stream && student.classNumber == classNumber) {
                        classStudents.push_back(student);
                    }
                }
                std::sort(classStudents.begin(), classStudents.end());
                for (size_t i = 0; i < classStudents.size(); ++i) {
                    for (auto& student : students) {
                        if (student.stream == stream && student.classNumber == classNumber &&
                            student.name == classStudents[i].name) {
                            student.classNumber = i + 1;
                        }
                    }
                }
            }
        }
    }

    void printRanks() {
        std::ofstream outputFile("rankings.txt");
        if (!outputFile.is_open()) {
            std::cerr << "Error opening output file." << std::endl;
            return;
        }
        
        for (const auto& student : students) {
            outputFile << (student.stream == 0 ? "Bio" : "Math") << "\t" << student.classNumber << "\t"
                       << student.rollNumber << "\t" << student.name << "\t" << student.totalMarks << std::endl;
        }

        outputFile.close();
    }
};

int main() {
    School school;

    // Dummy data - replace this with actual data input
    for (int stream = 0; stream <= 1; ++stream) {
        for (int classNumber = 1; classNumber <= (stream == 0 ? 3 : 5); ++classNumber) {
            for (int i = 1; i <= 40; ++i) {
                Student student;
                student.name = "Student" + std::to_string(i);
                student.marksBiology = rand() % 101;
                student.marksPhysics = rand() % 101;
                student.marksChemistry = rand() % 101;
                student.stream = stream;
                student.classNumber = classNumber;
                school.addStudent(student);
            }
        }
    }

    school.calculateRanks();
    school.printRanks();

    return 0;
}
