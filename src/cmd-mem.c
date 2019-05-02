#include "hal.h"
#include "ch.h"
#include "shell.h"
#include "chprintf.h"

static unsigned int *region = NULL;
static size_t length;

#define DEFAULT_PATTERN 0xAAAAAAAA
#define ERR_PRINT_LIMIT 100

static int should_stop(void) {
  uint8_t bfr[1];
  return chnReadTimeout(&SD1, bfr, sizeof(bfr), 1);
}

void cmd_init(BaseSequentialStream *chp, int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  
  if( argc != 0 ) {
    chprintf(chp, "Usage: init (initializes memory space for tests)\n\r");
    return;
  }

  if( region == NULL ) {
    length = chCoreGetStatusX();
    chprintf(chp, "Total free core memory: %d\n\r", length );

    length &= 0xFFFFFFF0; 
    region = (unsigned int *) chCoreAlloc(length);
    chprintf(chp, "Allocated region of %d bytes at 0x%08x\n\r", length, (unsigned int) region);
  } else
    chprintf(chp, "Region already allocated, resetting values only\n\r");

  unsigned int i;
  for( i = 0; i < length / sizeof(unsigned int); i++ ) {
    region[i] = DEFAULT_PATTERN;
  }
  return;
}

void cmd_check(BaseSequentialStream *chp, int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  
  if( argc != 0 ) {
    chprintf(chp, "Usage: check (checks that memory has not been corrupted)\n\r");
    return;
  }

  unsigned int i;
  unsigned int errs = 0;
  for( i = 0; i < length / sizeof(unsigned int); i++ ) {
    if( region[i] != DEFAULT_PATTERN ) {
      errs++;
      if( errs < ERR_PRINT_LIMIT ) {
	chprintf(chp, "0x%08x: delta 0x%08x\n\r", (unsigned int)&(region[i]), region[i] ^ DEFAULT_PATTERN );
      }
    }
  }
  return;
}

void cmd_upset(BaseSequentialStream *chp, int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  
  if( argc != 0 ) {
    chprintf(chp, "Usage: upset (induces a predictable error to check the check routine)\n\r");
    return;
  }
  region[ 84012 ] = 0xDEADBEEF;

}

void cmd_scan(BaseSequentialStream *chp, int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  
  if( argc != 0 ) {
    chprintf(chp, "Usage: scan (continuously checks that memory has not been upset)\n\r");
    return;
  }

  chprintf(chp, "Hit any key to stop.\n\r");
  
  unsigned int i;
  unsigned int errs = 0;
  while( !should_stop() && (errs == 0) ) {
    for( i = 0; i < length / sizeof(unsigned int); i++ ) {
      if( region[i] != DEFAULT_PATTERN ) {
	errs++;
	if( errs < ERR_PRINT_LIMIT ) {
	  chprintf(chp, "0x%08x: delta 0x%08x\n\r", (unsigned int)&(region[i]), region[i] ^ DEFAULT_PATTERN );
	}
      }
    }
  }

  if( errs != 0 ) {
    chprintf(chp, "Loop exited due to errors, errors found: %d\n\r", errs);
  } else {
    chprintf(chp, "Loop exited due to manual command.\n\r" );
  }
}
