//IIT2022004 question 2

import java.util.Scanner;

class Game{
    final int fixedFloorPrice = 10000;
    int getPrice(){
        return fixedFloorPrice;
    }
}

class Concert{
    final int fixedFloorPrice = 10000;
    final int costPerSeat = 100;
    int getPrice(int noOfSeats, int noOfShows){
        return noOfShows * (fixedFloorPrice + noOfSeats * costPerSeat);
    }

}

class Event{
    String eventType = "";
    int finalPrice = 0;
    public Event(String eventType){
        this.eventType = eventType;
    }    

    int getPrice(){
        Scanner sc = new Scanner(System.in);
        switch (eventType.toLowerCase()){
            case "game":
                Game game = new Game();
                finalPrice = game.getPrice();
                break;
            case "concert":
                Concert concert = new Concert();
                System.out.print("Enter number of seats: ");
                int noOfSeats = sc.nextInt();
                System.out.print("Enter number of shows: ");
                int noOfShows = sc.nextInt();
                finalPrice = concert.getPrice(noOfSeats, noOfShows);
                break;
            default:
                System.out.println("Invalid type entered.");
                break;
        }
        sc.close();
        return finalPrice;
    }


}

public class Auditorium {
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter event type (game/concert): ");
        String eventType = sc.nextLine();

        Event e = new Event(eventType);
        System.out.println("Total price for event is "+e.getPrice());

        sc.close();
    }
}
