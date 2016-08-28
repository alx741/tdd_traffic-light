#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 1000000
#define BAUD 4800
#define BAUD_PRESCALE ((((F_CPU/16) + (BAUD/2)) / (BAUD)) - 1)

char getchar(void)
{
    while ((UCSR0A & (1 << RXC0)) == 0) {}
    return UDR0;
}

int main(void)
{
    UBRR0H = (BAUD_PRESCALE >> 8);
    UBRR0L = BAUD_PRESCALE;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (0 << UMSEL00) | (0 << UMSEL01) | (1 << UCSZ00)
            | (1 << UCSZ01) | (0 << UCSZ02);

    DDRB = 0xFF;
    PORTB = 0x00;

    char character;
    while (1)
    {
        character = getchar();
        switch (character)
        {
            case 'r':
                PORTB = 0x01;
                break;

            case 'y':
                PORTB = 0x02;
                break;

            case 'g':
                PORTB = 0x04;
                break;

            default:
                PORTB = 0x00;
                break;
        }
    }
}
