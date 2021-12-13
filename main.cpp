#include <iostream>

class Monitor {
    bool pixels[80][50];
public:

    static void init(Monitor* monitor){
        for (int i = 0; i < 80; i++){
            for (int j = 0; j < 50; j++) {
                monitor->pixels[i][j] = 0;
            }
        }
    }

    static void display(Monitor* monitor){
        for (int i = 0; i < 80; i++){
            for (int j = 0; j < 50; j++){
                std::cout << monitor->pixels[i][j];
            }
            std::cout << std::endl;
        }
    }

    static void paint (Monitor* monitor, int begin_x, int begin_y, int end_x, int end_y){
        for (int i =begin_x; i < end_x; i++){
            for (int j = begin_y; j < end_y; j++) {
                monitor->pixels[i][j] = 1;
            }
        }
    }

    friend class Window;
};




class Window{
    int begin_x = 0;
    int begin_y = 0;
    int height = 0;
    int weight = 0;

public:
    int getBegin_x() {
        return begin_x;
    }

    int getBegin_y() {
        return begin_y;
    }

    int getHeight() {
        return height;
    }

    int getWeight() {
        return weight;
    }

    friend void move(Window* window, int shift_x, int shift_y);
    friend void resize(Window* window, int newHeight, int newWeight);
    friend class Monitor;

};
void move(Window* window, int shift_x, int shift_y){
    window->begin_x = window->begin_x + shift_x;
    window->begin_y = window->begin_y + shift_y;
    if (window->begin_x < 0) window->begin_x = 0;
    if (window->begin_x + window->weight > 80) window->begin_x = 80 - window->weight;
    if (window->begin_y < 0) window->begin_y = 0;
    if (window->begin_y + window->height > 50) window->begin_y = 50 - window->height;
}

void resize(Window* window, int newHeight, int newWeight){
    window->height = newHeight;
    window->weight = newWeight;
    if (window->height < 0) window->height = 0;
    if (window->begin_x + window->weight > 80) window->weight = 80 - window->begin_x;
    if (window->weight < 0) window->weight = 0;
    if (window->begin_y + window->height > 80) window->height = 80 - window->begin_y;
}


int main() {
    Window* window = new Window();
    Monitor* monitor = new Monitor();
    std::string cmd;
    while (true){
        std::cin >> cmd;
        int parameter, parameter_2;
        if (cmd == "move") {
            std::cout << "enter new vector: ";
            std::cin >> parameter >> parameter_2;
            Monitor::init(monitor);
            move(window, parameter, parameter_2);
            Monitor::paint(monitor, window->getBegin_x(), window->getBegin_y(), window->getBegin_x() + window->getWeight(), window->getBegin_y() + window->getHeight());
        }else if (cmd == "resize") {
            std::cout << "enter new size: ";
            std::cin >> parameter >> parameter_2;
            Monitor::init(monitor);
            resize(window, parameter, parameter_2);
            Monitor::paint(monitor, window->getBegin_x(), window->getBegin_y(), window->getBegin_x() + window->getWeight(), window->getBegin_y() + window->getHeight());
        }else if (cmd == "display") {
            Monitor::display(monitor);
        }else if (cmd == "close") {
            Monitor::init(monitor);
            return 0;
        }
        else std::cerr << "Invalid command!"; 
    }


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
