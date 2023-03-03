#ifndef BOB_H
#define BOB_H


class Bob
{
    public:
        Bob();
        virtual ~Bob();

        int Getwins() { return wins; }
        void Setwins(int val) { wins = val; }
        int Getloses() { return loses; }
        void Setloses(int val) { loses = val; }
        int Gethealth() { return health; }
        void Sethealth(int val) { health = val; }
        int Getdamage() { return damage; }
        void Setdamage(int val) { damage = val; }
        int Getreputation() { return reputation; }
        void Setreputation(int val) { reputation = val; }

    protected:

    private:
        int wins;
        int loses;
        int health;
        int damage;
        int reputation;
};

#endif // BOB_H
