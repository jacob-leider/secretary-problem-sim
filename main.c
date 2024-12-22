#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Perform a Fisher-Yates shuffle on `nums`.
 *
 * @param nums: An integer array.
 * @param n: Length of `nums`.
 */
void Shuffle(int *nums, int n) {
  srand(time(NULL)); // Seed the random number generator

  for (int i = n - 1; i > 0; i--) {
    int j = rand() % (i + 1); // Generate a random index between 0 and i
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
  }
}

/**
 * @brief Simulates a decision problem.
 *
 * @param nums: An integer array containing all and only elements 0, ..., n - 1.
 * @param n: the length of nums.
 * @param r: The stopping ratio. After `r` elements have been rejected, for
 * any `k` > 'n * r', if `nums[k]` is the largest element of `nums[0:k]`, `k` is
 * selected.
 *
 * @return bool: Whether the stopping criterion led to an optimal decision.
 */
int MakeDecision(int *nums, int n, float r) {
  int max_elt = -1;
  int chosen = -1;

  // Compute the largest element out of the first `floor(r * n)` elements.
  for (int i = 0; i < r * n; i++)
    if (nums[i] > max_elt)
      max_elt = nums[i];

  for (int i = ceil(r * n); i < n; i++) {
    // Only update `chosen` once.
    if (nums[i] > max_elt && chosen == -1)
      chosen = nums[i];

    // Always update max_elt.
    if (nums[i] > max_elt)
      max_elt = nums[i];
  }

  return chosen == n - 1;
}

int main() {
  // PARAMS
  const int seq_len = 10000;
  const int num_buckets = 10;
  const int num_trials = 1000000;
  const int num_trials_between_reports = 1000;
  const float min_stopping_ratio = 0.33;
  const float max_stopping_ratio = 0.40;

  int *arr = malloc(seq_len * sizeof(int));
  float *stopping_ratios = malloc(num_buckets * sizeof(float));
  float *correct = malloc(num_buckets * sizeof(float));

  for (int i = 0; i < seq_len; i++)
    arr[i] = i;

  printf("\n");
  for (int i = 0; i < num_buckets; i++)
    printf("+--------");
  printf("+\n|");

  for (int i = 0; i < num_buckets; i++) {
    stopping_ratios[i] =
        min_stopping_ratio +
        i * (max_stopping_ratio - min_stopping_ratio) / num_buckets;
    printf("% 6.1f%% |", (100 * stopping_ratios[i]));
  }

  printf("\n");
  for (int i = 0; i < num_buckets; i++)
    printf("+--------");
  printf("+\n");

  int first_pass = 1;
  for (int trial = 0; trial < num_trials; trial++) {
    Shuffle(arr, seq_len);

    // Maybe go up a line.
    int do_report = trial % num_trials_between_reports == 0;
    if (do_report) {
      if (first_pass)
        first_pass = 0;
      else
        printf("\033[1A\033[1A|");
    }

    // Test each stopping rule for this permutation of `arr`.
    for (int bucket = 0; bucket < num_buckets; bucket++) {
      if (MakeDecision(arr, seq_len, stopping_ratios[bucket]))
        correct[bucket]++;

      if (do_report)
        printf(" %4.4f |", (correct[bucket] / (trial + 1)));
    }

    // Maybe report updated probabilities.
    if (do_report) {
      printf("\n");
      for (int i = 0; i < num_buckets; i++)
        printf("+--------");
      printf("+\n");
    }
  }

  // Clean up.
  free(arr);
  free(stopping_ratios);
  free(correct);

  return 0;
}
