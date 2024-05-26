#ifndef GPIO_HPP
#define GPIO_HPP


class Switch {
    public:
        Switch(int pin);
        ~Switch();
        void turnOn();
        void turnOff();
        bool isOn();
    private:
        int pin;
        bool state;
};

class Button {
    public:
        Button(int pin);
        ~Button();
        bool isPressed();
        int readNumberOfPresses();
    private:
        int pin;
        int numOfPresses;
};


#endif