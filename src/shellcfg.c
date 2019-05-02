/*
    Copyright (C) 2016 Jonathan Struebel

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    common/shellcfg.c
 * @brief   CLI shell config.
 *
 * @addtogroup SHELL
 * @{
 */
#include <stdlib.h>

#include "hal.h"
#include "shell.h"
#include "chprintf.h"

char ** endptr;

/*
 * Shell history buffer
 */
char history_buffer[SHELL_MAX_HIST_BUFF];

/*
 * Shell completion buffer
 */
char *completion_buffer[SHELL_MAX_COMPLETIONS];

/*
 * Shell commands
 */
void cmd_test(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_init(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_check(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_upset(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_scan(BaseSequentialStream *chp, int argc, char *argv[]);

static const ShellCommand commands[] = {
  {"scan", cmd_scan},
  {"check", cmd_check},
  {"upset", cmd_upset},
  {"init", cmd_init},
  {"test", cmd_test},
  {NULL, NULL}
};

/*
 * Shell configuration
 */
const ShellConfig shell_cfg = {
  (BaseSequentialStream *)&SD1,
  commands,
  history_buffer,
  sizeof(history_buffer),
  completion_buffer
};

/** @} */
