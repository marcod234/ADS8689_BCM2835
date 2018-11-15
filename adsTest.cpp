#include <bcm2835.h>
#include <unistd.h>
#include <time.h>
#include "ADS8689_BCM2835.h"

int main()
{
  ADS8689 adc;
  struct timespec delay;
  
  delay.tv_sec = 0;
  delay.tv_nsec = 10000;
  
  if (!bcm2835_init())
  {
    printf("bcm2835_init failed. Are you running as root??\n");
    return 1;
  }
  
  //change tp bcm2835_aux_spi_begin() if using SPI1
  if (!bcm2835_spi_begin())
  {
    printf("bcm2835_spi_begin failed. Are you running as root??\n");
    return 1;
  }
  
  //using SPI0 and CS0, comment arguments for SPI1 and CS2
  if(!adc.begin(SPI_0, BCM2835_SPI_CS0))
    return 1;
  
  while(1)
  {
	  //read adc
    int val = adc.readADC();
    printf("val = %d\n", val);
	  nanosleep(&delay, NULL); //must wait at least 10000 ns before next read
  }
}
