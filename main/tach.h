#ifndef TACH_H
    #define TACH_H

volatile static unsigned int revcounter;
class Tach {
    private:
        
        
        const int rpmPin = 34;
        float oldtime=0;        
        float time;
        float rpm;
    public:
        Tach();
        int calcRPM();
};

#endif