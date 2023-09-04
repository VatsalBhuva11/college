import java.util.*;  

class Student{
    int studentID;
    String firstName;
    String lastName;
    public Student(int studentID, String firstName, String lastName){
        this.studentID = studentID;
        this.firstName = firstName;
        this.lastName = lastName;
    }
}

class StudentDatabase{
    static HashMap<Integer, Student> students = new HashMap<>();
    public static void addStudent(Student s){
        students.put(s.studentID,s);
    }
    public static void removeStudent(int studentID){
        if (students.containsKey(studentID)){
            Student removed = students.remove(studentID);
            System.out.println("Removed student with ID "+removed.studentID);
        } else {
            System.out.println("Student with ID "+studentID+" does not exist.");
        }
    }
    public static void printDetails(){
        students.forEach((k,v)->{
            System.out.println("StudentID: "+k);
            System.out.println("First Name: "+v.firstName);
            System.out.println("Last Name: "+v.lastName);
            System.out.println("------------------------------------------");
        });
    }
}

public class iit2022004_p3 {
    public static void main(String args[]){
        Student s1 = new Student(1, "Vatsal", "Bhuva");
        Student s2 = new Student(2, "A", "B");
        Student s3 = new Student(3, "John", "Doe");
        Student s4 = new Student(4, "Jane", "Doe");
        Student s5 = new Student(5, "Johnny", "Depp");

        System.out.println("ADDED 3 STUDENTS:");
        StudentDatabase.addStudent(s1);
        StudentDatabase.addStudent(s2);
        StudentDatabase.addStudent(s3);
        
        StudentDatabase.printDetails();
        
        System.out.println("ADDED 2 MORE STUDENTS:");
        StudentDatabase.addStudent(s4);
        StudentDatabase.addStudent(s5);
        
        StudentDatabase.printDetails();
        
        System.out.println("REMOVED FIRST 3 STUDENTS:");
        StudentDatabase.removeStudent(3);
        StudentDatabase.removeStudent(2);
        StudentDatabase.removeStudent(1);
        StudentDatabase.removeStudent(1);

        StudentDatabase.printDetails();
    }
}
