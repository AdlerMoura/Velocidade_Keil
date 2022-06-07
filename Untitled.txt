#include "mbed.h"

DigitalIn sensor(PB_0);

double micros(){
    using namespace std::chrono;
    auto now_ms = time_point_cast<microseconds>(Kernel::Clock::now());
    long micros = now_ms.time_since_epoch().count();
    return micros;
}

int main(){
    sensor.mode(PullUp);
    int estado = 1;
    int k = 0;
    float tempIni, T, f;
    int rpm;
    
    while (true){
        if (k == 0){
            tempIni = micros();
            k = 1;
        }
        
        if(estado && !sensor.read()){
            estado = 0;
        }

        if(!estado && sensor.read()){
            T = micros() - tempIni;
            printf("Período %f ms\n", T/1000.0);

            f = 1000000 / T;
            printf("Frequência: %f Hz\n", f);
            rpm = int(f * 60);
            printf("RPM: %d\n", rpm);
            /*
            raio = 0.06;
            float velocidade = f * 2.0 * 3.14 * raio;
            printf("Velocidade: %f m/s\n: ");
            */

            k = 0;
            estado = 1;
        }
    }
}