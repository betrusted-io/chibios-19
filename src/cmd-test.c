#include "hal.h"
#include "ch.h"
#include "shell.h"
#include "chprintf.h"

void cmd_test(BaseSequentialStream *chp, int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  
  if( argc != 1 ) {
    chprintf(chp, "Usage: test <echoval>:\n\r");
    return;
  }

  chprintf(chp, "Test echo %s\n\r", argv[0]);

  return;
}

