#### a shell like program using c

the function include base command like

- ls
- rm
- pwd and a buildin command "cd"

#### the command "cd" has a problem:

if we don't use the exit() for the parent process, the function "chdir" wouldn't make effect if we use the exit() for the parent process, there is another problem: it need exit for several times to quit.

#### update:

the "cd" problem has been solved, we cann't use fork for the "cd"

#### env:

Ubuntu 14.04LTS