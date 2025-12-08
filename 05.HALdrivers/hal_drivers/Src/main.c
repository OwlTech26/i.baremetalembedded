#include <stdint.h>

#if defined(USE_CASE_RUN_IDX_1)
#	include "uc_traffic_light.h"
#elif defined(USE_CASE_RUN_IDX_2)
#	include "uc_bmp280_spi.h"
#endif /* USE_CASE_RUN_IDX */

extern void initialise_monitor_handles();


int main(void)
{
  	initialise_monitor_handles();

#if defined(USE_CASE_RUN_IDX_1)
	UC_TRAFFIC_LIGHT_run();
#elif defined(USE_CASE_RUN_IDX_2)
	UC_BMP280_SPI_run();
#endif /* USE_CASE_RUN_IDX */
}

