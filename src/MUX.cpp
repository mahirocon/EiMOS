/*
 MUX.cpp
 A library that controlls the switching of an MUX.

 * Copyright (c) 2023, Chito Kim
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "MUX.h"
#include <Arduino.h>

MUX::MUX(int addr[], int addr_size, int enb[], int enb_size)
{
  address = addr;
  address_size = addr_size;
  enable = enb;
  enable_size = enb_size;
}
void
MUX::setMUX4051(int addr[], int enb[])
{
  address = addr;
  address_size = 3;
  enable = enb;
  enable_size = 2;
  initMUX();
}
void
MUX::setMUX4067(int addr[])
{
  address = addr;
  address_size = 4;
  enable = nullptr;
  enable_size = 0;
  initMUX();
}
void
MUX::initMUX()
{
  // set MUX pins as OUTPUT
  int i, n;
  for(i = 0; i < address_size; i++)
  {
    pinMode(address[i], OUTPUT);
  }
  for(i = 0; i < enable_size; i++)
  {
    pinMode(enable[i], OUTPUT);
  }
  slotSelect(0);
}
void
MUX::slotSelect(int slot_num)
{
  int i, x;
  int d = 1 << address_size;

  enbSelect(slot_num / d);
  for(i = 0, x = 1; i < address_size; i++, x *= 2)
  {
    writeAddress(i, ((slot_num % d) & x));
  }
}
void
MUX::enbSelect(int a)
{
  int i;
  for(i = 0; i < enable_size; i++)
  {
    writeEnable(i, (i == a) ? LOW : HIGH);
  }
}
void
MUX::writeAddress(int n, int state)
{
  digitalWrite(address[n], state);
}
void
MUX::writeEnable(int n, int state)
{
  digitalWrite(enable[n], state);
}
