#include <iostream>
#include <string>
#include <stdexcept> // For exception handling

using namespace std;

// Base class: Exam (Abstract Class)
class Exam {
protected:
    int examID;
    string subject;
    int duration; // in minutes

public:
    // Constructor
    Exam(int id, string sub, int dur) {
        if (dur <= 0) {
            throw invalid_argument("Invalid exam duration!");
        }
        examID = id;
        subject = sub;
        duration = dur;
    }

    // Virtual function to grade the exam
    virtual double gradeExam() = 0;

    // Display function
    virtual void display() {
        cout << "Exam ID: " << examID << ", Subject: " << subject << ", Duration: " << duration << " min";
    }

    virtual ~Exam() {} // Virtual destructor
};

// Derived class: MultipleChoiceExam
class MultipleChoiceExam : public Exam {
private:
    int totalQuestions;
    int correctAnswers;

public:
    // Constructor
    MultipleChoiceExam(int id, string sub, int dur, int questions, int correct)
        : Exam(id, sub, dur) {
        totalQuestions = questions;
        correctAnswers = correct;
    }

    // Grade exam by calculating percentage score
    double gradeExam() override {
        return (double)correctAnswers / totalQuestions * 100;
    }

    // Display function
    void display() override {
        Exam::display();
        cout << ", Total Questions: " << totalQuestions << ", Correct Answers: " << correctAnswers << endl;
    }
};

// Derived class: EssayExam
class EssayExam : public Exam {
private:
    string topic;
    double score;

public:
    // Constructor
    EssayExam(int id, string sub, int dur, string top)
        : Exam(id, sub, dur), topic(top), score(0) {}

    // Function to manually set the score
    void setScore(double s) {
        if (s < 0 || s > 100) {
            throw invalid_argument("Invalid score value!");
        }
        score = s;
    }

    // Grade exam returns the manually set score
    double gradeExam() override {
        return score;
    }

    // Display function
    void display() override {
        Exam::display();
        cout << ", Topic: " << topic << ", Score: " << score << endl;
    }
};

// Main function
int main() {
    try {
        // Creating MultipleChoiceExam instance
        MultipleChoiceExam mcExam(101, "Math", 60, 10, 8);
        cout << "Multiple Choice Exam:\n";
        mcExam.display();
        cout << "Grade: " << mcExam.gradeExam() << "%\n\n";

        // Creating EssayExam instance
        EssayExam essayExam(102, "History", 90, "World War II");
        cout << "Essay Exam:\n";
        essayExam.display();

        // Setting score manually and displaying result
        essayExam.setScore(85);
        cout << "Updated Essay Exam:\n";
        essayExam.display();
        cout << "Grade: " << essayExam.gradeExam() << "%\n";

    } catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
