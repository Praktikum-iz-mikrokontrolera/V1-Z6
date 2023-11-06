/* Praktikum iz mikrokontrolera Vezbe 1 Zadatak 6
 * Copyright (c) 2023 ETF
 * SPDX-License-Identifier: Apache-2.0
 */

// Obavezna biblioteka
#include "mbed.h"


// Duzina periode i broj medjustanja na diodi
#define PERIOD     10000
#define NUMBER_STATES     5


int main()
{
    PwmOut led(LED1);
    DigitalIn dugme(BUTTON1);

    led.period_us(PERIOD);

    //Trenutni intenzitet diode na skali od 0 do 1
    float intensity = 0;

    // Prethodno stanje dugmeta, potrebno je da je bilo ugaseno, pa zatim ukljuceno da bi se pritisak registrovao
    bool prethodnoStanje = 1;

    
    while (true) {
        if(prethodnoStanje == 1 && !dugme){
            // Ukoliko se int deli sa drugim brojem, kao rezultat se dobija int
            // Potrebno je eksplicitno naglasiti da se radi o deljenju floata zapisom prvog clana kao 1.0
            intensity += 1.0 / (NUMBER_STATES - 1);
        }

        prethodnoStanje = dugme;

        // Ukoliko smo prosli najvise stanje, ugasi diodu
        if(intensity > 1){
            intensity = 0;
        }

        // Slanje vrednosti intenziteta iz promenljive na diodu
        led.write(intensity);
    }
}


