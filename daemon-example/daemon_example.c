#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>

#define DAEMON_NAME "vdaemon"

void process()
{
    syslog(LOG_NOTICE, "Writing to my Syslog");
}

int main(int argc, char *argv[])
{
    // Set our logging mask and open the log.
    setlogmask(LOG_UPTO(LOG_NOTICE));
    openlog(DAEMON_NAME, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);

    syslog(LOG_INFO, "Entering Daemon");

    pid_t pid, sid;

    // Fork the parent process.
    pid = fork();
    if (pid < 0) {
        // Fork has failed so we should exit with failure immediately.
        exit(EXIT_FAILURE);
    }
    else if (pid > 0) {
        // We get a good pid, so exit the parent process only. 
        // But note that the child process will continue.
        exit(EXIT_SUCCESS);
    }

    // Change the file mode mask.
    umask(0);

    // Create a unique Session ID (SID) for the child process.
    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    // Change the working directory.
    // Since the root directory should exist in any Linux distribution, 
    // if we can't find it, we exit with failure.
    if (chdir("/") < 0) {
        exit(EXIT_FAILURE);
    }

    // Close standard file descriptors.
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    //----------------------
    // Main Process
    //----------------------
    while (true) {
        process();  // Run our Process
        sleep(60);  // Sleep for 60 seconds
    }

    // Close the log
    closelog();
}
