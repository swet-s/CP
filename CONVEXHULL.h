 
int orientation(pii p, pii q, pii r)
{
    int val = (q.second - p.second) * (r.first - q.first) -
              (q.first - p.first) * (r.second - q.second);
 
    if (val == 0) return 0;  
    return (val > 0)? 1: 2;
}


// shoelace algorithmn
int polygonArea2(vector<pii>& points)
{
    int area=0;
    int n=sz(points);
  
    int j = n - 1;
    for (int i = 0; i < n; i++)
    {
        area += (points[j].first + points[i].first) * (points[j].second - points[i].second);
        j = i; 
    }
    
    return abs(area);
}
 
int convexHull(vector<pii>& points)
{
    int n = sz(points);
    if (n < 3) return 0;
 
    vector<pii> hull;
 
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].first < points[l].first)
            l = i;
 
    int p = l, q;
    do
    {
        hull.push_back(points[p]);
        q = (p+1)%n;
        for (int i = 0; i < n; i++)
        {
           if (orientation(points[p], points[i], points[q]) == 2)
               q = i;
        }
 
        p = q;
 
    } while (p != l);

    // for (int i = 0; i < hull.size(); i++)
    //     cout << "(" << hull[i].first << ", "
    //           << hull[i].second << ")\n";
    
    return polygonArea2(hull);  
}
