import threading
import time
import os

# Restrict File Access to Specific Directory
ALLOWED_FOLDER = os.path.abspath("/home/vbuntu/Desktop/Vatsal/college/Sem 5/CS/asgn9/sandbox")  # Ensures full path

# Function to write data to a file only within the allowed folder
def write_to_file(folder, filename, data):
    # Check if the allowed folder exists
    if not os.path.exists(ALLOWED_FOLDER):
        raise FileNotFoundError(f"The allowed folder {ALLOWED_FOLDER} does not exist.")

    folder_path = os.path.abspath(folder)  # Get absolute path for folder
    if folder_path.startswith(ALLOWED_FOLDER):
        file_path = os.path.join(folder, filename)
        with open(file_path, 'w') as f:
            f.write(data)
        print(f"File written successfully to {file_path}")
    else:
        raise PermissionError("Write operation outside of sandbox folder is prohibited!")

# Function to handle sandboxed code execution
def sandbox_code():
    try:
        # Write to file in the allowed sandbox folder
        write_to_file(ALLOWED_FOLDER, "sandboxed_file.txt", "Data inside the sandbox")
        time.sleep(10)  # Simulate a long-running task
    except Exception as e:
        print(f"Error: {e}")

# Class to handle the sandbox timeout using threading
class SandboxThread(threading.Thread):
    def __init__(self, timeout):
        super().__init__()  # Proper initialization of the Thread
        self.timeout = timeout
        self.result = None

    def run(self):
        try:
            self.result = sandbox_code()
        except Exception as e:
            self.result = e

# Function to run the sandbox code with a timeout
def run_with_timeout(timeout_seconds):
    thread = SandboxThread(timeout=timeout_seconds)
    thread.start()
    thread.join(timeout_seconds)

    if thread.is_alive():
        print("Execution Timeout. Terminating sandbox.")
        # Terminate the thread (simulated since thread termination is complex in Python)
        raise Exception("Sandbox execution timed out")
    else:
        print("Sandbox executed successfully")

# Main execution
if __name__ == "__main__":
    try:
        # Run the sandbox code with a 5-second timeout
        run_with_timeout(5)
    except Exception as e:
        print(e)
