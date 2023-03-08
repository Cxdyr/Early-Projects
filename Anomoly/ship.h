#ifndef SHIP_H
#define SHIP_H


class ship
{
    public:
        ship();
        virtual ~ship();

        int Gethealth() { return health; }
        void Sethealth(int val) { health = val; }
        int Getfuel() { return fuel; }
        void Setfuel(int val) { fuel = val; }



    private:
        int health;
        int fuel;
};

#endif // SHIP_H
