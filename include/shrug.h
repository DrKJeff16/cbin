#if !defined(SHRUG_H)
#define SHRUG_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

/** \defgroup shrug All elements from shrug
 * @{
 */

#define TO_ZERO(zero, str) \
  if (zero) {              \
    printf("%s", str);     \
    fflush(stdout);        \
  } else {                 \
    printf("%s\n", str);   \
  }

/**
 * \struct shrug_args
 */
struct shrug_args {
  char **args;   /*!< The positional arguments string array */
  jbool list;    /*!< Whether to list all the available options */
  jbool md;      /*!< Whether to optimize output for markdown */
  size_t n_args; /*!< The amount of positional arguments passed */
  jbool random;  /*!< Whether to print a random option */
  jbool zero;    /*!< Whether to terminate with a null terminator instead of a newline */
};

/**
 * \typedef shrug_arg_t
 * \brief The arguments struct for argp.h
 */
typedef struct shrug_args shrug_arg_t;

const size_t N_EMOTIONS = 19;

enum emotions_index {
  FACEPALM,   /*!< "Facepalm" emotion */
  FIGHT,      /*!< "Fight" emotion */
  FUCKYOU,    /*!< "Fuck You" emotion */
  LENNY,      /*!< "Lenny" emotion */
  LENNYFIGHT, /*!< "Lenny Fight" emotion */
  LENNYSHRUG, /*!< "Lenny Shrug" emotion */
  LOVE,       /*!< "Love" emotion */
  MEH,        /*!< "Meh" emotion */
  NERD,       /*!< "Nerd" emotion */
  NICE,       /*!< "Nice" emotion */
  OMG,        /*!< "OMG" emotion */
  REALLY,     /*!< "Really...?" emotion */
  SADLENNY,   /*!< "Sad Lenny" emotion */
  SHRUG,      /*!< "Shrug" emotion (default) */
  SMILE,      /*!< "Smile" emotion */
  THIS,       /*!< "This..." emotion */
  TY,         /*!< "Thank You" emotion */
  WOO,        /*!< "Woo!" emotion */
  WTF,        /*!< "WTF" emotion */
};

/**
 * \typedef emotions_idx
 * \brief The emotions index type
 */
typedef enum emotions_index emotions_idx;

/**
 * \brief Operator for the emotions program
 * \param list Whether to only list the emotions
 * \param md Whether to optimize the output for markdown
 * \param idx The emotion index
 * \return If `list` is false, returns the emotion string that matches the `idx` index
 */
char *emotions(const jbool list, const jbool md, const emotions_idx idx);

/**
 * \brief Check if a string is a valid name for a predefined emotion
 * \param arg The string to check
 * \return Whether the string matches an emotion
 */
jbool is_emotion(char *const arg);

/**
 * \brief Get the index of an emotion given a string identifier for such emotion
 * \param str The string to check
 * \return The emotion index
 */
emotions_idx map_emotion(char *const str);

/**
 * \brief List all emotions, then exit successfully
 */
void list_emotions(void);

/**
 * \brief Show usage message, then exit
 * \param code The exit code
 * \param arguments The arguments struct for garbage collection
 */
static void show_usage(const int code, shrug_arg_t *arguments);

/**
 * \brief Initialize the `shrug_arg_t` struct
 * \return The `shrug_arg_t` struct
 */
static shrug_arg_t init_args(void);

/** @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !SHRUG_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
