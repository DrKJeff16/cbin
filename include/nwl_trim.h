#if !defined(NWL_TRIM_H)
#define NWL_TRIM_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int is_file(const char *path);
static void files_gc(char **files, const unsigned long long n);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !NWL_TRIM_H */
