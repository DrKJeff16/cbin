#if !defined(JEFF_H)
#define JEFF_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jasync.h>
#include <jeff/jdie.h>
#include <jeff/jerr.h>
#include <jeff/jfile.h>
#include <jeff/jhash.h>
#include <jeff/jinput.h>
#include <jeff/jlog.h>
#include <jeff/jmemory.h>
#include <jeff/jrandom.h>
#include <jeff/jsignal.h>
#include <jeff/jstring.h>
#include <jeff/jswap.h>
#include <jeff/jtypes.h>

#define JCAST(type, data) (type)(data)

#define J_PI_F 3.14159265358979323846
#define J_PI_LF 3.1415926535897932384626433832795028841971693993

#define J_TAU_F (2.0F * J_PI_F)
#define J_TAU_LF (2.0L * J_PI_LF)

#define jxor(x, y) (x ^ y)

static void verbose_print(const jbool verbose, const char *txt, FILE *restrict stream);
static void vverbose_print(const jbool verbose, FILE *restrict stream, const char *fmt, ...);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JEFF_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
