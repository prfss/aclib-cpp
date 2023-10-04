/// @file
/// @brief ２次元累積和を計算します
#include <cassert>
#include <vector>

using namespace std;

namespace aclext {
// <---
// name: 2D Cumulative Sum
/// @brief ２次元累積和を計算するクラスです
template <typename T>
struct CumulativeSum2D {
    vector<vector<T>> sum;

    template <typename I>
    /// `cnt`から2次元配列を作ります.
    CumulativeSum2D(const vector<vector<I>>& cnt) {
        assert(not cnt.empty());
        assert(not cnt[0].empty());
        const size_t n = cnt.size();
        const size_t m = cnt[0].size();
        sum = vector(n + 1, vector<T>(m + 1));
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

    /// @f$i \in [x1,x2], j \in [y1,y2]@f$を満たす@f$i,j@f$について@f$a[i][j]@f$の総和を取得します.
    T operator()(size_t x1, size_t y1, size_t x2, size_t y2) {
        return sum[x2 + 1][y2 + 1] - sum[x2 + 1][y1] - sum[x1][y2 + 1] + sum[x1][y1];
    }
};
// --->
}