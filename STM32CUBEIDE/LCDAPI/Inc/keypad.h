#ifndef KEYPAD_H  /* Compile guard */
#define KEYPAD_H  /* Compile guard */

/* Example "API" template for CE2812 Embedded Systems II
 *
 * This example is framed around the keypad to provide context, but this
 * same template should be applied to every peripheral / subsystem as a
 * best practice.
 *
 */

/**** #INCLUDES *****/
/* Only #include header files necessary for THIS file
 * to be interpreted correctly.  Do not include files that may be
 * needed by includers of this file.  The most common include needed will
 * be stdint.h if C99 types are used in prototypes.  Other examples might
 * be for project unique struct definitions.
 */
// for example - #include <stdint.h>

/***** #DEFINES *****/
/* Create symbolic definitions for anything users of this API need.  You can
 * also create definitions for things used only within the API, although
 * those could also be within the C file.
 *
 * Previously, we would have included I/O register defines here, but a
 * better approach will be to use a project-wide include with all registers.
 * This will allow porting to other processors much easier as all registers
 * are in one file instead of several.  See registers.h.
 */

/***** Typedefs *****/
/* Much like defines, include typedefs for any types that the user will
 * need access to and/or are used within the API's code.
 */

/***** Global Variables *****/
/* In the unfortunate situation where you absolutely need to use a global
 * variable, declare it within the header with 'extern' and then define
 * it in ONE source file, ONE source file only.
 */

/***** Global Constants *****/
/* Global constants behave a bit differently than #defines and are sometimes
 * preferred.  Declare it within the header with 'extern' and then define
 * and assign it in ONE source file, ONE source file only.
 */

/***** "Public" Prototypes *****/
/* Create prototypes for the "public" interface of the API.  These are the
 * only methods users of this API should be able to access.  Do not include
 * prototypes for the "private" helper methods or interrupt handlers that
 * should not be directly accessed by users.
 */

/* Initialize the I/O port used to interact with keypad.
 * Arguments:  none
 * Returns: void
 */
void keypad_init(void);

/* Returns key scan code (0-15) of the keypad.  Return value is an
 * int to be compatible with libc's getchar although EOF is not returned
 * in this version.  This method will block until a key is pressed.
 * Arguments:  none
 * Returns: int key code
 */
int keypad_getkey(void);

/* Returns key scan code (0-15) of the keypad if a key is currently
 * pressed otherwise returns EOF to indicate no key is pressed.  Return
 * value is an int to be compatible with libc's getkey.  This method
 * will not block.
 * Arguments:  none
 * Returns: int key code
 */
int keypad_getkey_noblock(void);

/* Similar to keypad_getkey except the ASCII value of the key is returned
 * promoted to int similar to libc's getchar.  Blocks.  No buffering is
 * offered in this version (unlike libc's getchar).
 * Arguments:  none
 * Returns: int ascii value of key
 */
int keypad_getchar(void);

/* How much detail should be in the "banner" comment of the prototype?
 * Ideally, this file is the primary documentation for users of the API,
 * so the comments should include everything the user would need to
 * know to use the function.  What about in the C file?  Well, there too,
 * ideally, but that might be difficult to maintain.  Suggestion - write
 * it here first as API is designed, and copy over to C file to write
 * functions.
 */

#endif   /* Compile guard */
