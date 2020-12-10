#include <iostream>
#include "olcNoiseMaker.h"
using namespace std;


atomic<double> dFrequency = 0.0;

double MakeNoise(double dTime){
    double dOutput = 1.0 * (sin(dFrequency * 2 * 3.14159 * dTime) + sin((dFrequency + 20.0)  * 2 * 3.14159 * dTime));
    return 0.4 * dOutput;

    //if (dOutput > 0) {
    //    return 0.2;
    //}
    //return -0.2;
}

int main() {

    wcout << "Hello World" << endl;

    vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

    for (auto d : devices) wcout << "Found output device: " << d << endl;
    
    olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);
    
    sound.SetUserFunction(MakeNoise);

    double dOctaveBaseFrequency = 110.0; //A2
    double d12thRootof2 = pow(2.0, 1.0 / 12.0);

    while (1) {

        bool keyPressed = false;
        for (int k = 0; k < 15; k++) {
            if (GetAsyncKeyState((unsigned char)("ZSXDCVGBHNJM\xbc"[k])) && 0x8000) {
                dFrequency = dOctaveBaseFrequency * pow(d12thRootof2, k);
                keyPressed = true;
            }
        }

        if(!keyPressed)
        {
            dFrequency = 0.0;
        }
        
    }
    
    return 0;
}