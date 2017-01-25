/**
 ** \file common.cc
 ** \brief Common definitions.
 */

#include <common.hh>

// Sole argument: the file to process.
const char* filename;

// The current state of error.
misc::error task_error;

// Counting the time spent in the various tasks.
misc::timer task_timer;
