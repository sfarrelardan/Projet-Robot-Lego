/* ********************************************
BE ROBOT
******************************************** */

#include <stdio.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "coroutine.h"
#include "brick.h"
#include "lego_robot.h"

#define MOTOR_A OUTA
#define MOTOR_B OUTB
#define MOTOR_C OUTC
#define MOTOR_D OUTD
#define ALL_MOTORS (MOTOR_A | MOTOR_B | MOTOR_C | MOTOR_D)
#define SENSOR1 IN1
#define SENSOR2 IN2
#define SENSOR3 IN3
#define SENSOR4 IN4

#define _boolean int
#define _integer int

int alive; /* Program is alive */

uint8_t sn_sensor1 = 0;
bool sensor1_is_present = false;
uint8_t sn_sensor2 = 0;
bool sensor2_is_present = false;
uint8_t sn_sensor3 = 0;
bool sensor3_is_present = false;
uint8_t sn_sensor4 = 0;
bool sensor4_is_present = false;

uint8_t sn_motor_a = 0;
uint8_t type_motor_a = TACHO_TYPE__NONE_;
int max_speed_motor_a = 0;
int max_position_motor_a = 0;
bool motor_a_is_present = false;
uint8_t sn_motor_b = 0;
uint8_t type_motor_b = TACHO_TYPE__NONE_;
int max_speed_motor_b = 0;
int max_position_motor_b = 0;
bool motor_b_is_present = false;
uint8_t sn_motor_c = 0;
uint8_t type_motor_c = TACHO_TYPE__NONE_;
int max_speed_motor_c = 0;
int max_position_motor_c = 0;
bool motor_c_is_present = false;
uint8_t sn_motor_d = 0;
uint8_t type_motor_d = TACHO_TYPE__NONE_;
int max_speed_motor_d = 0;
int max_position_motor_d = 0;
bool motor_d_is_present = false;

struct Lego_robot__main_robot_mem robot_state;

void main_robot_O_Clockwise_A(Lego_robot__main_robot_out *cdata, _boolean val)
{
	cdata->clockwise_A = val;
}
void main_robot_O_Counterclockwise_A(Lego_robot__main_robot_out *cdata, _boolean val)
{
	cdata->counterclockwise_A = val;
}
void main_robot_O_Cmd_Position_A(Lego_robot__main_robot_out *cdata, _boolean val)
{
	cdata->cmd_position_A = val;
}
void main_robot_O_Cmd_Speed_A(Lego_robot__main_robot_out *cdata, _boolean val)
{
	cdata->cmd_speed_A = val;
}
void main_robot_O_Value_A(Lego_robot__main_robot_out *cdata, _integer val)
{
	cdata->value_A = val;
}
void main_robot_O_Clockwise_B(Lego_robot__main_robot_out *cdata, _boolean val)
{
	cdata->clockwise_B = val;
}
void main_robot_O_Counterclockwise_B(Lego_robot__main_robot_out *cdata, _boolean val)
{
	cdata->counterclockwise_B = val;
}
void main_robot_O_Cmd_Position_B(Lego_robot__main_robot_out *cdata, _boolean val)
{
	cdata->cmd_position_B = val;
}
void main_robot_O_Cmd_Speed_B(Lego_robot__main_robot_out *cdata, _boolean val)
{
	cdata->cmd_speed_B = val;
}
void main_robot_O_Value_B(Lego_robot__main_robot_out *cdata, _integer val)
{
	cdata->value_B = val;
}
void main_robot_O_Clockwise_C(Lego_robot__main_robot_out *cdata, _boolean val)
{
	cdata->clockwise_C = val;
}
void main_robot_O_Counterclockwise_C(Lego_robot__main_robot_out *cdata, _boolean val)
{
	cdata->counterclockwise_C = val;
}
void main_robot_O_Cmd_Position_C(Lego_robot__main_robot_out *cdata, _boolean val)
{
	cdata->cmd_position_C = val;
}
void main_robot_O_Cmd_Speed_C(Lego_robot__main_robot_out *cdata, _boolean val)
{
	cdata->cmd_speed_C = val;
}
void main_robot_O_Value_C(Lego_robot__main_robot_out *cdata, _integer val)
{
	cdata->value_C = val;
}
void main_robot_O_Clockwise_D(Lego_robot__main_robot_out *cdata, _boolean val)
{
	cdata->clockwise_D = val;
}
void main_robot_O_Counterclockwise_D(Lego_robot__main_robot_out *cdata, _boolean val)
{
	cdata->counterclockwise_D = val;
}
void main_robot_O_Cmd_Position_D(Lego_robot__main_robot_out *cdata, _boolean val)
{
	cdata->cmd_position_D = val;
}
void main_robot_O_Cmd_Speed_D(Lego_robot__main_robot_out *cdata, _boolean val)
{
	cdata->cmd_speed_D = val;
}
void main_robot_O_Value_D(Lego_robot__main_robot_out *cdata, _integer val)
{
	cdata->value_D = val;
}

