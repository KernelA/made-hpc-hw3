#include <omp.h>

#include <iostream>
#include <random>

using namespace std;

// Circle is centered at origin
bool inside_half_circle(double x, double y, double radius) {
  return x * x + y * y <= radius * radius;
}

int main(int argc, char const* argv[]) {
  const size_t NUM_SAMPLES{10'000'000};

  const double CIRCLE_RADIUS{1};

  const double EXACT_PI{3.14159265358979323846};

  default_random_engine global_engine;

  size_t circle_counter{};

#pragma omp parallel shared(NUM_SAMPLES, global_engine, CIRCLE_RADIUS) default(none) reduction(+:circle_counter)
  {
    default_random_engine thread_local_engine;
#pragma omp critical
    thread_local_engine.seed(global_engine());

    uniform_real_distribution<double> uniform_generator(0, 1);

    double rand_x, rand_y;

#pragma omp for
    for (size_t i = 0; i < NUM_SAMPLES; i++) {
      rand_x = uniform_generator(thread_local_engine);
      rand_y = uniform_generator(thread_local_engine);

      if (inside_half_circle(rand_x, rand_y, CIRCLE_RADIUS)) {
        ++circle_counter;
      }
    }
  }

  double pi_approx{4.0 * static_cast<double>(circle_counter) / NUM_SAMPLES};

  cout << "Monte carlo approximation of pi: " << pi_approx
       << " abs tol: " << abs(pi_approx - EXACT_PI) << endl;

  return 0;
}
