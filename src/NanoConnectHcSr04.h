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

#ifndef NANOCONNECTHCSR04_NANOCONNECTHCSR04_H
#define NANOCONNECTHCSR04_NANOCONNECTHCSR04_H

#include <Arduino.h>
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/clocks.h"

#include "NanoConnectHcSr04.pio.h"


class NanoConnectHcSr04
{
public:
    /// @brief Constructor
    /// @param trigPin: trigger pin
    /// @param echoPin: echo pin
    /// @param pio: pio number 0=pio0, 1 = pio1
    /// @param sm: pio state machine  0-4
    NanoConnectHcSr04(int trigPin, int echoPin, PIO pio, uint sm);

    /// @brief destructor
    virtual ~NanoConnectHcSr04();

    /// @brief Read the HCSR04 and return the distance in centimeters
    /// @return
    float readSonar();
    uint sonar_offset;

private:
    /// @brief selected pio
    PIO sonar_pio ;

    /// @brief selected state machine
    uint sonar_sm ;
};

#endif //NANOCONNECTHCSR04_NANOCONNECTHCSR04_H
