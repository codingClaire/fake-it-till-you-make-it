/*判断一个点在多边形内部or外部*/
/*
射线法： 从判定点出发，任意引出一条射线
	和边界相交奇数次：点在多边形内
	和边界相交偶数次：点在多边形外
*/
/*
转角法：
多边形每条边的转角加起来
360°：点在多边形内
0°：点在多边形外

绕数/回转数 
*/

int is_point_in_polygon(Point p, Polygon poly)
{
	int windingNum = 0;
	int n = poly.size();
	for (int i = 0; i < n; i++)
	{
		if (isPointOnSegment(p, poly[i], poly[(i + 1) % n]))
			return -1;
		int k = dcmp(Cross(poly[(i + 1) % n] - poly[i], p - poly[i]));
		int d1 = dcmp(poly[i].y - p.y);
		int d2 = dcmp(poly[(i + 1) % n].y - p.y);
		if (k > 0 && d1 <= 0 && d2 > 0)
			windingNum++;
		if (k < 0 && d2 <= 0 && d1>0)
			windingNum--;
	}
	if (windingNum != 0)
		return 1;
	return 0;
}

/*凸包
基于水平序的Andrew算法
1.所有点从小到大排序 先按x 如果x相等再按照y排序
2.删除重复点 得到序列 p1,p2...
3.把p1，p2放到凸包中 
4.从p3开始 若新点在凸包前进方向左边则继续 在右边则删除最近加入凸包的点 直到新点在左边
5.上下都要求 合起来是完整的凸包
*/
/*计算凸包 */

int ConvexHull(Point* p, int n, Point* ch)
{
	sort(p, p + n);
	int m = 0;
	for (int i = 0; i < n; i++)
	{
		while (m > 1 && Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0)
			m--;
		ch[m++] = p[i];
	}
	int k = m;
	for (int i = n - 2; i >= 0; i--)
	{
		while (m > k&&Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0)
			m--;
		ch[m++] = p[i];
	}
	if (n > 1)
		m--;
	return m;
}
/*return 的m是凸包的点的个数 ch数组存放的是凸包的顶点 
