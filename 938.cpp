#include <cstdio>
#include <vector>

/*
P(R, B) =
  R/(R + B) * (R - 1)/(R + B - 1) * P(R - 2, B) +
  2 * R/(R + B) * B/(R + B - 1) * P(R, B - 1) +
  B/(R + B) * (B - 1)/(R + B - 1) * P(R, B)

rearrange and collect terms in P(R, B) to get:

P(R, B) = ((R - 1) *P(R - 2, B) + 2*B* P(R, B - 1))/(2*B + R - 1)

Now just use dynamic programming.

optimization: we only ever need the previous diagonal in the DP array.
  - lowers space complexity from O(R*B) to O(R + B) memory 
  - significantly improves cache locality
*/
long double solve(int R, int B)
{
  std::vector<std::vector<long double>> dp(R + 1, std::vector<long double>(B + 1));
  for (int r = 1; r <= R; ++r) dp[r][0] = 0.0L;
  for (int r = 1; r <= R; r += 2) dp[r][1] = 0.0L; // if odd red and 1 black, you can never remove all the red
  for (int b = 1; b <= B; ++b) dp[0][b] = 1.0L;
  for (int b = 1; b <= B; ++b) dp[1][b] = 0.0L; // if there's only 1 red card we can never remove it so the state inevitably becomes 1 (all) red
  // dp[2][1] = 0.33333333333L; // the only way to win is to draw both red cards the first time (2/3 * 1/2), otherwise we reduce to the case in the previous line

  // given in problem statement.
  // dp[2][2] = 0.46666666667L;
  // dp[10][9] = 0.4118903397L;
  // dp[34][25] = 0.3665688069L;
  for (int i = 2; i <= R + B; ++i) {
    for (int j = 0; j < i - 1; ++j) {
      int r = i - j;
      int b = j + 1;
      // Having the code check `if (dp[r][b] > 0.0L)` to skip recomputing slows down by a full second
      if (r > R || b > R) continue;
      int denom = 2*b + r - 1;
      dp[r][b] = ((r - 1)*dp[r - 2][b] + 2*b*dp[r][b - 1]) / denom;
    }
  }
  return dp[R][B];
}

int main()
{
  printf("ans=%.10Lf\n", solve(24690, 12345));
  return 0;
}
