#ifndef TROOP_H
#define TROOP_H


class troop
{
    public:
        troop();
        virtual ~troop();

        int Gethealth() { return health; }
        void Sethealth(int val) { health = val; }
        int Getdamage() { return damage; }
        void Setdamage(int val) { damage = val; }
        int Gethunger() { return hunger; }
        void Sethunger(int val) { hunger = val; }
        int Getid() { return id; }
        void Setid(int val) { id = val; }
        int Getstatus() { return status; }
        void Setstatus(int val) { status = val; }

        void Display();
    private:
        int health;
        int damage;
        int hunger;
        int id;
        int status;
};

#endif // TROOP_H
