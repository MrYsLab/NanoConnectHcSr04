/*
 Copyright (c) 2020-2021 Alan Yorinks All rights reserved.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU AFFERO GENERAL PUBLIC LICENSE
 Version 3 as published by the Free Software Foundation; either
 or (at your option) any later version.
 This library is distributed in the hope that it will be useful,f
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 General Public License for more details.

 You should have received a copy of the GNU AFFERO GENERAL PUBLIC LICENSE
 along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "NanoConnectHcSr04.h"

/// @brief Constructor
/// @param trigPin: trigger pin
/// @param echoPin: echo pin
/// @param pio: pio number 0=pio0, 1 = pio1
/// @param sm: pio state machine  0-4
NanoConnectHcSr04::NanoConnectHcSr04(int triggerPin, int echoPin, PIO pio=pio0, uint sm=0)
{
    this->sonar_sm = sm;
    this->sonar_pio = pio;
    sonar_offset = pio_add_program(pio0, &hc_sr04_program);
    hc_sr04_init(pio0, sm, sonar_offset, triggerPin, echoPin);
}

/// @brief Destructor
NanoConnectHcSr04::~NanoConnectHcSr04(){}

/// @brief Read the HCSR04 and return the distance in centimeters
/// @return
float NanoConnectHcSr04::readSonar() {
    // value is used to read from the sm RX FIFO
    uint32_t clock_cycles;
    // clear the FIFO: do a new measurement
    pio_sm_clear_fifos(this->sonar_pio, this->sonar_sm);
    // give the sm some time to do a measurement and place it in the FIFO
    sleep_ms(100);
    // check that the FIFO isn't empty

    if (pio_sm_is_rx_fifo_empty(this->sonar_pio, this->sonar_sm)) {
        // its empty so return 0.
        return 0.0;
    }

    // read one data item from the FIFO
    // Note: every test for the end of the echo pulse takes 2 pio clock ticks,
    //       but changes the 'timer' by only one
    clock_cycles = 2 * pio_sm_get(this->sonar_pio, this->sonar_sm);
    // using
    // - the time for 1 pio clock tick (1/125000000 s)
    // - speed of sound in air is about 340 m/s
    // - the sound travels from the HCS-R04 to the object and back (twice the distance)
    // we can calculate the distance in cm by multiplying with 0.000136
    float cm = (float) clock_cycles * 0.000136;
    return cm;
}


