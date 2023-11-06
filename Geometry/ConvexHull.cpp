// Kiểu điểm
struct Point {
    int x, y;
};

// Tích có hướng của AB và AC
long long cross(const Point &A, const Point &B, const Point &C) {
    return 1LL * (B.x - A.x) * (C.y - A.y) - 1LL * (C.x - A.x) * (B.y - A.y);
}

// A -> B -> C đi theo thứ tự theo chiều kim đồng hồ (-1), thẳng hàng (0), ngược chiều kim đồng hồ (1)
int ccw(const Point &A, const Point &B, const Point &C) {
    long long S = cross(A, B, C);
    if (S < 0) return -1;
    if (S == 0) return 0;
    return 1;
}

// Trả về bao lồi với thứ tự các điểm được liệt kê ngược chiều kim đồng hồ
vector<Point> convexHull(vector<Point> p, int n) {
    // Đưa điểm có tung độ nhỏ nhất (và trái nhất) lên đầu tập
    for (int i = 1; i < n; ++i) {
        if (p[0].y > p[i].y || (p[0].y == p[i].y && p[0].x > p[i].x)) {
            swap(p[0], p[i]);
        }
    }

    // Sắp xếp các điểm I theo góc tạo bởi trục hoành theo chiều dương và OI
    sort(p.begin() + 1, p.end(), [&p](const Point &A, const Point &B) {
        int c = ccw(p[0], A, B);
        if (c > 0) return true;
        if (c < 0) return false;
        return A.x < B.x || (A.x == B.x && A.y < B.y);
    });

    // Tập bao lồi
    vector<Point> hull;
    hull.push_back(p[0]);

    // Dựng bao lồi
    for (int i = 1; i < n; ++i) {
        while (hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), p[i]) < 0) {
            hull.pop_back();
        }
        hull.push_back(p[i]);
    }
    return hull;
}
