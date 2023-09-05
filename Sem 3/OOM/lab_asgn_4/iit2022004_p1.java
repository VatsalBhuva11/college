import java.util.Scanner;

interface Shape{
    double area();
    double perimeter();
}

class Circle implements Shape{
    double radius;
    public Circle(double radius){
        this.radius = radius;
    }

    @Override
    public double area(){
        return Math.PI * radius * radius;
    }

    @Override
    public double perimeter(){
        return 2 * Math.PI * radius;
    }

    public void circleDetails(){
        System.out.println("Area of circle is "+area()+" and perimeter is "+perimeter());
        System.out.println();
    }
}

class Rectangle implements Shape{
    double length;
    double width;
    public Rectangle(double length, double width){
        this.length = length;
        this.width = width;
    }

    @Override
    public double area(){
        return length * width;
    }

    @Override
    public double perimeter(){
        return 2*(length+width);
    }

    public void rectDetails(){
        System.out.println("Area of rectangle is "+area()+" and perimeter is "+perimeter());
        System.out.println();
    }
}

public class iit2022004_p1{
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter radius of circle: ");
        double radius = sc.nextDouble();

        Circle c = new Circle(radius);
        c.circleDetails();

        System.out.println("Enter length of rectangle: ");
        double length = sc.nextDouble();
        System.out.println("Enter width of rectangle: ");
        double width = sc.nextDouble();

        Rectangle r = new Rectangle(length, width);
        r.rectDetails();

        sc.close();
    }
}