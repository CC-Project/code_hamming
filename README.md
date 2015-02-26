Library for the Hamming Code
============================
Implementation of the Hamming Codes for PC and AVR architectures.
The set of the symbols used is {0,1}.
Previous general prog in release config was: 53KB.

Example are available in test/

TODO
----
Hamming extended code.
Matrix_mul -> Optimise by counting the number of 1, and returning the parity of the computed number.

Notes on the config file
------------------------
The DEBUG macro allows to compile functions to control the proceedings of the program.
If working with AVR devices, you need to change BAUD_RATE and F_CPU (CPU clock frequency).

Notes on the Matrix struct
-------------------------
Number of cols and rows are uint16_t -> Matrix max length is 65535 x 65535 (2^16 -1 * 2^16 - 1).
