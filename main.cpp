#include "mbed.h"

DigitalIn sensor(PA_5);

double micros(){
    using namespace std::chrono;
    auto now_ms = time_point_cast<microseconds>(Kernel::Clock::now());
    long micros = now_ms.time_since_epoch().count();
    return micros;
}

int main(){
    sensor.mode(PullUp);
    Timer tmr;
    float tempoIni, T, f;
    int k = 0, rpm;
    
    while (true){
        if (k == 0){
            while (sensor.read());
            tempoIni = micros();
            k = 1;
        } else{
            tempoIni = micros();
        }
        while (sensor.read());
        while (!sensor.read());
        T = micros() - tempoIni;

        printf("Período %f ms\n", T);
        f = 1000000.0 / T;
        printf("Frequência: %f Hz\n", f);
        rpm = int(f * 60);
        printf("RPM: %d\n", rpm);
        ThisThread::sleep_for(100ms);
    }
}