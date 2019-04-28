#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>

#include "q.h"

void print_help(char **argv);

int main(int argc, char** argv){

    int c, flag = 2;
    const char* opts = "min:H:X:Y:Z:C:";
    const struct option longopts[] = {
	//{*name, has_arg, *flag, val },
	{"help",          no_argument,     0, 'h'},
	{NULL, 0, NULL, 0}
    };
    int longindex = 0;

    opterr = 0;

    int num = 1;

    while ((c = getopt_long(argc, argv, opts, longopts, &longindex)) != -1) {
        if (c == 'h') {
	    print_help(argv);
	    return 0;
        } else {
            if (c == 'm') {
		printf("measure\n");
            } else if (c == 'i') {
                fprintf(stderr, "init\n");
            } else if (c == 'm') {
                fprintf(stderr, "measure\n");
            } else if (c == 'n') {
                fprintf(stderr, "numbers=%s\n", optarg);
		num = atoi(optarg);
            } else if (c == 'H') {
                fprintf(stderr, "hadamal target=%s\n", optarg);
            } else if (c == 'X') {
                fprintf(stderr, "X=%s\n", optarg);
            } else if (c == 'Y') {
                fprintf(stderr, "Y=%s\n", optarg);
            } else if (c == 'Z') {
                fprintf(stderr, "Z=%s\n", optarg);
            } else if (c == 'C') {
                fprintf(stderr, "control=%s\n", optarg);
            } else {
		print_help(argv);
                return -1;
            }
        }
    }

    struct qubits q;

    time_t t;
    srand((unsigned) time(&t));
    
    printf("init qubits...\n");
    init_qubits(&q, num);
    printf("done\n");

#if 0
    for(int i = 0; i < q.states; i++){
	fprintf(stderr, "%f + i%f\n", creal(q.amps[i]), cimag(q.amps[i]));
    }
#endif

    printf("apply hadamal...\n");
    for(int id = 0; id < num; id++){
	printf("for %d...\n", id);
	printf("generate...\n");
	double * m = hadamal(&q, id);
	for(int i = 0; i < q.states; i++){
	    for(int j = 0; j < q.states; j++){
		fprintf(stderr, " %f", m[i*q.states+j]);
	    }
	    fprintf(stderr, "\n");
	}
	printf("apply...\n");
	apply_qbits(&q, m);
	printf("free...\n");
	free(m);
	printf("done.\n");
    }
    printf("done\n");
    
    for(int i = 0; i < q.states; i++){
	fprintf(stderr, "%f + i%f\n", creal(q.amps[i]), cimag(q.amps[i]));
    }
    
    int ret = measure(&q);
    fprintf(stderr, "%d\n", ret);
    
    char *s = (char*)malloc(sizeof(char) * num + 1);
    s[num] = '\0';
    list_qbits_str(&q, ret, s);
    printf("%s\n", s);
    
    free_qubits(&q);
    free(s);
    
    return 0;
}

void print_help(char **argv){
    printf("usage %s: \n", argv[0]);
    printf("   -h, --help: print this help\n");
    printf("   -m: measure qubits\n");
    printf("   -i: initialize qubits\n");
    printf("   -n: specify the number of qubits\n");
    printf("   -H: apply Hadamal operation to the target qubit\n");
    printf("   -X: apply X-rotation to the target qubit\n");
    printf("   -Y: apply Y-rotation to the target qubit\n");
    printf("   -Z: apply Z-rotation to the target qubit\n");
    printf("   -C: specify the target qubit as controller\n");
}
