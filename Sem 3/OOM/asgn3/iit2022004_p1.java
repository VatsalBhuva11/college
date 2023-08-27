import java.util.Scanner;
class Circle{
    final double radius;
    public Circle(double radius){
        this.radius = radius; //radius attribute defined for every circle.
    }
    double circumference(){
        return 2 * Math.PI * radius;
    }
    double area(){
        return Math.PI *  Math.pow(radius, 2);
    }
}


class iit2022004_p1{
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter radius of circle: ");
        final double radius = sc.nextDouble();
        Circle c = new Circle(radius);

        System.out.println("Circumference of circle: " + c.circumference());
        System.out.println("Area of circle: " + c.area());

        sc.close();
    }
}