import java.util.Scanner;
import java.util.ArrayList;

class Student{
    final int roll_no;
    final float height;
    public static ArrayList<Student> students = new ArrayList<>();
    public Student(int roll_no, float height){
        this.roll_no = roll_no;
        this.height = height;
        students.add(this);
    }
    public void display_details(){
        System.out.println("Student's roll number is "+roll_no+" and height is "+height);
    }
    public static float averageHeight(){
        float sum = 0;
        int len = students.size();
        for (int i = 0; i<len; i++){
            sum += students.get(i).height;
        }
        return sum/len;
    }
}

public class iit2022004_p2 {
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter roll number: ");
        int roll = sc.nextInt();
        System.out.println("Enter height: ");
        float height = sc.nextFloat();

        Student s1 = new Student(roll, height);
        s1.display_details();
        System.out.println("Average height of students is: "+Student.averageHeight());
        
        Student s2 = new Student(4, 90);
        s2.display_details();
        System.out.println("Average height of students is: "+Student.averageHeight());
        
        sc.close();
    }
}
