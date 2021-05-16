FROM james9909/cs225-autograder:latest
RUN yum install -y gdb
RUN yum install -y epel-release
RUN yum install -y cmake3
ENTRYPOINT bash
