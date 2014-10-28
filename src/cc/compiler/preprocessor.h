/** \file preprocessor.h
	\brief Preprocessor defines all the operations necessary for the first pass in the compiler.
  */

#ifndef _PREPROCESSOR_H_
#define _PREPROCESSOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "symbol.h"

/* First Pass */

#define MAX_PREPROC_IDENT 2

#define PREPROC_DEFINE  0
#define PREPROC_INCLUDE 1

#define DEFAULT_INC_DIR "/usr/include/"
#define DEFAULT_LIB_DIR "/usr/lib/"


/*------------------------- Globals -------------------------*/

char *sys_inc_dir;
char *sys_lib_dir;

extern size_t total_newlines;
extern file_struct file;






/*------------------- Function Prototypes -------------------*/


/** Runs the preprocessor on the specified file.
  */
void run_preporcessor(file_struct *file);

/** 
  */
void include_headers(const char *prog, const char *ifilename, const char *ofilename);


/** This gets the next include name from the #include preprocessor directive.
  * It is malloced internally.  It _MUST_ be freed after each use.
  */
char *get_inc_fname(char *n);

/** 
  */
char *handle_defines(char *prog, char *filename);

/** Removes all comments from the import source file, and outputs an intermediary file for 
  * further processing.  At the moment, only handles 1 nested level of inclusion.
  */
void remove_comments(file_struct *file);


#endif
