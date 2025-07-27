#!/usr/bin/env -S nu --stdin

plugin use nuke

alias task = nuke task

mkdir target

task run --deps [build] {
    ./target/smc
}

task build --deps [
    main.o, manager.o, student.o, vec.o, utils.o
] --target target/smc {
    gcc -o target/smc target/*.o
}

task main.o --files [
    src/main.c
] --deps [
    manager.o, utils.o
] --target target/main.o {
    gcc -c src/main.c -I src -o target/main.o
}

task manager.o --files [
    src/manager.h, src/manager.c
] --deps [
    utils.o, student.o, vec.o
] --target target/manager.o {
    gcc -c src/manager.c -I src -o target/manager.o
}

task student.o --files [
    src/student.h, src/student.c
] --target target/student.o {
    gcc -c src/student.c -I src -o target/student.o
}

task vec.o --files [
    src/vec.h, src/vec.c
] --deps [
    student.o
] --target target/vec.o {
    gcc -c src/vec.c -I src -o target/vec.o
}

task utils.o --files [
    src/utils.h, src/utils.c
] --target target/utils.o {
    gcc -c src/utils.c -I src -o target/utils.o
}