// *****************************************************************
int robot_sensor_search(int type, char *name)
{
	int nb_sensor = 0;
	if (sensor_is_plugged(SENSOR1, type))
	{
		nb_sensor++;
		sensor1_is_present = true;
		printf("%s sensor is present on IN1\n", name);
	}
	if (sensor_is_plugged(SENSOR2, type))
	{
		nb_sensor++;
		sensor2_is_present = true;
		printf("%s sensor is present on IN2\n", name);
	}
	if (sensor_is_plugged(SENSOR3, type))
	{
		nb_sensor++;
		sensor3_is_present = true;
		printf("%s sensor is present on IN3\n", name);
	}
	if (sensor_is_plugged(SENSOR4, type))
	{
		nb_sensor++;
		sensor4_is_present = true;
		printf("%s sensor is present on IN4\n", name);
	}
	return (nb_sensor);
}
// *****************************************************************

// *****************************************************************
int robot_tacho_motor_search(int type, char *name)
{
	int nb_motor = 0;
	if (tacho_is_plugged(MOTOR_A, type))
	{
		tacho_reset(MOTOR_A);
		motor_a_is_present = true;
		type_motor_a = type;
		printf("%s motor is present on OUTA\n", name);
		nb_motor++;
	}
	if (tacho_is_plugged(MOTOR_B, type))
	{
		tacho_reset(MOTOR_B);
		motor_b_is_present = true;
		type_motor_b = type;
		printf("%s motor is present on OUTB\n", name);
		nb_motor++;
	}
	if (tacho_is_plugged(MOTOR_C, type))
	{
		tacho_reset(MOTOR_C);
		motor_c_is_present = true;
		type_motor_c = type;
		printf("%s motor is present on OUTC\n", name);
		nb_motor++;
	}
	if (tacho_is_plugged(MOTOR_D, type))
	{
		tacho_reset(MOTOR_D);
		motor_d_is_present = true;
		type_motor_d = type;
		printf("%s motor is present on OUTD\n", name);
		nb_motor++;
	}
	return (nb_motor);
}
// *****************************************************************

