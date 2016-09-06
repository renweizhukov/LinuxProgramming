# LinuxProgramming

## Makefile example

http://mrbook.org/blog/tutorials/make/

```bash
$ make -f Makefile-1
$ make -f Makefile-2
$ make -f Makefile-3
$ make -f Makefile-4
```

## Configure, make, make install examples

https://robots.thoughtbot.com/the-magic-behind-configure-make-make-install

1. Generate Configure and Makefile.in.

  ```bash
  $ aclocal
  $ autoconf
  $ automake --add-missing
  ```

2. Distribute the program.

  ```bash
  $ ./configure
  $ make dist
  ``` 

  To test the distribution,

  ```bash
  $ make distcheck
  ```

3. Build the program main.c and install the binary helloworld.

  ```bash
  $ ./configure
  $ make
  $ make install
  ```

## Daemon example

syslog_example.c illustrates a simple usage of syslog C APIs and daemon_example.c illustrates the basic code flow of Linux daemon, where the daemon is forked from its parent process. For how to write the daemon code, please refer to the following two webpages:

http://www.netzmafia.de/skripten/unix/linux-daemon-howto.html
http://shahmirj.com/blog/beginners-guide-to-creating-a-daemon-in-linux

### Build and Install

To build the two programs, simply run the command "scons". To install the executable daemon-example as a service on Ubuntu 16.04, please follow the steps as below:

1. (Optional) Copy the executable daemon-example to /usr/local/bin. 

  ```bash
  $ sudo cp daemon-example /usr/local/bin
  ```

  This step is not necessary. You may copy the executable daemon-example to any other path, as long as you update its path in daemon-example.service accordingly.

2. Copy the systemd unit file to /lib/systemd/system.

  ```bash
  $ sudo cp daemon-example.service /lib/systemd/system
  ```

3. Use systemctl to enable the service daemon-example.
  
  ```bash
  $ sudo systemctl enable daemon-example
  Created symlink from /etc/systemd/system/multi-user.target.wants/daemon-example.service to /lib/systemd/system/daemon-example.service.
  ```

  If you change daemon-example.service later, you need to force systemd to reload the new unit file.

  ```bash
  $ sudo systemctl daemon-reload
  ```

### syslog messages

The service daemon-example supports four systemctl commands: start, stop, restart, status. When it is started, you should see the following syslog messages.

```bash
$ tail -f /var/log/syslog
Sep  5 22:28:29 renwei-Meerkat systemd[1]: Starting Daemon Example...
Sep  5 22:28:29 renwei-Meerkat vdaemon[8887]: Writing to my Syslog
Sep  5 22:28:29 renwei-Meerkat systemd[1]: Started Daemon Example.
```

After it is started, it will keep writing a message into syslog every one minute. 

```bash
$ tail -f /var/log/syslog
Sep  5 22:29:29 renwei-Meerkat vdaemon[8887]: Writing to my Syslog
Sep  5 22:34:29 renwei-Meerkat vdaemon[8887]: message repeated 5 times: [ Writing to my Syslog]
```

When it is stopped, you should see the following syslog messages.

```bash
$ tail -f /var/log/syslog
Sep  5 22:35:32 renwei-Meerkat systemd[1]: Stopping Daemon Example...
Sep  5 22:35:32 renwei-Meerkat systemd[1]: Stopped Daemon Example.
```

### Uninstall

To remove the service daemon-example, you just need three simple steps.

1. Use systemctl to disable the service daemon-example.

  ```bash
  $ sudo systemctl disable daemon-example
  Removed symlink /etc/systemd/system/multi-user.target.wants/daemon-example.service.
  ```

2. Delete the systemd unit file.

  ```bash
  $ sudo rm -rf /lib/systemd/system/daemon-example.service
  ```

3. (Optional) Delete the executable daemon-example from /usr/local/bin.

  ```bash
  $ sudo rm -rf /usr/local/bin/daemon-example
  ```

### init.d script and upstart

Ubuntu has deviated from upstart and moved towards systemd since 15.04, so we only present the systemd approach of installing a service. We also present an old-school approach of installing a service -- init.d script. The init.d script daemon-example.sh is partially working. Below is a list of its known issues.

Issue 1. Starting the service doesn't create the pid file in /var/run.

  ```bash
  $ sudo service daemon-example start
  ```

Issue 2. Starting the service multiple times will create more than one running instance of daemon-example.

Issue 3. Stopping the service doesn't kill the daemon process although it doesn't report any error.

  ```bash
  sudo service daemon-example stop 
  ```

To try it,

1. Copy the init.d script to /etc/init.d.

   ```bash
   $ sudo cp daemon-example.sh /etc/init.d/daemon-example
   ```

2. Use update-rc.d to install the service.

   ```bash
   $ sudo update-rc.d daemon-example defaults
   ```
