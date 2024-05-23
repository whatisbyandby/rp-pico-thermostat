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

#endif