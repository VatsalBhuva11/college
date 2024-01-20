import mysql.connector
from datetime import datetime, timedelta

# Function to create the table if it doesnt exist
def initialize_database(myCursor):
    myCursor.execute('''
        CREATE TABLE IF NOT EXISTS bookdata (
            bookId VARCHAR(255) PRIMARY KEY,
            bookName VARCHAR(255),
            authorName VARCHAR(255),
            issueStatus VARCHAR(15),
            studentId VARCHAR(255),
            dueDate DATE,
            fine INT
        );
    ''')

# Function to add a new book to the database
def add_book(myCursor):
    book_name = input("Enter the name of the book: ")
    author_name = input("Enter author's name: ")
    book_id = input("Enter books ID: ")
    book_status = 'available'
    student_id = None
    due_date = None

    myCursor.execute("INSERT INTO bookdata VALUES (%s, %s, %s, %s, %s, %s, %s)",
                     (book_id, book_name, author_name, book_status, student_id, due_date, 0))

# Function to delete a book from the database
def delete_book(myCursor):
    book_id_to_remove = input("Enter the ID of the book you want to remove from the records: ")
    myCursor.execute("DELETE FROM bookdata WHERE bookId=%s", (book_id_to_remove,))

# Function to update book information
def update_book(myCursor):
    book_to_be_updated = input("Enter the ID of the book whose info you want to update: ")
    student_id = input("Enter student ID: ")
    due_date = input("Enter due date (YYYY-MM-DD): ")
    myCursor.execute("UPDATE bookdata SET studentId=%s, dueDate=%s WHERE bookId=%s",
                     (student_id, due_date, book_to_be_updated))

# Function to issue a book to a student
def issue_book(myCursor):
    book_to_be_issued = input("Enter the ID of the book to be issued: ")
    student_id = input("Enter student ID: ")
    due_date = (datetime.now() + timedelta(days=15)).strftime('%Y-%m-%d')
    myCursor.execute("UPDATE bookdata SET issueStatus='issued', studentId=%s, dueDate=%s WHERE bookId=%s",
                     (student_id, due_date, book_to_be_issued))

# Function to return a book and calculate fine if applicable
def return_book(myCursor):
    book_to_be_returned = input("Enter the ID of the book to be returned: ")
    myCursor.execute("SELECT dueDate FROM bookdata WHERE bookId=%s", (book_to_be_returned,))
    due_date = myCursor.fetchone()[0]
    current_date = datetime.now().strftime('%Y-%m-%d')

    # Convert due_date to string before passing to strptime
    fine = max(0, (datetime.strptime(current_date, '%Y-%m-%d') - datetime.combine(due_date, datetime.min.time())).days * 5)
    myCursor.execute("UPDATE bookdata SET issueStatus='available', studentId=NULL, dueDate=NULL, fine=%s WHERE bookId=%s",
                     (fine, book_to_be_returned))


# Function to view books issued to a particular student
def view_books_by_student(myCursor):
    student_id = input("Enter student ID to view issued books: ")
    myCursor.execute("SELECT * FROM bookdata WHERE studentId=%s", (student_id,))
    books = myCursor.fetchall()
    print("Books issued to Student ID {}: ".format(student_id))
    for row in books:
        print(row)

# Function to search for a book by its ID
def search_book_by_id(myCursor):
    book_id_to_search = input("Enter the ID of the book you want to search: ")
    myCursor.execute("SELECT * FROM bookdata WHERE bookId=%s", (book_id_to_search,))
    book = myCursor.fetchone()
    print("Book details for ID {}: ".format(book_id_to_search))
    print(book)

# Function to check the status of books issued by a student
def check_issued_books(myCursor):
    student_id = input("Enter student ID to check issued books: ")
    myCursor.execute("SELECT * FROM bookdata WHERE studentId=%s", (student_id,))
    issued_books = myCursor.fetchall()
    print("Books issued to Student ID {}: ".format(student_id))
    for row in issued_books:
        print(row)

con = mysql.connector.connect(host='localhost', password='', user='root', database='library')

if con.is_connected():
    print("Connection established")

myCursor = con.cursor()

try:
    initialize_database(myCursor)

    while True:
        print("Choose from the following:\n1. Add book\n2. Delete book\n3. Update book info\n4. Issue book\n5. Return book\n6. View books issued to a student\n7. Search for a book by ID\n8. Check status of books issued by a student\n9. Quit")

        choice = int(input("Enter your choice: "))

        if choice == 1:
            add_book(myCursor)
        elif choice == 2:
            delete_book(myCursor)
        elif choice == 3:
            update_book(myCursor)
        elif choice == 4:
            issue_book(myCursor)
        elif choice == 5:
            return_book(myCursor)
        elif choice == 6:
            view_books_by_student(myCursor)
        elif choice == 7:
            search_book_by_id(myCursor)
        elif choice == 8:
            check_issued_books(myCursor)
        elif choice == 9:
            print("Quitting the program.")
            break
        else:
            print("Invalid choice. Please enter a valid option.")

        con.commit()  # To finalize the changes into the database

        myCursor.execute("SELECT * FROM bookdata")
        myResult = myCursor.fetchall()

        print("Updated Book Database:")
        for row in myResult:
            print(row)

except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    myCursor.close()
    con.close()
