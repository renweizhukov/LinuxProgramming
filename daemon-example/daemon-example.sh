#!/bin/bash
# /etc/init.d/daemon_example.sh
# Wei Ren <renwei@smartconn.cc>
### BEGIN INIT INFO
# Provides: Daemon Example.
# Required-Start:    $syslog
# Required-Stop:     $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: daemon_example init.d script.
### END INIT INFO

PATH=/sbin:/usr/sbin:/bin:/usr/bin

# Source function library on Ubuntu.
# For some Linux distributions, the path may be "/etc/init.d/functions".
. /lib/lsb/init-functions

NAME=daemon-example
DAEMON=/usr/local/bin/$NAME
PIDFILE=/var/run/$NAME.pid

# Exit if the binary either doesn't exist or doesn't have the execute permission.
[ -x "$DAEMON" ] || exit 1

start() 
{
    # Return
    #   0 if daemon has been started.
    #   1 if daemon is already running.
    #   other if daemon cannot be started.
    start-stop-daemon --start --quiet --make-pidfile --pidfile $PIDFILE --exec $DAEMON
}

stop() 
{
    # Return
    #   0 if daemon has been stopped.
    #   1 if daemon is already stopped.
    #   other if daemon cannot be stopped.
    start-stop-daemon --stop --quiet --retry=TERM/30/KILL/5 --pidfile $PIDFILE --exec $DAEMON    
}

# See how we were called.
case "$1" in
    start)
        log_daemon_msg "Starting $NAME."
        start
        case "$?" in 
            0) 
                log_end_msg 0
                ;;
            1)
                log_progress_msg "already started."
                log_end_msg 0
                ;;
            *) 
                log_end_msg 1
                ;;
        esac
        ;;
    stop)
        log_daemon_msg "Stopping $NAME"
        stop
        case "$?" in
            0)
                log_end_msg 0
                ;;
            1) 
                log_progress_msg "already stopped."
                log_end_msg 0
                ;;
            *)
                log_end_msg 1
                ;;
        esac
        ;;
    status)
        status_of_proc -p $PIDFILE $DAEMON && exit 0 || exit $?
        ;;
    restart)
        $0 stop
        $0 start
        ;;
    *)
        echo "Usage: $0 {start|stop|status|restart}"
        exit 3
        ;;
esac
