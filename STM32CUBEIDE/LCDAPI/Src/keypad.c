/* Example "API" template for CE2812 Embedded Systems II
 *
 * This example is framed around the keypad to provide context, but this
 * same template should be applied to every peripheral / subsystem as a
 * best practice.
 *
 */

/***** #INCLUDES *****/
/* Include every header that is needed for this file to be interpreted
 * correctly.  Ideally, there should be no reliance in the order in which
 * header files are included.  Do not rely on a header file to be included
 * by other header files.
 */
#include "keypad.h"
#include "registers.h"

#include <stdio.h>
#include "uart_driver.h"
#include <stdint.h>

/***** #DEFINES *****/
/* You can create definitions that are valid only within this file.  This
 * can make sense, but is not all that common.
 */
#define ROW_COUNT 4
#define COL_COUNT 4

/***** Static Function Prototypes *****/
/* Prototype static functions.  These functions can only be called from
 * within this source file.
 */

/* Executes a single scan of the keypad.
 * Arguments:  none
 * Returns: int, code of the scanned key or -1 if no key detected
 */
static int scan(void);
static int convert_key_index_to_value(int);
static int process_row(int);
static int scan_columns(void);


/***** File-scope Variables / Constants *****/
/* In order to communicate data between the public API and ISRs in particular
 * you will likely need a file-scope variable.  This is preferred to global.
 * Declare it here with 'static.'
 *
 * If many methods access I/O registers, it is OK to declare pointers to
 * those registers at file-scope as well.  This will avoid the overhead of
 * creating those variables in each method and each time a method is called
 * (although, optimized code would unlikely actually create the variable in
 * memory...).  Keep these file-scope for a reasonable amount of safety.
 * They should also be * const.
 */
static volatile uint32_t * const gpioc = (uint32_t *) GPIOC_BASE;
static int process_row(int);

/* Initialize the I/O port used to interact with keypad.
 * Arguments:  none
 * Returns: void
 */
void keypad_init(void)
{
	// RCC is only used here, so no file-scope declaration
	volatile uint32_t * const rcc = (uint32_t *) RCC_BASE;

	// enable GPIOC's clock
	rcc[AHB1ENR] |= (1 << GPIOCEN);

	// Set the rows to output, cols to input
	uint32_t temp = gpioc[MODER];

	// Just in case, clear all mode bits for PC0-PC7
	temp &= ~(0xFFFF);
	// PC3-PC7 to output ('01')
	gpioc[MODER] |= temp | (OUTPUT<<MODER7) | (OUTPUT<<MODER6) |
								(OUTPUT<<MODER5) |(OUTPUT<<MODER4);
	// Enable pullups on cols - just in case, clear first for PC0-PC3
	temp = gpioc[PUPDR];
	temp &= ~(0xFF);
	gpioc[PUPDR] |= (PULL_UP<<PUPDR3)|(PULL_UP<<PUPDR2)|
						(PULL_UP<<PUPDR1)|(PULL_UP<<PUPDR0);
}

/* Returns key scan code (0-15) of the keypad.  Return value is an
 * int to be compatible with libc's getchar although EOF is not returned
 * in this version.  This method will block until a key is pressed.
 * Arguments:  none
 * Returns: int key code
 */
int keypad_getkey(void)
{
	int key = -1;

	while(key == -1)
	{
		key = keypad_getkey_noblock();
	}

	return key;
}

/* Returns key scan code (0-15) of the keypad if a key is currently
 * pressed otherwise returns EOF to indicate no key is pressed.  Return
 * value is an int to be compatible with libc's getkey.  This method
 * will not block.
 * Arguments:  none
 * Returns: int key code
 */
int keypad_getkey_noblock(void)
{
	return scan();
}

/* Similar to keypad_getkey except the ASCII value of the key is returned
 * promoted to int similar to libc's getchar.  Blocks.  No buffering is
 * offered in this version (unlike libc's getchar).
 * Arguments:  none
 * Returns: int ascii value of key
 */
int keypad_getchar(void)
{
	static const char keys[] = {	'1','2','3','A',
									'4','5','6','B',
									'7','8','9','C',
									'*','0','#','D' };
	return keys[keypad_getkey()];
}

/* Executes a single scan of the keypad.
 * Arguments:  none
 * Returns: int, code of the scanned key or -1 if no key detected
 */
static int scan()
{
	/* This routine will drive rows low, and check columns for low. */
	//
	keypad_init();
	//default value if nothing is pressed (COL_COUNT*COL_COUNT)
	int pressed_index_value = COL_COUNT*COL_COUNT;
	int row_index = 0;
	int row_offset = 0;

	//keypad_row_loop
	//loops until all rows are scanned
	while(row_index < ROW_COUNT) {
	//index of column is returned
	int column_index = process_row(row_index);
	//if the column index is hit, the pressed index value changes
	if(column_index != COL_COUNT){
		pressed_index_value = column_index + row_offset;
	}
	row_index++;
	//advance to next row of keys
	row_offset += COL_COUNT;
	}

	//if nothing is pressed, keep scanning for key
	if((pressed_index_value == (COL_COUNT*COL_COUNT))) {
		return keypad_getkey();
	}

	return pressed_index_value;
}

static int process_row(int row_index) {
	//uint32_t *gpio_c_moder = (uint32_t) *(GPIOC_BASE + MODER);
	//first row is on pin 4, so row passed in is added to row offset
	int row_pin_offset = 4;

	//set row pin to output
	gpioc[MODER] &= ~(0b11<<((row_pin_offset + row_index)*2));
	gpioc[MODER] |= (OUTPUT<<((row_pin_offset + row_index)*2));

	//delays for 1 ms
	delay_ms(1);

	//return column index of key pressed
	int column_index_pressed = scan_columns();

	//turn row pin back to input
	gpioc[MODER] &= ~(0b11<<((row_pin_offset + row_index)*2));
	gpioc[MODER] |= (INPUT<<((row_pin_offset + row_index)*2));

	return column_index_pressed;

}

//returns column index of pressed key  or COL_COUNT if not
static int scan_columns() {
	int column_index = 0;
	int column_pin = COL_COUNT;

	//loop repeats until all columns are scanned
	while(column_index < COL_COUNT) {
		int column_input = gpioc[IDR];
		column_input = column_input>>column_index;
		column_input &= 1;
		//column input is checked to see if it's pressed
		if(column_input == 0) {
			column_pin = column_index;
		}
		column_index++;
	}
	return column_pin;
}



