abstract class Shape {
    protected String color;
    public Shape(String color) {
        this.color = color;
    }
    public abstract double calculateArea();
    public abstract double calculatePerimeter();
    public String getColor() {
        return color;
    }
}
class Circle extends Shape {
    private double radius;
    public Circle(String color, double radius) {
        super(color);
        this.radius = radius;
    }
    public double calculateArea() {
        return Math.PI * radius * radius;
    }
    public double calculatePerimeter() {
        return 2 * Math.PI * radius;
    }
}
class Rectangle extends Shape {
    double length;
    double width;
    public Rectangle(String color, double length, double width) {
        super(color);
        this.length = length;
        this.width = width;
    }
    public double calculateArea() {
        return length * width;
    }
    public double calculatePerimeter() {
        return 2 * (length + width);
    }
}
class Square extends Rectangle {
    public Square(String color, double sideLength) {
        super(color, sideLength, sideLength);
    }
}
class IIT2022004_tut5_q3 {
    public static void main(String[] args) {
        Circle circle = new Circle("Yellow", 3.0);
        Rectangle rectangle = new Rectangle("Blue", 3.0, 4.0);
        Square square = new Square("Pink", 4.0);
        System.out.println("Circle     - Color: " + circle.getColor() + "  , Area: " + circle.calculateArea() + ", Perimeter: " + circle.calculatePerimeter());
        System.out.println("Rectangle  - Color: " + rectangle.getColor() + " , Area: " + rectangle.calculateArea() + ", Perimeter: " + rectangle.calculatePerimeter());
        System.out.println("Square     - Color: " + square.getColor() + ", Area: " + square.calculateArea() + ", Perimeter: " + square.calculatePerimeter());
    }
}
