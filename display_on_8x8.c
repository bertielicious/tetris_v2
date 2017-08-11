#include "config.h"
#include <pic.h>
#include "send_no_op_spi_byte.h"
#include "send_spi_byte.h"
void display_on_8x8(char sum_row1, char *sr2)
{
    CS = 0;
    send_no_op_spi_byte();
    send_spi_byte(0x01, sum_row1);
    CS = 1;
    CS = 0;
    send_no_op_spi_byte();
    send_spi_byte(0x02, *sr2);
    CS = 1;
}
