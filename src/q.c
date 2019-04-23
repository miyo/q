#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "q.h"

void init_qubits(struct qubits * q, int n)
{
    q->num = n;
    q->states = (int)pow(2, n);
    q->amps = (double complex*)malloc(sizeof(double complex) * q->states);
    for(int i = 0; i < q->states; i++){
	q->amps[i] = 0.0+0.0i;
    }
    q->amps[0] = 1.0+0.0i;
}

void free_qubits(struct qubits *q)
{
    free(q->amps);
}

void set_qbits(struct qubits *q, int index)
{
    for(int i = 0; i < q->states; i++){
	q->amps[i] = 0.0+0.0i;
    }
    q->amps[index] = 1.0+0.0i;
}

int random_choise(double* ps, int len)
{
    double weight = 0;
    int id = 0;
 
    for(int i = 0; i < len; i++) {
	printf(" ps[%d] = %f\n", i, ps[i]);
	weight += ps[i];
    }
    printf("weight = %f\n", weight);
  
    double r = (double)rand()/RAND_MAX * weight;
    printf("random = %f\n", r);
 
    for(int i = 0; i < len; i++) {
	if(r < ps[i]) {
	    id = i;
	    break;
	}
	r -= ps[i];
    }
  
    return id;
}

int measure(struct qubits *q)
{
    double *ps;
    ps = (double*)malloc(sizeof(double) * q->states);
    for(int i = 0; i < q->states; i++){
	ps[i] = cabs(q->amps[i]);
	ps[i] = ps[i] * ps[i];
    }
    int id = random_choise(ps, q->states);
    free(ps);
    return id;
}

void apply_qbits(struct qubits *q, double *m)
{
    size_t sz = q->states;

    double complex *na = (double complex*)malloc(sizeof(double complex) * sz);
    for(int i = 0; i < sz; i++){
	na[i] = 0.0 + 0.0i;
    }
    
    for(int i = 0; i < sz; i++){
	for(int j = 0; j < sz; j++){
	    na[i] += m[sz*j+i] * q->amps[j];
	}
    }
    free(q->amps);
    q->amps = na;
}

void list_qbits_str(struct qubits *q, int value, char *s)
{
    for(int i = 0; i < q->num; i++){
	int pt = q->num-1-i;
	if(value & 0x01){
	    s[pt] = '1';
	}else{
	    s[pt] = '0';
	}
	value = value >> 1;
    }
    
}


double * hadamal(struct qubits *q, int id)
{
    size_t sz = q->states;
    size_t sz2 = sz * sz;
    double * m = (double*)malloc(sizeof(double) * sz2);
    for(int i = 0; i < sz2; i++){
	m[i] = 0.0d;
    }
    int uu = (int)pow(2, id);
    int ll = (int)pow(2, (q->num - 1 - id));
    for(int u = 0; u < uu; u++){
	for(int l = 0; l < ll; l++){
	    int i0 = pow(u*2, q->num - id) + l;
	    int i1 = i0 + pow(2, q->num - 1 - id);
	    m[i0*sz+i0] = 1 / sqrt(2);
	    m[i0*sz+i1] = 1 / sqrt(2);
	    m[i1*sz+i0] = 1 / sqrt(2);
	    m[i1*sz+i1] = - 1 / sqrt(2);
	}
    }

    return m;
}
