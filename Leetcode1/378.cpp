class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();  // 矩陣大小 n x n

        // 搜尋範圍：最小值 ~ 最大值
        int left = matrix[0][0];
        int right = matrix[n - 1][n - 1];

        while (left < right) {
            int mid = left + (right - left) / 2;

            // 計算矩陣中 <= mid 的元素數量
            int count = countLessEqual(matrix, mid, n);

            if (count < k) {
                left = mid + 1;   // 第 k 小在右半邊
            } else {
                right = mid;      // 第 k 小在左半邊或就是 mid
            }
        }
        return left;  // left == right 時就是答案
    }

private:
    // 計算矩陣中 <= target 的元素數量
    int countLessEqual(vector<vector<int>>& matrix, int target, int n) {
        int count = 0;
        int row = n - 1, col = 0;  // 從左下角開始

        while (row >= 0 && col < n) {
            if (matrix[row][col] <= target) {
                // 這一列的元素都 <= target
                count += row + 1;
                col++;
            } else {
                row--;  // 太大往上移
            }
        }
        return count;
    }
};
