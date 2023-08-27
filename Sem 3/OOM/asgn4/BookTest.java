import java.util.Scanner;

class Book{
    String title;
    String author;
    int yearPublished;
    double price;

    //default constructor
    public Book(){
        this.title = "unknown";
        this.author = "unknown";
        this.yearPublished = 2000;
        this.price = 0;
    }
    //constructor with all parameters
    public Book(String title, String author, int yearPublished, double price){
        this.title = title;
        this.author = author;
        this.yearPublished = yearPublished;
        this.price = price;
    }

    public String displayDetails(){
        return("Title: "+title+", author: "+author+", yearPublished: "+yearPublished+", price: "+price);
    }

}


class BookTest{
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        
        System.out.println("Enter book title: ");
        String title = sc.nextLine();
        
        System.out.println("Enter book author: ");
        String author = sc.nextLine();

        System.out.println("Enter book's year of publication: ");
        int yearPublished = sc.nextInt();

        System.out.println("Enter book price: ");
        double price = sc.nextDouble();

        Book b1 = new Book(title, author, yearPublished, price);
        Book b2 = new Book(); //using default constructor
        System.out.println("Book details of b1: "+b1.displayDetails());
        System.out.println("Book details of b2: "+b2.displayDetails());

        sc.close();
    }
}