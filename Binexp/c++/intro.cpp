#include <iostream>
#include <iomanip>
#include <string>
#include <cstdint>
#include <unistd.h>

// Structure to store data
struct DataStorage {
    std::string data;
};

class HelloWorldInterface {
public:
    virtual void sayHello() const = 0;
    virtual void setData(const std::string& newData) = 0;
    virtual void displayData() const = 0;
     virtual void win() const = 0;
};

class HelloWorld : public HelloWorldInterface {
private:
    DataStorage storage;

public:
    void sayHello() const override {
        std::cout << "Hello, World!" << std::endl;
    }

    void setData(const std::string& newData) override {
        storage.data = newData;
    }

    void displayData() const override {
        std::cout << "Stored Data: " << storage.data << std::endl;
    }

    void win() const override {
    	system("/bin/sh");
    }
};

// Function to display memory layout
void displayMemoryLayout(const void* memory, std::size_t size) {
    const std::uintptr_t* addresses = static_cast<const std::uintptr_t*>(memory);

    std::cout << "C++ Vtable will work like this: " << std::endl;
    std::cout << "helloWorldObj->sayHello() --> 0x5555xxxx->0x5555yyyy" << std::endl;
    std::cout << "0x5555xxxx means the helloWorldObj address and 0x5555yyyy mean the sayHello function address" << std::endl;
    std::cout << "Now you're job is to call the WIN" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;



    std::cout << "helloWorldObj Memory Layout:" << std::endl;
    for (std::size_t i = 0; i < size / sizeof(std::uintptr_t); ++i) {
        std::cout << i+1 << ". " << "0x" << std::hex << std::setw(8) << std::setfill('0') << addresses[i] << std::dec << std::endl;
    }
}

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}


int main() {
	init();
    // Dynamically allocate memory for the HelloWorld object
    HelloWorld* helloWorldObj = new HelloWorld;

    int choice;
    std::string inputData;

    do {
        std::cout << "Menu:" << std::endl;
        std::cout << std::endl;
        std::cout << "1. Call HelloWorld" << std::endl;
        std::cout << "2. Set Data" << std::endl;
        std::cout << "3. Display Data" << std::endl;
        std::cout << "4. Display Memory Layout" << std::endl;
        std::cout << "5. Exit" << std::endl;

        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                // Use the vtable from the allocated memory
                reinterpret_cast<HelloWorldInterface*>(helloWorldObj)->sayHello();
                break;
            case 2:
                std::cout << "Enter data: ";
                read(0, helloWorldObj, 0x10);
                std::cout << "Data set successfully." << std::endl;
                break;
            case 3:
                helloWorldObj->displayData();
                break;
            case 4:
                // Display the memory layout, including the vtable address
                displayMemoryLayout(helloWorldObj, sizeof(HelloWorld));
                break;
            case 5:
                std::cout << "Exiting program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter a valid option." << std::endl;
                break;
        }
    } while (choice != 5);

    // Free the allocated memory
    delete helloWorldObj;

    return 0;
}
