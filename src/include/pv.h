/*
 * Functions used across the program.  Include "config.h" first.
 *
 * Copyright 2002-2008, 2010, 2012-2015, 2017, 2021, 2023 Andrew Wood
 *
 * Distributed under the Artistic License v2.0; see `doc/COPYING'.
 */

#ifndef _PV_H
#define _PV_H 1

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Opaque structure for PV internal state.
 */
struct pvstate_s;
typedef struct pvstate_s *pvstate_t;

/*
 * Valid number types for pv_getnum_check().
 */
typedef enum {
  PV_NUMTYPE_INTEGER,
  PV_NUMTYPE_DOUBLE
} pv_numtype_t;


/*
 * Simple string functions for processing numbers.
 */

/*
 * Return the given string converted to a double.
 */
extern double pv_getnum_d(const char *);

/*
 * Return the given string converted to an unsigned integer.
 */
extern unsigned int pv_getnum_ui(const char *);

/*
 * Return the given string converted to an unsigned long long.
 */
extern unsigned long long pv_getnum_ull(const char *);

/*
 * Return zero if the given string is a number of the given type. NB an
 * integer is both a valid integer and a valid double.
 */
extern int pv_getnum_check(const char *, pv_numtype_t);

/*
 * String handling wrappers.
 */

/*
 * Wrapper for sprintf(), falling back to sprintf() on systems without that
 * function.
 */
extern int pv_snprintf(char *, size_t, const char *, ...);

/*
 * Implementation of strlcat() where it is unavailable: append a string to a
 * buffer, constraining the buffer to a particular size and ensuring
 * termination with '\0'.
 */
extern size_t pv_strlcat(char *, const char *, size_t);
          
/*
 * Main PV functions.
 */

/*
 * Create a new state structure, and return it, or 0 (NULL) on error.
 */
extern pvstate_t pv_state_alloc(const char *);

/*
 * Set the formatting string, given a set of old-style formatting options.
 */
extern void pv_state_set_format(pvstate_t state, bool progress,
				bool timer, bool eta,
				bool fineta, bool rate,
				bool average_rate, bool bytes,
				bool bufpercent,
				unsigned int lastwritten,
				const char *name);

/*
 * Set the various options.
 */
extern void pv_state_force_set(pvstate_t, bool);
extern void pv_state_cursor_set(pvstate_t, bool);
extern void pv_state_numeric_set(pvstate_t, bool);
extern void pv_state_wait_set(pvstate_t, bool);
extern void pv_state_delay_start_set(pvstate_t, double);
extern void pv_state_linemode_set(pvstate_t, bool);
extern void pv_state_bits_set(pvstate_t, bool);
extern void pv_state_null_set(pvstate_t, bool);
extern void pv_state_no_op_set(pvstate_t, bool);
extern void pv_state_skip_errors_set(pvstate_t, unsigned int);
extern void pv_state_stop_at_size_set(pvstate_t, bool);
extern void pv_state_sync_after_write_set(pvstate_t, bool);
extern void pv_state_direct_io_set(pvstate_t, bool);
extern void pv_state_rate_limit_set(pvstate_t, unsigned long long);
extern void pv_state_target_buffer_size_set(pvstate_t, unsigned long long);
extern void pv_state_no_splice_set(pvstate_t, bool);
extern void pv_state_size_set(pvstate_t, unsigned long long);
extern void pv_state_interval_set(pvstate_t, double);
extern void pv_state_width_set(pvstate_t, unsigned int);
extern void pv_state_height_set(pvstate_t, unsigned int);
extern void pv_state_name_set(pvstate_t, const char *);
extern void pv_state_format_string_set(pvstate_t, const char *);
extern void pv_state_watch_pid_set(pvstate_t, unsigned int);
extern void pv_state_watch_fd_set(pvstate_t, int);
extern void pv_state_average_rate_window_set(pvstate_t, int);

extern void pv_state_inputfiles(pvstate_t, int, const char **);

/*
 * Work out whether we are in the foreground.
 */
extern bool pv_in_foreground(void);

/*
 * Work out the terminal size.
 */
extern void pv_screensize(unsigned int *width, unsigned int *height);

/*
 * Calculate the total size of all input files.
 */
extern unsigned long long pv_calc_total_size(pvstate_t);

/*
 * Set up signal handlers ready for running the main loop.
 */
extern void pv_sig_init(pvstate_t);

/*
 * Enter the main transfer loop, transferring all input files to the output.
 */
extern int pv_main_loop(pvstate_t);

/*
 * Watch the selected file descriptor of the selected process.
 */
extern int pv_watchfd_loop(pvstate_t);

/*
 * Watch the selected process.
 */
extern int pv_watchpid_loop(pvstate_t);

/*
 * Shut down signal handlers after running the main loop.
 */
extern void pv_sig_fini(pvstate_t);

/*
 * Free a state structure, after which it can no longer be used.
 */
extern void pv_state_free(pvstate_t);


#ifdef ENABLE_DEBUGGING
# if __STDC_VERSION__ < 199901L && !defined(__func__)
#  if __GNUC__ >= 2
#   define __func__ __FUNCTION__
#  else
#   define __func__ "<unknown>"
#  endif
# endif
# define debug(x,...) debugging_output(__func__, __FILE__, __LINE__, x, __VA_ARGS__)
#else
# define debug(x,...) do { } while (0)
#endif

/*
 * Set the debugging destination file, if debugging is enabled.
 */
void debugging_output_destination(const char *);

/*
 * Output debugging information, if debugging is enabled.
 */
void debugging_output(const char *, const char *, int, const char *, ...);


#ifdef __cplusplus
}
#endif

#endif /* _PV_H */

/* EOF */
