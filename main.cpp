#include <iostream>

class Monitor {
    static const int width = 80;
    static const int height = 50;
    bool pixels[width][height];
public:

    void init(){
        for (int i = 0; i < width; i++){
            for (int j = 0; j < height; j++) {
                pixels[i][j] = 0;
            }
        }
    }

    void display(){
        for (int i = 0; i < width; i++){
            for (int j = 0; j < height; j++){
                std::cout << pixels[i][j];
            }
            std::cout << std::endl;
        }
    }

    void paint (int begin_x, int begin_y, int end_x, int end_y){
        for (int i =begin_x; i < end_x; i++){
            for (int j = begin_y; j < end_y; j++) {
               pixels[i][j] = 1;
            }
        }
    }

    //friend class Window;
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

    void move( int shift_x, int shift_y){
        begin_x = begin_x + shift_x;
        begin_y = begin_y + shift_y;
        if (begin_x < 0) begin_x = 0;
        if (begin_x + weight > 80) begin_x = 80 - weight;
        if (begin_y < 0) begin_y = 0;
        if (begin_y + height > 50) begin_y = 50 - height;
    }

    void resize(int newHeight, int newWeight){
        height = newHeight;
        weight = newWeight;
        if (height < 0) height = 0;
        if (begin_x + weight > 80) weight = 80 - begin_x;
        if (weight < 0) weight = 0;
        if (begin_y + height > 80) height = 80 - begin_y;
    }



   //friend class Monitor;

};


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
            monitor->init();
            window->move(parameter, parameter_2);
            monitor->paint(window->getBegin_x(), window->getBegin_y(), window->getBegin_x() + window->getWeight(), window->getBegin_y() + window->getHeight());
        }else if (cmd == "resize") {
            std::cout << "enter new size: ";
            std::cin >> parameter >> parameter_2;
            monitor->init();
            window->resize(parameter, parameter_2);
            monitor->paint(window->getBegin_x(), window->getBegin_y(), window->getBegin_x() + window->getWeight(), window->getBegin_y() + window->getHeight());
        }else if (cmd == "display") {
            monitor->display();
        }else if (cmd == "close") {
            monitor->init();
            break;
        }
        else std::cerr << "Invalid command!"; 
    }

    delete window;
    delete monitor;

    return 0;
}
