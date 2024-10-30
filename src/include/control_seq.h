#ifndef _CONTROL_SEQ_H_

// Interrupts the currently running process
#define ASCII_ETX  '\x03'  // End of Text (Ctrl+C)
// Signals end-of-file (EOF) in input
#define ASCII_EOF  '\x04'  // End of Transmission (Ctrl+D)
// Suspends the current process (background)
#define ASCII_SUB  '\x1A'  // Substitute (Ctrl+Z)
// Clears the screen
#define ASCIIFF    '\x0C'  // Form Feed (Ctrl+L)
// Moves the cursor to the beginning of the line
#define ASCII_SOH  '\x01'  // Start of Heading (Ctrl+A)
// Moves the cursor to the end of the line
#define ASCII_ENQ  '\x05'  // Enquiry (Ctrl+E)
// Newline character (Line Feed)
#define ASCII_LF   '\x0A'  // Line Feed (LF)
// Carriage Return
#define ASCII_CR   '\x0D'  // Carriage Return (CR)
// Escape character, often used in terminal control sequences
#define ASCII_ESC  '\x1B'  // Escape (ESC)
// Deletes from the cursor to the end of the line
#define ASCII_VT   '\x0B'  // Vertical Tab (VT)

// Up arrow key escape sequence
#define ESC_UP     "\x1B[A"  // Up Arrow (ESC[A)
// Down arrow key escape sequence
#define ESC_DOWN   "\x1B[B"  // Down Arrow (ESC[B)
// Left arrow key escape sequence
#define ESC_LEFT   "\x1B[D"  // Left Arrow (ESC[D)
// Right arrow key escape sequence
#define ESC_RIGHT  "\x1B[C"  // Right Arrow (ESC[C)

#endif // !_CONTROL_SEQ_H_

