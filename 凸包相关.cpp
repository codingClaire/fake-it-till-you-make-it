/*�ж�һ�����ڶ�����ڲ�or�ⲿ*/
/*
���߷��� ���ж����������������һ������
	�ͱ߽��ཻ�����Σ����ڶ������
	�ͱ߽��ཻż���Σ����ڶ������
*/
/*
ת�Ƿ���
�����ÿ���ߵ�ת�Ǽ�����
360�㣺���ڶ������
0�㣺���ڶ������

����/��ת�� 
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

/*͹��
����ˮƽ���Andrew�㷨
1.���е��С�������� �Ȱ�x ���x����ٰ���y����
2.ɾ���ظ��� �õ����� p1,p2...
3.��p1��p2�ŵ�͹���� 
4.��p3��ʼ ���µ���͹��ǰ�������������� ���ұ���ɾ���������͹���ĵ� ֱ���µ������
5.���¶�Ҫ�� ��������������͹��
*/
/*����͹�� */

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
/*return ��m��͹���ĵ�ĸ��� ch�����ŵ���͹���Ķ��� 
