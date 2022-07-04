#ifndef __INCLUDE_MINDSTORM_MOTOR__
#define __INCLUDE_MINDSTORM_MOTOR__
struct MotorPortInfo
{
  unsigned int pin1;      // IN0
  unsigned int pin2;      // IN1
  unsigned int pin5w;     // DET0 TP
  unsigned int pin5r;     // INT0
  unsigned int pin6;      // DIR
  unsigned char adc1;     // adc channel 1
  unsigned char adc2;     // adc channel 2
};
typedef struct MotorPortInfo MotorPortInfo;

enum MotorPortID
{
  MOTOR_PORT_A = 0x00,
  MOTOR_PORT_B = 0x01,
  MOTOR_PORT_C = 0x02,
  MOTOR_PORT_D = 0x03
};
typedef enum MotorPortID MotorPortID;

enum MotorState
{
  MOTOR_BACKWARD  = 0x00,
  MOTOR_OFF       = 0x01,
  MOTOR_FORWARD   = 0x02
};
typedef enum MotorState MotorState;

/* initialize the gpio pins necessary for sensor functions
 * this should be done on startup
 */
void motor_init(void);

/* set the state of an attached motor
 *
 * params:
 *   port - the port to query
 *   state - one of MOTOR_FORWARD, MOTOR_BACKWARD, MOTOR_OFF
 *
 * errors:
 *   the behaviour is undefined if no motor is attached
 */
void motor_set_state(MotorPortID port, MotorState state);
#endif /* __INCLUDE_MINDSTORM_MOTOR__ */


/******************************************************************************
 *       ninjastorms - shuriken operating system                              *
 *                                                                            *
 *    Copyright (C) 2013 - 2016  Andreas Grapentin et al.                     *
 *                                                                            *
 *    This program is free software: you can redistribute it and/or modify    *
 *    it under the terms of the GNU General Public License as published by    *
 *    the Free Software Foundation, either version 3 of the License, or       *
 *    (at your option) any later version.                                     *
 *                                                                            *
 *    This program is distributed in the hope that it will be useful,         *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *    GNU General Public License for more details.                            *
 *                                                                            *
 *    You should have received a copy of the GNU General Public License       *
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 ******************************************************************************/
