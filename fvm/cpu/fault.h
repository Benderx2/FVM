//! FVM Fault Header
#ifndef __FAULT_H
#define __FAULT_H
#define E_NOERR 0x0F
#define E_DIVZERO 0x10
#define E_STACKEND 0x11
#define E_NOFPU 0x12
#define E_INVALIDOPCODE 0x13
#define E_NOMEM 0x14
#define E_GPF 0x15
void E_DIVZERO_ERR();
void E_STACKEND_ERR();
void E_NOFPU_ERR();
void E_INVALIDOPCODE_ERR();
void E_NOMEM_ERR();
void E_GPF_ERR();
#endif


