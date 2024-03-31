# Trabalho realizado nas Semanas #4

## Task 1

The `printenv` command allows to list all the environment variables of a system or the ones that are passed as arguments.

```shell
printenv PWD
# Output : /home/seed
```

Likewise, `env | grep PWD` allows to check a particular environment variable of our system.

```shell
env | grep PWD
# Output: PWD=/home/seed
```

The `unset PWD` command deletes the environment variable from our variables array. As for the export command it edits or creates an environment variable depending on whether it already exists or not.

```shell
export PWD=/home/seed/Desktop
# Changes directory  to : seed@VM:~/Desktop$
```

## Task 2

Using the `diff` command with both output files as arguments, we conclude that between child and parent processes created by a `fork` command, there is no difference in terms of environmental variables.

## Task 3

> `execve()` executes the program referred to by pathname. This causes the program that is currently being run by the calling process to be replaced with a new program, with newly initialized stack, heap, and (initialized  and  uninitialized) data segments.

When the `execve`() is passed a *Null* pointer it does not have access to the environmental variables because it is limited to the variables inside the process. However, from the moment it receives `environ` as an argument, defined by `extern char**environ;` it succeeds and outputs the environment variables in the present.

> SYNOPSIS
>
>        extern char **environ;
>
> DESCRIPTION
>
>        The variable environ points to an array of pointers to strings
>        called the "environment".  The last pointer in this array has the
>        value NULL.  This array of strings is made available to the
>        process by the execve(2) call when a new program is started.
>        When a child process is created via fork(2), it inherits a copy
>        of its parent's environment.

Therefore we conclude that the `execve()` gives us control of the arguments and variables to which a process has access when executing a program, in direct contrast to fork, in which the child process directly inherits the environmental variables.

## Task 4

The command `system()` creates a new process to which all environment variables are passed from the previous process.

On the one hand, `execve()` runs a command directly. On the other hand, `system()` executes a `/bin/sh -c "command"`, that is, it executes `/bin/sh` prompting the shell to execute the command.

The  system()  library  function uses `fork` to create a child process that executes the shell command specified in command using `execl`  as follows:

```shell
       execl("/bin/sh", "sh", "-c", command, (char *) NULL);
```

Therefore,using `system()`, the environment variables array of the calling process is passed to the new program /bin/sh.

## Task 5

Set-UID is an important security mechanism in UNIX systems. It allows a user to execute a program with root privileges.

By changing the owner of the program to root and changing the program into set-UID, a user can run the program even without being logged in as a root user.

```shell
sudo chown root setUID # Chnages the owner into root
sudo chmod 4755 setUID # Changes into a set-UID program in its permissions.
```

***

It is important to understand what the `chmod` command does:

* the topmost bit, setuid, is mapped to the executable location of the user permissions, as follows:

  - `-` if neither the executable bit nor the setuid bit are set;

  - `x` if only the executable bit is set;

  - `S` is only the setuid bit is set;

  - `s` if both bits are set;

- the second bit, setgid, is likewise mapped to the executable location of the group permissions, again using `-`, `x`, `S` and `s`;
- the third bit, the sticky bit, is mapped to the executable location of the “other” permissions, but using `-`, `x`, `T` and `t`.

Thus the twelve bits fit in nine characters:

```
       11          10           9
        |           |           |
 8  7   6    5  4   3    2  1   0
 r  w  x/s   r  w  x/s   r  w  x/t
```

***

To understand the interaction between environment variables and Set-UID programs, we defined the following variables.

```shell
export PATH=$PATH:/home/seed/
export LD_LIBRARY_PATH="My own variable 1"
export COURSE_NAME="My own variable 2"
```

By running our Set-UID program and outputting its result into a file, we concluded that the variables we defined were in the environment variables array. The exception was the LD_LIBRARY_PATH. The LD_LIBRARY_PATH is an environment variable that helps the user to set a path for shared libraries which can be made available during the execution. This would allow a malicious program to make changes to those libraries, such as replacing them with more malicious code. In order to prevent that, a Set-UID program does not receive this variable, as it could compromise the system and expose a vulnerability. 

## Task 6

We started by creating the Set-UID program

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
system("ls");
return 0;
}
```

and created a fake `ls` in the same directory that runs:

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
printf("Malicious program\n");
}
```

This program is supposed to be a fake malicious program that could be run by a Set-UID program.

Afterward, we changed the environment variable `PATH` in order to call the fake `ls` in the beginning of the variable.

```shell
export PATH=/home/seed/seed-labs/category-software/Environment_Variable_and_SetUID/Labsetup:$PATH
```

This allowed to check that the the command `ls` called corresponds to our "malicious program". We can therefore conclude that there are risks to executing a `system()` call inside a Set-UID program.
