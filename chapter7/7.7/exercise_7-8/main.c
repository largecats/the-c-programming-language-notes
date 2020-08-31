/*
Exercise 7-8. Write a program to print a set of files, starting each new one on a new page, with a title and a running page
count for each file.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100
#define LINES_PER_PAGE 10

void print_file(char *prog, char *filename);
void start_page(void);
void end_page(int pageNo);

int main(int argc, char *argv[]) {
    int i = 0;
    char *prog = argv[0];

    while (--argc > 0) {
        print_file(prog, *++argv);
    }
}

/*
$ gcc chapter7/7.7/exercise_7-8/main.c -o chapter7/7.7/exercise_7-8/result.out

$ chapter7/7.7/exercise_7-8/result.out chapter7/7.7/exercise_7-8/c_wiki.txt chapter7/7.7/exercise_7-8/spark_wiki.txt
-----------------------------------------------
Title: chapter7/7.7/exercise_7-8/c_wiki.txt

C (/siː/, as in the letter c) is a general-purpose, procedural computer programming language supporting structured programming, lexical variable scope, and recursion, with a static type system. By design, C provides constructs that map efficiently to typical machine instructions. It has found lasting use in applications previously coded in assembly language. Such applications include operating systems and various application software for computer architectures that range from supercomputers to PLCs and embedded systems.

A successor to the programming language B, C was originally developed at Bell Labs by Dennis Ritchie between 1972 and 1973 to construct utilities running on Unix. It was applied to re-implementing the kernel of the Unix operating system.[5] During the 1980s, C gradually gained popularity. It has

Page 1
-----------------------------------------------
become one of the most widely used programming languages,[6][7] with C compilers from various vendors available for the majority of existing computer architectures and operating systems. C has been standardized by the ANSI since 1989 (ANSI C) and by the International Organization for Standardization (ISO).

C is an imperative procedural language. It was designed to be compiled to provide low-level access to memory and language constructs that map efficiently to machine instructions, all with minimal runtime support. Despite its low-level capabilities, the language was designed to encourage cross-platform programming. A standards-compliant C program written with portability in mind can be compiled for a wide variety of computer platforms and operating systems with few changes to its source code.

Page 2
-----------------------------------------------
Title: chapter7/7.7/exercise_7-8/spark_wiki.txt

Apache Spark has its architectural foundation in the resilient distributed dataset (RDD), a read-only multiset of data items distributed over a cluster of machines, that is maintained in a fault-tolerant way.[2] The Dataframe API was released as an abstraction on top of the RDD, followed by the Dataset API. In Spark 1.x, the RDD was the primary application programming interface (API), but as of Spark 2.x use of the Dataset API is encouraged[3] even though the RDD API is not deprecated.[4][5] The RDD technology still underlies the Dataset API.[6][7]

Spark and its RDDs were developed in 2012 in response to limitations in the MapReduce cluster computing paradigm, which forces a particular linear dataflow structure on distributed programs: MapReduce programs read input data from disk, map a function across the data, reduce the results of the ma

Page 1
-----------------------------------------------
p, and store reduction results on disk. Spark's RDDs function as a working set for distributed programs that offers a (deliberately) restricted form of distributed shared memory.[8]

Spark facilitates the implementation of both iterative algorithms, which visit their data set multiple times in a loop, and interactive/exploratory data analysis, i.e., the repeated database-style querying of data. The latency of such applications may be reduced by several orders of magnitude compared to Apache Hadoop MapReduce implementation.[2][9] Among the class of iterative algorithms are the training algorithms for machine learning systems, which formed the initial impetus for developing Apache Spark.[10]

Apache Spark requires a cluster manager and a distributed storage system. For cluster management, S

Page 2
-----------------------------------------------
park supports standalone (native Spark cluster, where you can launch a cluster either manually or use the launch scripts provided by the install package. It is also possible to run these daemons on a single machine for testing), Hadoop YARN, Apache Mesos or Kubernetes. [11] For distributed storage, Spark can interface with a wide variety, including Alluxio, Hadoop Distributed File System (HDFS),[12] MapR File System (MapR-FS),[13] Cassandra,[14] OpenStack Swift, Amazon S3, Kudu, Lustre file system,[15] or a custom solution can be implemented. Spark also supports a pseudo-distributed local mode, usually used only for development or testing purposes, where distributed storage is not required and the local file system can be used instead; in such a scenario, Spark is run on a single machine with one executor per CPU core.

Page 3

$ chapter7/7.7/exercise_7-8/result.out chapter7/7.7/exercise_7-8/file.txt
chapter7/7.7/exercise_7-8/result.out: can't open chapter7/7.7/exercise_7-8/file.txt
*/

void print_file(char *prog, char *filename) {
    char line[MAXLINE];
    int lineNo = 1, pageNo = 1;
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "%s: can't open %s\n", prog, filename);
        exit(1);
    }
    start_page();
    printf("Title: %s\n\n", filename);
    while (fgets(line, MAXLINE, fp) != NULL) {
        if (lineNo > LINES_PER_PAGE) {
            end_page(pageNo);
            pageNo++;
            start_page();
            lineNo = 0;
            fprintf(stdout, "%s", line);
        }
        else {
            fprintf(stdout, "%s", line);
        }
        lineNo++;
    }
    end_page(pageNo);

}

void start_page(void) {
    fprintf(stdout, "-----------------------------------------------\n");
}

void end_page(int pageNo) {
    fprintf(stdout, "\n\nPage %d\n", pageNo);
}