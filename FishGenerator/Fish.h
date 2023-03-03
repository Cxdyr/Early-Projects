#ifndef FISH_H
#define FISH_H


class Fish
{
    public:
        Fish();
        virtual ~Fish();
        Fish(const Fish& other);

        char GetType() { return Type; }
        void SetType(char val) { Type = val; }
        char GetSchool() { return School; }
        void SetSchool(char val) { School = val; }
        double Getlongitude() { return longitude; }
        void Setlongitude(double val) { longitude = val; }
        double Getlatitude() { return latitude; }
        void Setlatitude(double val) { latitude = val; }

        void Display();


    private:
        char Type;
        char School;
        double longitude;
        double latitude;
};

#endif // FISH_H