// *****************************************************************
int init(void)
{
	uint32_t i;
	int l_motor = 0;
	int m_motor = 0;
	int touch_sensor = 0;
	int color_sensor = 0;
	int us_sensor = 0;
	int ir_sensor = 0;

	l_motor = robot_tacho_motor_search(LEGO_EV3_L_MOTOR, "L-Motor");
	m_motor = robot_tacho_motor_search(LEGO_EV3_M_MOTOR, "M-Motor");
	if (l_motor < 2)
	{
		printf("Please, plug two L-MOTORS motors and try again.\n");
		/* Inoperative without two wheel motors */
		return (0);
	}

	touch_sensor = robot_sensor_search(LEGO_EV3_TOUCH, "Touch");
	color_sensor = robot_sensor_search(LEGO_EV3_COLOR, "Color");
	us_sensor = robot_sensor_search(LEGO_EV3_US, "Ultrasonic");
	ir_sensor = robot_sensor_search(LEGO_EV3_IR, "Infrared");
	if (touch_sensor < 2)
	{
		printf("Please, plug two touch sensors and try again.\n");
		/* Inoperative without two touch sensors */
		return (0);
	}
	printf("*** ( EV3 ) %d touch sensor found, %d color sensor found, %d ultrasonic found, %d infrared found ***\n", touch_sensor, color_sensor, us_sensor, ir_sensor);
	printf("*** ( EV3 ) %d wheel motor found, %d head motor found ***\n", l_motor, m_motor);

	/* Search motor sequence numbers */
	for (i = 0; i < DESC_LIMIT; i++)
	{
		if (ev3_tacho[i].type_inx != TACHO_TYPE__NONE_)
		{
			if (ev3_tacho_desc_port(i) == OUTPUT_A)
			{
				sn_motor_a = i;
				get_tacho_max_speed(sn_motor_a, &max_speed_motor_a);
				if (type_motor_a == LEGO_EV3_M_MOTOR)
				{
					set_tacho_position(sn_motor_a, 0);
					max_position_motor_a = 180;
				}
			}

			if (ev3_tacho_desc_port(i) == OUTPUT_B)
			{
				sn_motor_b = i;
				get_tacho_max_speed(sn_motor_b, &max_speed_motor_b);
				if (type_motor_b == LEGO_EV3_M_MOTOR)
				{
					set_tacho_position(sn_motor_b, 0);
					max_position_motor_b = 180;
				}
			}

			if (ev3_tacho_desc_port(i) == OUTPUT_C)
			{
				sn_motor_c = i;
				get_tacho_max_speed(sn_motor_c, &max_speed_motor_c);
				if (type_motor_c == LEGO_EV3_M_MOTOR)
				{
					set_tacho_position(sn_motor_c, 0);
					max_position_motor_c = 180;
				}
			}

			if (ev3_tacho_desc_port(i) == OUTPUT_D)
			{
				sn_motor_d = i;
				get_tacho_max_speed(sn_motor_d, &max_speed_motor_d);
				if (type_motor_d == LEGO_EV3_M_MOTOR)
				{
					set_tacho_position(sn_motor_d, 0);
					max_position_motor_d = 180;
				}
			}
		}
	}

	/* Search sensor sequence numbers */
	for (i = 0; i < DESC_LIMIT; i++)
	{
		if (ev3_sensor_desc_port(i) == INPUT_1)
		{
			sn_sensor1 = i;
		}
		if (ev3_sensor_desc_port(i) == INPUT_2)
		{
			sn_sensor2 = i;
		}
		if (ev3_sensor_desc_port(i) == INPUT_3)
		{
			sn_sensor3 = i;
		}
		if (ev3_sensor_desc_port(i) == INPUT_4)
		{
			sn_sensor4 = i;
		}
	}

	printf("Press BACK on the EV3 brick for EXIT...\n");

	return (1);
}
// *****************************************************************

// *****************************************************************
// Coroutine of the EV3 brick keys handling
CORO_CONTEXT(handle_brick_control);

CORO_DEFINE(handle_brick_control)
{
	CORO_LOCAL uint8_t keys, pressed = EV3_KEY__NONE_;

	CORO_BEGIN();
	for (;;)
	{
		/* Waiting any brick's key is pressed or released */
		CORO_WAIT((keys = brick_keys()) != pressed);
		pressed = keys;
		alive = 0;

		CORO_YIELD();
	}
	CORO_END();
}
// *****************************************************************

