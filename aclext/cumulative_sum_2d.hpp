#include <vector>

using namespace std;

namespace aclext {
// <---
// name: 2D Cumulative Sum
template <typename I, typename O>
struct CumulativeSum2D {
    vector<vector<O>> sum;
    CumulativeSum2D(const vector<vector<I>>& cnt) {
        assert(not cnt.empty());
        assert(not cnt[0].empty());
        const size_t n = cnt.size();
        const size_t m = cnt[0].size();
        sum = vector(n + 1, vector<O>(m + 1));
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < m; j++) {
                sum[i + 1][j + 1] = cnt[i][j];
            }
        }

        for (size_t i = 1; i <= n; i++) {
            for (size_t j = 0; j < m; j++) {
                sum[i][j + 1] += sum[i][j];
            }
        }

        for (size_t j = 1; j <= m; j++) {
            for (size_t i = 0; i < n; i++) {
                sum[i + 1][j] += sum[i][j];
            }
        }
    }

    O operator()(size_t x1, size_t y1, size_t x2, size_t y2) {
        return sum[x2 + 1][y2 + 1] - sum[x2 + 1][y1] - sum[x1][y2 + 1] + sum[x1][y1];
    }
};
// --->
}