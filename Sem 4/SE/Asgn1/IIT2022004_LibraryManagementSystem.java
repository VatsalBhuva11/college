package Library;

import java.sql.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.util.Scanner;

public class LibraryManagementSystem {

    static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://localhost:3306/library";

    static final String USER = "root";
    static final String PASS = "root";

    public static void main(String[] args) {
        Connection conn = null;
        Statement stmt = null;

        try {
            Class.forName(JDBC_DRIVER);
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            stmt = conn.createStatement();

            createTable(stmt);

            Scanner scanner = new Scanner(System.in);

            while (true) {

                System.out.println("\n1. Add Book");
                System.out.println("2. Delete Book");
                System.out.println("3. Update Book");
                System.out.println("4. Issue/Return Book");
                System.out.println("5. View Books Issued to a Student");
                System.out.println("6. Search Book by ID");
                System.out.println("7. Check Issued Books Status");
                System.out.println("8. Exit");

                System.out.print("Enter your choice: ");
                int choice = scanner.nextInt();

                switch (choice) {
                    case 1:
                        addBook(stmt, scanner);
                        break;
                    case 2:
                        deleteBook(stmt, scanner);
                        break;
                    case 3:
                        updateBook(stmt, scanner);
                        break;
                    case 4:
                        issueReturnBook(stmt, scanner);
                        break;
                    case 5:
                        viewBooksIssuedToStudent(stmt, scanner);
                        break;
                    case 6:
                        searchBookByID(stmt, scanner);
                        break;
                    case 7:
                        checkIssuedBooksStatus(stmt, scanner);
                        break;
                    case 8:
                        System.out.println("Exiting...");
                        conn.close();
                        System.exit(0);
                    default:
                        System.out.println("Invalid choice. Please enter a number between 1 and 8.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void createTable(Statement stmt) throws SQLException {
        String createTableSQL = "CREATE TABLE IF NOT EXISTS books " +
                "(id INT PRIMARY KEY AUTO_INCREMENT, " +
                " name VARCHAR(255), " +
                " author VARCHAR(255), " +
                " issue_status VARCHAR(10), " +
                " student_id INT, " +
                " due_date DATE, " +
                " fine INT)";

        stmt.executeUpdate(createTableSQL);
    }

    private static void addBook(Statement stmt, Scanner scanner) throws SQLException {
        System.out.print("Enter book name: ");
        String name = scanner.next();
        System.out.print("Enter author name: ");
        String author = scanner.next();

        String addBookSQL = "INSERT INTO books (name, author, issue_status) VALUES ('" + name + "', '" + author
                + "', 'available')";
        stmt.executeUpdate(addBookSQL);

        System.out.println("Book added successfully.");
    }

    private static void deleteBook(Statement stmt, Scanner scanner) throws SQLException {
        System.out.print("Enter book ID to delete: ");
        int bookId = scanner.nextInt();

        String deleteBookSQL = "DELETE FROM books WHERE id = " + bookId;
        stmt.executeUpdate(deleteBookSQL);

        System.out.println("Book deleted successfully.");
    }

    private static void updateBook(Statement stmt, Scanner scanner) throws SQLException {
        System.out.print("Enter book ID to update: ");
        int bookId = scanner.nextInt();

        System.out.println("1. Update Book ID");
        System.out.println("2. Update Book Name");
        System.out.println("3. Update Author Name");
        System.out.println("4. Update Issue Status");

        System.out.print("Enter your choice: ");
        int updateChoice = scanner.nextInt();

        String columnName = "";
        String newValue = "";

        switch (updateChoice) {
            case 1:
                columnName = "id";
                System.out.print("Enter new book ID: ");
                newValue = scanner.next();
                break;
            case 2:
                columnName = "name";
                System.out.print("Enter new book name: ");
                newValue = scanner.next();
                break;
            case 3:
                columnName = "author";
                System.out.print("Enter new author name: ");
                newValue = scanner.next();
                break;
            case 4:
                columnName = "issue_status";
                System.out.print("Enter new issue status: ");
                newValue = scanner.next();
                break;
            default:
                System.out.println("Invalid choice.");
                return;
        }

        String updateBookSQL = "UPDATE books SET " + columnName + " = '" + newValue + "' WHERE id = " + bookId;
        stmt.executeUpdate(updateBookSQL);

        System.out.println("Book updated successfully.");
    }

    private static void issueReturnBook(Statement stmt, Scanner scanner) throws SQLException {
        System.out.print("Enter book ID: ");
        int bookId = scanner.nextInt();

        String getBookSQL = "SELECT * FROM books WHERE id = " + bookId;
        ResultSet rs = stmt.executeQuery(getBookSQL);

        if (rs.next()) {
            String issueStatus = rs.getString("issue_status");
            if (issueStatus.equals("available")) {
                System.out.print("Enter student ID: ");
                int studentId = scanner.nextInt();
                System.out.print("Enter due date (YYYY-MM-DD): ");
                String dueDate = scanner.next();

                String issueBookSQL = "UPDATE books SET issue_status = 'issued', student_id = " + studentId
                        + ", due_date = '" + dueDate + "' WHERE id = " + bookId;
                stmt.executeUpdate(issueBookSQL);

                System.out.println("Book issued successfully.");
            } else if (issueStatus.equals("issued")) {
                String returnBookSQL = "UPDATE books SET issue_status = 'available', student_id = NULL, due_date = NULL WHERE id = "
                        + bookId;
                stmt.executeUpdate(returnBookSQL);

                System.out.println("Book returned successfully.");
                String dueDate = rs.getString("due_date");
                if (dueDate != null) {
                    java.util.Date currentDate = new java.util.Date();
                    java.util.Date dueDateObj = java.sql.Date.valueOf(dueDate);

                    if (currentDate.after(dueDateObj)) {
                        long daysLate = (currentDate.getTime() - dueDateObj.getTime()) / (1000 * 60 * 60 * 24);
                        int fine = (int) (daysLate - 15) * 5;
                        if (fine > 0) {
                            System.out.println("Fine applicable: Rs. " + fine);
                            String updateFineSQL = "UPDATE books SET fine = " + fine + " WHERE id = " + bookId;
                            stmt.executeUpdate(updateFineSQL);
                        }
                    }
                }
            }
        } else {
            System.out.println("Book not found.");
        }
    }

    private static void viewBooksIssuedToStudent(Statement stmt, Scanner scanner) throws SQLException {
        System.out.print("Enter student ID: ");
        int studentId = scanner.nextInt();

        String viewBooksSQL = "SELECT * FROM books WHERE student_id = " + studentId;
        ResultSet rs = stmt.executeQuery(viewBooksSQL);

        System.out.println("\nBooks issued to Student ID " + studentId + ":");
        while (rs.next()) {
            int bookId = rs.getInt("id");
            String bookName = rs.getString("name");
            String author = rs.getString("author");
            String issueStatus = rs.getString("issue_status");

            System.out.println(
                    "Book ID: " + bookId + ", Name: " + bookName + ", Author: " + author + ", Status: " + issueStatus);
        }
    }

    private static void searchBookByID(Statement stmt, Scanner scanner) throws SQLException {
        System.out.print("Enter book ID to search: ");
        int bookId = scanner.nextInt();

        String searchBookSQL = "SELECT * FROM books WHERE id = " + bookId;
        ResultSet rs = stmt.executeQuery(searchBookSQL);

        if (rs.next()) {
            String bookName = rs.getString("name");
            String author = rs.getString("author");
            String issueStatus = rs.getString("issue_status");
            int studentId = rs.getInt("student_id");
            String dueDate = rs.getString("due_date");
            int fine = rs.getInt("fine");

            System.out.println("\nBook Details:");
            System.out.println("Book ID: " + bookId);
            System.out.println("Name: " + bookName);
            System.out.println("Author: " + author);
            System.out.println("Issue Status: " + issueStatus);

            if (issueStatus.equals("issued")) {
                System.out.println("Student ID: " + studentId);
                System.out.println("Due Date: " + dueDate);

                if (fine > 0) {
                    System.out.println("Fine: Rs. " + fine);
                }
            }
        } else {
            System.out.println("Book not found.");
        }
    }

    private static void checkIssuedBooksStatus(Statement stmt, Scanner scanner) throws SQLException {
        System.out.print("Enter student ID: ");
        int studentId = scanner.nextInt();

        String checkStatusSQL = "SELECT * FROM books WHERE student_id = " + studentId + " AND issue_status = 'issued'";
        ResultSet rs = stmt.executeQuery(checkStatusSQL);

        System.out.println("\nBooks issued to Student ID " + studentId + ":");
        while (rs.next()) {
            int bookId = rs.getInt("id");
            String bookName = rs.getString("name");
            String author = rs.getString("author");
            String dueDate = rs.getString("due_date");

            System.out.println(
                    "Book ID: " + bookId + ", Name: " + bookName + ", Author: " + author + ", Due Date: " + dueDate);
        }
    }
}