// *****************************************************************
int main(void)
{
	int val = 0;
	FLAGS_T state;
	/* inputs */
	int sensor_1 = 0;
	int sensor_2 = 0;
	int sensor_3 = 0;
	int sensor_4 = 0;
	int motor_speed_sensor_a = 0;
	int motor_speed_sensor_b = 0;
	int motor_speed_sensor_c = 0;
	int motor_speed_sensor_d = 0;
	/* outputs */
	Lego_robot__main_robot_out cdata = {0};

	printf("Waiting the EV3 brick online...\n");
	if (!brick_init())
		return (1);

	printf("*** ( EV3 ) Hello! ***\n");
	alive = init();

	// Initialization of the robot state
	Lego_robot__main_robot_reset(&robot_state);

	while (alive)
	{
		// Inputs: sensors
		if (sensor1_is_present)
		{
			get_sensor_value(0, sn_sensor1, &sensor_1);
		}
		if (sensor2_is_present)
		{
			get_sensor_value(0, sn_sensor2, &sensor_2);
		}
		if (sensor3_is_present)
		{
			get_sensor_value(0, sn_sensor3, &sensor_3);
		}
		if (sensor4_is_present)
		{
			get_sensor_value(0, sn_sensor4, &sensor_4);
		}

		// Inputs: motor speed
		if (motor_a_is_present)
		{
			get_tacho_speed(sn_motor_a, &motor_speed_sensor_a);
		}
		if (motor_b_is_present)
		{
			get_tacho_speed(sn_motor_b, &motor_speed_sensor_b);
		}
		if (motor_c_is_present)
		{
			get_tacho_speed(sn_motor_c, &motor_speed_sensor_c);
		}
		if (motor_d_is_present)
		{
			get_tacho_speed(sn_motor_d, &motor_speed_sensor_d);
		}

		// Lustre code
		Lego_robot__main_robot_step(sensor_1,
									sensor_2,
									sensor_3,
									sensor_4,
									motor_speed_sensor_a,
									motor_speed_sensor_b,
									motor_speed_sensor_c,
									motor_speed_sensor_d,
									&cdata,
									&robot_state);

		// Motor A
		if (motor_a_is_present)
		{
			if (type_motor_a == LEGO_EV3_L_MOTOR && cdata.cmd_speed_A)
			{
				if (cdata.value_A > max_speed_motor_a)
					val = max_speed_motor_a;
				else
					val = cdata.value_A;
				if (cdata.clockwise_A)
				{
					tacho_set_speed_sp(MOTOR_A, val);
					tacho_run_forever(MOTOR_A);
				}
				if (cdata.counterclockwise_A)
				{
					tacho_set_speed_sp(MOTOR_A, -val);
					tacho_run_forever(MOTOR_A);
				}
				if (!(cdata.clockwise_A || cdata.counterclockwise_A))
				{
					tacho_stop(MOTOR_A);
				}
			}
			if (type_motor_a == LEGO_EV3_M_MOTOR && cdata.cmd_position_A)
			{
				if (cdata.value_A > max_position_motor_a)
					val = max_position_motor_a;
				else if (cdata.value_A < -max_position_motor_a)
					val = -max_position_motor_a;
				else
					val = cdata.value_A;
				set_tacho_speed_sp(sn_motor_a, 100);
				set_tacho_ramp_up_sp(sn_motor_a, 0);
				set_tacho_ramp_down_sp(sn_motor_a, 0);
				set_tacho_position_sp(sn_motor_a, val);
				set_tacho_command_inx(sn_motor_a, TACHO_RUN_TO_ABS_POS);
				do
				{
					get_tacho_state_flags(sn_motor_a, &state);
				} while (state);
			}
		}

		// Motor B
		if (motor_b_is_present)
		{
			if (type_motor_b == LEGO_EV3_L_MOTOR && cdata.cmd_speed_B)
			{
				if (cdata.value_B > max_speed_motor_b)
					val = max_speed_motor_b;
				else
					val = cdata.value_B;
				if (cdata.clockwise_B)
				{
					tacho_set_speed_sp(MOTOR_B, val);
					tacho_run_forever(MOTOR_B);
				}
				if (cdata.counterclockwise_B)
				{
					tacho_set_speed_sp(MOTOR_B, -val);
					tacho_run_forever(MOTOR_B);
				}
				if (!(cdata.clockwise_B || cdata.counterclockwise_B))
				{
					tacho_stop(MOTOR_B);
				}
			}
			if (type_motor_b == LEGO_EV3_M_MOTOR && cdata.cmd_position_B)
			{
				if (cdata.value_B > max_position_motor_b)
					val = max_position_motor_b;
				else if (cdata.value_B < -max_position_motor_b)
					val = -max_position_motor_b;
				else
					val = cdata.value_B;
				set_tacho_speed_sp(sn_motor_b, 100);
				set_tacho_ramp_up_sp(sn_motor_b, 0);
				set_tacho_ramp_down_sp(sn_motor_b, 0);
				set_tacho_position_sp(sn_motor_b, val);
				set_tacho_command_inx(sn_motor_b, TACHO_RUN_TO_ABS_POS);
				do
				{
					get_tacho_state_flags(sn_motor_b, &state);
				} while (state);
			}
		}

		// Motor C
		if (motor_c_is_present)
		{
			if (type_motor_c == LEGO_EV3_L_MOTOR && cdata.cmd_speed_C)
			{
				if (cdata.value_C > max_speed_motor_c)
					val = max_speed_motor_c;
				else
					val = cdata.value_C;
				if (cdata.clockwise_C)
				{
					tacho_set_speed_sp(MOTOR_C, val);
					tacho_run_forever(MOTOR_C);
				}
				if (cdata.counterclockwise_C)
				{
					tacho_set_speed_sp(MOTOR_C, -val);
					tacho_run_forever(MOTOR_C);
				}
				if (!(cdata.clockwise_C || cdata.counterclockwise_C))
				{
					tacho_stop(MOTOR_C);
				}
			}
			if (type_motor_c == LEGO_EV3_M_MOTOR && cdata.cmd_position_C)
			{
				if (cdata.value_C > max_position_motor_c)
					val = max_position_motor_c;
				else if (cdata.value_C < -max_position_motor_c)
					val = -max_position_motor_c;
				else
					val = cdata.value_C;
				set_tacho_speed_sp(sn_motor_c, 100);
				set_tacho_ramp_up_sp(sn_motor_c, 0);
				set_tacho_ramp_down_sp(sn_motor_c, 0);
				set_tacho_position_sp(sn_motor_c, val);
				set_tacho_command_inx(sn_motor_c, TACHO_RUN_TO_ABS_POS);
				do
				{
					get_tacho_state_flags(sn_motor_c, &state);
				} while (state);
			}
		}

		// Motor D
		if (motor_d_is_present)
		{
			if (type_motor_d == LEGO_EV3_L_MOTOR && cdata.cmd_speed_D)
			{
				if (cdata.value_D > max_speed_motor_d)
					val = max_speed_motor_d;
				else
					val = cdata.value_D;
				if (cdata.clockwise_D)
				{
					tacho_set_speed_sp(MOTOR_D, val);
					tacho_run_forever(MOTOR_D);
				}
				if (cdata.counterclockwise_D)
				{
					tacho_set_speed_sp(MOTOR_D, -val);
					tacho_run_forever(MOTOR_D);
				}
				if (!(cdata.clockwise_D || cdata.counterclockwise_D))
				{
					tacho_stop(MOTOR_D);
				}
			}
			if (type_motor_d == LEGO_EV3_M_MOTOR && cdata.cmd_position_D)
			{
				if (cdata.value_D > max_position_motor_d)
					val = max_position_motor_d;
				else if (cdata.value_D < -max_position_motor_d)
					val = -max_position_motor_d;
				else
					val = cdata.value_D;
				set_tacho_speed_sp(sn_motor_d, 100);
				set_tacho_ramp_up_sp(sn_motor_d, 0);
				set_tacho_ramp_down_sp(sn_motor_d, 0);
				if (cdata.clockwise_D)
				{
					set_tacho_position_sp(sn_motor_d, val);
				}
				if (cdata.counterclockwise_D)
				{
					set_tacho_position_sp(sn_motor_d, -val);
				}
				set_tacho_command_inx(sn_motor_d, TACHO_RUN_TO_ABS_POS);
				do
				{
					get_tacho_state_flags(sn_motor_d, &state);
				} while (state);
			}
		}

		CORO_CALL(handle_brick_control);

		sleep_ms(10);
	}

	tacho_stop(MOTOR_A);
	tacho_stop(MOTOR_B);
	tacho_stop(MOTOR_C);
	tacho_stop(MOTOR_D);

	brick_uninit();

	printf("*** ( EV3 ) Bye! ***\n");
	return (0);
}
