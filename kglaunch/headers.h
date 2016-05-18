#ifndef D_LHEADERS
#define D_LHEADERS
typedef struct _butaction {
  char Name[100];
  char Icon[500];
  char Command[500];
} BUTACTION;
#define WAIT(pid) {\
  pid_t w;\
  int status;\
  do { \
                   w = waitpid(pid, &status, WUNTRACED | WCONTINUED); \
                   if (w == -1) { \
                       perror("waitpid"); \
                       exit(EXIT_FAILURE); \
                   }\
               } while (!WIFEXITED(status) && !WIFSIGNALED(status));\
}
#endif
