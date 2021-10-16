#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

float dotprod(float* a, float* b, size_t N) {
  int tid;
  float local_sum = 0.0f;

  tid = omp_get_thread_num();

#pragma omp for
  for (int i = 0; i < N; ++i) {
    local_sum += a[i] * b[i];
#pragma critical
    printf("tid = %d i = %d\n", tid, i);
  }

  return local_sum;
}

int main(int argc, char* argv[]) {
  const size_t N = 100;
  float sum = 0.0f;
  float a[N], b[N];

  for (int i = 0; i < N; ++i) {
    a[i] = b[i] = (float)i;
  }

#pragma omp parallel shared(a, b, N), default(none), reduction(+ : sum)
  sum = dotprod(a, b, N);

  printf("Sum = %f\n", sum);

  float one_thread_sum = dotprod(a, b, N);

  if (sum != one_thread_sum) {
    printf("OMP sum %f == sum %f? %s\n", sum, one_thread_sum,
           sum == one_thread_sum ? "true" : "false");
    return 1;
  }

  return 0;
}