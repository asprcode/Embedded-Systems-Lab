#include <lpc17xx.h>

void lcd_init(void);
void write(int, int);
void delay_lcd(unsigned int);
void lcd_comdata(int, int);
void clear_ports(void);
void lcd_puts(unsigned char*);

int main()
{
    unsigned char msg1[] = "MIT";                // Fixed: Implicit size
    unsigned char msg2[] = "Department of CS";  // Fixed: Implicit size
    
    SystemInit();
    SystemCoreClockUpdate();
    lcd_init();
    lcd_comdata(0x80, 0);  // Set cursor to first line
    delay_lcd(800);
    lcd_puts(msg1);
    
    lcd_comdata(0xC0, 0);  // Set cursor to second line
    delay_lcd(800);
    lcd_puts(msg2);
}

void lcd_init()
{
    LPC_PINCON->PINSEL10 &= 0XFC003FFF;  // Configure pins as GPIO
    
    // Initialize the GPIO pins as outputs for the LCD control and data lines
    LPC_GPIO0->FIODIR |= 0X0F<<23 | 1<<27 | 1<<28;
    
    clear_ports();
    delay_lcd(3200);
    
    lcd_comdata(0x33, 0);  // Function set: 8-bit mode
    delay_lcd(30000);
    
    lcd_comdata(0x32, 0);  // Function set: 4-bit mode
    delay_lcd(30000);
    
    lcd_comdata(0x28, 0);  // Display control: 2-line display, 5x7 font
    delay_lcd(30000);
    
    lcd_comdata(0x0C, 0);  // Display ON, cursor OFF
    delay_lcd(30000);
    
    lcd_comdata(0x06, 0);  // Entry mode: Increment cursor, no shift
    delay_lcd(30000);
    
    lcd_comdata(0x01, 0);  // Clear display
    delay_lcd(30000);
}

void lcd_comdata(int temp1, int type)
{
    int temp2;
    
    // Upper nibble
    temp2 = temp1 & 0xF0;  // Mask upper nibble
    temp2 = temp2 << 19;   // Shift upper nibble to correct position
    write(temp2, type);
    
    // Lower nibble
    temp2 = temp1 & 0x0F;  // Mask lower nibble
    temp2 = temp2 << 23;   // Shift lower nibble to correct position
    write(temp2, type);
}

void write(int temp2, int type)
{
    clear_ports();
    LPC_GPIO0->FIOPIN = temp2;  // Write data to the LCD data pins
    if (type == 0)
        LPC_GPIO0->FIOCLR = 1 << 27;  // RS = 0 for command
    else
        LPC_GPIO0->FIOSET = 1 << 27;  // RS = 1 for data
    
    LPC_GPIO0->FIOSET = 1 << 28;  // Enable pin (E = 1)
    delay_lcd(25);
    LPC_GPIO0->FIOCLR = 1 << 28;  // Disable pin (E = 0)
}

void delay_lcd(unsigned int r1)
{
    unsigned int r;
    for (r = 0; r < r1; r++) {
        // Simple delay loop
    }
}

void clear_ports(void)
{
    LPC_GPIO0->FIOCLR = 0x0F << 23;  // Clear data pins
    LPC_GPIO0->FIOCLR = 1 << 27;     // Clear RS
    LPC_GPIO0->FIOCLR = 1 << 28;     // Clear E
}

void lcd_puts(unsigned char* buf1)
{
    unsigned int i = 0;
    unsigned int temp3;
    while (buf1[i] != '\0')
    {
        temp3 = buf1[i];
        lcd_comdata(temp3, 1);  // Write data
        i++;
        if (i == 16)
            lcd_comdata(0xC0, 0);  // Move to second line after 16 characters
    }
}
